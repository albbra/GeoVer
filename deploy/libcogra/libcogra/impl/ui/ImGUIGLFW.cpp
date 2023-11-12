#include <cogra/ui/ImGUIGLFW.h>
// GLFW
#include <GLFW/glfw3.h>
#ifdef _WIN32
#undef APIENTRY
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>   // for glfwGetWin32Window
#endif
#define GLFW_HAS_WINDOW_TOPMOST       (GLFW_VERSION_MAJOR * 1000 + GLFW_VERSION_MINOR * 100 >= 3200) // 3.2+ GLFW_FLOATING
#define GLFW_HAS_WINDOW_HOVERED       (GLFW_VERSION_MAJOR * 1000 + GLFW_VERSION_MINOR * 100 >= 3300) // 3.3+ GLFW_HOVERED
#define GLFW_HAS_WINDOW_ALPHA         (GLFW_VERSION_MAJOR * 1000 + GLFW_VERSION_MINOR * 100 >= 3300) // 3.3+ glfwSetWindowOpacity
#define GLFW_HAS_PER_MONITOR_DPI      (GLFW_VERSION_MAJOR * 1000 + GLFW_VERSION_MINOR * 100 >= 3300) // 3.3+ glfwGetMonitorContentScale
#define GLFW_HAS_VULKAN               (GLFW_VERSION_MAJOR * 1000 + GLFW_VERSION_MINOR * 100 >= 3200) // 3.2+ glfwCreateWindowSurface
#ifdef GLFW_RESIZE_NESW_CURSOR  // let's be nice to people who pulled GLFW between 2019-04-16 (3.4 define) and 2019-11-29 (cursors defines) // FIXME: Remove when GLFW 3.4 is released?
#define GLFW_HAS_NEW_CURSORS          (GLFW_VERSION_MAJOR * 1000 + GLFW_VERSION_MINOR * 100 >= 3400) // 3.4+ GLFW_RESIZE_ALL_CURSOR, GLFW_RESIZE_NESW_CURSOR, GLFW_RESIZE_NWSE_CURSOR, GLFW_NOT_ALLOWED_CURSOR
#else
#define GLFW_HAS_NEW_CURSORS          (0)
#endif

namespace cogra::ui
{
ImGUIGLFW::ImGUIGLFW(GLFWwindow * window)
  : m_window(window)
{
  // Setup back-end capabilities flags
  ImGuiIO& io = ImGui::GetIO();
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)
  io.BackendPlatformName = "imgui_impl_glfw";

  // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
  io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
  io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
  io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
  io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
  io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
  io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
  io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
  io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
  io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
  io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
  io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
  io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
  io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
  io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
  io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
  io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
  io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
  io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
  io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
  io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
  io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
  io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

  io.SetClipboardTextFn = setClipboardTextCallback;
  io.GetClipboardTextFn = getClipboardTextCallback;
  io.ClipboardUserData = this;
#if defined(_WIN32)
  io.ImeWindowHandle = (void*)glfwGetWin32Window(m_window);
#endif

  // Create mouse cursors
  // (By design, on X11 cursors are user configurable and some cursors may be missing. When a cursor doesn't exist,
  // GLFW will emit an error which will often be printed by the app, so we temporarily disable error reporting.
  // Missing cursors will return NULL and our _UpdateMouseCursor() function will use the Arrow cursor instead.)
  GLFWerrorfun prev_error_callback = glfwSetErrorCallback(NULL);
  m_MouseCursors[ImGuiMouseCursor_Arrow] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
  m_MouseCursors[ImGuiMouseCursor_TextInput] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
  m_MouseCursors[ImGuiMouseCursor_ResizeNS] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
  m_MouseCursors[ImGuiMouseCursor_ResizeEW] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
  m_MouseCursors[ImGuiMouseCursor_Hand] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
#if GLFW_HAS_NEW_CURSORS
  m_MouseCursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_RESIZE_ALL_CURSOR);
  m_MouseCursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);
  m_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);
  m_MouseCursors[ImGuiMouseCursor_NotAllowed] = glfwCreateStandardCursor(GLFW_NOT_ALLOWED_CURSOR);
#else
  m_MouseCursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
  m_MouseCursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
  m_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
  m_MouseCursors[ImGuiMouseCursor_NotAllowed] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
#endif
  glfwSetErrorCallback(prev_error_callback);
}

ImGUIGLFW::~ImGUIGLFW()
{
  for(ImGuiMouseCursor cursor_n = 0; cursor_n < ImGuiMouseCursor_COUNT; cursor_n++)
  {
    glfwDestroyCursor(m_MouseCursors[cursor_n]);
    m_MouseCursors[cursor_n] = nullptr;
  }
}

void ImGUIGLFW::onMouseButton(int32 button, int32 action, int32 mods)
{
  if(action == GLFW_PRESS && button >= 0 && button < IM_ARRAYSIZE(m_mouseJustPressed))
    m_mouseJustPressed[button] = true;
}

void ImGUIGLFW::onMouseScroll(float64 yoffset)
{
  ImGuiIO& io = ImGui::GetIO();
  io.MouseWheel += (float)yoffset;
}

void ImGUIGLFW::onKey(int32 key, int32 scanCode, int32 action, int32 mods)
{
  ImGuiIO& io = ImGui::GetIO();
  if(action == GLFW_PRESS)
    io.KeysDown[key] = true;
  if(action == GLFW_RELEASE)
    io.KeysDown[key] = false;

  // Modifiers are not reliable across systems
  io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
  io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
  io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
#ifdef _WIN32
  io.KeySuper = false;
#else
  io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
#endif
}

void ImGUIGLFW::onChar(uint32 c)
{
  ImGuiIO& io = ImGui::GetIO();
  io.AddInputCharacter(c);
}

void ImGUIGLFW::newFrame()
{
  ImGuiIO& io = ImGui::GetIO();
  IM_ASSERT(io.Fonts->IsBuilt() && "Font atlas not built! It is generally built by the renderer back-end. Missing call to renderer _NewFrame() function? e.g. ImGui_ImplOpenGL3_NewFrame().");

  // Setup display size (every frame to accommodate for window resizing)
  int w, h;
  int display_w, display_h;
  glfwGetWindowSize(m_window, &w, &h);
  glfwGetFramebufferSize(m_window, &display_w, &display_h);
  // <Quirin> I had to change the following two lines the subsequent three lines to make sure that dpi scaling works correctly.
  //io.DisplaySize = ImVec2((float)w, (float)h);
  //if(w > 0 && h > 0) io.DisplayFramebufferScale = ImVec2((float)display_w / w, (float)display_h / h);
  auto dpi = getMonitorScaleFactor();
  io.DisplayFramebufferScale = ImVec2(dpi, dpi);
  if(w > 0 && h > 0) io.DisplaySize = ImVec2((float)w / io.DisplayFramebufferScale.x, (float)h / io.DisplayFramebufferScale.y);

  // Setup time step
  double current_time = glfwGetTime();
  io.DeltaTime = m_time > 0.0 ? (float)(current_time - m_time) : (float)(1.0f / 60.0f);
  m_time = current_time;

  updateMousePosAndButtons();
  updateMouseCursor();

  // Update game controllers (if enabled and available)
  updateGamepads();
}

void ImGUIGLFW::setClipboardTextCallback(void * user_data, const char * text)
{
  ImGUIGLFW* instance = reinterpret_cast<ImGUIGLFW*>(user_data);
  instance->setClipboardText(text);
}

const char * ImGUIGLFW::getClipboardTextCallback(void * user_data)
{
  ImGUIGLFW* instance = reinterpret_cast<ImGUIGLFW*>(user_data);
  return instance->getClipboardText();
}

void ImGUIGLFW::setClipboardText(const char * text)
{
  glfwSetClipboardString(m_window, text);
}

const char * ImGUIGLFW::getClipboardText()
{
  return glfwGetClipboardString(m_window);
}

void ImGUIGLFW::updateMousePosAndButtons()
{
  // Update buttons
  ImGuiIO& io = ImGui::GetIO();
  for(int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
  {
    // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
    io.MouseDown[i] = m_mouseJustPressed[i] || glfwGetMouseButton(m_window, i) != 0;
    m_mouseJustPressed[i] = false;
  }

  // Update mouse position
  const ImVec2 mouse_pos_backup = io.MousePos;
  io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
#ifdef __EMSCRIPTEN__
  const bool focused = true; // Emscripten
#else
  const bool focused = glfwGetWindowAttrib(m_window, GLFW_FOCUSED) != 0;
#endif
  if(focused)
  {
    if(io.WantSetMousePos)
    {
      glfwSetCursorPos(m_window, (double)mouse_pos_backup.x, (double)mouse_pos_backup.y);
    }
    else
    {
      double mouse_x, mouse_y;
      glfwGetCursorPos(m_window, &mouse_x, &mouse_y);

      // <Quirin> I had to change the following line to the line below to make sure that dpi scaling works correctly.
      //io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);
      io.MousePos = ImVec2((float)mouse_x / io.DisplayFramebufferScale.x, (float)mouse_y / io.DisplayFramebufferScale.y);
    }
  }
}

void ImGUIGLFW::updateMouseCursor()
{
  ImGuiIO& io = ImGui::GetIO();
  if((io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) || glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
    return;

  ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
  if(imgui_cursor == ImGuiMouseCursor_None || io.MouseDrawCursor)
  {
    // Hide OS mouse cursor if imgui is drawing it or if it wants no cursor
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  }
  else
  {
    // Show OS mouse cursor
    // FIXME-PLATFORM: Unfocused windows seems to fail changing the mouse cursor with GLFW 3.2, but 3.3 works here.
    glfwSetCursor(m_window, m_MouseCursors[imgui_cursor] ? m_MouseCursors[imgui_cursor] : m_MouseCursors[ImGuiMouseCursor_Arrow]);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
}

void ImGUIGLFW::updateGamepads()
{
  ImGuiIO& io = ImGui::GetIO();
  memset(io.NavInputs, 0, sizeof(io.NavInputs));
  if((io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad) == 0)
    return;

  // Update gamepad inputs
#define MAP_BUTTON(NAV_NO, BUTTON_NO)       { if (buttons_count > BUTTON_NO && buttons[BUTTON_NO] == GLFW_PRESS) io.NavInputs[NAV_NO] = 1.0f; }
#define MAP_ANALOG(NAV_NO, AXIS_NO, V0, V1) { float v = (axes_count > AXIS_NO) ? axes[AXIS_NO] : V0; v = (v - V0) / (V1 - V0); if (v > 1.0f) v = 1.0f; if (io.NavInputs[NAV_NO] < v) io.NavInputs[NAV_NO] = v; }
  int axes_count = 0, buttons_count = 0;
  const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
  const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttons_count);
  MAP_BUTTON(ImGuiNavInput_Activate, 0);     // Cross / A
  MAP_BUTTON(ImGuiNavInput_Cancel, 1);     // Circle / B
  MAP_BUTTON(ImGuiNavInput_Menu, 2);     // Square / X
  MAP_BUTTON(ImGuiNavInput_Input, 3);     // Triangle / Y
  MAP_BUTTON(ImGuiNavInput_DpadLeft, 13);    // D-Pad Left
  MAP_BUTTON(ImGuiNavInput_DpadRight, 11);    // D-Pad Right
  MAP_BUTTON(ImGuiNavInput_DpadUp, 10);    // D-Pad Up
  MAP_BUTTON(ImGuiNavInput_DpadDown, 12);    // D-Pad Down
  MAP_BUTTON(ImGuiNavInput_FocusPrev, 4);     // L1 / LB
  MAP_BUTTON(ImGuiNavInput_FocusNext, 5);     // R1 / RB
  MAP_BUTTON(ImGuiNavInput_TweakSlow, 4);     // L1 / LB
  MAP_BUTTON(ImGuiNavInput_TweakFast, 5);     // R1 / RB
  MAP_ANALOG(ImGuiNavInput_LStickLeft, 0, -0.3f, -0.9f);
  MAP_ANALOG(ImGuiNavInput_LStickRight, 0, +0.3f, +0.9f);
  MAP_ANALOG(ImGuiNavInput_LStickUp, 1, +0.3f, +0.9f);
  MAP_ANALOG(ImGuiNavInput_LStickDown, 1, -0.3f, -0.9f);
#undef MAP_BUTTON
#undef MAP_ANALOG
  if(axes_count > 0 && buttons_count > 0)
    io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
  else
    io.BackendFlags &= ~ImGuiBackendFlags_HasGamepad;
}

float ImGUIGLFW::getMonitorScaleFactor()
{
#if defined(_WIN32)
  HWND hWnd = glfwGetWin32Window(m_window);
  HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
  /* The following function only exists on Windows 8.1+, but we don't want to make that a dependency */
  static HRESULT(WINAPI *GetDpiForMonitor_)(HMONITOR, UINT, UINT*, UINT*) = nullptr;
  static bool GetDpiForMonitor_tried = false;

  if(!GetDpiForMonitor_tried)
  {
    auto shcore = LoadLibrary(TEXT("shcore"));
    if(shcore)
      GetDpiForMonitor_ = (decltype(GetDpiForMonitor_))GetProcAddress(shcore, "GetDpiForMonitor");
    GetDpiForMonitor_tried = true;
  }

  if(GetDpiForMonitor_)
  {
    uint32_t dpiX, dpiY;
    if(GetDpiForMonitor_(monitor, 0 /* effective DPI */, &dpiX, &dpiY) == S_OK)
      return dpiX / 96.0f;
  }
  return 1.f;
#elif defined(__linux__)
  float ratio = 1.0f;
  FILE *fp;
  /* Try to read the pixel ratio from KDEs config */
  auto currentDesktop = std::getenv("XDG_CURRENT_DESKTOP");
  if(currentDesktop && currentDesktop == std::string("KDE"))
  {
    fp = popen("kreadconfig5 --group KScreen --key ScaleFactor", "r");
    if(!fp)
      return 1;

    if(fscanf(fp, "%f", &ratio) != 1)
      return 1;
  }
  else
  {
    /* Try to read the pixel ratio from GTK */
    fp = popen("gsettings get org.gnome.desktop.interface scaling-factor", "r");
    if(!fp)
      return 1;

    int ratioInt = 1;
    if(fscanf(fp, "uint32 %i", &ratioInt) != 1)
      return 1;
    ratio = ratioInt;
  }
  if(pclose(fp) != 0)
    return 1;
  return ratio >= 1 ? ratio : 1;

#else
  int fbwidth, fbheight, width, height;
  glfwGetFramebufferSize(window, &fbwidth, &fbheight);
  glfwGetWindowSize(window, &width, &height);
  return (float)fbheight / (float)height;
#endif
}
}
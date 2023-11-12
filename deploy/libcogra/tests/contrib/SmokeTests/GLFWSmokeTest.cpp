/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <GLFW/glfw3.h>
#include <gtest/gtest.h>

#define GL_MAJOR_VERSION 0x821B
#define GL_MINOR_VERSION 0x821C

namespace
{
    void error(int /*errnum*/, const char * /*errmsg*/)
    {
        glfwTerminate();
        FAIL();
    }
}

TEST(GLFWSmokeTest, SimpleWindowComesUp)
{
    EXPECT_EQ(glfwInit(), GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(640, 480, "GLFW Smoke Test", nullptr, nullptr);
    //EXPECT_NE(window, 0);
    glfwSetErrorCallback(error);

    glfwMakeContextCurrent(window);

    int frames = 0;
    const int maxFrames = 16;
    while(frames < maxFrames)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
        frames++;
    }
    EXPECT_EQ(frames, maxFrames);
    glfwTerminate();
}

TEST(GLFWSmokeTest, OpenGL45CoreProfileWindowComesUp)
{
    const GLint desiredMajorVersion = 4;
    const GLint desiredMinorVersion = 5;

    EXPECT_EQ(glfwInit(), GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, desiredMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, desiredMinorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "GLFW Smoke Test OpenGL 4.6 Smoke Test", nullptr, nullptr);
    //EXPECT_NE(window, 0);
    glfwSetErrorCallback(error);

    glfwMakeContextCurrent(window);
    GLint majorVersion, minorVersion;
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    EXPECT_EQ(desiredMajorVersion, majorVersion);
    EXPECT_EQ(desiredMinorVersion, minorVersion);
    int frames = 0;
    const int maxFrames = 16;
    while(frames < maxFrames)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
        frames++;
    }
    EXPECT_EQ(frames, maxFrames);
    glfwTerminate();
}

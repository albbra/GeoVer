/// Cogra --- Coburg Graphics Framework 201
/// (C) 2017-2018 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <iostream>
#include <array>
#include <glad/glad.h>
#include <cogra/types.h>


#include <cogra/gl/GLSLProgram.h>
#include <cogra/ui/ExaminerControllerApp.h>
#include <cogra/ui/GLFWWindow.h>
#include <cogra/graphics/drawable/PolyLineDrawable.h>

#include "PolynomialCurveSegment.h"
#include "BezierCurveSegment.h"
#include "MonomialCurveSegment.h"
#include "LagrangeCurveSegment.h"
#include <cogra/ui/PointDragger.h>
#include "TransformationController2D.h"
#include <imgui/imgui.h>
#include <algorithm>
#include <cogra/gl/Screenshot.h>

using cogra::ui::GLFWWindow;
using cogra::ui::GLFWWindowConfig;
using cogra::ui::PointDragger;
using namespace cogra::graphics::drawable;


namespace
{
cogra::f32vec2 transformPoint(f32mat3 m, f32vec2 p)
{
    f32vec3 p3(p.x, p.y, 1.0f);
    const auto t = glm::inverse(m) * p3;
    return f32vec2(t.x, t.y);
}
}

namespace cogra
{
namespace ui
{
class BaseApp2D : public cogra::ui::GLFWApp
{
public:
    BaseApp2D(GLFWwindow* window) : GLFWApp(window) { }

    void onKey(int32_t key, int32_t, int32_t action, int32_t) override
    {
        if(key == GLFW_KEY_F5 && action == GLFW_PRESS)
        {
            m_screenshot.triggerSaveToClipboard();
        }

        if(key == GLFW_KEY_F1 && action == GLFW_PRESS)
        {
            setIsUIEnabled(!isUIEnabled());
        }
    }

    void onPostDraw() 
    {
        m_screenshot.saveToClipboardIfTriggered();
    }

    void onMouseButton(int32_t button, int32_t action, int32_t mods) override
    {

        if(button == GLFW_MOUSE_BUTTON_2)
        {
            if(action == GLFW_PRESS)
            {
                const auto d = getNormalizedMousePosition();
                m_transformationController.startTranslation(d);
            }
            else
            {
                m_transformationController.endTranslation();
            }
        }

        if(button == GLFW_MOUSE_BUTTON_3)
        {
            if(action == GLFW_PRESS)
            {
                const auto d = getNormalizedMousePosition();
                m_transformationController.startScale(d);
            }
            else
            {
                m_transformationController.endScale();
            }
        }
    }

    void onCursorPosition(float64, float64) override
    {
        const auto d = getNormalizedMousePosition();
        m_transformationController.updateTranslation(d);
        m_transformationController.updateScale(d);
    }

    cogra::f32mat3 getCameraTransformation() const
    {
        return m_transformationController.transformation();
    }

    void onFramebufferSize(int width, int height) override
    {
        GL_SAFE_CALL(glViewport(0, 0, width, height));
        m_aspectCorrection = (width < height) ? f32vec2(1.0f, static_cast<float>(width) / static_cast<float>(height)) : f32vec2(static_cast<float>(height) / static_cast<float>(width), 1.0f);
    }

    f32mat3 getAspectCorrectionScale() const
    {
        return f32mat3(m_aspectCorrection.x, 0, 0, 0, m_aspectCorrection.y, 0, 0, 0, 1);
    }

    cogra::float32 getScaleFactor() const
    {
        return m_transformationController.getScaleFactor();
    }

private:

    cogra::gl::Screenshot               m_screenshot;

    GeoVer::TransformationController2D    m_transformationController;
    
    f32vec2                             m_aspectCorrection;
};
}
}
/// /// <summary>
/// An application that draws 2D curves.
/// </summary>
namespace GeoVer
{
class PolynomialCurvesApp : public cogra::ui::BaseApp2D
{
public:
    explicit PolynomialCurvesApp(GLFWwindow* window)
        : BaseApp2D(window)
        , m_drawCurveProgram("../shaders/drawCurve.vert.glsl", "../shaders/drawCurve.geom.glsl", "../shaders/drawCurve.frag.glsl")
        , m_drawPointsProgram("../shaders/drawPoints.vert.glsl", "../shaders/drawPoints.geom.glsl", "../shaders/drawPoints.frag.glsl")
        , m_curve(createCurve(UIData::Monomial, { f32vec2(-0.8f, -0.3f), f32vec2(0.8f, -0.4f), f32vec2(0.0f, 0.5f), f32vec2(0.1f, -0.1f) }))
    {
        updateCurve();
        GL_SAFE_CALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
        onFramebufferSize(this->getFramebufferWidth(), this->getFramebufferHeight());
    }

    ~PolynomialCurvesApp() override = default;

private:

    //! The GPU program that draws the curve.
    cogra::gl::GLSLProgram                                              m_drawCurveProgram;

    //! The GPU program that draws circles.
    cogra::gl::GLSLProgram                                              m_drawPointsProgram;

    //! The drawable that holds GPU data for drawing the curve.
    cogra::graphics::drawable::PolyLineDrawable                         m_lineDrawable;

    //! A drawable for the control net.
    cogra::graphics::drawable::PolyLineDrawable                         m_controlNet;

    //! UI Element for dragging points around the screen.
    PointDragger                                                        m_pointDragger;

    //! Pointer to the curve.
    unique_ptr<PolynomialCurveSegment>                                  m_curve;

    //! Data obtained by the user inteface.
    struct UIData
    {
        //! Number of samples that is used to sample the curve.
        int32 nSamples = 128;

        //! The linewidth in pixels that is used to draw the curve.
        float32 curveLineWidth = 5.0f;

        //! Size of the control polygon.
        float32 controlPolygonLineWidth = 4.0f;

        //! Point size of the control coefficients.
        float32 controlPointSize = 20.0f;

        //! A type for selecting the curve.
        enum CurveType : int32 { Monomial, Lagrange, Bezier };

        //! The currently selected curve that is rendered.
        CurveType curveType = Monomial;

        bool showControlPolygon = true;

        bool showControlPoints = true;

        bool showCurve = true;

        f32vec3 curveColor = f32vec3(0.0f, 0.0f, 0.0f);

        f32vec3 controlPolygonColor = f32vec3(0.5f, 0.5f, 0.5f);

        f32vec3 controlPointColor = f32vec3(1.0f, 0.0f, 0.0f);
    };

    UIData m_uiData;

    unique_ptr<PolynomialCurveSegment> createCurve(UIData::CurveType curveType, const std::vector<f32vec2>& controlPoints)
    {
        switch(curveType)
        {
            case UIData::Monomial:
                return std::make_unique<MonomialCurveSegment>(controlPoints);
                break;
            case UIData::Lagrange:
                return std::make_unique<LagrangeCurveSegment>(controlPoints);
                break;
            case UIData::Bezier:
                return std::make_unique<BezierCurveSegment>(controlPoints);
                break;
        }
    }

public:

    void onMouseButton(int32_t button, int32_t action, int32_t mods) override
    {
        BaseApp2D::onMouseButton(button, action, mods);
       
        if(button == GLFW_MOUSE_BUTTON_1)
        {
            if(action == GLFW_PRESS)
            {
                const auto d = getNormalizedMousePosition();
                m_pointDragger.onMouseDown(transformPoint(getAspectCorrectionScale() * getCameraTransformation(),
                                                          f32vec2(static_cast<float32>(d.x), static_cast<float32>(d.y))),
                                           m_curve->getCoefficients(),
                                           m_uiData.controlPointSize * 2.0f / glm::max(getFramebufferDimensions().x, getFramebufferDimensions().y) / getScaleFactor());
            }
            else
            {
                m_pointDragger.onMouseUp();
            }
        }
    }

    void onCursorPosition(float64 xpos, float64 ypos) override
    {
        BaseApp2D::onCursorPosition(xpos, ypos);
        const auto d = getNormalizedMousePosition();
        if(m_pointDragger.onMouseMove(transformPoint(getAspectCorrectionScale() * getCameraTransformation(),
                                                     f32vec2(static_cast<float32>(d.x), static_cast<float32>(d.y))),
                                      m_curve->getCoefficients()))
        {
            updateCurve();
        }
    }

    void onDraw() override
    {
        GL_SAFE_CALL(glClear(GL_COLOR_BUFFER_BIT));      
        const auto pixelScale = (2.0f / std::min(getFramebufferWidth(), getFramebufferHeight()));

        if(m_uiData.showControlPolygon)
        {
            m_drawCurveProgram.use();
            m_drawCurveProgram.setUniform("u_halfLineWidth", 0.5f * m_uiData.controlPolygonLineWidth * pixelScale);
            const auto a = getAspectCorrectionScale();
            const auto t = getCameraTransformation();
            const auto m = a * t;
            m_drawCurveProgram.setUniform("u_transformationMatrix", m);
            m_drawCurveProgram.setUniform("u_color", m_uiData.controlPolygonColor);
            m_controlNet.setPrimitiveType(PolyLineDrawable::LineStripAdjacency);
            m_controlNet.draw();
        }

        if(m_uiData.showControlPoints)
        {
            m_drawPointsProgram.use();
            m_drawPointsProgram.setUniform("u_transformationMatrix", getAspectCorrectionScale() * getCameraTransformation());
            m_drawPointsProgram.setUniform("u_color", m_uiData.controlPointColor);
            m_drawPointsProgram.setUniform("u_radius", 0.5f * m_uiData.controlPointSize * f32vec2(2.0f / getFramebufferWidth(), 2.0f / getFramebufferHeight()));
            m_controlNet.setPrimitiveType(PolyLineDrawable::Points);
            m_controlNet.draw();
        }

        if(m_uiData.showCurve)
        {
            m_drawCurveProgram.use();
            m_drawCurveProgram.setUniform("u_transformationMatrix", getAspectCorrectionScale() * getCameraTransformation());
            m_drawCurveProgram.setUniform("u_color", m_uiData.curveColor);
            m_drawCurveProgram.setUniform("u_halfLineWidth", 0.5f * m_uiData.curveLineWidth * pixelScale);
            m_lineDrawable.setPrimitiveType(PolyLineDrawable::LineStripAdjacency);
            m_lineDrawable.draw();
        }
    }

    void onDrawUI() override
    {
        bool curveChanged = false;
        ImGui::Begin("Options");
        {
            if(ImGui::CollapsingHeader("Curve"))
            {
                if(ImGui::CollapsingHeader("Coefficients"))
                {
                    for(size_t i = 0; i < m_curve->getCoefficients().size(); i++)
                    {
                        std::string name = "C" + std::to_string(i);
                        curveChanged |= ImGui::SliderFloat2(name.c_str(), &m_curve->getCoefficients()[i].x, -2.0f, 2.0f);
                    }
                }

                auto curveTypeChanged = ImGui::Combo("Curve Type", reinterpret_cast<int*>(&m_uiData.curveType), "Monmial\0Lagrange\0Bezier\0\0");
                if(curveTypeChanged)
                {
                    switch(m_uiData.curveType)
                    {
                        case UIData::CurveType::Monomial:
                            m_curve = m_curve->toMonomialCurveSegment();
                            break;
                        case UIData::CurveType::Lagrange:
                            m_curve = m_curve->toLagrangeCurveSegment();
                            break;
                        case UIData::CurveType::Bezier:
                            m_curve = m_curve->toBezierCurveSegment();
                            break;
                    }
                }

                curveChanged |= curveTypeChanged;

                if(ImGui::Button("Elevate Degree"))
                {
                    if(m_curve->getDegree() + 1 <= GeoVer::PolynomialCurveSegment::maxDegree)
                    {
                        m_curve->elevateDegree();
                        curveChanged = true;
                    }
                }
                if(ImGui::Button("Reduce Degree"))
                {
                    if(m_curve->getDegree() - 1 >= GeoVer::PolynomialCurveSegment::minDegree)
                    {
                        m_curve->reduceDegree();
                        curveChanged = true;
                    }
                }
            }

            if(ImGui::CollapsingHeader("Evaluation"))
            {
                curveChanged |= ImGui::SliderInt("Number of Samples", &m_uiData.nSamples, 2, 4096);
            }

            if(ImGui::CollapsingHeader("Rendering"))
            {
                ImGui::Checkbox("Show Curve", &m_uiData.showCurve);
                if(m_uiData.showCurve)
                {
                    ImGui::SliderFloat("Curve Width", &m_uiData.curveLineWidth, 1.0f, 32.0f);
                    ImGui::ColorEdit3("Curve Color", &m_uiData.curveColor.x);
                }

                ImGui::Checkbox("Show Control Polygon", &m_uiData.showControlPolygon);
                if(m_uiData.showControlPolygon)
                {
                    ImGui::SliderFloat("Control Polygon Width", &m_uiData.controlPolygonLineWidth, 1.0f, 32.0f);
                    ImGui::ColorEdit3("Conrol Polygon Color", &m_uiData.controlPolygonColor.x);
                }

                ImGui::Checkbox("Show Control Points", &m_uiData.showControlPoints);
                if(m_uiData.showControlPoints)
                {
                    ImGui::SliderFloat("Control Point Size", &m_uiData.controlPointSize, 1.0f, 32.0f);
                    ImGui::ColorEdit3("Control Point Color", &m_uiData.controlPointColor.x);
                }
            }
            ImGui::End();
        }

        if(curveChanged)
        {
            updateCurve();
        }
    }

private:

    void updateCurve()
    {
        const auto sampledPoints = m_curve->sample(std::max(2, m_uiData.nSamples));
        m_lineDrawable.setPoints(sampledPoints);
        m_controlNet.setPoints(m_curve->getCoefficients());
    }
};
}

int main()
{
    try
    {
        GLFWWindowConfig c;
        c.width = 768;
        c.height = 768;
        c.windowTitle = "PolynomialCurvesApp";
        c.glMajorVersion = 3;
        c.glMinorVersion = 3;
        c.loadGLExtensions = true;
        c.disableDeprecatedFunctions = true;
        GLFWWindow<GeoVer::PolynomialCurvesApp> app(c);
        app.run();
    }
    catch(std::exception& exception)
    {
        std::cerr << exception.what() << "\n";
    }
    return 1;
}


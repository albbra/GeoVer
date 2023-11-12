/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 - 2018 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <vector>
#include <glad/glad.h>
#include <cogra/types.h>

#include <cogra/ui/GLFWApp.h>
#include <cogra/ui/GLFWWindow.h>
#include <cogra/gl/GLSLProgram.h>

using namespace cogra;

using cogra::ui::GLFWWindow;
using cogra::ui::GLFWWindowConfig;

class SimpleTriangleBinary : public cogra::ui::GLFWApp
{
public:
	explicit SimpleTriangleBinary(GLFWwindow* window)
		: GLFWApp(window)
		, m_triangleProgram(cogra::gl::GLSLProgram::createFromBinary("../shaders/triangle.vert.spv", "", "", "", "../shaders/triangle.frag.spv"))
        , m_nIndices(0)
    {
		

        GL_SAFE_CALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));

        std::vector<f32vec4> positions;
        positions.emplace_back(0.0f, 1.0f, 0.0f, 1.0f);
        positions.emplace_back(1.0f, -1.0f, 0.0f, 1.0f);
        positions.emplace_back(-1.0f, -1.0f, 0.0f, 1.0f);

        std::vector<i32vec3> indices;
        indices.emplace_back(0, 1, 2);
        m_nIndices = static_cast<uint32>(indices.size()) * 3;

        GL_SAFE_CALL(glGenVertexArrays(1, &m_vao));
        GL_SAFE_CALL(glBindVertexArray(m_vao));
        
        GLuint pb;
        const GLuint positionBindingIndex = 0;
        GL_SAFE_CALL(glGenBuffers(1, &pb));
        GL_SAFE_CALL(glBindBuffer(GL_ARRAY_BUFFER, pb));
        GL_SAFE_CALL(glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(f32vec4), positions.data(), GL_STATIC_DRAW));

        GLuint ib;
        GL_SAFE_CALL(glGenBuffers(1, &ib));
        GL_SAFE_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib));
        GL_SAFE_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(i32vec3), indices.data(), GL_STATIC_DRAW));
        
        auto positionAttribIndex = static_cast<GLuint>(m_triangleProgram.getAttributeLocation("inVertex"));
        GL_SAFE_CALL(glEnableVertexAttribArray(positionAttribIndex));
        GL_SAFE_CALL(glVertexAttribPointer(positionAttribIndex, 4, GL_FLOAT, GL_FALSE, 0, nullptr));       
        GL_SAFE_CALL(glBindVertexArray(0));
    }

    ~SimpleTriangleBinary() override = default;

    void onFramebufferSize(int width, int height) override
    {
        GL_SAFE_CALL(glViewport(0, 0, width, height));
    }

    void onDraw() override
    {
        GL_SAFE_CALL(glClear(GL_COLOR_BUFFER_BIT));
        m_triangleProgram.use();
        GL_SAFE_CALL(glBindVertexArray(m_vao));
        GL_SAFE_CALL(glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_INT, nullptr));
    }

private:
    GLuint                                              m_vao;

    uint32                                              m_nIndices;

    cogra::gl::GLSLProgram					            m_triangleProgram;
};

int main()
{
    try
    {
        GLFWWindowConfig c;
        c.glMajorVersion = 4;
        c.glMinorVersion = 6;
        c.loadGLExtensions = false;
        c.windowTitle = "Simple Triangle Binary";
        GLFWWindow<SimpleTriangleBinary> app(c);
        app.run();
    }
    catch(std::exception& exception)
    {
        std::cerr << exception.what() << "\n";
    }
    return 1;
}

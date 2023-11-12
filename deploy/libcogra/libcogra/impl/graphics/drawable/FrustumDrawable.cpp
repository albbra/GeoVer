/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/graphics/drawable/FrustumDrawable.h>
#include <array>
namespace cogra
{
    namespace graphics
    {
        namespace drawable
        {
            FrustumDrawable::FrustumDrawable()
            {
                std::array<f32vec4, NumberVertices> positions =
                {
                  f32vec4(0,   0,  0, 0), // 0
                  f32vec4(-1, -1, -1, 1), // 1
                  f32vec4(-1, +1, -1, 1), // 2
                  f32vec4(1, +1, -1, 1), // 3
                  f32vec4(1, -1, -1, 1), // 4
                  f32vec4(-1, -1, +1, 1), // 5
                  f32vec4(-1, +1, +1, 1), // 6
                  f32vec4(1, +1, +1, 1), // 7
                  f32vec4(1, -1, +1, 1)  // 8
                };
                std::array<uint32, NumberOfIndices> indexBuffer =
                {
                  0, 5, 0, 6, 0, 7, 0, 8,
                  1, 2, 2, 3, 3, 4, 4, 1,
                  5, 6, 6, 7, 7, 8, 8, 5
                };

                GL_SAFE_CALL(glGenVertexArrays(1, &m_vertexArrayObjectID));
                GL_SAFE_CALL(glGenBuffers(1, &m_positionBufferID));
                GL_SAFE_CALL(glGenBuffers(1, &m_indexBufferID));
                GL_SAFE_CALL(glBindVertexArray(m_vertexArrayObjectID));

                GL_SAFE_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_positionBufferID));
                GL_SAFE_CALL(glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(GLfloat) * 4, positions.data(),
                                          GL_STATIC_DRAW));
                GL_SAFE_CALL(glEnableVertexAttribArray(0));
                GL_SAFE_CALL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr));

                GL_SAFE_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID));
                GL_SAFE_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(uint32), indexBuffer.data(),
                                          GL_STATIC_DRAW));
                m_shader =
                    gl::GLSLProgram::createFromSource(
                        "#version 400 core                                   \n"
                        "#pragma optimize(on)                                \n"
                        "uniform mat4 u_mvp;                                 \n"
                        "uniform mat4 u_camI;                                \n"
                        "in vec4 inVertex;                                   \n"
                        "void main()                                         \n"
                        "{	                                                 \n"
                        "  vec4 t	= inVertex.w == 0.0 ? vec4(0,0,0,1) : u_camI * inVertex;                       \n"
                        "  gl_Position	= u_mvp * (t / t.w);                 \n"
                        "}                                                   \n",
                        "", "", "",
                        "#version 400 core      \n"
                        "#pragma optimize(on)   \n"
                        "out vec4 fragColor;    \n"
                        "uniform vec4 u_color;  \n"
                        "void main()            \n"
                        "{                      \n"
                        "  fragColor = u_color; \n"
                        "}                      \n"
                    );
            }

            FrustumDrawable::~FrustumDrawable()
            {
                glBindVertexArray(0);
                glDeleteVertexArrays(1, &m_vertexArrayObjectID);
                glDeleteBuffers(1, &m_indexBufferID);
                glDeleteBuffers(1, &m_positionBufferID);
            }

            void FrustumDrawable::draw() const
            {
                m_shader.use();
                m_shader.setUniform("u_camI", m_inverseCameraMatrix);
                m_shader.setUniform("u_mvp", m_modelViewProjection);
                m_shader.setUniform("u_color", m_color);
                GL_SAFE_CALL(glBindVertexArray(m_vertexArrayObjectID));
                GL_SAFE_CALL(glDrawElements(GL_LINES, NumberOfIndices, GL_UNSIGNED_INT, nullptr));
                GL_SAFE_CALL(glBindVertexArray(0));
            }

            void FrustumDrawable::setInverseCameraMatrix(const glm::mat4x4& inverseCameraMatrix)
            {
                m_inverseCameraMatrix = inverseCameraMatrix;
            }

            void FrustumDrawable::setModelViewProjection(const glm::mat4x4& modelViewProjection)
            {
                m_modelViewProjection = modelViewProjection;
            }

            void FrustumDrawable::setColor(f32vec4 color)
            {
                m_color = color;
            }
        }
    }
}

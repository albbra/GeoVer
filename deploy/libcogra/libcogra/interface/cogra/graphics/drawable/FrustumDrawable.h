/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_DRAWABLE_FRUSTRUMDRAWABLE_H_
#define COGRA_GRAPHICS_DRAWABLE_FRUSTRUMDRAWABLE_H_
#include <cogra/types.h>
#include <cogra/graphics/drawable/Drawable.h>
#include <glad/glad.h>

#include <memory>
#include <cogra/gl/GLSLProgram.h>
namespace cogra
{
    namespace graphics
    {
        namespace drawable
        {
            //! \brief A class for drawing a frustum that is defined using an inverse projection matrix.
            class FrustumDrawable : public Drawable
            {
            private:
                enum { NumberVertices = 9, NumberOfIndices = 24 };

            public:

                //! \brief Creates the frustum.
                FrustumDrawable();

                //! \brief Destroys the frustum.
                virtual ~FrustumDrawable();

                //! \brief Renders the frustum as lines. No shader has to be bound.
                void draw() const override;

                //! \brief Sets the inverse matrix of the camera matrix that defines the frustum.
                //! \param inverseCameraMatrix Inverse of the matrix that defines the frustum.
                void setInverseCameraMatrix(const glm::mat4x4& inverseCameraMatrix);

                //! \brief Sets the matrix for rendering the frustum.
                //! \param modelViewProjection The combined model view projection matrix.
                void setModelViewProjection(const glm::mat4x4& modelViewProjection);

                //! \brief Sets the color of the lines of the rendered frustum.
                //! \param color RGBA color value.
                void setColor(f32vec4 color);

            private:
                //! OpenGL handle to vertex array object.
                GLuint                m_vertexArrayObjectID;

                //! OpenGL handle of the position buffer.
                GLuint                m_positionBufferID;

                //! OpenGL handle of the index buffer.
                GLuint                m_indexBufferID;

                //! Shader.
                gl::GLSLProgram       m_shader;

                //! The inverse matrix of the camera matrix that defines the frustum.
                glm::mat4x4           m_inverseCameraMatrix;

                //! Matrix for rendering the frustum.
                glm::mat4x4           m_modelViewProjection;

                //! Color of the lines of the rendered frustum.
                f32vec4             m_color;
            };
        }
    }
}
#endif

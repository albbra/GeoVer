/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_DRAWABLE_SKYBOX_H_
#define COGRA_GRAPHICS_DRAWABLE_SKYBOX_H_
#include <memory>
#include <cogra/types.h>
#include <cogra/graphics/drawable/ScreenFillingPrimitive.h>
#include <cogra/gl/GLSLProgram.h>
#include <cogra/gl/Sampler.h>
namespace cogra
{
    namespace gl
    {
        class  TextureCubeMap;
    }
    namespace graphics
    {
        namespace drawable
        {
            //! Renders a sky-ox using a specific shader.
            class SkyBox
            {
            public:

                //! \brief Create a skybox using a cube texture map.
                //! \param[in,out]  textureCubeMap Reference to the cube that is used to render the skybox.
                explicit SkyBox(std::shared_ptr<gl::TextureCubeMap> textureCubeMap);

                //! \brief Default destructor.
                ~SkyBox();

                //! \brief Renders the sky box.
                //! \param[in,out]  aspect Relationship of width in pixels over height in pixels.
                //! \param[in,out]  modelViewMatrix Modelview matrix to transform the skybox.
                void draw(float32 aspect, const glm::mat4x4& modelViewMatrix);
            private:
                std::shared_ptr<gl::TextureCubeMap>	m_textureCubeMap;

                gl::Sampler							m_sampler;

                ScreenFillingPrimitive			    m_screenFillingPrimitve;

                std::unique_ptr<gl::GLSLProgram>	m_skyBoxShader;
            };
        }
    }
}
#endif

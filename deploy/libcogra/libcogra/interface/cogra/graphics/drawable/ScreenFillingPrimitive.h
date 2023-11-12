/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_DRAWABLE_SCREENFILLINGPRIMITVE_H_
#define COGRA_GRAPHICS_DRAWABLE_SCREENFILLINGPRIMITVE_H_
#include <glad/glad.h>
#include <cogra/graphics/drawable/Drawable.h>
#include <cogra/graphics/drawable/MeshDrawable.h>
namespace cogra
{
    namespace graphics
    {
        namespace drawable
        {
            class ScreenFillingPrimitive : public Drawable
            {
            public:
                ScreenFillingPrimitive();

                virtual ~ScreenFillingPrimitive() = default;

                void draw() const override;

            private:
                MeshDrawable            m_screenFillingMesh;
            };
        }
    }
}
#endif

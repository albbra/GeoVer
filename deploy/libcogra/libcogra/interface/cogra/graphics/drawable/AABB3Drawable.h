/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_DRAWABLE_AABB3DDRAWABLE_H_
#define COGRA_GRAPHICS_DRAWABLE_AABB3DDRAWABLE_H_

#include <cogra/graphics/geometry/AxisAlignedBoundingBox.h>
#include <cogra/graphics/drawable/MeshDrawable.h>
#include <glad/glad.h>
namespace cogra
{
    namespace graphics
    {
        namespace drawable
        {
            class AABB3Drawable : public Drawable
            {
            private:
               
            public:

                AABB3Drawable();

                virtual ~AABB3Drawable();

                void draw() const override;

                static cogra::f32mat4 unitCubeToAABB(const cogra::graphics::geometry::AABB3& aabb);
            private:
                cogra::graphics::drawable::MeshDrawable m_unitBoundingBox;
            
            };
        }
    }
}
#endif

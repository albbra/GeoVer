/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_DRAWABLE_DRAWABLE_H_
#define COGRA_GRAPHICS_DRAWABLE_DRAWABLE_H_

namespace cogra
{
    namespace graphics
    {
        namespace drawable
        {
            class Drawable
            {
            public:
                Drawable();

                virtual void draw() const = 0;
            };
        }
    }
}

#endif

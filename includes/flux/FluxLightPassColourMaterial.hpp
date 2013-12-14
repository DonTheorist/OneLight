#ifndef FLUX_LIGHTPASSCOLOURMATERIAL_H
#define FLUX_LIGHTPASSCOLOURMATERIAL_H

#include "FluxMaterial.hpp"
#include "FluxTexture.hpp"
#include "FluxError.hpp"
#include <iostream>

namespace Flux
{
    /** This class handles the dynamic lighting for any SpriteBatch using a ColourMaterial
     * @see
     *      ColourMaterial
     *      SpriteBatch
     *      PointLight
     */
    class LightPassColourMaterial : public Material
    {
        public:
            LightPassColourMaterial();
            ~LightPassColourMaterial();

            virtual FluxError loadAttributes(const unsigned int offset);
            virtual FluxError loadUniforms();

        private:
            FluxError initialise();

            GLuint vertexAttribLocation;
    };
}

#endif


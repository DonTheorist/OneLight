#ifndef FLUX_LIGHTPASSNORMALMATERIAL_H
#define FLUX_LIGHTPASSNORMALMATERIAL_H

#include "FluxMaterial.hpp"
#include "FluxTexture.hpp"
#include "FluxError.hpp"
#include <iostream>

namespace Flux
{
    /** This class handles the dynamic lighting for any SpriteBatch using a NormalMaterial
     * @see
     *      NormalMaterial
     *      SpriteBatch
     *      PointLight
     */
    class LightPassNormalMaterial : public Material
    {
        public:
            LightPassNormalMaterial(Texture *normalMap);
            ~LightPassNormalMaterial();

            virtual FluxError loadAttributes(const unsigned int offset);
            virtual FluxError loadUniforms();

        private:
            FluxError initialise();

            Texture *normalMap;

            GLuint vertexAttribLocation;
            GLuint normalAttribLocation;
            GLuint rotationAttribLocation;
            GLuint normalSamplerUniformLocation;
    };
}

#endif


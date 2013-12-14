#ifndef FLUX_LIGHTPASSTEXTUREMATERIAL_H
#define FLUX_LIGHTPASSTEXTUREMATERIAL_H

#include "FluxMaterial.hpp"
#include "FluxTexture.hpp"
#include "FluxError.hpp"
#include <iostream>

namespace Flux
{
    /** This class handles the dynamic lighting for any SpriteBatch using a TextureMaterial
     * @see
     *      TextureMaterial
     *      SpriteBatch
     *      PointLight
     */
    class LightPassTextureMaterial : public Material
    {
        public:
            LightPassTextureMaterial(Texture *texture);
            ~LightPassTextureMaterial();

            virtual FluxError loadAttributes(const unsigned int offset);
            virtual FluxError loadUniforms();

        private:
            FluxError initialise();

            Texture *texture;

            GLuint vertexAttribLocation;
            GLuint textureAttribLocation;
            GLuint textureSamplerUniformLocation;
    };
}

#endif


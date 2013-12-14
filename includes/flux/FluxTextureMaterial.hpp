#ifndef FLUX_TEXTUREMATERIAL_H
#define FLUX_TEXTUREMATERIAL_H

#include <iostream>
#include <cassert>
#include <string>
#include <array>
#include "FluxMaterial.hpp"
#include "FluxRectangle2D.hpp"
#include "FluxTexture.hpp"
#include "SDL_image.h"

class Sprite;

namespace Flux
{
    /** A Material with a colour and texture attribute.
     * @see
     *  Material
     */
    class TextureMaterial : public Material
    {
        public:
            TextureMaterial(std::shared_ptr<Texture> texture);
            virtual ~TextureMaterial();
            virtual FluxError loadAttributes(const unsigned int offset);
            virtual FluxError loadUniforms();
            virtual unsigned int vboOffset() const;
            virtual FluxError fillVBO(const Sprite *sprite, GLfloat *vbo);

            Texture* getTexture();

        private:
            FluxError initialise();

            std::shared_ptr<Texture> texture;
            GLint vertexAttribLocation;
            GLint colourAttribLocation;
            GLint textureAttribLocation;
            GLint uSamplerUniformLocation;
    };
}

#endif


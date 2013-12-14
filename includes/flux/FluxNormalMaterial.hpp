#ifndef FLUX_NORMALMATERIAL_H
#define FLUX_NORMALMATERIAL_H

#include <iostream>
#include <cassert>
#include <string>
#include <array>
#include "FluxMaterial.hpp"

#include "FluxRectangle2D.hpp"
#include "FluxTexture.hpp"
#include "FluxUtils.hpp"
#include "FluxError.hpp"

#include "SDL_image.h"

class Sprite;

namespace Flux
{
    /** A Material with a colouri, texture and normal map attribute.
     * @see
     *  Material
     */
    class NormalMaterial : public Material
    {
        public:
            NormalMaterial(std::shared_ptr<Texture> texture, std::shared_ptr<Texture> normalMap);
            virtual ~NormalMaterial();
            virtual FluxError loadAttributes(const unsigned int offset);
            virtual FluxError loadUniforms();
            virtual unsigned int vboOffset() const;
            virtual FluxError fillVBO(const Sprite *sprite, GLfloat *vbo);

            Texture *getTexture();
            Texture* getNormalMap();

        private:
            FluxError initialise();

            std::shared_ptr<Texture> texture, normalMap;
            GLuint vertexAttribLocation;
            GLuint colourAttribLocation;
            GLuint textureAttribLocation;
            GLuint normalAttribLocation;
            GLuint rotationAttribLocation;

            GLint textureSamplerUniformLocation;
    };
}

#endif


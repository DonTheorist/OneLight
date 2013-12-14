#ifndef FLUX_TEXTURE_H
#define FLUX_TEXTURE_H

#include <iostream>
#include <cassert>

#if !EMSCRIPTEN
#define USE_GLEW 0
#endif

#if USE_GLEW
#include "GL/glew.h"
#endif

#include <SDL/SDL.h>
#if !USE_GLEW
#include <SDL/SDL_opengl.h>
#endif

#include "SDL_image.h"

namespace Flux
{
    /** A class encapsulating a texture which can be used by Materials.
     * @par
     * A texture is loaded and stored as a SDL_Surface, this class also stores OpenGL data (e.g buffer locations) which are generated when a Texture is loaded.
     * @par
     * A texture should never be manually instansiated, instead TextureManager should be used, this ensures that each image file is only loaded once.
     * @see
     *  TextureManager
     */
    class Texture
    {
        public:
            /** Destructor, which cleans up the SDL_Surface and OpenGL texture. */
            ~Texture();

            SDL_Surface* getImage() const;
            GLuint getTextureBuffer() const;
            GLuint getTextureBufferLocation() const;
            GLenum getTextureUnit() const;

        private:
            /** Private constructor to prevent manual instantiation. */
            Texture();

            Texture(const Texture &texture);
            Texture(const Texture &&texture);
            Texture operator=(const Texture &texture);

            SDL_Surface *image;
            GLuint textureBuffer;
            GLuint textureBufferLocation;
            GLenum textureUnit;

            /* Friend to allow TextureManager to create new Texture's. */
            friend class TextureManager;
    };
}

#endif


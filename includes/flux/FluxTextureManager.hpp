#ifndef FLUX_TEXTUREMANAGER_H
#define FLUX_TEXTUREMANAGER_H

#include <iostream>
#include <unordered_map>

#include "FluxTexture.hpp"

namespace Flux
{
    class TextureManager
    {
        public:
            ~TextureManager();

            std::shared_ptr<Texture> loadTexture(const std::string &image);

        private:
            TextureManager();
            TextureManager(const TextureManager &tm);
            TextureManager operator= (const TextureManager &tm);
            Texture* createTexture(const std::string &image);
            void initialiseTexture(Texture *t);

            std::unordered_map<std::string, std::shared_ptr<Texture>> loadedTextures;
            int nextTextureUnit = 1;

            friend class Root;
    };
}

#endif


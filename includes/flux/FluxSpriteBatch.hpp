#ifndef FLUX_SPRITEBATCH_H
#define FLUX_SPRITEBATCH_H

#include <iostream>
#include <vector>
#include <array>
#include <memory>

#include "FluxMaterial.hpp"
#include "FluxColourMaterial.hpp"
#include "FluxTextureMaterial.hpp"
#include "FluxNormalMaterial.hpp"
#include "FluxLightPassNormalMaterial.hpp"
#include "FluxLightPassColourMaterial.hpp"
#include "FluxLightPassTextureMaterial.hpp"
#include "FluxError.hpp"

namespace Flux
{
    class Sprite;

    /** This class is used to render many sprites witht he same material in one OpenGL draw call.
     * @par
     * A SpriteBatch consists of astd::vector of Sprite's a Material and optionally sexond Material for light passes. A SpriteBatch must be instanciated with a Material but the light pass material is automatically created if needed.
     * @par 
     * SpriteBatch handles the creates and filling of VertexBufferObjects as well as Index Buffers, adding sprites automatically will resize and reload these if necesary.
     * @par 
     * The order of the Speite's within SpriteBatch should be releid on for ordering, in SpriteBatch can re-order them internally. Instead use Sprite::setDepth() for determining which Sprite's are drawn on top (or behind) others.
     * @par 
     * In order to draw all the sprites one on baacth redundant triangles are used to make all the srpties one triangle strip. Internally an Index Buffer is created whcih automatically creates thee everytime a Sprite is added.
     * @see
     *      Sprite
     *      Material
     */
    class SpriteBatch
    {
        public:
            /** Constructor which takes a Material.
             * @param material The material which should be used to draw the Sprite's.
             */
            SpriteBatch(std::shared_ptr<Material> material);

            /** Default destructor. */
            ~SpriteBatch();
    
            /** Adds a Sprite to be drawn with this SpriteBatch. Will be added to the end if the std::vector of Sprites. The current VBO will be automatically resized if too small to hold the new sprite. */
            FluxError addSprite(std::shared_ptr<Sprite> sprite);

            /** Removed the given Sprite. Rather than removing the Sprite from (potentially) the middle of the sprites vector and then having to update the whole VBO, the Sprite to be removed is swapped with the end one, which is then popped off. This way only one sprite in the VBO (the one which as at the end) has to be updated.
             */
            FluxError removeSprite(std::shared_ptr<Sprite> sprite);

            /** Removed all Sprite's from this SpriteBatch. */
            void clear();

            /** For the VBO for the Sprite at index. Used internally and by Sprite, should never have to be called manually. */
            FluxError updateVBO(const unsigned int index);

            /** Bind the OpenGL buffers for rendering. Only called by Renderer, should never have to be called manually. */
            void bindBuffers() const;

            /** Returns a pointer (not a shared_ptr) to the current Material. */
            Material* getMaterial() const;

            /** Returns a pointer (not a shared_ptr) to the current Material used for the light pass. */
            Material *getLightMaterial() const;

            /** Get the number of vertices of all the Sprite's in this SpriteBatch. */
            unsigned int getNumVerts() const;

            /** Returns a pointer to the Index Buffer. */
            unsigned short* getIndexBuffer();

            std::vector<std::shared_ptr<Sprite>>* getSpritesPtr();

            /** Returns a GLuint representing the OpenGL Index Buffer for this SpriteBatch. */
            GLuint getIBO();

            /** Returns whether lighting has been enabled for this SpriteBatch. */
            bool isLightsEnabled() const;

            /** Sets whether lighting should be used for this SpriteBatch, if being set to true for the first time will automatically create a Material for the light pass (based upon the current Material). */
            FluxError setLightEnabled(const bool lightEnabled);

            /** Returns  whether the SpriteBacth has any Sprite's attached. */
            bool isEmpty();

            /** Force an update of the VBO for all Sprite's. */
            void forceUpdate();
    
        private:
            /** Generates, binds and fills a VBO and an IBO. */
            FluxError createVBO();

            std::shared_ptr<Material> material = nullptr;
            std::shared_ptr<Material> lightMaterial = nullptr;
            std::vector<std::shared_ptr<Sprite>> sprites;
            std::vector<unsigned short> indexBuffer;
            GLuint vbo, ibo;
            bool lightEnabled = false;

    };
}

#endif


#ifndef FLUX_SPRITE_H
#define FLUX_SPRITE_H

#include <iostream>
#include <array>
#include <unordered_map>

#include "FluxVector2.hpp"
#include "FluxVector3.hpp"
#include "FluxMatrix4.hpp"
#include "FluxColour.hpp"
#include "FluxRectangle2D.hpp"
#include "FluxAttribute.hpp"
#include "rapidxml.hpp"

#if USE_GLEW
#include "GL/glew.h"
#endif

#include <SDL/SDL.h>
#if !USE_GLEW
#include <SDL/SDL_opengl.h>
#endif

namespace Flux
{
    class SpriteBatch;
    /** Represents a drawable sprite.
     * @par
     * This class contains four vertices, which represent the corners of the spprite to be rendered. Each vertex contains all the data the could be required by a Material, this means a Material can choose which vertex attributes to upload to the OpenGL buffers. This precents unused data being unecesarily copied.
     * @par
     * The four vertices are held in a continuous std::array, with indexes 0, 1, 2, 3 representing lower left, upper left lower right and upper right respectivly. The position of the sprite is defiend by vertex 0, the lower left corner.
     * @par
     * A pivot point is defined and is the point a sprite is rotated around, be default it is set to the centre of the Sprite when it is inialised and is automatically moved when translate is called.
     * @par
     * A sprite is created with a Rectangle2D which is used to set the intial position of the four vertices.
     * The tranformation functions will call the attached SpriteBatch to update the OpenGL buffers, therefore these functions should not be called until after adding this Sprite to a SpriteBatch.
     */
    class Sprite
    {
        public:
            /** Initialises the vertices with the supplied data, also sets the pivot to be the middle of the sprite.
             * @param rectangle The area to draw the sprite to.
             * @param colour The colour of each vertex.
             * @param source The area of a texture to be drawn onto the sprite, this is converted to UB coordinates.
             * @param normalSource Same as source but for a normal map.
             */
            Sprite(const Rectangle2D &rectangle, const Colour &colour, const Rectangle2D &source=Rectangle2D::ZERO, const Rectangle2D &normalSource=Rectangle2D::ZERO);

            Sprite(const std::string &xmlSpriteSheet, const Flux::Rectangle2D &rectangle, const Colour &colour, const Rectangle2D &source=Rectangle2D::ZERO, const Rectangle2D &normalSource=Rectangle2D::ZERO); 

            /** Default destructor. */
            ~Sprite();

            /** Translates the four vertices by the given Vector2. Also translates the pivot point.
             * If autoUpdate is true then calls current SpriteBatch to update the OpenGL buffers.
             */
            void translate(const Vector2 &translate);

            /** Rotates the four vertices around the pivot point.
             * If autoUpdate is true then calls current SpriteBatch to update the OpenGL buffers.
             */
            void rotate(const float &theta);

            /** Sets the position of the given Vector2.
             * If autoUpdate is true then calls current SpriteBatch to update the OpenGL buffers.
             */
            void setPosition(const Vector2 &position);

            /** Sets the colour for each vertex
             * If autoUpdate is true then calls current SpriteBatch to update the OpenGL buffers.
             */
            void setColour(const Colour &colour);

            /** Sets the colour of the vertex at index.
             * If autoUpdate is true then calls current SpriteBatch to update the OpenGL buffers.
             */
            void setVertexColour(const int index, const Colour &colour);

            /** Sets the area of a texture to draw on the sprite, automatically converted into UV coordinates.
             * If autoUpdate is true then calls current SpriteBatch to update the OpenGL buffers.
             */
            void setTextureSource(const Rectangle2D &source);

            void setTextureSource(const std::string &sprite);

            void setNormalSource(const Rectangle2D &source);
            void setNormalSource(const std::string &sprite);
    
            /** Returns the position of the sprite.
             * Specifcially returns the posotion of vertex at index 0.
             */
            Vector2 getPosition();

            /** Sets the z compontents of each vertex.
             * If autoUpdate is true then calls current SpriteBatch to update the OpenGL buffers.
             */
            void setDepth(const float depth);

            /** Sets whether the transoformation functions should auto update the OpenGL buffers (via calls the SpriteBatch). */
            void setAutoUpdate(const bool autoUpdate);

            void normaliseTextureUV(float width, float height);
            void normaliseNormalUV(float width, float height);

            /** Used by SpriteBatch to set where in it's vector of Sprite's this Sprite resides.
             * This should never be called by anything other than SpriteBatch.
             */
            void setVBOIndex(const unsigned int vboIndex);

            /** Get the index of this Sprite in the attached SpriteBatch vector of Sprites. */
            unsigned int getVBOIndex() const;

            /** Sets the SpriteBatch which this Sprite belongs. Should only be called once (an assert will fil if not). */
            void setSpriteBatch(SpriteBatch *sb);

            void setRectangle(const Rectangle2D &rectangle);
            float getWidth();
            float getHeight();

            /** Get a pointer to the SpriteBatch this Sprite belongs to. */
            SpriteBatch* getSpriteBatch();

            /** Returns a cont pointer to the vertices of this Sprite. */
            const vertex* getVertices() const;

            void setTextureDimensions(float textureWidth, float textureHeight);
            void setNormalDimensions(float normalWidth, float normalHeight);

        private:
            std::array<vertex, 4> vertices;
            std::unordered_map<std::string, Rectangle2D> spriteMap;
            unsigned int vboIndex;
            SpriteBatch *sb = nullptr;
            Vector2 pivot;
            bool autoUpdate = true;
            float textureWidth = 1.0f, textureHeight = 1.0f;
            float normalWidth = 1.0f, normalHeight = 1.0f;
    };
}

#endif


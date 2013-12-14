#ifndef FLUX_ROOT_H
#define FLUX_ROOT_H

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

#include "FluxRenderer.hpp"
#include "FluxSpriteBatch.hpp"
#include "FluxCamera.hpp"
#include "FluxTextureManager.hpp"
#include "FluxLightManager.hpp"
#include "FluxPointLight.hpp"
#include "FluxTextDrawer.hpp"
#include "FluxError.hpp"
#include "FluxTimer.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

namespace Flux
{
    /** The core of Flux.
     * A root must be created as it creates and manages the renderer, as well creating and managing the SDL_Surface Flux renders to.
     * Only one instance of Root should be created, treat it a bit like a singleton.
     * The root also has a method for rendering a frame to the SDL_Surface.
     * As well as this the root also maintains the scene, which is all Sprite, SpriteBatch and PointLight to be rendered.
     */
    class Root
    {
        public:
            /** Default constructor. */
            Root();
            /** Default desctructor.
             * Release TextureManager and LightManager as well as destroying the SDL_Surface and performing SDL cleanup. */
            ~Root();

            /** Initialises the root.
             * Creates and sets up the SDL_Surface and prepars Flux for using OpenGL.
             * It also creates a TextureManager and a LightManager.
             * Calling initialise with no options creates a window 1280 x 720 px and creates an OrthographicCamera for this size, with a near and far plane of -10.0f and 10.0f resprectively. The camera will be positioned such that the lower left corner of the window is at (0, 0, 0) and it will be looking down the z-axis such that if two objects are being drawn the one with the larger z-axis will be behind the other. In other words the negative z-axis is coming out of the window and the positive going on.
             */

            FluxError initialise();

            /** Same as Root::initialise() except that a custom width, height and camera are supplied. */
            FluxError initialise(Camera* camera);

            /** Renders the current scene to the SDL_Surface. This will need to be called regualry from some form up update/game loop. */
            FluxError renderFrame();

            /** Adds a SpriteBatch to the scene. */
            FluxError addToScene(std::shared_ptr<SpriteBatch> sb);

            /** Add a TextDrawer to the scene. */
            FluxError addToScene(std::shared_ptr<TextDrawer> td);

            /** Add a PointLight to the scene. Calls LightManager::addLight() */
            FluxError addToScene(std::shared_ptr<PointLight> pl);

            FluxError removeFromScene(std::shared_ptr<SpriteBatch> sb);
            FluxError removeFromScene(std::shared_ptr<TextDrawer> td);
            FluxError removeFromScene(std::shared_ptr<PointLight> pl);

            Colour getBackgroundColour();
            void setBackgroundColour(const Colour &backgroundColour);

            TextureManager* getTextureManager();
            LightManager* getLightManager();

            float getElapsedSeconds();
            float getElapsedMilliSeconds();

        private:
            /** Prevent copying of root. */
            Root(const Root &r);

            Root(const Root &&r);

            /** Prevent copying of root. */
            Root& operator=(const Root &r);

            /** The SDL_Surface to which Root::renderFrame renders the current scene. */
            SDL_Surface *screen;

            /** Container for all SpriteBatch to be rendered. */
            std::vector<std::shared_ptr<SpriteBatch>> scene;
            //std::map<std::string, std::shared_ptr<SpriteBatch>> scene;

            /** The renderer to use with Root::renderFrame. */
            Renderer *renderer;

            TextureManager *textureManager;
            LightManager *lightManager;

            Timer timer;
    };
}

#endif


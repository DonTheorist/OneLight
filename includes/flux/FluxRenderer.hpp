#ifndef FLUX_RENDERER_H
#define FLUX_RENDERER_H

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cassert>

#include "FluxSpriteBatch.hpp"
#include "FluxCamera.hpp"
#include "FluxLightManager.hpp"
#include "FluxError.hpp"
#include "FluxColour.hpp"

namespace Flux
{
    /** Class that handles the actual rendering of a scene.
     * Should be created and managed automatically by Root. Therefore is a friend to Root and has a private constructor.
     * @see
     *      Root
     */
    class Renderer
    {
        public:
            /** Default destructor. */
            ~Renderer();

            /** Uses OpenGL to render a single frame of the supplied scene and lights. Assumes that OpenGL and an SDL_Surface have already been setup by root. */
            FluxError renderFrame(const std::vector<std::shared_ptr<SpriteBatch>> *scene, const LightManager *lightManager);

            Colour getBackgroundColour();
            void setBackgroundColour(const Colour &backgroundColour);

        private:
            /** Default constructor, takes a width, height and a camera which are used for rendering calculatiosn. */
            Renderer(Camera *camera);

            Camera *camera;
            float width, height;
            Colour backgroundColour = Colour::BLACK;

            friend class Root;
    };
}

#endif


#ifndef FLUX_LIGHTMANAGER_H
#define FLUX_LIGHTMANAGER_H

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

#include <iostream>
#include <array>
#include <vector>
#include <cassert>
#include <algorithm>

#include "FluxUtils.hpp"
#include "FluxPointLight.hpp"
#include "FluxError.hpp"

namespace Flux
{
    /** A class for creating and storing lights.
     *  When performing light calculations all PointLight objets are needed, thus LightManager is responsible for creating
     *  and storing PointLight's.
     *  @par
     *  It provides convenvience methods for loading specific PointLight data into arrays for passing over the the graphics card.
     *  @par
     *  Constructor is private and Root is a friend so that only the Root can create LightManager's, this allows for only
     *  one to ever be created. 
     *  @see
     *      PointLight
     *      Root
     */
    class LightManager
    {
        public:
            /** Default destructor. */
            ~LightManager();

            FluxError addLight(std::shared_ptr<PointLight> light);
            FluxError removeLight(std::shared_ptr<PointLight> light);
            unsigned int getNumLights() const;
            GLfloat* getPositions() const;
            GLfloat* getColours() const;
            GLfloat* getAttenuations() const;
            void updateArrays(unsigned int idex);

        private:
            LightManager();
            LightManager(const LightManager &lm);
            LightManager operator= (const LightManager &lm);

            std::vector<std::shared_ptr<PointLight>> lights;
            std::vector<GLfloat> position, colour, attenuation;

            friend class Root;
    };
}

#endif



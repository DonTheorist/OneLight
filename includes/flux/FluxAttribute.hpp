#ifndef FLUX_ATTRIBUTE_H
#define FLUX_ATTRIBUTE_H

#if USE_GLEW
#include "GL/glew.h"
#endif

#include <SDL/SDL.h>
#if !USE_GLEW
#include <SDL/SDL_opengl.h>
#endif

#include <array>

class Vector3;
class Colour;
class Vector2;

namespace Flux
{
    /** Struct to hold vertex attributes used by Material
     * @see
     *     Material
     *     ColourMaterial
     *     TextureMaterial
     *     NormalMaterial
     */

    struct vertex
    {
        Vector3 position;
        Colour colour;
        Vector2 texUV;
        Vector2 normalUV;
        float rotation;
    };

    /** Struct to hold vertex attribtes for light pass
     * @see
     *     Material
     */
    //struct lightVertex
    //{
    //    Vector3 position;
    //    Vector2 normalUV;
    //};
}

#endif


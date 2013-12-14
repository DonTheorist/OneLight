#ifndef FLUX_MATERIAL_H
#define FLUX_MATERIAL_H

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
#include <map>
#include <vector>
#include <array>
#include <sstream>
#include <fstream>

#include "FluxMatrix4.hpp"
#include "FluxVector3.hpp"
#include "FluxColour.hpp"
#include "FluxSprite.hpp"
#include "FluxUtils.hpp"
#include "FluxError.hpp"

namespace Flux
{
    /** A Material encapsulates an OpenGl program object (which in turn has a vertex and fragment shader). This class also provides methods for creating, loading and linking sgaders, as well as loading attributes and unforms during rendering.
     * @par
     * In Flux there are two types of Material built in: standard Material's for colouring Sprite's (ColourMaterial, TextureMaterial, NormalMaterial) and light pass Material's for computing per pixel lighting (LightPassColourMaterial, LightPassTextureMaterial and LightPassNormalMaterial). Each standard Material is paired with a light pass Material, the former of which is automatically created when needed. As such when using Flux you will only need to ever create and initialise the standard Material's.
     */
    class Material
    {
        public:
            /** Default constructor. */
            Material();

            /** Default destructor. */
            virtual ~Material();

            /** Load the sttributes needed by the shader.
             * @param offset The length of each interleaved object in the current VBO.
             */
            virtual FluxError loadAttributes(const unsigned int offset) = 0;

            /** Load the uniforms needed by the current shader. */
            virtual FluxError loadUniforms() = 0;

            /** Fills an array with the interleaved attribute data of a given Sprite for the current shader.
             * @param sprite The Sprite whose data is to be copied.
             * @param vbo The array in which to copy data into.
             */
            virtual FluxError fillVBO(const Sprite *sprite, GLfloat *vbo) { return E_OK; };

            /** Returns the offset of elements in the current VBO. This is effectively how many elements (GLFloats) in one object. */
            virtual unsigned int vboOffset() const { return E_OK; };

            GLuint getProgramObject();
        
        protected:
            /** Links the two loaded shaders to the current programObject. */
            FluxError linkShader(const GLuint vertexShader, const GLuint fragmentShader);

            /** Links the two loaded shaders against the supplied programObject. */
            FluxError linkShader(const GLuint programObject, const GLuint vertexShader, const GLuint fragmentShader);

            /** Loads the given string as a shader and sets shader to the OpenGL number represeting the loaded shader. */
            FluxError loadShader(const GLchar *src, GLenum type, GLuint *shader) const;

            GLuint programObject;
    };

}
#endif



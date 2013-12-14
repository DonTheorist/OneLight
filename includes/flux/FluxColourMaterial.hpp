#ifndef FLUX_COLOURMATERIAL_H
#define FLUX_COLOURMATERIAL_H
     
#include "FluxMaterial.hpp"
#include "FluxColour.hpp"
#include "FluxAttribute.hpp"
#include "FluxError.hpp"

#include <cassert>

namespace Flux
{
    /** A Material with a colour attribute.
     * @see
     *  Material
     */
    class ColourMaterial : public Material
    {
        public:
            /** Default constructor. */
            ColourMaterial();

            /** Default destructor. */
            virtual ~ColourMaterial();

            virtual FluxError loadAttributes(const unsigned int offset);
            virtual FluxError loadUniforms();
            virtual FluxError fillVBO(const Sprite *sprite, GLfloat *vbo);
            virtual unsigned int vboOffset() const;

        private:
            FluxError initialise();

            GLuint vertexAttribLocation;
            GLuint colourAttribLocation;
    };
}

#endif


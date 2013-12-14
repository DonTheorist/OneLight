#ifndef FLUX_COLOUR_H
#define FLUX_COLOUR_H

#include <iostream>

#include "FluxUtils.hpp"

namespace Flux
{
    /** Class represting an RGBA colour.
     *  All values are in the range [0,1].
     *  @para
     *      Values are not normalised when set, so using values outside of the range [0,1] should be considered as undefiend behaviour.
     */
    class Colour
    {
        public:
            /** Default constructor. */
            Colour();
            /** Constructor which sets r, g, b and a all to the same value/ */
            Colour(const float rgba);
            /** Constructor which sets r, g and b to the first value and a to the second. */
            Colour(const float rgb, const float a);
            /** Constructor for seting r, g, b and a all seperatly. a defaults to 1. */
            Colour(const float r, const float g, const float b, const float a = 1.0f);
            /** Default destructor. */
            ~Colour();

            /** Used for writing Colour to a stream. Helpful for debugging anf logging. */
            friend std::ostream& operator<<(std::ostream &out, const Colour &c);

            /** Colour(1). */
            static const Colour WHITE;
            /** Colour(0, 1). */
            static const Colour BLACK;
            /** Colour(1, 0, 0). */
            static const Colour RED;
            /** Colour(0, 0, 1). */
            static const Colour BLUE;
            /** Colour(0, 1, 0). */
            static const Colour GREEN;
            /** Colour(0, 0.498, 1). */
            static const Colour AZURE;
            /** Colour(0.863, 0.078, 0.235). */
            static const Colour CRIMSON;
            /** Colour(0.596, 0.984, 0.596). */
            static const Colour PALEGREEN;

            float r, g, b, a;
    };

}

#endif


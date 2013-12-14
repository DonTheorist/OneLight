#ifndef FLUX_RECTANGLE2D_H
#define FLUX_RECTANGLE2D_H

#include <iostream>
#include <cassert>

#include "FluxVector2.hpp"

namespace Flux
{
    /** Represetns a 2D axis aligned rectangle.
     * Defines as point in 2D space with a width and a height. The width is taken along (right) the x axis and the height up the y axis.
     * In effect the position Vector2 represents the lower left hand corner of the rectangle.
     * @see
     *  Vector2
     */
    class Rectangle2D
    {
        public:
            /** Default constructor. */
            Rectangle2D();

            /** Constructir taking the x and y position of the lower left hand corner and the width and height to extend it. */
            Rectangle2D(const float x, const float y, const float width, const float height);

            /** Same as Rectangle2D(const int x, const int y, const float width, const float height) except the Vector2 represents x and y. */
            Rectangle2D(const Vector2 &position, const float width, const float height);

            /** Default destructor. */
            ~Rectangle2D();

            /** Returns the centre of the rectangle
             * The position plus half height and half width.
             */
            Vector2 getCentre() const;

            /** Test if two rectancgles intersect. */
            bool intersect(const Rectangle2D &r);

            /** Write the rectangle to a stream. Handy for debugging. */
            friend std::ostream& operator<<(std::ostream &out, const Rectangle2D &rv);

            /** Rectangle(0.0f, 0.0f, 0.0f, 0.f). */
            static const Rectangle2D ZERO;

            /** Position of the recangle (lower left hand corner).
             * Made public for easy access. */
            Vector2 position;

            float width, height;
    };
}

#endif


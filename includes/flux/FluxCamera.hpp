#ifndef FLUX_CAMERA_H
#define FLUX_CAMERA_H

#include "FluxMatrix4.hpp"
#include "FluxVector2.hpp"
#include "FluxVector3.hpp"
#include <iostream>

namespace Flux
{
   /** Base class for a Camera id 3D space.
    * @par
    * A Camera encapsulates several components which are used for rendering.
    * @par
    *  The actual Camera is represented by an eye Vector3 which is it's position in 3D space, this eye is looking at a target and has an up vector. These two components give the eye (an hence the camera) an orientation.
    * @par
    *  The camera also contains a projection and view matrix, whcih is passed to shaders and used for rendering.
    * @see
    *      OrthographicCamera
    */
    class Camera
    {
        public:
            Camera(const Vector2 &position, const float width, const float height, const float depth);
            ~Camera();

            Vector2 getPosition() const;
            void setPosition(const Vector2 &position);

            Matrix4 getProjview() const;

            float getWidth() const;
            float getHeight() const;
            float getDepth() const;

        protected:
            Matrix4 projview;
            Vector2 position;

            float width, height, depth;
    };
}

#endif


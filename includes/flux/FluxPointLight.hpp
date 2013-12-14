#ifndef FLUX_POINTLIGHT_H
#define FLUX_POINTLIGHT_H

#include <iostream>
#include "FluxVector3.hpp"
#include "FluxColour.hpp"

namespace Flux
{
    class LightManager;

    /** A PointLight is a light which spreads out uniformly from a point. In this sense it can be thought of like a lightbulb.
     * @par
     * A PointLight has a colour, which is used in lighting caulcations.
     * @par
     * In order to simulate the light 'dropping off' (i.e losing intentsitng with distance) the attenuation of the lgiht is calculated by the fragment shaders. This uses the following equation \f$ k_0 + d \cdot k_1 + d^2 \cdot k_2\f$ where \f$d\f$ is the distance from the light and \f$k_0\f$, \f$k_1\f$ and \f$k_2\f$ are the constant, linear and quadratic coefficents repsectively.  
     * @par
     * It should be noted that for all three light pass materials (LightPassColourMaterial, LightPassTextureMaterial and LightPassNormalMaterial) the lighting calulcations are performed for each light on each fragment, even if the fragment is far enough away from the fragment as to have no effect.
     * PointLight also maintains a pointer to the LightManager which created it, as well as its index in the data structor in said LightManager. These variables are used internally and shouldn't be altered with.
     */
    class PointLight
    {
        public:
            /** Constructor.
             * @param position Position of light in 3D space.
             * @param colour The colour of the light.
             * @param k0 Constant coeffecient of attenuation.
             * @param k1 Linear coefficient if attenuation.
             * @param k2 Quadratic coefficient of attenuation.
             */
            PointLight(const Vector3 &position, const Colour &colour, const float k0, const float k1, const float k2);

            /** Default destructor. */
            ~PointLight();

            Vector3 getPosition();
            void setPosition(const Vector3 &position);
            Colour getColour();
            void setColour(const Colour &colour);
            Vector3 getAttenuationAsVector3();
            void setAttenuationAsVector3(const Vector3 &attenuation);
            void setConstantAttenuation(const float k0);
            void setLinearAttenuation(const float k1);
            void setQuadraticAttenuation(const float k2);
            unsigned int getIndex();
            void setIndex(const unsigned int index);
            void setLightManager(LightManager *lightManager);

        private:
            Vector3 position;
            Colour colour;
            Vector3 attenuation;

            unsigned int index;
            LightManager *lightManager = nullptr;
    };
}

#endif


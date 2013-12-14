#ifndef FLUX_RANDOM_H
#define FLUX_RANDOM_H

#ifndef EMSCRIPTEN
#include <random>
#else
#include <cstdlib>
#include <ctime>
#endif

namespace Flux
{
    /** Class for producing uniform random numbers.
     * Uses either std::m129937 if compiling for desktop or a C function fallback of using emscripten.
     * Siliently makes the choise using #ifdefs.
     */ 
    class Random
    {
        public:
            /** Default constructor.
             * Also seeds the random numbers, this only happens the first time the function is instanciated.
             */
            Random();

            /** Default destructor. */
            ~Random();

            /** Produces an integer in the range [min, max]. */
            int randRange(int min, int max);

        private:
            /** Used for checking is the class has been instaniated before. Ensures seeding only happned once. */
            static bool initialised;
#ifndef EMSCRIPTEN
            /** Used when compiling for desktop. */
            std::mt19937 gen;
#endif

    };
}

#endif


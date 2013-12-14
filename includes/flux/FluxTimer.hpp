#ifndef FLUX_TIMER_H
#define FLUX_TIMER_H

#include <iostream>
#include <chrono>
#include <ratio>

namespace Flux
{
    class Timer
    {
        public:
            Timer();
            ~Timer();

            float elapsedSeconds();
            float elapsedMilliSeconds();
            void reset();
            bool haveSecondsElapsed(float seconds);
            bool haveMilliSecondsElapsed(float milliseconds);

        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> start;
    };
}

#endif


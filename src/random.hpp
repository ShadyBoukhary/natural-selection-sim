#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__
#include <random>

namespace Random
{
    static std::random_device dev;
    static std::mt19937 rng(dev());

    static int getRandomInt(int a, int b)
    {
        std::uniform_int_distribution<std::mt19937::result_type> dist(a, b);
        return dist(rng);
    }

    static double getRandomDouble(int a, int b)
    {
        std::uniform_real_distribution<double> dist(a, b);
        return dist(rng);
    }



}



#endif

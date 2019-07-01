#ifndef __STATE_HPP__
#define __STATE_HPP__

#define DEFAULT_ENERGY 1800
#include "location.hpp"
#include <random>

class State
{
public:
    State();
    State(Location location, uint64_t energy, bool isAlive);
    State(const State& other) = default;
    State(State&&) = default;
    Location getLocation() const;
    uint64_t getEnergy() const;
    bool isAlive() const;

    bool operator==(const State &);
    State& operator=(State &) & = default;
private:
    Location location;
    uint64_t energy;
    bool alive;
};

#endif

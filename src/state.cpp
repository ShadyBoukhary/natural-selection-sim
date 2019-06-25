#include "state.hpp"

State::State() : location(Location()), energy(DEFAULT_ENERGY), alive(true) {}

State::State(Location location, uint64_t energy, bool isAlive)
{
    this->location = location;
    this->energy = energy;
    alive = isAlive;
}

Location State::getLocation() const { return location; }

uint64_t State::getEnergy() const { return energy; }

bool State::isAlive() const { return alive; }

bool State::operator==(const State & rhs) 
{
    return location == rhs.location && energy == rhs.energy && alive == rhs.alive;
}

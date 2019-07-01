#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <vector>
#include <memory>
#include <chrono>
#include "state.hpp"

class Organism;
using TimePoint = std::chrono::high_resolution_clock::time_point;

class OrganismDay
{
public:
    OrganismDay(const State & state);
    OrganismDay(const OrganismDay& other) = default;
    std::vector<State> getStates() const;
    std::vector<std::shared_ptr<Organism>> getEatenOrganisms() const;
    void eatOrganism(const std::shared_ptr<Organism> & organism);
    State getCurrentState() const;
    void addState(const State & state);
    void die();
    void move(const Location & location, double mass, double speed);

private:

    std::vector<std::shared_ptr<Organism>> eatenOrganisms;
    std::vector<State> states;
    bool isAlive;
    TimePoint timeOfDeath;
    TimePoint homeTime;
};

#endif

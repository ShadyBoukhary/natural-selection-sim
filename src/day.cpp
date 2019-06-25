#include "day.hpp"

OrganismDay::OrganismDay(const State & state)
{
    isAlive = state.isAlive();
    states.push_back(state);
}

std::vector<State> OrganismDay::getStates() const { return states; }

std::vector<std::shared_ptr<Organism>> OrganismDay::getEatenOrganisms() const
{
    return eatenOrganisms;
}

void OrganismDay::eatOrganism(const std::shared_ptr<Organism> & organism)
{
    eatenOrganisms.push_back(organism);
}

State OrganismDay::getCurrentState() const
{
    return states.back();
}

void OrganismDay::addState(const State & state)
{
    states.push_back(state);
}

void OrganismDay::die()
{
    const State current = getCurrentState();
    addState(State(current.getLocation(), current.getEnergy(), false));
    isAlive = false;
    timeOfDeath = std::chrono::high_resolution_clock::now();
}

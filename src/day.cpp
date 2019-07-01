#include "day.hpp"
#include "organism.hpp"

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
  const State current = getCurrentState();
  uint64_t newEnergy = current.getEnergy() + organism->getMass() / 2;
  eatenOrganisms.push_back(organism);

  addState(State(current.getLocation(), newEnergy, current.isAlive()));
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

#include <iostream>
void OrganismDay::move(const Location &location, double mass, double speed)
{
  const State current = getCurrentState();
  double newEnergy = current.getEnergy() - 0.5 * mass * pow(speed, 2);
  if (newEnergy < 0.01)
  {
      die();
  }
  else
  {
    addState(State(location, newEnergy, current.isAlive()));
  }
}

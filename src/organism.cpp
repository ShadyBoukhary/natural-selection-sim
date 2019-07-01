#include "organism.hpp"
#include "random.hpp"

Organism::Organism(Location location)
{
    mass = Random::getRandomDouble(10, 100);
    speed = Random::getRandomDouble(1, 1);
    visibility = Random::getRandomInt(1, 1);
    int start = static_cast<int>(TrophicLevel::Plant);
    int end = static_cast<int>(TrophicLevel::Apex);
    trophicLevel = static_cast<TrophicLevel>(Random::getRandomInt(start, end));
    uint64_t energy = Random::getRandomInt(1000, 10000);
    days.push_back(OrganismDay(State(location, energy, true)));
}

Organism::Organism(double mass, double speed, TrophicLevel trophicLevel, uint32_t visibility, const State & state)
{
    this->mass = mass;
    this->speed = speed;
    this->trophicLevel = trophicLevel;
    this->visibility = visibility;
    days.push_back(OrganismDay(state));
}

double Organism::getMass() const { return mass; }

double Organism::getSpeed() const { return speed; }

TrophicLevel Organism::getTrophicLevel() const { return trophicLevel; }

OrganismDay& Organism::getCurrentDay()
{
    checkEmptyDays();
    return days.back();
}

void Organism::checkEmptyDays() const
{
    if (days.empty()) { throw std::runtime_error("There not days."); }
}

std::vector<State> Organism::getAllCurrentDayStates() const
{
    checkEmptyDays();
    return days.back().getStates();
}

bool Organism::operator==(const Organism & rhs){
    return mass == rhs.mass && speed == rhs.speed && trophicLevel == rhs.trophicLevel && &days == &rhs.days;
}

void Organism::eat(const std::shared_ptr<Organism> &organism)
{
    // TODO: Check if it can be eaten first
    organism->die();
    getCurrentDay().eatOrganism(organism);
}

void Organism::die()
{
    getCurrentDay().die();
}

const OrganismDay Organism::getCurrentDayReadOnly() const
{
    return days.back();
}

State Organism::getCurrentState() const
{
    return getCurrentDayReadOnly().getCurrentState();
}

bool Organism::isAlive() const
{
    return getCurrentDayReadOnly().getCurrentState().isAlive();
}

uint64_t Organism::searchForFood(const std::map<Location, uint64_t>& map) const
{
    Location location = getCurrentState().getLocation();

    // Check 4 neighbors within organism's visibility
    for (uint32_t vis = 1; vis <= visibility; vis++) {
      auto it = map.find(Location(location.getX() + vis, location.getY()));
      if (it != map.end()) {
        return it->second;
      } else {

        it = map.find(Location(location.getX(), location.getY() + vis));
        if (it != map.end()) {
          return it->second;
        } else {

          it = map.find(Location(location.getX() - vis, location.getY()));
          if (it != map.end()) {
              return it->second;
          } else {
            it = map.find(Location(location.getX(), location.getY() - vis));
            if (it != map.end()) {
                return it->second;
            }
          }
        }
      }
    }
    return -1;
}

#include <iostream>
std::vector<Location> Organism::availableLocations(const std::map<Location, uint64_t> &map, uint64_t maxX, uint64_t maxY) const {

  Location location = getCurrentState().getLocation();
  std::vector<Location> locations;

  for (uint32_t vis = 1; vis <= speed; vis++) {
      int64_t newX = location.getX() + vis;
      if (newX < maxX)
      {
        auto it = map.find(Location(newX, location.getY()));
        if (it == map.end()) {
          Location newLocation(newX, location.getY());
          locations.push_back(newLocation);
        }
      }

      int64_t newY = location.getY() + vis;
      if (newY < maxY)
      {

          auto it1 = map.find(Location(location.getX(), newY));
          if (it1 == map.end()) {
          Location newLocation(location.getX(), newY);
          locations.push_back(newLocation);
        }
      }

      newX = (int64_t)location.getX() - vis;
      if (newX >= 0)
      {

        auto it = map.find(Location(newX, location.getY()));
        if (it == map.end()) {
          Location newLocation(newX, location.getY());
          locations.push_back(newLocation);
        }
      }

      newY = (int64_t)location.getY() - vis;
      if (newY >= 0)
      {
        auto it1 = map.find(Location(location.getX(), newY));
        if (it1 == map.end()) {
          Location newLocation(location.getX(), newY);
          locations.push_back(newLocation);
        }
      }
  }
  return locations;
}

void Organism::move(const Location &location, double speed)
{
    getCurrentDay().move(location, mass, speed);
}

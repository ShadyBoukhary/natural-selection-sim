#include "simulation.hpp"
#include "random.hpp"
#include <iostream>

Simulation::Simulation(uint64_t organismsCount, uint64_t mapSizeX, uint64_t mapSizeY)
{
    sizeX = mapSizeX;
    sizeY = mapSizeY;
    organisms.resize(organismsCount);
    initOrganisms();
}

void Simulation::initOrganisms()
{
  std::cout << "Initializing...\n";
  uint64_t count = 0;
  for (auto &organism : organisms) {
    uint64_t x = Random::getRandomInt(0, sizeX - 1);
    uint64_t y = Random::getRandomInt(0, sizeY - 1);
    Location location(x, y);
    do {
      x = Random::getRandomInt(0, sizeX - 1);
      y = Random::getRandomInt(0, sizeY - 1);
      location = Location(x, y);
    } while (map.find(location) != map.end());
    organism = std::make_shared<Organism>(location);
    map.insert(std::make_pair(location, count));
    count++;
  }
}

void Simulation::printMap()
{
  std::cout << "Map:\n";
  for (int x = 0; x < sizeX; x++) {
    for (int y = 0; y < sizeY; y++) {
      std::cout << (map.count(Location(x, y)) != 0 ? "X " : "0 ");
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void Simulation::step()
{
    for (auto & organism : organisms)
    {
        if (organism->isAlive() && organism->getTrophicLevel() > TrophicLevel::Plant)
        {
            uint64_t index = organism->searchForFood(map);
            const Location &location = organism->getCurrentState().getLocation();
            uint64_t mapIndex = map.at(location);
            if (index == -1)
            {
                // TODO: Move randomly
                const auto &locations = organism->availableLocations(map, sizeX, sizeY);
                uint32_t idx = Random::getRandomInt(0, locations.size() - 1);
                organism->move(locations[idx], organism->getSpeed());
            } else {
              // TODO: If mass is greater && can reach | if mass is less move
              // away
              const auto &other = organisms[index];
              // If mass is 1.5x greater, then the organism can prey on it
              // TODO: Add trophic level maybe later depending on results
              if (organism->getMass() > other->getMass() * 1.1 ||
                  other->getTrophicLevel() == TrophicLevel::Plant) {
                organism->eat(other);
                // TODO: find speed depending on distance
                organism->move(other->getCurrentState().getLocation(),
                               organism->getSpeed());
                map.erase(other->getCurrentState().getLocation());
              } else {
                const auto &locations = organism->availableLocations(map, sizeX, sizeY);
                if (locations.empty()) {
                  organism->move(organism->getCurrentState().getLocation(),
                                 organism->getSpeed());
                } else {
                  uint32_t idx = Random::getRandomInt(0, locations.size() - 1);
                  organism->move(locations[idx], organism->getSpeed());
                }
              }
            }
            map.erase(location);
            map.insert(std::make_pair(organism->getCurrentState().getLocation(), mapIndex));
        }
    }
    removeCorpses();
}

void Simulation::removeCorpses()
{
  auto it = map.begin();
  while (it != map.end()) {
    if (!organisms[it->second]->isAlive()) {
      it = map.erase(it);
    } else
      it++;
  }
}

const std::map<Location, uint64_t> & Simulation::getMap() const { return map; }

const std::vector<std::shared_ptr<Organism>> & Simulation::getOrganisms() const { return organisms; }

std::pair<uint64_t, uint64_t> Simulation::getMapSize() const
{
    return std::make_pair(sizeX, sizeY);
}

void Simulation::printStats()
{
    uint32_t plants = 0;
    uint32_t primary = 0;
    uint32_t secondary = 0;
    uint32_t tertiary = 0;
    uint32_t apex = 0;
    for (auto & [location, index] : map)
    {
        std::cout << "Location: " << location.toString() << std::endl;
        TrophicLevel level = organisms[index]->getTrophicLevel();
        switch (level)
        {
        case TrophicLevel::Plant:
            plants++;
            break;
        case TrophicLevel::Primary:
            primary++;
            break;
        case TrophicLevel::Secondary:
            secondary++;
            break;
        case TrophicLevel::Tertiary:
            tertiary++;
            break;
        case TrophicLevel::Apex:
            apex++;
            break;
        }
    }

    std::cout << "Plant: " << plants << "\n"
              << "Primary: " << primary << "\n"
              << "Secondary: " << secondary << "\n"
              << "Tertiary: " << tertiary << "\n"
              << "Apex: " << apex << "\n";
}

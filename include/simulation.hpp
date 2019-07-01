#ifndef __SIMULATION_HPP__
#define __SIMULATION_HPP__

#include <cstdint>
#include <map>
#include "organism.hpp"

class Simulation
{
public:
    Simulation(uint64_t organismsCount, uint64_t mapSizeX, uint64_t mapSizeY);
    void printMap();
    void step();
    void removeCorpses();
    const std::map<Location, uint64_t> & getMap() const;
    const std::vector<std::shared_ptr<Organism>> & getOrganisms() const;
    std::pair<uint64_t, uint64_t> getMapSize() const;
    void printStats();

private:
    void initOrganisms();
    std::map<Location, uint64_t> map;
    std::vector<std::shared_ptr<Organism>> organisms;
    uint64_t sizeX;
    uint64_t sizeY;
};

#endif

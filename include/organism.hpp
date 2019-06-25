#ifndef __ORGANISM_HPP__
#define __ORGANISM_HPP__
#include "day.hpp"

enum class TrophicLevel;

class Organism
{
public:
    Organism();
    Organism(double mass, double speed, TrophicLevel trophicLevel, const State & state);
    Organism(const Organism&) = default;
    Organism(Organism&&) = default;
    double getMass() const;
    double getSpeed() const;
    TrophicLevel getTrophicLevel() const;
    OrganismDay& getCurrentDay();
    inline void checkEmptyDays() const;
    std::vector<OrganismDay> getAllDays();

    bool isAlive() const;
    TimePoint getTimeOfDeath() const;
    TimePoint getHomeTime() const;
    State getCurrentState() const;
    std::vector<State> getAllCurrentDayStates() const;

    void eat(const std::shared_ptr<Organism> & organism);
    void die();

    bool operator==(const Organism& rhs);
    bool operator<(const Organism& rhs);
    bool operator>(const Organism& rhs);
    Organism& operator=(const Organism&) & = default;
    Organism& operator=(Organism&&) && = default;

private:
    const OrganismDay getCurrentDayReadOnly() const;
    double mass;
    double speed;
    TrophicLevel trophicLevel;
    std::vector<OrganismDay> days;
};

enum class TrophicLevel
{
    Plant, Primary, Secondary, Tertiary, Apex
};

#endif


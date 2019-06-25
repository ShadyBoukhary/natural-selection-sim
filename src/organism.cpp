#include "organism.hpp"

Organism::Organism() : mass(0), speed(0), trophicLevel(TrophicLevel::Plant)
{
    days.push_back(OrganismDay(State()));
}

Organism::Organism(double mass, double speed, TrophicLevel trophicLevel, const State & state)
{
    this->mass = mass;
    this->speed = speed;
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

bool Organism::isAlive() const
{
    return getCurrentDayReadOnly().getCurrentState().isAlive();
}

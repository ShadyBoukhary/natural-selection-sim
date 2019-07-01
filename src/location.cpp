#include "location.hpp"

Location::Location() : x(0), y(0){}

Location::Location(uint64_t x, uint64_t y) :
    x(x), y(y){}

void Location::changeLocation(uint32_t x) { this->x = x; }

void Location::changeLocation(uint32_t x, uint32_t y)
{
    changeLocation(x);
    this->y = y;
}

std::string Location::toString() const
{
    return "{x: " + std::to_string(x) + ", y: " + std::to_string(y) + "}";
}

uint32_t Location::getX() const {
  return x;
}

uint32_t Location::getY() const { return y; }


bool Location::operator==(const Location & rhs)
{
    return x == rhs.x && y == rhs.y;
}

bool Location::operator<(const Location & rhs) const
{
  if (x != rhs.x)
    return x < rhs.x;
  return y < rhs.y;
}
bool Location::operator>(const Location & rhs) const
{
  if (x != rhs.x)
    return x > rhs.x;
  return y > rhs.y;
}

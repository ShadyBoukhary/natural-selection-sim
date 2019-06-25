#include "location.hpp"

Location::Location() : x(0), y(0), orientation(Orientation::North) {}

Location::Location(uint32_t x, uint32_t y, Orientation orientation) :
    x(x), y(y), orientation(orientation) {}

void Location::changeLocation(uint32_t x) { this->x = x; }

void Location::changeLocation(uint32_t x, uint32_t y)
{
    changeLocation(x);
    this->y = y;
}

void Location::changeLocation(uint32_t x, uint32_t y, Orientation orientation)
{
    changeLocation(x, y);
    this->orientation = orientation;
}

void Location::changeOrientation(Orientation orientation)
{
    this->orientation = orientation;
}

uint32_t Location::getX() { return x; }

uint32_t Location::getY() { return y; }

Orientation Location::getOrientation() { return orientation; }

bool Location::operator==(const Location & rhs)
{
    return x == rhs.x && y == rhs.y && orientation == rhs.orientation;
}



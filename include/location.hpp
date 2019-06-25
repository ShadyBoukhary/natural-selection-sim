#ifndef __LOCATION_HPP__
#define __LOCATION_HPP__

#include <cstdint>

enum class Orientation {
  North,
  South,
  East,
  West,
  NorthEast,
  NorthWest,
  SouthEast,
  SouthWest
};

class Location
{
public:
    Location();
    Location(uint32_t x, uint32_t y, Orientation orientation);
    Location(const Location&) = default;
    Location(Location&&) = default;
    void changeLocation(uint32_t x);
    void changeLocation(uint32_t x, uint32_t y);
    void changeLocation(uint32_t x, uint32_t y, Orientation orientation);
    void changeOrientation(Orientation orientation);
    inline uint32_t getX();
    inline uint32_t getY();
    inline Orientation getOrientation();

    bool operator==(const Location &);
    Location& operator=(Location &) & = default;
    Location& operator=(Location &&) && = default;

  private:
    uint32_t x, y;
    Orientation orientation;
};

#endif

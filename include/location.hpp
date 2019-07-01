#ifndef __LOCATION_HPP__
#define __LOCATION_HPP__

#include <cstdint>
#include <string>

class Location
{
public:
    Location();
    Location(uint64_t x, uint64_t y);
    Location(const Location&) = default;
    Location(Location&&) = default;
    void changeLocation(uint32_t x);
    void changeLocation(uint32_t x, uint32_t y);
    std::string toString() const;
    uint32_t getX() const;
    uint32_t getY() const;

    bool operator==(const Location &);
    bool operator<(const Location &) const;
    bool operator>(const Location &) const;
    Location& operator=(const Location &) = default;
    Location& operator=(Location &&) && = default;

  private:
    uint64_t x, y;
};

#endif

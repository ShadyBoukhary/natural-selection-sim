#include <iostream>
#include "organism.hpp"

int main(int argc, char** argv)
{
    std::shared_ptr<Organism> organism = std::make_shared<Organism>();

    State state(Location(1, 1, Orientation::NorthEast), 50, true);
    std::shared_ptr<Organism> organism1 =
        std::make_shared<Organism>(21.1, 5, TrophicLevel::Primary, state);

    organism->eat(organism1);

    std::cout << "Ref count of organism: " << organism.use_count() << "\n";
    std::cout << "Ref count of organism1: " << organism1.use_count() << "\n";
    std::cout << "Organism1 Alive: " << organism1->isAlive() << "\n";
    return 0;
}

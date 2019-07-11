#include "Character.h"
#include <iostream>

Character::Character() : root(nullptr), name(""), mass(0)
{

}

void Character::SetBones()
{
    std::cout << "Setting Bones" << std::endl;
}

inline void Character::SetName(std::string)
{
    this->name = name;
}

inline void Character::SetMass(float mass)
{
    this->mass = mass;
}

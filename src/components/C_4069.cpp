/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4069
*/

#include "C_4069.hpp"

C_4069::C_4069(std::string name):
    _name(name),
    _type("4069")
{
    for (int count = 0; count != 14; count++) {
        _pin[count] = nullptr;
        _linkedPinNum[count] = 0;
    }
}

C_4069::~C_4069()
{
}

nts::Tristate C_4069::compute(std::size_t pin)
{
    switch (pin) {
        case 2:
            return gate(_pin[0]->compute(_linkedPinNum[0]));
            break;
        case 4:
            return gate(_pin[2]->compute(_linkedPinNum[2]));
            break;
        case 6:
            return gate(_pin[4]->compute(_linkedPinNum[4]));
            break;
        case 8:
            return gate(_pin[8]->compute(_linkedPinNum[8]));
            break;
        case 10:
            return gate(_pin[10]->compute(_linkedPinNum[10]));
            break;
        case 12:
            return gate(_pin[12]->compute(_linkedPinNum[12]));
            break;
    }
    return (nts::FALSE); // not supposed to happen
}

void C_4069::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    _pin[pin - 1] = &other;
    _linkedPinNum[pin - 1] = otherPin;
}
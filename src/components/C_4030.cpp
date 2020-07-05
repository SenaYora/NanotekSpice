/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4030
*/

#include "C_4030.hpp"

C_4030::C_4030(std::string name):
    _name(name),
    _type("4030")
{
    for (int count = 0; count != 14; count++) {
        _pin[count] = nullptr;
        _linkedPinNum[count] = 0;
    }
}

C_4030::~C_4030()
{
}

nts::Tristate C_4030::compute(std::size_t pin)
{
    switch (pin) {
        case 3:
            return gate(_pin[0]->compute(_linkedPinNum[0]), _pin[1]->compute(_linkedPinNum[1]));
            break;
        case 4:
            return gate(_pin[4]->compute(_linkedPinNum[4]), _pin[5]->compute(_linkedPinNum[5]));
            break;
        case 10:
            return gate(_pin[7]->compute(_linkedPinNum[7]), _pin[8]->compute(_linkedPinNum[8]));
            break;
        case 11:
            return gate(_pin[11]->compute(_linkedPinNum[11]), _pin[12]->compute(_linkedPinNum[12]));
            break;
    }
    return (nts::FALSE); // not supposed to happen
}

void C_4030::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    _pin[pin - 1] = &other;
    _linkedPinNum[pin - 1] = otherPin;
}
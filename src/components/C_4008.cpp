/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4008
*/

#include "C_4008.hpp"

C_4008::C_4008(std::string name):
    _name(name),
    _type("4008")
{
    for (int count = 0; count != 16; count++) {
        _pin[count] = nullptr;
        _linkedPinNum[count] = 0;
    }
    for (int count = 0; count != 4; count++) {
        _carryOut[count] = nts::UNDEFINED;
    }
}

C_4008::~C_4008()
{
}

nts::Tristate C_4008::compute(std::size_t pin)
{
    switch (pin) {
        case 10:
            return (calculate(_pin[6]->compute(_linkedPinNum[6]), _pin[5]->compute(_linkedPinNum[5]), _pin[8]->compute(_linkedPinNum[8]), 0));
            break;
        case 11:
            compute(10);
            return (calculate(_pin[4]->compute(_linkedPinNum[4]), _pin[3]->compute(_linkedPinNum[3]), _carryOut[0], 1));
            break;
        case 12:
            compute(11);
            return (calculate(_pin[2]->compute(_linkedPinNum[2]), _pin[1]->compute(_linkedPinNum[1]), _carryOut[1], 2));
            break;
        case 13:
            compute(12);
            return (calculate(_pin[0]->compute(_linkedPinNum[0]), _pin[14]->compute(_linkedPinNum[14]), _carryOut[2], 3));
            break;
        case 14:
            compute(13);
            return (_carryOut[3]);
            break;
    }
    return (nts::FALSE); // not supposed to happen
}

nts::Tristate C_4008::calculate(nts::Tristate valueA, nts::Tristate valueB, nts::Tristate carryIn, int index)
{
    nts::Tristate result = G_XOR::gate(valueA, valueB);

    _carryOut[index] = G_OR::gate(G_AND::gate(result, carryIn), G_AND::gate(valueA, valueB));
    return (G_XOR::gate(result, carryIn));
}

void C_4008::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    _pin[pin - 1] = &other;
    _linkedPinNum[pin - 1] = otherPin;
}
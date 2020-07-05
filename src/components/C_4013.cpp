/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4013
*/

#include "C_4013.hpp"

C_4013::C_4013(std::string name):
    _name(name),
    _type("4013"),
    _flipflop{FlipFlop("1"), FlipFlop("2")}
{
    _flipflop[0].setValue(nts::FALSE);
    _flipflop[1].setValue(nts::FALSE);
    for (int count = 0; count != 14; count++) {
        _pin[count] = nullptr;
        _linkedPinNum[count] = 0;
    }
}

C_4013::~C_4013()
{
}

nts::Tristate C_4013::compute(std::size_t pin)
{
    switch (pin) {
        case 1:
            return (dualFlipFlop(
                _pin[6 - 1]->compute(_linkedPinNum[6 - 1]),
                _pin[4 - 1]->compute(_linkedPinNum[4 - 1]),
                _pin[3 - 1]->compute(_linkedPinNum[3 - 1]),
                _pin[5 - 1]->compute(_linkedPinNum[5 - 1]), 0, 0
            ));
        case 2:
            return (dualFlipFlop(
                _pin[6 - 1]->compute(_linkedPinNum[6 - 1]),
                _pin[4 - 1]->compute(_linkedPinNum[4 - 1]),
                _pin[3 - 1]->compute(_linkedPinNum[3 - 1]),
                _pin[5 - 1]->compute(_linkedPinNum[5 - 1]), 0, 1
            ));
        case 13:
            return (dualFlipFlop(
                _pin[8 - 1]->compute(_linkedPinNum[8 - 1]),
                _pin[10  -1]->compute(_linkedPinNum[10 - 1]),
                _pin[11 - 1]->compute(_linkedPinNum[11 - 1]),
                _pin[9 - 1]->compute(_linkedPinNum[9 - 1]), 1, 0
            ));
        case 12:
            return (dualFlipFlop(
                _pin[8 - 1]->compute(_linkedPinNum[8 - 1]),
                _pin[10  -1]->compute(_linkedPinNum[10 - 1]),
                _pin[11 - 1]->compute(_linkedPinNum[11 - 1]),
                _pin[9 - 1]->compute(_linkedPinNum[9 - 1]), 1, 1
            ));
    }
    return (nts::FALSE);
}

nts::Tristate C_4013::dualFlipFlop(nts::Tristate s, nts::Tristate r, nts::Tristate clock, nts::Tristate data, int index, int q)
{
    _flipflop[index].gate(s, r, clock, data);
    return (_flipflop[index].compute(q));
}

void C_4013::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    _pin[pin - 1] = &other;
    _linkedPinNum[pin - 1] = otherPin;
}
/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4514
*/

#include "C_4514.hpp"

C_4514::C_4514(std::string name):
    _name(name),
    _type("4040")
{
    for (int count = 0; count != 24; count++) {
        _pin[count] = nullptr;
        _linkedPinNum[count] = 0;
    }
}

C_4514::~C_4514() { }

nts::Tristate C_4514::compute(std::size_t pin)
{
    nts::Tristate input1 = _pin[1]->compute(_linkedPinNum[1]);
    nts::Tristate input2 = _pin[2]->compute(_linkedPinNum[2]);
    nts::Tristate input3 = _pin[20]->compute(_linkedPinNum[20]);
    nts::Tristate input4 = _pin[21]->compute(_linkedPinNum[21]);

    switch (pin) {
        case 11:
            return (static_cast<nts::Tristate>(!input1 && !input2 && !input3 && !input4));
        case 9:
            return (static_cast<nts::Tristate>(input1 && !input2 && !input3 && !input4));
        case 10:
            return (static_cast<nts::Tristate>(!input1 && input2 && !input3 && !input4));
        case 8:
            return (static_cast<nts::Tristate>(input1 && input2 && !input3 && !input4));
        case 7:
            return (static_cast<nts::Tristate>(!input1 && !input2 && input3 && !input4));
        case 6:
            return (static_cast<nts::Tristate>(input1 && !input2 && input3 && !input4));
        case 5:
            return (static_cast<nts::Tristate>(!input1 && input2 && input3 && !input4));
        case 4:
            return (static_cast<nts::Tristate>(input1 && input2 && input3 && !input4));
        case 18:
            return (static_cast<nts::Tristate>(!input1 && !input2 && !input3 && input4));
        case 17:
            return (static_cast<nts::Tristate>(input1 && !input2 && !input3 && input4));
        case 20:
            return (static_cast<nts::Tristate>(!input1 && input2 && !input3 && input4));
        case 19:
            return (static_cast<nts::Tristate>(input1 && input2 && !input3 && input4));
        case 14:
            return (static_cast<nts::Tristate>(!input1 && !input2 && input3 && input4));
        case 13:
            return (static_cast<nts::Tristate>(input1 && !input2 && input3 && input4));
        case 16:
            return (static_cast<nts::Tristate>(!input1 && input2 && input3 && input4));
        case 15:
            return (static_cast<nts::Tristate>(input1 && input2 && input3 && input4));
    }
    return (nts::FALSE);
}

void C_4514::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    _pin[pin - 1] = &other;
    _linkedPinNum[pin - 1] = otherPin;
}
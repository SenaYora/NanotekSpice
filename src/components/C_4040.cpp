/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4040
*/

#include "C_4040.hpp"

C_4040::C_4040(std::string name):
    _name(name),
    _type("4040"),
    _simulation(0),
    _counter(0),
    _output{
        nts::FALSE, nts::FALSE, nts::FALSE, nts::FALSE,
        nts::FALSE, nts::FALSE, nts::FALSE, nts::FALSE,
        nts::FALSE, nts::FALSE, nts::FALSE, nts::FALSE
    }
{
    for (int count = 0; count != 16; count++) {
        _pin[count] = nullptr;
        _linkedPinNum[count] = 0;
    }
}

C_4040::~C_4040() { }

nts::Tristate C_4040::compute(std::size_t pin)
{
    nts::Tristate clock = _pin[10 - 1]->compute(_linkedPinNum[10 - 1]);
    nts::Tristate reset = _pin[11 - 1]->compute(_linkedPinNum[11 - 1]);

    if (reset == nts::TRUE)
        _counter = 0;
    if (_simulation % 12 == 0 && clock == nts::FALSE) {
        _counter += 1;
        if (reset == nts::TRUE)
            _counter = 0;
        std::size_t bit_num = 11;
        for (std::size_t i = 1u << (12 - 1); i; i >>= 1, bit_num -= 1)
            _output[bit_num] = static_cast<nts::Tristate>(_counter & i ? 1 : 0);
    }
    _simulation += 1;
    switch (pin) {
        case 9 :
            return (_output[0]);
        case 7 :
            return (_output[1]);
        case 6 :
            return (_output[2]);
        case 5 :
            return (_output[3]);
        case 3 :
            return (_output[4]);
        case 2 :
            return (_output[5]);
        case 4 :
            return (_output[6]);
        case 13 :
            return (_output[7]);
        case 12 :
            return (_output[8]);
        case 14 :
            return (_output[9]);
        case 15 :
            return (_output[10]);
        case 1 :
            return (_output[11]);
    }
    return (nts::FALSE);
}

void C_4040::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    _pin[pin - 1] = &other;
    _linkedPinNum[pin - 1] = otherPin;
}
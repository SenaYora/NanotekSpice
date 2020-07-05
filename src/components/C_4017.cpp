/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4017
*/

#include "C_4017.hpp"

C_4017::C_4017(std::string name):
    _name(name),
    _type("4017"),
    _simulation(0),
    _counter(1),
    _output{
        nts::FALSE, nts::FALSE, nts::FALSE, nts::FALSE,
        nts::FALSE, nts::FALSE, nts::FALSE, nts::FALSE,
        nts::FALSE, nts::FALSE
    }
{
    for (int count = 0; count != 15; count++) {
        _pin[count] = nullptr;
        _linkedPinNum[count] = 0;
    }
}

C_4017::~C_4017() { }

nts::Tristate C_4017::compute(std::size_t pin)
{
    nts::Tristate masterReset = _pin[14]->compute(_linkedPinNum[14]);
    nts::Tristate clock = _pin[13]->compute(_linkedPinNum[13]);

    if (!(_simulation % 11) && clock == nts::TRUE) {
        _counter *= 2;
        if (masterReset == nts::TRUE || _counter >= 1024)
            _counter = 1;
    }
    std::size_t bit_num = 9;
    for (std::size_t i = 1u << (10 - 1); i; i >>= 1, bit_num -= 1)
        _output[bit_num] = static_cast<nts::Tristate>(_counter & i ? 1 : 0);
    _simulation += 1;
    switch (pin) {
        case 3 :
            return (_output[0]);
        case 2 :
            return (_output[1]);
        case 4 :
            return (_output[2]);
        case 7 :
            return (_output[3]);
        case 10 :
            return (_output[4]);
        case 1 :
            return (_output[5]);
        case 5 :
            return (_output[6]);
        case 6 :
            return (_output[7]);
        case 9 :
            return (_output[8]);
        case 11 :
            return (_output[9]);
        case 12 :
            return (static_cast<nts::Tristate>(_counter <= 16));
    }
    return (nts::FALSE);
}

void C_4017::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    _pin[pin - 1] = &other;
    _linkedPinNum[pin - 1] = otherPin;
}
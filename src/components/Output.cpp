/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Output
*/

#include "Output.hpp"

Output::Output(std::string name):
    _name(name),
    _type("Output")
{
    _pin[0] = nullptr;
    _linkedPinNum[0] = 0;
}

Output::~Output()
{
}

nts::Tristate Output::compute(std::size_t pin)
{
    if (!_pin[0])
        throw Errors("output named '" + _name + "' is not linked", "Link");
    if (pin == 1)
        return _pin[0]->compute(_linkedPinNum[0]);
    return (nts::FALSE);
}

void Output::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin - 1 != 0)
        throw Errors("pin '" + std::to_string(pin) + "' doesn't exist on Output component", "Link");
    _pin[pin - 1] = &other;
    _linkedPinNum[pin - 1] = otherPin;
}
/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_input
*/

#include "Input.hpp"

Input::Input(std::string name) :
    _name(name),
    _type("Input"),
    _value(nts::UNDEFINED)
{
    _pin[0] = nullptr;
}

Input::~Input()
{
}

void Input::setLink(std::size_t pin, __attribute__((unused)) nts::IComponent &other, __attribute__((unused)) std::size_t otherPin)
{
    if (pin - 1 != 0)
        throw Errors("pin '" + std::to_string(pin) + "' doesn't exist on Input component", "Link");
}

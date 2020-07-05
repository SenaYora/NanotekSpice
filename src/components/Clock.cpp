/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Clock
*/

#include "Clock.hpp"

Clock::Clock(std::string name):
    Input(name)
{
    _type = "Clock";
}

Clock::~Clock()
{
}

void Clock::invertValue()
{
    if (_value == nts::FALSE) {
        _value = nts::TRUE;
    } else
        _value = nts::FALSE;
}
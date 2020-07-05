/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** True
*/

#include "True.hpp"

True::True(std::string name):
    Input(name)
{
    _type = "True";
    _value = nts::TRUE;
}

True::~True()
{
}

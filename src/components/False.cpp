/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** False
*/

#include "False.hpp"

False::False(std::string name):
    Input(name)
{
    _type = "False";
    _value = nts::FALSE;
}

False::~False()
{
}

/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** G_XOR
*/

#include "G_XOR.hpp"

nts::Tristate G_XOR::gate(nts::Tristate valueA, nts::Tristate valueB)
{
    if (valueA == nts::UNDEFINED || valueB == nts::UNDEFINED)
        return (nts::UNDEFINED);
    if ((valueA == valueB))
        return (nts::FALSE);
    return (nts::TRUE);
}
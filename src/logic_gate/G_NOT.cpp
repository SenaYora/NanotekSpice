/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** G_NOT
*/

#include "G_NOT.hpp"

nts::Tristate G_NOT::gate(nts::Tristate valueA, __attribute__((unused)) nts::Tristate valueB)
{
    if (valueA == nts::UNDEFINED)
        return (nts::UNDEFINED);
    if (valueA == nts::FALSE)
        return (nts::TRUE);
    return (nts::FALSE);
}
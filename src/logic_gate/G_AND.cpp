/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** G_AND
*/

#include "G_AND.hpp"

nts::Tristate G_AND::gate(nts::Tristate valueA, nts::Tristate valueB)
{
    if (valueA == nts::UNDEFINED && valueB == nts::UNDEFINED)
        return (nts::UNDEFINED);
    if (valueA == nts::UNDEFINED) {
        if (valueB == nts::FALSE)
            return (nts::FALSE);
        return (nts::UNDEFINED);
    }
    if (valueB == nts::UNDEFINED) {
        if (valueA == nts::FALSE)
            return (nts::FALSE);
        return (nts::UNDEFINED);
    }
    if (valueA && valueB)
        return (nts::TRUE);
    return (nts::FALSE);
}
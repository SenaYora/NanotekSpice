/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** G_NOR
*/

#include "G_NOR.hpp"

nts::Tristate G_NOR::gate(nts::Tristate valueA, nts::Tristate valueB)
{
    if (valueA == nts::UNDEFINED && valueB == nts::UNDEFINED)
        return (nts::UNDEFINED);
    if (valueA == nts::UNDEFINED) {
        if (valueB == nts::FALSE)
            return (nts::UNDEFINED);
        return (nts::FALSE);
    }
    if (valueB == nts::UNDEFINED) {
        if (valueA == nts::FALSE)
            return (nts::UNDEFINED);
        return (nts::FALSE);
    }
    if (!(valueA || valueB))
        return (nts::TRUE);
    return (nts::FALSE);
}
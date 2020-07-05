/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** G_OR
*/

#include "G_OR.hpp"

nts::Tristate G_OR::gate(nts::Tristate valueA, nts::Tristate valueB)
{
    if (valueA == nts::UNDEFINED && valueB == nts::UNDEFINED)
        return (nts::UNDEFINED);
    if (valueA == nts::UNDEFINED) {
        if (valueB == nts::FALSE)
            return (nts::UNDEFINED);
        return (nts::TRUE);
    }
    if (valueB == nts::UNDEFINED) {
        if (valueA == nts::FALSE)
            return (nts::UNDEFINED);
        return (nts::TRUE);
    }
    if (valueA || valueB)
        return (nts::TRUE);
    return (nts::FALSE);
}
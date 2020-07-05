/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** G_NAND
*/

#include "G_NAND.hpp"

nts::Tristate G_NAND::gate(nts::Tristate valueA, nts::Tristate valueB)
{
    if (valueA == nts::UNDEFINED && valueB == nts::UNDEFINED)
        return (nts::UNDEFINED);
    if (valueA == nts::UNDEFINED) {
        if (valueB == nts::FALSE)
            return (nts::TRUE);
        return (nts::UNDEFINED);
    }
    if (valueB == nts::UNDEFINED) {
        if (valueA == nts::FALSE)
            return (nts::TRUE);
        return (nts::UNDEFINED);
    }
    if (!(valueA && valueB))
        return (nts::TRUE);
    return (nts::FALSE);
}

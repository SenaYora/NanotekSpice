/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** G_NAND
*/

#ifndef G_NAND_HPP_
#define G_NAND_HPP_

#include "ILogicGate.hpp"

class G_NAND : public ILogicGate {
    protected:
        nts::Tristate gate(nts::Tristate valueA, nts::Tristate valueB);
};

#endif /* !G_NAND_HPP_ */

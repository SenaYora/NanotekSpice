/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** G_XOR
*/

#ifndef G_XOR_HPP_
#define G_XOR_HPP_

#include "ILogicGate.hpp"

class G_XOR : public ILogicGate {
    protected:
        nts::Tristate gate(nts::Tristate valueA, nts::Tristate valueB);
};

#endif /* !G_XOR_HPP_ */

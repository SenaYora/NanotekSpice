/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** G_NOR
*/

#ifndef G_NOR_HPP_
#define G_NOR_HPP_

#include "ILogicGate.hpp"

class G_NOR : public ILogicGate {
    protected:
        nts::Tristate gate(nts::Tristate valueA, nts::Tristate valueB);
};

#endif /* !G_NOR_HPP_ */

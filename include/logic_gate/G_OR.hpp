/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** G_OR
*/

#ifndef G_OR_HPP_
#define G_OR_HPP_

#include "ILogicGate.hpp"

class G_OR : public ILogicGate {
    protected:
        nts::Tristate gate(nts::Tristate valueA, nts::Tristate valueB);
};

#endif /* !G_OR_HPP_ */

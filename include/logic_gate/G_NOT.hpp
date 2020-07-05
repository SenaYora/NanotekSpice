/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** G_NOT
*/

#ifndef G_NOT_HPP_
#define G_NOT_HPP_

#include "ILogicGate.hpp"

class G_NOT : public ILogicGate {
    protected:
        nts::Tristate gate(nts::Tristate valueA, nts::Tristate valueB = nts::UNDEFINED);
};

#endif /* !G_NOT_HPP_ */

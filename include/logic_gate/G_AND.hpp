/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** G_AND
*/

#ifndef G_AND_HPP_
#define G_AND_HPP_

#include "ILogicGate.hpp"

class G_AND : public ILogicGate {
    protected:
        nts::Tristate gate(nts::Tristate valueA, nts::Tristate valueB);
};

#endif /* !G_AND_HPP_ */

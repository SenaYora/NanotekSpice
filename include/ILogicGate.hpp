/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** ILogicGate
*/

#ifndef ILOGICGATE_HPP_
#define ILOGICGATE_HPP_

#include "IComponent.hpp"

class ILogicGate {
    public:
        virtual ~ILogicGate() = default;

        virtual nts::Tristate gate(nts::Tristate valueA, nts::Tristate valueB) = 0;
};

#endif /* !ILOGICGATE_HPP_ */

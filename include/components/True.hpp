/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** True
*/

#ifndef TRUE_HPP_
#define TRUE_HPP_

#include "Input.hpp"

class True : public Input {
    public:
        True(std::string);
        ~True();

        void dump() const { std::cout << "It's a " << _type << " component named: " << _name << " (" << _value << ")" << std::endl; }
        void setValue(__attribute__((unused)) nts::Tristate value) { throw Errors("cannot set value of a True component", "Input"); };
};

#endif /* !TRUE_HPP_ */

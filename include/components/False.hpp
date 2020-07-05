/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** False
*/

#ifndef FALSE_HPP_
#define FALSE_HPP_

#include "Input.hpp"

class False : public Input {
    public:
        False(std::string);
        ~False();

        void dump() const { std::cout << "It's a " << _type << " component named: " << _name << " (" << _value << ")" << std::endl; }
        void setValue(__attribute__((unused)) nts::Tristate value) { throw Errors("cannot set value of a False component", "Input"); };
};

#endif /* !FALSE_HPP_ */

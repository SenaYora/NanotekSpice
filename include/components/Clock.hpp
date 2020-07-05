/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include "Input.hpp"

class Clock : public Input {
    public:
        Clock(std::string);
        ~Clock();

        void dump() const { std::cout << "It's a " << _type << " component named: " << _name << " (" << _value << ")" << std::endl; }
        void invertValue();
};

#endif /* !CLOCK_HPP_ */

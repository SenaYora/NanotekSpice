/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** FlipFlop
*/

#ifndef FLIPFLOP_HPP_
#define FLIPFLOP_HPP_

#include "IComponent.hpp"
#include "G_NOT.hpp"

class FlipFlop : public nts::IComponent, public G_NOT {
    public:
        FlipFlop(std::string);
        ~FlipFlop();

        nts::Tristate compute(std::size_t pin = 1) { return _memory[pin]; };
        void setLink(__attribute__((unused))std::size_t pin, __attribute__((unused))nts::IComponent &other, __attribute__((unused))std::size_t otherPin) { };
        void dump() const { };
        virtual void setValue(nts::Tristate value);
        std::string const &getName() const { return _name; };

        void gate(nts::Tristate s, nts::Tristate r, nts::Tristate clock, nts::Tristate data);

    private:
        std::string _name;
        nts::Tristate _memory[2];
};

#endif /* !FLIPFLOP_HPP_ */

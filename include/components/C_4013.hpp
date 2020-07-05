/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4013
*/

#ifndef C_4013_HPP_
#define C_4013_HPP_

#include "FlipFlop.hpp"

class C_4013 : public nts::IComponent {
    public:
        C_4013(std::string);
        ~C_4013();

        nts::Tristate compute(std::size_t pin = 1);
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);
        void dump() const { std::cout << "It's a " << _type << " component named: " << _name << std::endl; }
        std::string const &getName() const { return _name; };

    protected:
    private:
        std::string _name;
        std::string _type;
        nts::IComponent *_pin[14];
        std::size_t _linkedPinNum[14];

        FlipFlop _flipflop[2];
        nts::Tristate dualFlipFlop(nts::Tristate s, nts::Tristate r, nts::Tristate clock, nts::Tristate data, int index, int q);
};

#endif /* !C_4013_HPP_ */

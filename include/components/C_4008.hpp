/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4008
*/

#ifndef C_4008_HPP_
#define C_4008_HPP_

#include "IComponent.hpp"
#include "G_XOR.hpp"
#include "G_AND.hpp"
#include "G_OR.hpp"

class C_4008 : public nts::IComponent, public G_XOR, public G_AND, public G_OR {
    public:
        C_4008(std::string name);
        ~C_4008();

        nts::Tristate compute(std::size_t pin = 1);
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);
        void dump() const { std::cout << "It's a " << _type << " component named: " << _name << std::endl; }
        std::string const &getName() const { return _name; };

    private:
        std::string _name;
        std::string _type;
        nts::IComponent *_pin[16];
        std::size_t _linkedPinNum[16];
        nts::Tristate _carryOut[4];

        nts::Tristate calculate(nts::Tristate, nts::Tristate, nts::Tristate, int);
};

#endif /* !C_4008_HPP_ */

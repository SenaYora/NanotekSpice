/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4030
*/


#ifndef C_4030_HPP_
#define C_4030_HPP_

#include "IComponent.hpp"
#include "G_XOR.hpp"

class C_4030 : public nts::IComponent, public G_XOR {
    public:
        C_4030(std::string);
        ~C_4030();

        nts::Tristate compute(std::size_t pin = 1);
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);
        void dump() const { std::cout << "It's a " << _type << " component named: " << _name << std::endl; }
        std::string const &getName() const { return _name; };

    private:
        std::string _name;
        std::string _type;
        nts::IComponent *_pin[14];
        std::size_t _linkedPinNum[14];
};

#endif /* !C_4030_HPP_ */

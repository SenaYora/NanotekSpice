/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4001
*/

#ifndef C_4001_HPP_
#define C_4001_HPP_

#include "IComponent.hpp"
#include "G_NOR.hpp"

class C_4001 : public nts::IComponent, public G_NOR {
    public:
        C_4001(std::string);
        ~C_4001();

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

#endif /* !C_4001_HPP_ */
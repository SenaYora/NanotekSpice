/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4514
*/

#ifndef C_4514_HPP_
#define C_4514_HPP_

#include "IComponent.hpp"

class C_4514 : public nts::IComponent {
    public:
        C_4514(std::string);
        ~C_4514();

        nts::Tristate compute(std::size_t pin = 1);
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);
        void dump() const { std::cout << "It's a " << _type << " component named: " << _name << std::endl; }
        std::string const &getName() const { return _name; };

    private:
        std::string _name;
        std::string _type;

        nts::Tristate _output[16];
        nts::IComponent *_pin[24];
        std::size_t _linkedPinNum[24];
};

#endif /* !C_4514_HPP_ */

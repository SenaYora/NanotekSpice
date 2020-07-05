/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Input
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include "IComponent.hpp"

class Input : public nts::IComponent {
    public:
        Input(std::string);
        ~Input();

        nts::Tristate compute(__attribute__((unused)) std::size_t pin = 1) { return (_value); };
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);
        void dump() const { std::cout << "It's an " << _type << " component named: " << _name << " (" << _value << ")" << std::endl; }
        virtual void setValue(nts::Tristate value) { _value = value; };
        std::string const &getName() const { return _name; };

    protected:
        std::string _name;
        std::string _type;
        nts::IComponent *_pin[1];
        nts::Tristate _value;
};

#endif /* !INPUT_HPP_ */
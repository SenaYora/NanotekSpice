/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4040
*/

#ifndef C_4040_HPP_
#define C_4040_HPP_

#include "IComponent.hpp"

class C_4040 : public nts::IComponent {
    public:
        C_4040(std::string);
        ~C_4040();

        nts::Tristate compute(std::size_t pin = 1);
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);
        void dump() const { std::cout << "It's a " << _type << " component named: " << _name << std::endl; }
        std::string const &getName() const { return _name; };

    private:
        std::string _name;
        std::string _type;
        std::size_t _simulation;
        std::size_t _counter;

        nts::Tristate _output[12];
        nts::IComponent *_pin[16];
        std::size_t _linkedPinNum[16];
};

#endif /* !C_4040_HPP_ */

/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4017
*/

#ifndef C_4017_HPP_
#define C_4017_HPP_

#include "IComponent.hpp"

class C_4017 : public nts::IComponent {
    public:
        C_4017(std::string);
        ~C_4017();

        nts::Tristate compute(std::size_t pin = 1);
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);
        void dump() const { std::cout << "It's a " << _type << " component named: " << _name << std::endl; }
        std::string const &getName() const { return _name; };

    private:
        std::string _name;
        std::string _type;
        std::size_t _simulation;
        std::size_t _counter;

        nts::Tristate _output[10];
        nts::IComponent *_pin[15];
        std::size_t _linkedPinNum[15];
};

#endif /* !C_4017_HPP_ */

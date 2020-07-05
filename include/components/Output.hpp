/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Output
*/

#ifndef OUTPUT_HPP_
#define OUTPUT_HPP_

#include "IComponent.hpp"

class Output : public nts::IComponent {
    public:
        Output(std::string);
        ~Output();

        nts::Tristate compute(std::size_t pin = 1);
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);
        void dump() const { std::cout << "It's a " << _type << " component named: " << _name << std::endl; };
        std::string const &getName() const { return _name; };

    private:
        std::string _name;
        std::string _type;
        nts::IComponent *_pin[1];
        std::size_t _linkedPinNum[1];
};

#endif /* !OUTPUT_HPP_ */

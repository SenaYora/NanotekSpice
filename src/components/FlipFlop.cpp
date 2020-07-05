/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** FlipFlop
*/

#include "FlipFlop.hpp"

FlipFlop::FlipFlop(std::string name) : _name(name)
{
    _memory[0] = nts::UNDEFINED;
    _memory[1] = nts::UNDEFINED;
}

FlipFlop::~FlipFlop() { }

void FlipFlop::gate(nts::Tristate s, nts::Tristate r, nts::Tristate clock, nts::Tristate data)
{
    if (s == nts::TRUE || r == nts::TRUE) {
        _memory[0] = s;
        _memory[1] = r;
    } else {
        if (clock == nts::TRUE) {
            _memory[0] = data;
            _memory[1] = G_NOT::gate(data);
        }
    }
}

void FlipFlop::setValue(nts::Tristate value)
{
    _memory[0] = value;
    _memory[1] = G_NOT::gate(value);
}
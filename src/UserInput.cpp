/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** UserInput
*/

#include "UserInput.hpp"

namespace nts {
    namespace loop {
        bool _is_looping = false;
        void stopLoop(__attribute__((unused))int dummy) { _is_looping = false; };
    }
}

UserInput::UserInput(char const *argv[]) :
    _is_running(true),
    _parser(std::make_unique<Parser>(argv[0] ? argv[0] : ""))
{
    _parser->startParsing(argv);
}

UserInput::~UserInput() { }

void UserInput::run()
{
    std::string input;

    simulate();
    display();
    while (_is_running) {
        displayPrompt();
        std::getline(std::cin, input);
        computeInput(input);
    }
}

void UserInput::computeInput(std::string input)
{
    if (std::cin.eof() || input == "exit")
        exit();
    else if (input == "simulate")
        simulate();
    else if (input == "loop")
        loop();
    else if (input == "display")
        display();
    else if (input == "dump")
        dump();
    else
        other(input);
}

void UserInput::simulate()
{
    _parser->computeOutput();
    _parser->changeClock();
}

void UserInput::loop()
{
    nts::loop::_is_looping = true;
    signal(SIGINT, nts::loop::stopLoop);

    while (nts::loop::_is_looping) simulate();
}

void UserInput::display() const
{
    _parser->displayOutput();
}

void UserInput::dump() const
{
    _parser->dump();
}

void UserInput::other(std::string input)
{
    _parser->parseInput(input);
}

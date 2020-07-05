/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** UserInput
*/

#ifndef USERINPUT_HPP_
#define USERINPUT_HPP_

#include <iostream>
#include <csignal>
#include <regex>
#include "Parser.hpp"

class UserInput {
    public:
        UserInput(char const *argv[]);
        ~UserInput();

        void displayPrompt() const { std::cout << "> "; };

        void run();
        void exit() { _is_running = false; };
        void computeInput(std::string);
        void simulate();
        void loop();
        void display() const;
        void dump() const;
        void other(std::string input);

    private:
        bool _is_running;
        std::unique_ptr<Parser> _parser;
};

#endif /* !USERINPUT_HPP_ */

/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <map>
#include <algorithm>

#include "Errors.hpp"
#include "True.hpp"
#include "False.hpp"
#include "Clock.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "C_4001.hpp"
#include "C_4008.hpp"
#include "C_4011.hpp"
#include "C_4013.hpp"
#include "C_4017.hpp"
#include "C_4030.hpp"
#include "C_4040.hpp"
#include "C_4069.hpp"
#include "C_4071.hpp"
#include "C_4081.hpp"
#include "C_4514.hpp"

#define VOID_REGEX "^[ \t]*(#+.*)*\n$"
#define HEAD_REGEX(c) (Parser::strcat_inc("^\\.", c, ":[ \t]*(#+.*)*\n$"))
#define INIT_REGEX "^[ \t]*[a-zA-Z0-9_]+[ \t]+[a-zA-Z0-9_]+[ \t]*(#+.*)*\n$"
#define LINK_REGEX "^[ \t]*[a-zA-Z0-9_]+:([0-9]{1}|[12]{1}[0-9]{1})[ \t]+[a-zA-Z0-9_]+:([0-9]{1}|[12]{1}[0-9]{1})[ \t]*(#+.*)*\n$"
#define INPUT_REGEX "^[ \t]*([a-zA-Z0-9_]+)=(0*[01]{1})$"

namespace nts {
    template<typename T>
    std::unique_ptr<nts::IComponent> createTypedComponent(std::string const &value)
    {
        return (std::make_unique<T>(value));
    }
}

class Parser {
    public:
        Parser(std::string const &filename);
        ~Parser();

        void startParsing(const char *inputs[]);
        void parseInput(std::string input);
        void parseLine(std::string const &line);
        void parseChipsets(std::string const &line);
        void parseLinks(std::string const &line);

        nts::IComponent *getComponent(std::string const &name);
        std::unique_ptr<nts::IComponent> createComponent(std::string const &type, std::string const &value);

        void changeClock();
        void computeOutput();
        void displayOutput() const;
        void dump() const;

        void setInput(std::string name, nts::Tristate value);

        // Static inline to define Regex
        static std::string strcat_inc(const std::string &str, const std::string &str2, const std::string &str3) { return str + str2 + str3; };

    private:
        std::string _filename;
        std::string _step;
        std::vector<std::unique_ptr<nts::IComponent>> _circuit;
        std::map<std::string, nts::Tristate> _output;
};

#endif /* !PARSER_HPP_ */

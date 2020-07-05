/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Parser
*/

#include "Parser.hpp"

Parser::Parser(std::string const &filename) :
    _filename(filename), _step("null")
    { }

Parser::~Parser() { }

std::unique_ptr<nts::IComponent> Parser::createComponent(std::string const &type, std::string const &value)
{
    if (type.compare("true") == 0)
        return (nts::createTypedComponent<True>(value));
    if (type.compare("false") == 0)
        return (nts::createTypedComponent<False>(value));
    if (type.compare("clock") == 0)
        return (nts::createTypedComponent<Clock>(value));
    if (type.compare("input") == 0)
        return (nts::createTypedComponent<Input>(value));
    if (type.compare("output") == 0)
        return (nts::createTypedComponent<Output>(value));
    if (type.compare("4001") == 0)
        return (nts::createTypedComponent<C_4001>(value));
    if (type.compare("4008") == 0)
        return (nts::createTypedComponent<C_4008>(value));
    if (type.compare("4011") == 0)
        return (nts::createTypedComponent<C_4011>(value));
    if (type.compare("4013") == 0)
        return (nts::createTypedComponent<C_4013>(value));
    if (type.compare("4017") == 0)
        return (nts::createTypedComponent<C_4017>(value));
    if (type.compare("4030") == 0)
        return (nts::createTypedComponent<C_4030>(value));
    if (type.compare("4040") == 0)
        return (nts::createTypedComponent<C_4040>(value));
    if (type.compare("4069") == 0)
        return (nts::createTypedComponent<C_4069>(value));
    if (type.compare("4071") == 0)
        return (nts::createTypedComponent<C_4071>(value));
    if (type.compare("4081") == 0)
        return (nts::createTypedComponent<C_4081>(value));
    if (type.compare("4514") == 0)
        return (nts::createTypedComponent<C_4514>(value));
    return (nullptr);
}

void Parser::setInput(std::string name, nts::Tristate value)
{
    for (auto it = _circuit.begin(); it != _circuit.end(); it++)
        if ((*it)->getName().compare(name) == 0 && dynamic_cast<Input *>(it->get())) {
            dynamic_cast<Input *>(it->get())->setValue(value);
            return;
        }
    throw Errors("a provided input '" + name + "' is unknown", "Input");
}

void Parser::parseInput(std::string input)
{
    std::basic_regex<char> inputReg(INPUT_REGEX);
    std::smatch matches;
    std::string input_name;
    nts::Tristate input_value;

    if (!std::regex_search(input, matches, static_cast<std::basic_regex<char>>("=")))
        return;
    input_name = matches.prefix();
    input_value = static_cast<nts::Tristate>(std::stoi(matches.suffix()));
    setInput(input_name, input_value);
}

void Parser::startParsing(const char *inputs[])
{
    std::basic_regex<char> void_reg(VOID_REGEX);
    std::ifstream file(_filename);

    if (!file.is_open())
        throw Errors("file cannot be open", "Open");
    for (std::string line; std::getline(file, line, '\n');) {
        if (std::regex_match(line + "\n", void_reg))
            continue;
        parseLine(line + "\n");
    }
    if (!_step.compare("null"))
        throw Errors("no .chipsets section found", "Parsing");
    for (std::size_t i = 1; inputs[i]; i++)
        parseInput(inputs[i]);
    for (auto it = _circuit.begin(); it != _circuit.end(); it++)
        if (dynamic_cast<Input *>(it->get()) && (*it)->compute() == nts::UNDEFINED)
            throw Errors("One or several input values are not provided", "Input");
}

nts::IComponent *Parser::getComponent(std::string const &name)
{
    for (auto it = _circuit.begin(); it != _circuit.end(); it++)
        if ((*it)->getName().compare(name) == 0)
            return (it->get());
    return (nullptr);
}

void Parser::parseLine(std::string const &line)
{
    if (!_step.compare("null") && std::regex_match(line, std::basic_regex<char> (HEAD_REGEX("chipsets")))) {
        _step = "chipsets";
    } else if (!_step.compare("chipsets")) {
        std::basic_regex<char> reg(HEAD_REGEX("links"));
        if (std::regex_match(line, reg))
            _step = "links";
        else
            parseChipsets(line);
    } else if (!_step.compare("links")) {
        parseLinks(line);
    }
}

void Parser::parseChipsets(std::string const &line)
{
    std::string type;
    std::string name;
    std::stringstream str(line);

    str >> type >> name;
    if (type.find(":") != std::string::npos)
        throw Errors("no .links section found", "Parsing");
    if (!std::regex_match(line, std::basic_regex<char>(INIT_REGEX)))
        throw Errors("one or several chipsets contain a syntax error", "Syntax");
    for (auto it = _circuit.begin(); it != _circuit.end(); it++)
        if ((*it)->getName().compare(name) == 0)
            throw Errors("several components share the same name : " + name, "Parsing");
    if (!createComponent(type, name))
        throw Errors("component '" + type + "' doesn't exist", "Parsing");
    _circuit.push_back(createComponent(type, name));
}

void Parser::parseLinks(std::string const &line)
{
    std::smatch m;

    if (!std::regex_match(line, std::basic_regex<char>(LINK_REGEX)))
        throw Errors("one or several links contain a syntax error", "Syntax");
    std::regex_search(line, m, std::basic_regex<char>("[ \t]+"));

    std::string link1 = m.prefix();
    std::string link2 = m.suffix();

    std::regex_search(link1, m, std::basic_regex<char>(":"));
    nts::IComponent *ptr1 = getComponent(m.prefix());
    std::size_t pin1 = std::stoi(m.suffix());
    if (!ptr1)
        throw Errors("component name '" + std::string(m.prefix()) + "' is unknown", "Link");

    std::regex_search(link2, m, std::basic_regex<char>(":"));
    nts::IComponent *ptr2 = getComponent(m.prefix());
    std::size_t pin2 = std::stoi(m.suffix());
    if (!ptr2)
        throw Errors("component name '" + std::string(m.prefix()) + "' is unknown", "Link");

    ptr1->setLink(pin1, *ptr2, pin2);
    ptr2->setLink(pin2, *ptr1, pin1);
}

void Parser::changeClock()
{
    for (auto it = _circuit.begin(); it != _circuit.end(); it++)
        if (dynamic_cast<Clock *>(it->get()))
            dynamic_cast<Clock *>(it->get())->invertValue();
}

void Parser::computeOutput()
{
    _output.clear();
    for (auto it = _circuit.begin(); it != _circuit.end(); it++)
        if (dynamic_cast<Output *>(it->get()))
            _output.insert(
                std::pair<std::string, nts::Tristate>(
                    dynamic_cast<Output *>(it->get())->getName(),
                    dynamic_cast<Output *>(it->get())->compute()
                )
            );
}

void Parser::displayOutput() const
{
    std::for_each(
        _output.begin(),
        _output.end(),
        [](std::pair<std::string, nts::Tristate> p) {
            if (p.second == nts::UNDEFINED)
                std::cout <<  p.first << "=" << "U" << std::endl;
            else
                std::cout <<  p.first << "=" << static_cast<int>(p.second) << std::endl;
        }
    );
}

void Parser::dump() const
{
    for (auto it = _circuit.begin(); it != _circuit.end(); it++)
        (*it)->dump();
    // std::for_each(_circuit.begin(), _circuit.end(), [](std::unique_ptr<nts::IComponent> c) { c->dump(); });
}
/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** main
*/

#include "IComponent.hpp"
#include "UserInput.hpp"

int main(__attribute__((unused))int argc, char const *argv[])
{
    try {
        UserInput user(argv + 1);
        user.run();
    } catch (Errors const &e) {
        std::cout
            << "[Error] - "
            << e.getType() << " error has occured : "
            << e.what() << std::endl;
    }
    return (0);
}

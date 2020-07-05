/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Error
*/

#ifndef ERRORS_HPP_
#define ERRORS_HPP_

#include <iostream>

class Errors : public std::exception {
    public:
        Errors(std::string const &message, std::string const &type);

        const std::string &getType() const { return _type; };
        const char *what() const noexcept override { return _message.data(); };

    private:
        std::string _message;
        std::string _type;
};

#endif /* !ERRORS_HPP_ */

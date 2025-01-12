//
// Created by ionut on 16.12.2024.
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

////////// INCLUDE SECTION //////////
#include <stdexcept>
#include <string>

////////// DESCRIPTION //////////

/// this class will manage the exceptions

////////// DEFINITION OF CLASS //////////
class standard_error : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class loading_error : public standard_error {
public:
    explicit loading_error(const std::string &msg);
};

class file_error : public loading_error {
public:
    explicit file_error(const std::string &msg);
};

class typing_error : public loading_error {
public:
    explicit typing_error(const std::string &msg);
};

#endif //EXCEPTIONS_H

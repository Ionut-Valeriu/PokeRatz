//
// Created by ionut on 16.12.2024.
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class loading_error : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class asset_error : public loading_error {
public:
    explicit asset_error(const std::string &name);
};


#endif //EXCEPTIONS_H

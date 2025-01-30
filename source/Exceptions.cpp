//
// Created by ionut on 16.12.2024.
//

#include "Exceptions.h"

loading_error::loading_error(const std::string &msg)
    : game_error("Loading error: " + msg + "\n") {
}

file_error::file_error(const std::string &msg)
    : loading_error("File error:\n" + msg) {
}

typing_error::typing_error(const std::string &msg)
    : loading_error("Typing error:\n" + msg) {
}

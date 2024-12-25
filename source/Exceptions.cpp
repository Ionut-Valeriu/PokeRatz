//
// Created by ionut on 16.12.2024.
//

#include "Exceptions.h"

asset_error::asset_error(const std::string &name)
    : loading_error("Unknown Asset Type: " + name) {
}

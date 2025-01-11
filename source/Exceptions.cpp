//
// Created by ionut on 16.12.2024.
//

#include "Exceptions.h"

config_error::config_error(const std::string &msg)
    : loading_error("Unknown configuration command: " + msg
                    + "\nSee \"resources/config/config.txt\"\n") {
}

asset_error::asset_error(const std::string &name)
    : loading_error("Unknown Asset Type: " + name +
        + "\nSee \"resources/config/assets.txt\"\n") {
}

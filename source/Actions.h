//
// Created by ionut on 23.10.2024.
//

#ifndef ACTIONS_H
#define ACTIONS_H
#include <string>


class Actions {
    std::string m_name = "NONE";
    std::string m_type = "NONE";

public:

    Actions();
    Actions(std::string name, std::string type);

    const std::string& name() const { return m_name; }
    const std::string& type() const { return m_type; }
};



#endif //ACTIONS_H

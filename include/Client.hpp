#pragma once
#include <string>

class Client {
public:
    Client() = default;
    Client(const std::string&& _name);

    std::string getName() const;
private:
    std::string name;
};
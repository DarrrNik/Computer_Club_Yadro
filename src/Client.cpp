#include "Client.hpp"

Client::Client(const std::string&& _name) : name(_name) {}

std::string Client::getName() const { return name; }
#pragma once

#include <memory>

#include "Client.hpp"

class ComputerTable {
public:
    ComputerTable() = default;
    ComputerTable(unsigned int num, const std::string name);

    void changeClient(const std::shared_ptr<Client> cl);

    void setNumber(unsigned int num);
    bool isBusy() const;
    std::shared_ptr<const Client> getClient() const;
private:
    std::shared_ptr<Client> client;
    unsigned int number;
    bool busy;
};
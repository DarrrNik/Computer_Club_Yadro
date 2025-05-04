#include <utility>

#include "ComputerTable.hpp"

ComputerTable::ComputerTable(unsigned int num, const std::string name = std::string())
    : number(num), client(new Client(std::move(name))), busy(false) {}

void ComputerTable::changeClient(const std::shared_ptr<Client> cl) { 
    busy = cl->getName() != ""; 
    client = cl; 
}

ComputerTable& ComputerTable::setNumber(unsigned int num) { number = num; }
bool ComputerTable::isBusy() const { return busy; }
std::shared_ptr<const Client> ComputerTable::getClient() const { return client; }
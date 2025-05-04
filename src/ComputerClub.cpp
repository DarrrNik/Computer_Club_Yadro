#include <vector>
#include <functional>
#include <algorithm>

#include "ComputerClub.hpp"

const std::array<std::string, ComputerClub::NUM_OF_ERRORS> ComputerClub::errors = { 
    "YouShallNotPass", "NotOpenYet", "PlaceIsBusy", "ClientUnknown", "ICanWaitNoLonger!"
};

ComputerClub::ComputerClub(std::size_t numOfTables, Time begin, Time end) 
    : tables(std::vector<Table>(numOfTables)), tBegin(begin), 
        tEnd(end), clQueue() 
{
    for (int t = 1; t <= numOfTables; ++t)
        tables[t - 1].setNumber(t);
}

void ComputerClub::request(const Request req) {
    void (ComputerClub::* reqHandler)(const Request&) = ComputerClub::reqOutError;
    switch (std::get<reqIncomeEvent>(req)) {
        case InClientHasCome:
            reqHandler = ComputerClub::reqInClientHasCome;
        break;
        case InClientHasSat:
            reqHandler = ComputerClub::reqInClientHasSat;
        break;
        case InClientIsWaiting:
            reqHandler = ComputerClub::reqInClientIsWaiting;
        break;
        case InClientHasLeft:
            reqHandler = ComputerClub::reqInClientHasLeft;
        break;
    }
    (this->*reqHandler)(req);
}

void ComputerClub::reqInClientHasCome(const Request& req) {
    std::cout << std::get<reqTime>(req) << ' '
        << std::get<reqIncomeEvent>(req) << ' '
        << std::get<reqName>(req) << std::endl;

    int countSame = std::count_if(clients.begin(), clients.end(), [&req](const std::shared_ptr<Client> cl) {
        return cl->getName() == std::get<reqName>(req);
    });

    if (countSame != 0 || std::get<reqTime>(req) < tBegin) {
        Request outReq = req;
        std::get<reqErrors>(outReq) = (countSame != 0) ? (Errors::YouShallNotPass) : (Errors::NotOpenYet);
        std::get<reqIncomeEvent>(outReq) = IncomeEvent::InNoEvent;
        reqOutError(outReq);
        return;
    }

    std::string name = std::get<reqName>(req);
    clients.insert(std::shared_ptr<Client>(new Client(std::move(name))));
}
void ComputerClub::reqInClientHasSat(const Request& req) {
    std::cout << std::get<reqTime>(req) << ' '
        << std::get<reqIncomeEvent>(req) << ' '
        << std::get<reqName>(req) << ' '
        << std::get<reqTableNum>(req) << std::endl;

    auto countCl = std::find_if(clients.begin(), clients.end(), [&req](const std::shared_ptr<Client>& cl) {
        return cl->getName() == std::get<reqName>(req);
    });

    if (tables[std::get<reqTableNum>(req) - 1].isBusy() || countCl == clients.end()) {
        Request outReq = req;
        std::get<reqErrors>(outReq) = (countCl == clients.end()) ? (Errors::ClientUnknown) : (Errors::PlaceIsBusy);
        std::get<reqIncomeEvent>(outReq) = IncomeEvent::InNoEvent;
        reqOutError(outReq);
        return;
    }

    tables[std::get<reqTableNum>(req) - 1].changeClient(*countCl);
}
void ComputerClub::reqInClientIsWaiting(const Request& req) {
    auto clPlace = std::find_if(tables.begin(), tables.end(), [&req](const Table& t){
        return std::get<reqName>(req) == t.getClient()->getName();
    });
    if (clPlace == tables.end())
        return;

    int countFree = std::count_if(tables.begin(), tables.end(), [&req](const Table& t) {
        return t.isBusy();
    });

    if (countFree != 0) {
        Request outReq = req;
        std::get<reqErrors>(outReq) = Errors::ICanWaitNoLonger;
        std::get<reqIncomeEvent>(outReq) = IncomeEvent::InNoEvent;
        reqOutError(outReq);
        return;
    }
    if (clQueue.size() >= tables.size()) {
        Request outReq = req;
        std::get<reqIncomeEvent>(outReq) = IncomeEvent::InNoEvent;
        reqOutClientHasLeft(outReq);
    }

}
void ComputerClub::reqInClientHasLeft(const Request& req) {

}

void ComputerClub::reqOutClientHasLeft(const Request& req) {
    std::cout << std::get<reqTime>(req) << ' '
        << static_cast<int>(OutcomeEvent::OutClientHasLeft) << ' '
        << std::get<reqName>(req) << std::endl;
}
void ComputerClub::reqOutOutClientHasSat(const Request& req) {

}
void ComputerClub::reqOutError(const Request& req) {
    std::cout << std::get<reqTime>(req) << ' ' 
        << static_cast<int>(OutcomeEvent::OutError) << ' '
        << errors[static_cast<int>(std::get<reqErrors>(req))] << std::endl;
}

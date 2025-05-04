#pragma once

#include <vector>
#include <array>
#include <tuple>
#include <set>
#include <queue>

#include "ComputerTable.hpp"
#include "Time.hpp"

class ComputerClub {
public:
    enum IncomeEvent { InClientHasCome = 0, InClientHasSat, InClientIsWaiting, InClientHasLeft, InNoEvent };
    enum OutcomeEvent { OutClientHasLeft = 11, OutClientHasSat, OutError, OutNoEvent};
    enum Errors {YouShallNotPass = 0, NotOpenYet, PlaceIsBusy, ClientUnknown, ICanWaitNoLonger};

    using Table = ComputerTable;

    using Request = std::tuple<Time, IncomeEvent, Errors, std::string, int>;
    enum ReqPoitions { reqTime = 0, reqIncomeEvent, reqErrors, reqName, reqTableNum };

    ComputerClub(std::size_t numOfTables, Time begin, Time end);
    
    void request(const Request req);

    static const std::size_t NUM_OF_ERRORS = 5;
    static const std::array<std::string, NUM_OF_ERRORS> errors;
private:
    void reqInClientHasCome(const Request& req);
    void reqInClientHasSat(const Request& req);
    void reqInClientIsWaiting(const Request& req);
    void reqInClientHasLeft(const Request& req);

    void reqOutClientHasLeft(const Request& req);
    void reqOutOutClientHasSat(const Request& req);
    void reqOutError(const Request& req);

    std::vector<Table> tables;
    std::set<std::shared_ptr<Client>> clients;
    std::queue<std::shared_ptr<Client>> clQueue;
    Time tBegin, tEnd;
};

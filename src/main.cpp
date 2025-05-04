#include <iostream>
#include <utility>
#include <tuple>

#include "Time.hpp"
#include "ComputerClub.hpp"

int main() {
    int tablesNum;
    Time begin, end;
    std::cin >> tablesNum;
    std::cin >> begin >> end;

    ComputerClub club(tablesNum, begin, end);

    while (true) {
        ComputerClub::Request req;
        int evId;

        std::cin >> std::get<ComputerClub::reqTime>(req) 
            >> evId 
            >> std::get<ComputerClub::reqName>(req);
        std::get<ComputerClub::reqIncomeEvent>(req) = ComputerClub::IncomeEvent(evId);
        if (ComputerClub::IncomeEvent(evId) == ComputerClub::InClientHasSat)
            std::cin >> std::get<ComputerClub::reqTableNum>(req);

        club.request(req);
    }
}
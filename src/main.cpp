#include <iostream>
#include <fstream>
#include <utility>
#include <tuple>

#include "Time.hpp"
#include "ComputerClub.hpp"

int main(int argc, char** argv) {
    std::ifstream fin(argv[1]);
    if (!fin) {
        fin.close(); 
        std::cout << "File with such name does not exist." << std::endl;
        return 0;
    }

    int tablesNum;
    Time begin, end;
    fin >> tablesNum;
    fin >> begin >> end;

    ComputerClub club(tablesNum, begin, end);

    while (!fin.eof()) { 
        ComputerClub::Request req;
        int evId;

        fin >> std::get<ComputerClub::reqTime>(req) 
            >> evId 
            >> std::get<ComputerClub::reqName>(req);
        std::get<ComputerClub::reqIncomeEvent>(req) = ComputerClub::IncomeEvent(evId);
        if (ComputerClub::IncomeEvent(evId) == ComputerClub::InClientHasSat)
            fin >> std::get<ComputerClub::reqTableNum>(req);

        club.request(req);
    }
}
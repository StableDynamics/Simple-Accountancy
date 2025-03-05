// Simple Accountancy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "BankStatement.h"

int main(int argc, char* argv[])
{
    // Program takes in the filename at launch in the format of "path\filename.csv"
    // Error check inputs
    if (argc < 2)
    {
        std::cerr << "Program has not been supplied enough arguments. Have you given it the location"
            " of a file?" << std::endl;
    }

    // Loop through all the files that were supplied
    for (size_t i = 1; i < argc; i++)
    {
        std::string fname{ argv[i] };

        // Create AccountData class object for supplied file
        try
        {
            BankStatement statement(fname);

            std::cout << "Created class from " << fname << "\n\n";
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return -1;
        }
    }
	return 0;
}

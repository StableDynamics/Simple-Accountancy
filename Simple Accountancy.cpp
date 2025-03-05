// Simple Accountancy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "BankStatement.h"

int main(int argc, char* argv[])
{
    // Program takes in the filename at launch in the format of "filename.exe" "path\filename.csv"	
    // TO DO Check that it has the right number of launch inputs
    // TO DO Check that it is a csv file
    for (size_t i = 1; i < argc; i++)
    {
        std::string fname{ argv[i] };

        // Create AccountData class object for supplied file
        BankStatement statement(fname);
    }
    
    std::cout << "Hello World!\n";
}

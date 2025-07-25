
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "BankStatement.h"
#include "GlobalDiscriminatorConfiguration.h"

#ifdef _WIN32
#include "Windows_SelectFiles.h"
#endif // _WIN32


int main(int argc, char* argv[])
{    
    try
    {
        // load config data
        globalDiscriminatorConfiguration.load();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    // Program takes in the filename at launch in the format of "path\filename.csv" or through a user selection
    std::vector<std::string> filePathVec;

    // Error check inputs
    if (argc < 2)
    {
#ifdef _WIN32
        // Open file explorer
        try
        {
            filePathVec = getCSV();
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return -1;
        }
#else
        std::cerr << "Program has not been supplied enough arguments. Have you given it the location"
            " of a file?" << std::endl;
        return -1;
#endif
    }
    else
    {
        for (size_t i = 1; i < argc; i++)
        {
            filePathVec.emplace_back(argv[i]);
        }
    }
	
	// Create vectors of class objects
	std::vector<BankStatement> bankStatementsVec;
    int idx{ 0 };

    // Loop through all the files that were supplied
    for (auto fname : filePathVec)
    {
        // Create class objects for supplied file
        try
        {
            bankStatementsVec.emplace_back(fname);

            std::cout << "Created class from " << fname << std::endl << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return -1;
        }

        // Print Summary
        bankStatementsVec[idx].printStatementSummary();
		bankStatementsVec[idx].printPerMonthDetails();
        idx += 1;
    }

    std::cout << "Finished processing all files" << std::endl << std::endl;

	std::cout << "Press enter to exit..." << std::endl;
    std::cin.get();

	return 0;
}

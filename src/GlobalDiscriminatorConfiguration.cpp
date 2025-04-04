#include "GlobalDiscriminatorConfiguration.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ItemType.h"

using json = nlohmann::json;

// Default values
int GlobalDiscriminatorConfiguration::initCount;
GlobalDiscriminatorConfiguration::impl* GlobalDiscriminatorConfiguration::pimpl;
std::array <std::string, (static_cast<int>(IncomeOrExpense::maxIncomeOrExpense) + 1)> GlobalDiscriminatorConfiguration::accptdIorEVals;

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Public functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GlobalDiscriminatorConfiguration::GlobalDiscriminatorConfiguration()
{
    // record number of source files which instanciate a GlobalDiscriminatorConfiguration
    ++initCount;

    // Set accepted IorE values if not set already
    if (accptdIorEVals[0] == "")
    {
        size_t idx = 0;
        for (auto iOrE : IncomeOrExpense::enumData)
        {
            accptdIorEVals[idx] = std::string(iOrE);
            idx += 1;
        }
        accptdIorEVals[idx] = "Income or Expense";
    }
}

GlobalDiscriminatorConfiguration::~GlobalDiscriminatorConfiguration()
{
    // The last source file cleans up at program exit
    if (--initCount == 0)
    {
        if (pimpl)
        {
            delete pimpl;
        }
    }
}

// internal implementation
void GlobalDiscriminatorConfiguration::impl::load(const std::string& fname)
{
    // See if the file can be opened
    std::ifstream file(fname, std::ifstream::in);
    if (!file.is_open())
    {
        writeToFile(fname);
    }
    else
    {
        // Load data
        json configDataTemp = json::parse(file);

        // Make sure file has correct number of values
        if (configDataTemp.size() != static_cast<int>(ItemType::maxItemTypes))
        {
            std::string in; int exitId{ 0 };
            std::cout << "Data file is incorrect size, would you like to replace file with default values [y/n]?" << std::endl;
            std::cin >> in;
            while (exitId != 1)
            {
                if (in != "y" && in != "Y" && in != "n" && in != "N")
                {
                    std::cout << "Accepted inputs are y or n. Please try again: " << std::endl;
                    in.clear();
                    std::cin >> in;
                }
                else if (in == "n" || in == "N")
                {
                    throw std::runtime_error("Data file has incorrect values and user has elected to not replace file.");
                }
                else
                    exitId = 1;
            }
            writeToFile(fname);
        }
        else
        {
            configData = configDataTemp;
        }
        file.close();
    }
}

// Load global state    
void GlobalDiscriminatorConfiguration::load()
{
    const std::string fname{ ".\\ItemTypeList.json" };
    if (pimpl) delete pimpl;
    pimpl = new impl;
    pimpl->load(fname);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Private functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GlobalDiscriminatorConfiguration::impl::writeToFile(const std::string& fname) {
    for (auto itemType : ItemType::itemTypeStringsOther)
    {
        // Top Level Item Type
        configData[std::string(itemType)] = {{ "Your Item Type Description", accptdIorEVals.back(), "Your Item Sub-Type"},
        { "Your Other Item Type Description", accptdIorEVals.back(), "Your Item Sub-Type" }};
    }

    std::ofstream file(fname);
    file << configData.dump(1);
    file.flush();
    file.close();
}
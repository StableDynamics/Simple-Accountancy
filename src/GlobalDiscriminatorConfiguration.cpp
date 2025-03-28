#include "GlobalDiscriminatorConfiguration.h"

#include <fstream>

#include "ItemType.h"

// Default values
int GlobalDiscriminatorConfiguration::initCount;
GlobalDiscriminatorConfiguration::impl* GlobalDiscriminatorConfiguration::pimpl;

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Public functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// internal implementation
void GlobalDiscriminatorConfiguration::impl::load(const std::string& fname)
{
    using json = nlohmann::json;
    // See if the file can be opened
    std::ifstream file(fname, std::ifstream::in);
    if (!file.is_open())
    {
        json tempData = {
            {"Other",
                {"Your Item Type Description", "Your Item Sub-Type"},
                {"Your Item Type Description", "Your Item Sub-Type"}
            },
            {"Salary",
                {"Your Item Type Description", "Your Item Sub-Type"}
            }
        };

        /*json tempData;
        tempData.push_back({ "test" });*/

        std::ofstream file("testdata.json");
        file << tempData;
        file.flush();
        file.close();

        //for (auto itemType : ItemType::itemTypeStringsOther)
        //{
        //    // Top Level Item Type
        //    configData.emplace_back(std::string(itemType));
        //    //configData[0].emplace_back("Your Item Type Description", "Your Item Sub-Type");
        //}

        //std::ofstream file2("testItems.json");
        //file2 << configData;
        //file2.flush();
        //file2.close();
    }
    else
    {
        // Load data


        file.close();
    }
}

// (re)load global state    
void GlobalDiscriminatorConfiguration::load()
{
    const std::string fname{ ".\\itemtypelist.json" };
    if (pimpl) delete pimpl;
    pimpl = new impl;
    pimpl->load(fname);
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Private functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GlobalDiscriminatorConfiguration::GlobalDiscriminatorConfiguration()
{
    // record number of source files which instanciate a GlobalDiscriminatorConfiguration
    ++initCount;

    // Load config file
    this->load();
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
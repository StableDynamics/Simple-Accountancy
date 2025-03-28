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
        // Create default JSON object
        json config;

        for (auto itemType : ItemType::itemTypeStringsOther)
            config.emplace_back(itemType);
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
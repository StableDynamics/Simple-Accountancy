#pragma once

#include <string>

#include "json.hpp"

// This class contains the configuration data for the itemtypediscriminator
class GlobalDiscriminatorConfiguration
{
public:
    GlobalDiscriminatorConfiguration();

    ~GlobalDiscriminatorConfiguration();

    // Static method to get the instance of the class
    static GlobalDiscriminatorConfiguration& getInstance()
    {
        static GlobalDiscriminatorConfiguration instance;
        return instance;
    }

    // Delete copy constructor and assignment operator to prevent copying
    GlobalDiscriminatorConfiguration(const GlobalDiscriminatorConfiguration&) = delete;
    GlobalDiscriminatorConfiguration& operator=(const GlobalDiscriminatorConfiguration&) = delete;

    // Load global state    
    void load();

    // public parameter accessor
    const nlohmann::json& getConfigData() const
    {
        return getImpl().getConfigData();
    }

private:
    // internal implementation   
    struct impl
    {
        void load(const std::string& fname);

        const nlohmann::json& getConfigData() const
        {
            return configData;
        }

        void writeToFile(const std::string& fname);

        nlohmann::json configData;
    };
    
    static int initCount;
    static impl* pimpl;
    static impl& getImpl()
    {
        return *pimpl;
    }
};

static GlobalDiscriminatorConfiguration globalDiscriminatorConfiguration;
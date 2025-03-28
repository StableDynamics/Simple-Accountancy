#pragma once

#include <string>

#include "json.hpp"

// This class contains the configuration data for the itemtypediscriminator
class GlobalDiscriminatorConfiguration
{
public:
    // Static method to get the instance of the class
    static GlobalDiscriminatorConfiguration& getInstance()
    {
        static GlobalDiscriminatorConfiguration instance;
        return instance;
    }

    // Delete copy constructor and assignment operator to prevent copying
    GlobalDiscriminatorConfiguration(const GlobalDiscriminatorConfiguration&) = delete;
    GlobalDiscriminatorConfiguration& operator=(const GlobalDiscriminatorConfiguration&) = delete;

    // public parameter accessor
    const nlohmann::json& getConfigData() const
    {
        return getImpl().getConfigData();
    }

private:
    GlobalDiscriminatorConfiguration();

    ~GlobalDiscriminatorConfiguration();

    // internal implementation   
    struct impl
    {
        void load(const std::string& fname);

        const nlohmann::json& getConfigData() const
        {
            return configData;
        }

        nlohmann::json configData;
    };


    // Load global state    
    void load();
    static int initCount;
    static impl* pimpl;
    static impl& getImpl()
    {
        return *pimpl;
    }
};

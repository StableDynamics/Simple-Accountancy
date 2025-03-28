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


    // (re)load global state    
    void load();

    // public parameter accessor

private:
    GlobalDiscriminatorConfiguration();

    ~GlobalDiscriminatorConfiguration();

    // internal implementation   
    struct impl
    {
        void load(const std::string& fname);

        // int get_param_a() const; need to add in get data functions from configData

        nlohmann::json configData;
    };

    static int initCount;
    static impl* pimpl;
    static impl& getImpl()
    {
        return *pimpl;
    }
};

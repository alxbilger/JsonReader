#include <JsonReader/config.h>

#include <sofa/core/ObjectFactory.h>
using sofa::core::ObjectFactory;

extern "C" {
    SOFA_JSONREADER_API void initExternalModule();
    SOFA_JSONREADER_API const char* getModuleName();
    SOFA_JSONREADER_API const char* getModuleVersion();
    SOFA_JSONREADER_API const char* getModuleLicense();
    SOFA_JSONREADER_API const char* getModuleDescription();
    SOFA_JSONREADER_API const char* getModuleComponentList();
}

void initExternalModule()
{
    static bool first = true;
    if (first)
    {
        first = false;
    }
}

const char* getModuleName()
{
    return sofa_tostring(SOFA_TARGET);
}

const char* getModuleVersion()
{
    return sofa_tostring(JSONREADER_VERSION);
}

const char* getModuleLicense()
{
    return "MIT";
}

const char* getModuleDescription()
{
    return "SOFA plugin allowing to read scene written in the json format";
}

const char* getModuleComponentList()
{
    /// string containing the names of the classes provided by the plugin
    static std::string classes = ObjectFactory::getInstance()->listClassesFromTarget(sofa_tostring(SOFA_TARGET));
    return classes.c_str();
}

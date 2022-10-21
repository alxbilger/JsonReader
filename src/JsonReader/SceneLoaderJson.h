#pragma once

#include <JsonReader/config.h>
#include <sofa/simulation/Node.h>
#include <sofa/simulation/SceneLoaderFactory.h>

namespace sofa::simulation
{

class SOFA_JSONREADER_API SceneLoaderJson : public sofa::simulation::SceneLoader
{
public:
    bool canLoadFileExtension(const char* extension) override;
    bool canWriteFileExtension(const char *extension) override;
    sofa::simulation::NodeSPtr doLoad(const std::string& filename, const std::vector<std::string>& sceneArgs) override;
    std::string getFileTypeDesc() override;
    void getExtensionList(ExtensionList* list) override;

    // Test if load succeed
    static bool loadSucceed;

    static sofa::simulation::NodeSPtr loadFromMemory(const char* filename, const char* data);

};

} // namespace sofa::simulation

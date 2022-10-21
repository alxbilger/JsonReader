#include <JsonReader/SceneLoaderJson.h>
#include <sofa/simulation/SceneLoaderFactory.h>
#include <sofa/simulation/Node.h>
#include <algorithm>
#include <fstream>
#include <JsonReader/json.hpp>
#include <sofa/core/ObjectFactory.h>
#include <sofa/simulation/graph/DAGNode.h>


namespace sofa::simulation
{

// register the loader in the factory
const SceneLoader* loaderJson = SceneLoaderFactory::getInstance()->addEntry(new SceneLoaderJson());
bool SceneLoaderJson::loadSucceed = true;

bool SceneLoaderJson::canLoadFileExtension(const char* extension)
{
    std::string ext = extension;
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return ext == "json" || ext == "jscn";
}

bool SceneLoaderJson::canWriteFileExtension(const char* extension)
{
    return canLoadFileExtension(extension);
}

void createObject(const std::string& objectType, nlohmann::basic_json<nlohmann::ordered_map>::reference json, Node::SPtr parent, const std::string& filename)
{
    std::string objectName = parent->getNameHelper().resolveName(objectType, sofa::core::ComponentNameHelper::Convention::xml);
    if (!json.is_string())
    {
        try
        {
            objectName = json.value("name", objectName);
        }
        catch (nlohmann::json::exception& e)
        {
            msg_error("SceneLoaderJson") << e.what() ;
        }
    }

    core::objectmodel::BaseObjectDescription desc {objectName.c_str(), objectType.c_str()};

    if (json.is_object())
    {
        for (const auto& [key, value] : json.items())
        {
            if (value.is_string())
            {
                desc.setAttribute(key, value);
            }
        }
    }

    auto object = core::ObjectFactory::CreateObject(parent.get(), &desc);
    object->setInstanciationSourceFileName(filename);
}

void readNodeData(core::BaseData* data, const std::string& key, nlohmann::basic_json<nlohmann::ordered_map>::const_reference val)
{
    if (data)
    {
        if (val.is_string())
        {
            data->read(val);
        }
        else
        {
            msg_error("SceneLoaderJson") << "Cannot parse " << val << " for node data " << key;
        }
    }
}


Node::SPtr createNode(nlohmann::basic_json<nlohmann::ordered_map>::reference json, Node::SPtr parent, const std::string& filename)
{
    std::string nodeName;

    if (json.is_array())
    {
        Node::SPtr probablyRoot;
        for (auto& el : json)
        {
            Node::SPtr node = createNode(el, parent, filename);
            if (parent == nullptr)
            {
                probablyRoot = node;
            }
        }
        return probablyRoot;
    }
    else
    {
        try
        {
            nodeName=json.value("name", "Node");
        }
        catch(nlohmann::json::exception& e)
        {
            msg_error("SceneLoaderJson") << e.what();
        }
        Node::SPtr node=core::objectmodel::New<sofa::simulation::graph::DAGNode>(nodeName,
            dynamic_cast<sofa::simulation::graph::DAGNode*>(parent.get()));
        node->setInstanciationSourceFileName(filename);


        for(auto& [key, val] : json.items())
        {
            const bool isInObjectFactory = core::ObjectFactory::getInstance()->hasCreator(key);
            if(isInObjectFactory)
            {
                if (val.is_array())
                {
                    for (auto& el : val)
                    {
                        createObject(key, el, node, filename);
                    }
                }
                else
                {
                    createObject(key, val, node, filename);
                }
            }
            else
            {
                if(auto* data=node->findData(key))
                {
                    readNodeData(data, key, val);
                }
                else
                {
                    if (key != "Node")
                    {
                        msg_warning("SceneLoaderJson") << "Json node not found in the object factory, and not a Node Data: " << key << ": " << val;
                    }
                    createNode(val, node, filename);
                }
            }
        }
        return node;
    }

}

Node::SPtr processJson(nlohmann::ordered_json json, const std::string& filename)
{
    sofa::simulation::NodeSPtr root;

    for (auto& [key, val] : json.items())
    {
        if (root)
        {
            msg_error("SceneLoaderJson") << "Root node has already been created. Abort";
            break;
        }

        const bool isInObjectFactory = core::ObjectFactory::getInstance()->hasCreator(key);
        if (isInObjectFactory)
        {
            msg_error("SceneLoaderJson") << key << " found in object factory: it should be a child of a Node";
        }
        else
        {
            root = createNode(val, nullptr, filename);
        }
    }
    return root;
}

sofa::simulation::NodeSPtr SceneLoaderJson::doLoad(const std::string& filename,
                                                   const std::vector<std::string>& sceneArgs)
{
    if (!canLoadFileName(filename.c_str()))
        return nullptr;

    std::ifstream f(filename);
    nlohmann::ordered_json data = nlohmann::ordered_json::parse(f);
    sofa::simulation::Node::SPtr root = processJson(data, filename);

    return root;
}

std::string SceneLoaderJson::getFileTypeDesc()
{
    return "JSON Scenes";
}

void SceneLoaderJson::getExtensionList(ExtensionList* list)
{
    list->clear();
    list->push_back("json");
    list->push_back("jscn");
}

NodeSPtr SceneLoaderJson::loadFromMemory(const char* filename, const char* data)
{
    sofa::simulation::Node::SPtr root;
    try
    {
        nlohmann::ordered_json parsedData = nlohmann::ordered_json::parse(data);
        root = processJson(parsedData, filename);
    }
    catch(nlohmann::json::exception& e)
    {
        msg_error("SceneLoaderJson") << "Error reading json string from memory: " << e.what();
    }

    return root;
}

} // namespace sofa::simulation

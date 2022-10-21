#include <JsonReader/SceneLoaderJson.h>
#include <gtest/gtest.h>
#include <sofa/testing/NumericTest.h>

namespace sofa
{

TEST(SceneLoaderJson, jsonError)
{
    auto root = sofa::simulation::SceneLoaderJson::loadFromMemory("test.json", R"(
{
    "Node": {
        "name": "root",
        "dt": "0.02",
        "gravity": "0 -10 0",
        "printLog": "true" string
    }
}
    )");

    EXPECT_EQ(root, nullptr);
}

TEST(SceneLoaderJson, simpleRootNode)
{
    auto root = sofa::simulation::SceneLoaderJson::loadFromMemory("test.json", R"(
{
    "Node": {
        "name": "root",
        "dt": "0.02",
        "gravity": "0 -10 0",
        "printLog": "true"
    }
}
    )");

    EXPECT_NE(root, nullptr);
    EXPECT_TRUE(root->f_printLog.getValue());
    EXPECT_FLOATINGPOINT_EQ(root->dt_.getValue(), 0.02_sreal);
}

}

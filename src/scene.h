#pragma once

#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "glm/glm.hpp"
#include "utilities.h"
#include "bvh.h"
#include "sceneStructs.h"
using namespace std;

struct bbox;
struct bvhNode;

class Scene
{
private:
    ifstream fp_in;
    void InitializeCameraAndRenderState();
    void loadFromJSON(const std::string& jsonName);
    void loadFromOBJ(const std::string& objName);
    void transformToTarget(const glm::vec3& bboxCenter, const glm::vec3& bboxScale);
public:
    Scene();
    ~Scene();
    void LoadFromFile(string filename);
    void autoCentralize();
    bool sceneReady = false;

    Mesh mesh;
    std::vector<Geom> geoms;
    std::vector<Material> materials;
    RenderState state;
    std::unordered_map<std::string, uint32_t> MatNameToID;

    // bvh
    std::vector<bbox> triangleBboxes;
    std::vector<bvhNode> bvhNodes;
    int max_leaf_size = 8;
    int max_depth = 10;
    int binsToSplit = 32;

    void buildBVH();
    int buildBVHRecursive(bvhNode& parent, int startIndex, int size, int depth);
    void validateBVH(int maxDepth);

    // default options
    bool renderWithPathTracing = true;
    bool sortByMaterial = false;
    bool autoCentralizeObj = true;
    bool useBVH = false;
    bool useBasicBVC = false; // bounding volume culling
    bool useLeafSizeNotDepth = true;

    glm::vec3 rotationOffset = glm::vec3(0.0f, -45.0f, 0.0f);
    glm::vec3 translationOffset = glm::vec3(0.0f, 3.0f, 0.0f);
    float scaleOffset = 2.0f;
};

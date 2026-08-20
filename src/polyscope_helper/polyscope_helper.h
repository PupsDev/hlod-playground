#pragma once
std::vector<glm::vec3> getColors(const std::vector<int>& ids)
{
    static const std::vector<glm::vec3> palette = {
        {0.894f, 0.102f, 0.110f}, {0.216f, 0.494f, 0.722f},
        {0.302f, 0.686f, 0.290f}, {0.596f, 0.306f, 0.639f},
        {1.000f, 0.498f, 0.000f}, {1.000f, 1.000f, 0.200f},
        {0.651f, 0.337f, 0.157f}, {0.969f, 0.506f, 0.749f},
        {0.600f, 0.600f, 0.600f}, {0.122f, 0.467f, 0.706f},
        {0.682f, 0.780f, 0.909f}, {0.737f, 0.741f, 0.133f},
        {0.400f, 0.761f, 0.647f}, {0.984f, 0.604f, 0.600f},
        {0.792f, 0.698f, 0.839f}, {0.694f, 0.349f, 0.157f},
        {0.969f, 0.713f, 0.824f}, {0.651f, 0.808f, 0.890f},
        {0.800f, 0.922f, 0.773f}, {0.996f, 0.851f, 0.651f},
        {0.902f, 0.741f, 0.741f}, {0.741f, 0.902f, 0.902f},
        {0.902f, 0.902f, 0.741f}, {0.741f, 0.741f, 0.902f},
        {0.851f, 0.651f, 0.851f}, {0.651f, 0.851f, 0.851f},
        {0.851f, 0.851f, 0.651f}, {0.651f, 0.851f, 0.651f},
        {0.851f, 0.651f, 0.651f}, {0.651f, 0.651f, 0.851f},
        {0.851f, 0.851f, 0.851f}, {0.451f, 0.451f, 0.451f}
    };

    std::vector<glm::vec3> colors;
    colors.reserve(ids.size());

    for (int id : ids)
        colors.push_back(palette[id % palette.size()]);

    return colors;
}

void addSurfaceMeshColorQuantity(const std::string& meshName,const std::string& quantityName, const std::vector<int>& labels )
{
    polyscope::getSurfaceMesh(meshName)->addFaceColorQuantity(quantityName , getColors(labels));
}

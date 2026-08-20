#pragma once
#include "polyscope/curve_network.h"
#include "polyscope/point_cloud.h"
#include "polyscope/surface_mesh.h"
#include "polyscope_helper/polyscope_helper.h"
#include <hlod/builder/builder.h>
namespace hlod {
  class HLODManager
  {
    public:
    HLODManager() = default;
    void loadMesh() {

      builder.loadMesh(vertices_, faces_);
      polyscope::registerSurfaceMesh(coolMeshName, vertices_, faces_);
      polyscope::getSurfaceMesh(coolMeshName)->resetTransform();
    }
    void partition()
    {
      builder.computeInitialPartition();
      auto partition = builder.meshPartition();
      addSurfaceMeshColorQuantity(coolMeshName, "partition", partition);
    }


    Builder builder;
    std::string coolMeshName = "mesh";
    Eigen::MatrixXd vertices_;
    Eigen::MatrixXi faces_;

  };
}

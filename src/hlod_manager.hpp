#pragma once
#include "polyscope/curve_network.h"
#include "polyscope/point_cloud.h"
#include "polyscope/surface_mesh.h"
#include "polyscope_helper/polyscope_helper.h"
#include <hlod/builder/builder.h>
namespace hlod {
  struct HLODManagerParameters {
    BuilderParameters builder_parameters;
  };
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
      //parameters_.builder_parameters.partition_method = PartitionMethod::METIS;
      builder.setParameters(parameters_.builder_parameters);
      builder.computeInitialPartition();
      const auto partition = builder.meshPartition();
      addSurfaceMeshColorQuantity(coolMeshName, "partition", partition);
    }
    /*
    void gridPartition()
    {

      parameters_.builder_parameters.partition_method = PartitionMethod::GRID;
      builder.setParameters(parameters_.builder_parameters);
      builder.computeInitialPartition();
      const auto partition = builder.meshPartition();
      addSurfaceMeshColorQuantity(coolMeshName, "grid_partition", partition);
    }**/
    void setParameters( const HLODManagerParameters& parameters) {
      parameters_ = parameters;
    }

    HLODManagerParameters parameters_;
    Builder builder;
    std::string coolMeshName = "mesh";
    Eigen::MatrixXd vertices_;
    Eigen::MatrixXi faces_;

  };
}

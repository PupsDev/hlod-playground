#pragma once
#include "hlod_manager.hpp"

namespace hlod::ui {
void drawParameters(HLODManager& manager)
{
    auto& builder = manager.parameters_.builder_parameters;

    if (ImGui::CollapsingHeader(
            "Builder",
            ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Indent();

        ImGui::InputInt(
            "Num clusters",
            &builder.num_clusters
        );

        ImGui::SliderFloat(
            "Simplification ratio",
            &builder.simplification_ratio,
            0.0f,
            1.0f
        );

        // ------------------------------------------------------------
        // Partition method
        // ------------------------------------------------------------

        const char* methods[] =
        {
            "METIS",
            "GRID"
        };

        int method = static_cast<int>(builder.partition_method);

        if (ImGui::Combo(
                "Partition method",
                &method,
                methods,
                IM_ARRAYSIZE(methods)))
        {
            builder.partition_method =
                static_cast<hlod::PartitionMethod>(method);
        }

        // ------------------------------------------------------------
        // Grid
        // ------------------------------------------------------------

        if (builder.partition_method == PartitionMethod::GRID)
        {
            if (ImGui::TreeNode("Grid partitioner"))
            {
                auto& grid = builder.grid_partitioner_parameters;

                ImGui::DragFloat(
                    "Cell size",
                    &grid.cell_size,
                    0.01f,
                    0.001f,
                    100.0f
                );

                ImGui::Checkbox(
                    "Use vertex",
                    &grid.use_vertex
                );

                ImGui::InputInt(
                    "Grid num clusters",
                    &grid.num_clusters
                );

                ImGui::TreePop();
            }
        }

        // ------------------------------------------------------------
        // METIS
        // ------------------------------------------------------------

        if (builder.partition_method == PartitionMethod::METIS)
        {
            if (ImGui::TreeNode("METIS partitioner"))
            {
                auto& metis = builder.metis_partitioner_parameters;

                ImGui::InputInt(
                    "METIS num clusters",
                    &metis.num_clusters
                );

                ImGui::Checkbox(
                    "Use contiguous",
                    &metis.use_contiguous
                );

                ImGui::TreePop();
            }
        }

        ImGui::Unindent();
    }
}
void displayBuilder_UI(HLODManager& manager)
  {
  ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (ImGui::TreeNode("Builder"))
    {
      drawParameters(manager);
      if (ImGui::Button("Load Mesh"))
      {
        manager.loadMesh();

      }
      if (ImGui::Button("Compute initial partition"))
      {
        manager.partition();
      }/*
      if (ImGui::Button("Compute grid partition"))
      {
        manager.gridPartition();
      }*/
      ImGui::TreePop();
    }
  }

  void displayHLOD_UI(HLODManager& manager)
  {
  ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (ImGui::TreeNode("HLOD"))
    {
      displayBuilder_UI(manager);
      ImGui::TreePop();
    }
  }
}


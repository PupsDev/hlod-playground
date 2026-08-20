#pragma once
#include "hlod_manager.hpp"

namespace hlod::ui {
void displayBuilder_UI(HLODManager& manager)
  {
  ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (ImGui::TreeNode("Builder"))
    {
      if (ImGui::Button("Load Mesh"))
      {
        manager.loadMesh();

      }
      if (ImGui::Button("Compute initial partition"))
      {
        manager.partition();
      }
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


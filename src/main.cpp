#include "polyscope/polyscope.h"
#include <igl/readOBJ.h>
#include "polyscope/deps/args/args/args.hxx"


#include "hlod_manager.hpp"
#include "hlod-ui/hlod_ui.h"

Eigen::MatrixXd meshV;
Eigen::MatrixXi meshF;

int main(int argc, char **argv) {
    // Configure the argument parser
    // Configure the argument parser
    args::ArgumentParser parser(
        "ASAP\nBy mladeuil",
        ""
    );

    args::Positional<std::string> inFile(
        parser,
        "mesh",
        "input mesh"
    );

    // Parse args
    try {
        parser.ParseCLI(argc, argv);
    }
    catch (args::Help) {
        std::cout << parser;
        return 0;
    }
    catch (args::ParseError& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    // Options
    polyscope::options::autocenterStructures = true;
    polyscope::view::windowWidth = 1024;
    polyscope::view::windowHeight = 1024;

    // Initialize polyscope
    polyscope::init();

    std::string filename = args::get(inFile);

    // Read the mesh
    igl::readOBJ(filename, meshV, meshF);



    hlod::HLODManager manager;
    manager.vertices_ = meshV;
    manager.faces_ = meshF;
    // Add the callback
    polyscope::state::userCallback = [&]( ){

        ImGui::PushItemWidth(100);
        ImGuiIO &io = ImGui::GetIO();

        hlod::ui::displayHLOD_UI(manager);
    };

    // Show the gui
    polyscope::show();

    return 0;
}

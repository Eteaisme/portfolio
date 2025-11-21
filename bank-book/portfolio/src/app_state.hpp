#pragma once

#include <string>
#include <vector>

struct AppState {
    std::string current_screen = "home";
    int selected_project = 0;
    std::vector<std::string> project_entries = {
        "portfolio",
        "neontra",
        "frc",
    };

    const std::string& SelectedProject() const;
};

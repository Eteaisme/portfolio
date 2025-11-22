#include "content.hpp"

#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace {
Element BuildProjectDetails(const std::string& project_name) {
    if (project_name == "portfolio") {
        return vbox({
            text("portfolio") | bold,
            separator(),
        });
    }
    if (project_name == "neontra") {
        return vbox({
            text("neontra") | bold,
            separator(),
        });
    }
    if (project_name == "frc") {
        return vbox({
            text("frc") | bold,
            separator(),
        });
    }
    return text("unknown project") | dim;
}
}  // namespace

ftxui::Element BuildContent(const AppState& state, ftxui::Component& projects_menu) {
    if (state.current_screen == "home") {
        return vbox({
            text("hi, i'm elliot, a computing student @ the university of guelph."),
            text("i enjoy coffee, reading, music, math & computers."),
            text("looking for S26 work."),
        });
    }

    if (state.current_screen == "projects") {
        Element right_content = BuildProjectDetails(state.SelectedProject());
        Element left_menu = projects_menu->Render() | size(WIDTH, GREATER_THAN, 18);

        return hbox({
            left_menu,
            separator(),
            right_content | flex,
        });
    }

    if (state.current_screen == "contact") {
        return vbox({
            text("email me at: "),
            hyperlink("mailto:eteaisme@gmail.com", text("eteaisme@gmail.com")) | bold,
            separator(),
            text("follow me at: "),
            hyperlink("github.com/Eteaisme", text("github.com/Eteaisme")) | bold,
        }) | center;
    }

    return text("");
}

ftxui::Element BuildNavBar(const AppState& state) {
    return hbox({
               text("    elliot tam    ") | bold,
               text("    h") | bold,
               (state.current_screen == "home" ? text(" home    ") | bold : text(" home    ")),
               text("    p") | bold,
               (state.current_screen == "projects" ? text(" projects    ") | bold : text(" projects    ")),
               text("    c") | bold,
               (state.current_screen == "contact" ? text(" contact    ") | bold : text(" contact    ")),
           })
        | center
        | border;
}

ftxui::Element BuildFooter() {
    return hbox({
               text("made with "),
               text("") | bold,
               text(" in "),
               text("🇨🇦"),
               text("    q") | bold,
               text(" quit"),
           })
        | center;
}

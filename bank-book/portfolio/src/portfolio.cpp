#include "portfolio.hpp"

#include "content/content.hpp"
#include "projects/projects.hpp" 

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace ftxui;

int PortfolioApp::Run() {
    auto screen = ScreenInteractive::Fullscreen();
    auto projects_menu = MakeProjectsMenu(state_.project_entries, &state_.selected_project);

    auto document = Renderer(projects_menu, [&] {
        Element nav_bar = BuildNavBar(state_);
        Element footer = BuildFooter();

        Element inner_box =
            vbox({
                nav_bar,
                filler(),
                BuildContent(state_, projects_menu),
                filler(),
                footer,
            })
            | size(HEIGHT, GREATER_THAN, 40);

        return vbox({
            filler(),
            hbox({
                filler(),
                inner_box,
                filler(),
            }),
            filler(),
        });
    });

    auto main_component = CatchEvent(document, [&](Event event) {
        if (event == Event::Character('h')) {
            state_.current_screen = "home";
            return true;
        }
        if (event == Event::Character('p')) {
            state_.current_screen = "projects";
            return true;
        }
        if (event == Event::Character('c')) {
            state_.current_screen = "contact";
            return true;
        }
        if (event == Event::Character('q')) {
            screen.Exit();
            return true;
        }
        return false;
    });

    screen.Loop(main_component);
    return 0;
}

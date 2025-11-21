#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/canvas.hpp>
#include <string>
#include <vector>

using namespace ftxui;
Component MakeProjectsMenu(std::vector<std::string>& entries, int* selected) {
    auto menu = Menu(&entries, selected);
    menu = CatchEvent(menu, [&entries, selected](Event e) {
        if (e == Event::Character('j')) {
            if (*selected + 1 < (int)entries.size())
                (*selected)++;
            return true;
        }
        if (e == Event::Character('k')) {
            if (*selected - 1 >= -1)
                (*selected)--;
            return true;
        }
        return false;
    });
    return Renderer(menu, [menu] { return menu->Render() | vscroll_indicator | frame | border; });
}

int main() {
    auto screen = ScreenInteractive::Fullscreen();
    std::string current_screen = "home";

    int selected_project = 0;
    std::vector<std::string> project_entries = {
        "portfolio",
        "neontra",
        "frc",
    };
    auto projects_menu = MakeProjectsMenu(project_entries, &selected_project);

    auto content = [&]() -> Element {
        if (current_screen == "home") {
            return vbox({
                text("hi, i'm elliot, a computing student @ the university of guelph."),
                text("i enjoy coffee, reading, music, math & computers."),
                text("looking for S26 work."),
            });
        }

        if (current_screen == "projects") {
            Element right_content;

            const std::string& sel = project_entries[selected_project];
            if (sel == "portfolio") {
                right_content = vbox({
                    text("portfolio") | bold,
                    separator(),
                });
            } else if (sel == "neontra") {
                right_content = vbox({
                    text("neontra") | bold,
                    separator(),
                });
            } else if (sel == "frc") {
                right_content = vbox({
                    text("frc") | bold,
                    separator(),
                });
            } else {
                right_content = text("unknown project") | dim;
            }
            Element left_menu =
                projects_menu->Render()
                | size(WIDTH, GREATER_THAN, 18);

            Element layout = hbox({
                left_menu,
                separator(),
                right_content | flex,
            });

            return layout;
        }

        if (current_screen == "contact") {
            return vbox({
                text("email me at: "),
                hyperlink("mailto:eteaisme@gmail.com", text("eteaisme@gmail.com")) | bold,
                separator(),
                text("follow me at: "),
                hyperlink("github.com/Eteaisme", text("github.com/Eteaisme")) | bold,
            }) | center;
        }

        return text("");
    };

    // Document: nav bar, content, footer, centered inner box
    auto document = Renderer(projects_menu, [&] {
        Element nav_bar =
            hbox({
                text("    elliot tam    ") | bold,
                text("    h") | bold,
                (current_screen == "home"     ? text(" home    ") | bold : text(" home    ")),
                text("    p") | bold,
                (current_screen == "projects" ? text(" projects    ") | bold : text(" projects    ")),
                text("    c") | bold,
                (current_screen == "contact"  ? text(" contact    ") | bold : text(" contact    ")),
            }) | center | border;

        Element footer =
            hbox({
                text("made with "),
                text("") | bold,
                text(" in "),
                text("🇨🇦"),
                text("    q") | bold,
                text(" quit"),
            }) | center;

        Element inner_box =
            vbox({
                nav_bar,
                filler(),
                content(),
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

    // Global event handler for navigation
    auto main_component = CatchEvent(document, [&](Event event) {
        if (event == Event::Character('h')) {
            current_screen = "home";
            return true;
        }
        if (event == Event::Character('p')) {
            current_screen = "projects";
            return true;
        }
        if (event == Event::Character('c')) {
            current_screen = "contact";
            return true;
        }
        if (event == Event::Character('q')) {
            screen.Exit();
            return true;
        }
        return false; // let projects_menu handle arrows / j/k
    });

    screen.Loop(main_component);
    return 0;
}

#include "projects_menu.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

ftxui::Component MakeProjectsMenu(std::vector<std::string>& entries, int* selected) {
    auto menu = Menu(&entries, selected);
    menu = CatchEvent(menu, [&entries, selected](Event e) {
        if (e == Event::Character('j')) {
            if (*selected + 1 < static_cast<int>(entries.size())) {
                (*selected)++;
            }
            return true;
        }
        if (e == Event::Character('k')) {
            if (*selected - 1 >= -1) {
                (*selected)--;
            }
            return true;
        }
        return false;
    });
    return Renderer(menu, [menu] { return menu->Render() | vscroll_indicator | frame | border; });
}

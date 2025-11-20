#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

int main() {
    auto screen = ScreenInteractive::Fullscreen();

    Element nav_bar = 
        hbox({
            text("elliot tam") | bold,
            text(" | "),
            text("h") | bold, text(" home"),
            text(" | "),
            text("p") | bold, text(" projects"),
            text(" | "),
            text("m") | bold, text(" mail"),
        }) | center;


    Element footer =
        hbox({
            text("made with "),
            text("") | bold,          
            text(" in "),
            text("🇨🇦"),
        }) | center;

    Element inner_box =
        vbox({
            nav_bar,
            filler(),
            separator(),
            footer,
            separator(),
        }) 
        | size(HEIGHT, GREATER_THAN, 10)
        | size(WIDTH, GREATER_THAN, 40)
        | center;

    Element outer_box =
        vbox({
            filler(),
            hbox({
                filler(),
                inner_box | borderLight,   
                filler(),
            }),
            filler(),
        });

    auto document = Renderer([&] {
        return outer_box;
    });

    screen.Loop(document);
}

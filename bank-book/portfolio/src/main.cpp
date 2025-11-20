#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/deprecated.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

int main() {
    auto screen = ScreenInteractive::Fullscreen();

    std::string current_screen = "home";

    auto content = [&]() -> Element {
        if (current_screen == "home") {
            return vbox({
                    text("hi, i'm elliot, a computing student @ the university of guelph."),
                    text("i enjoy coffee, reading, music, math & computers."),
                    text("looking for S25 work."),
                    });
        }
        if (current_screen == "projects") {
            return text("projects go here") | center | bold;
        } 
        if (current_screen == "mail") {
            return vbox({
                    text("contact me at: "),
                    text("eteaisme@gmail.com ") | bold
                    }) | center;
        }
        return text("");
    };

    auto document = Renderer([&] {

        Element nav_bar =
            hbox({
                text("    elliot tam    ") | bold,
                text("    h") | bold, 
                (current_screen == "home" ? text(" home    ") | bold 
                                          : text(" home    ")),
                text("    p") | bold, 
                (current_screen == "projects" ? text(" projects    ") | bold
                                              : text(" projects    ")),
                text("    m") | bold, 
                (current_screen == "mail" ? text(" mail    ") | bold
                                          : text(" mail    ")),
            }) | center | border;

        Element footer =
            hbox({
                text("made with "),
                text("") | bold,
                text(" in "),
                text("🇨🇦"),
                text("        q") | bold,
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
            | size(HEIGHT, GREATER_THAN, 40)
            | size(WIDTH, GREATER_THAN, 80)
            | center;

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
            current_screen = "home";
            return true;
        }
        if (event == Event::Character('p')) {
            current_screen = "projects";
            return true;
        }
        if (event == Event::Character('m')) {
            current_screen = "mail";
            return true;
        }
        if (event == Event::Character('q')) {
            screen.Exit();
            return true;
        }
        return false;
    });

    screen.Loop(main_component);
}

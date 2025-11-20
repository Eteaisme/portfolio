#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/canvas.hpp>
#include <cmath>

using namespace ftxui;

int main() {
    //Create a dynamic screen, box, current screen identifier & mouse --- xy varibles. 
    auto screen = ScreenInteractive::Fullscreen();
    std::string current_screen = "home";
    int local_x = 0;
    int local_y = 0;
    Box plot_box;

    //Renders and plots to the boxa  3d gaussian plot taken from ftxui examples
    auto renderer_plot_3 = Renderer([&] {
        auto c = Canvas(100, 100);
        int size = 15;

        float my = (local_y - 90) / -5.f;
        float mx = (local_x - 3 * my) / 5.f;

        std::vector<std::vector<float>> ys(size, std::vector<float>(size));

        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                float dx = x - mx;
                float dy = y - my;
                ys[y][x] = -1.5 + 3.0 * std::exp(-0.2f * (dx * dx + dy * dy));
            }
        }

        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                if (x != 0) {
                    c.DrawPointLine(
                        5*(x-1) + 3*y, 90 - 5*y - 5*ys[y][x-1],
                        5*(x)   + 3*y, 90 - 5*y - 5*ys[y][x]);
                }
                if (y != 0) {
                    c.DrawPointLine(
                        5*x + 3*(y-1), 90 - 5*(y-1) - 5*ys[y-1][x],
                        5*x + 3*(y)  , 90 - 5*(y)   - 5*ys[y][x]);
                }
            }
        }
        return canvas(std::move(c));
    });

    auto plot_component = Renderer([&] {
        Element e = renderer_plot_3->Render();
        return e | reflect(plot_box);
    });




//Changes content displayed based on current screen
    auto content = [&]() -> Element {
        if (current_screen == "home") {
            return vbox({
                text("hi, i'm elliot, a computing student @ the university of guelph."),
                text("i enjoy coffee, reading, music, math & computers."),
                text("looking for S26 work."),
            });
        }
        if (current_screen == "projects") {
            return vbox({
                plot_component->Render(),
            }) | center;
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

// Describes entire doccument,nav-bar, footer & innerbox.
    auto document = Renderer([&] {
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


// Event listener looking for mouse and keys
    auto main_component = CatchEvent(document, [&](Event event) {
        if (event.is_mouse() && event.mouse().motion) {
            int mx = event.mouse().x;
            int my = event.mouse().y;

            local_x = (mx - plot_box.x_min) * 2;
            local_y = (my - plot_box.y_min) * 4;

            return true;
        }

        if (event == Event::Character('h')) { current_screen = "home"; return true; }
        if (event == Event::Character('p')) { current_screen = "projects"; return true; }
        if (event == Event::Character('c')) { current_screen = "contact"; return true; }
        if (event == Event::Character('q')) { screen.Exit(); return true; }

        return false;
    });
    screen.Loop(main_component);
    return 0;
}

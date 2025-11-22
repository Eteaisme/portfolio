#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

#include "../app-state/app-state.hpp"

ftxui::Element BuildContent(const AppState& state, ftxui::Component& projects_menu);
ftxui::Element BuildNavBar(const AppState& state);
ftxui::Element BuildFooter();

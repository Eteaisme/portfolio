#pragma once

#include <ftxui/component/component.hpp>
#include <string>
#include <vector>

ftxui::Component MakeProjectsMenu(std::vector<std::string>& entries, int* selected);

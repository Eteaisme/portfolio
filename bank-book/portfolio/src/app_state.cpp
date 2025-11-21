#include "app_state.hpp"

namespace {
const std::string& EmptyString() {
    static const std::string empty;
    return empty;
}
}  // namespace

const std::string& AppState::SelectedProject() const {
    if (selected_project < 0 || selected_project >= static_cast<int>(project_entries.size())) {
        return EmptyString();
    }
    return project_entries[selected_project];
}

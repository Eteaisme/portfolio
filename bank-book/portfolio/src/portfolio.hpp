#pragma once

#include "app-state/app-state.hpp"

class PortfolioApp {
public:
    int Run();

private:
    AppState state_;
};

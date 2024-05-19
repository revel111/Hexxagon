#include "menu.h"

auto main() -> int {
    auto menu = Menu(1200, 800);
    menu.render();

    return 0;
}
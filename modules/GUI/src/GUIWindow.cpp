#include <utility>
#include "../include/GUIWindow.h"

GUIWindow::GUIWindow(std::string title, Uint16 width, Uint16 height) : GUIBase() {
    this->width = width;
    this->height = height;
    this->title = std::move(title);
}

GUIWindow::~GUIWindow() = default;

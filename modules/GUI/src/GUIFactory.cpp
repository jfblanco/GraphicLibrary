#include <utility>

#include "../include/GUIFactory.h"
#include "../include/GUIWindow.h"
#include "../include/GUIEditorWindows.h"

GUIWindow* createWindow(std::string title, Uint8 width, Uint8 heigth) {
    return new GUIWindow(std::move(title), width, heigth);
}

void GUIFactory::createMainWindow(GUIEditorWindows* _editorWindo) {
    _editorWindo->mainMenuWindow = createWindow("Game Engine Menu", 500, 600);
}

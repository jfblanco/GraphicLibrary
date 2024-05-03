#ifndef ENGINETEST_GUIEDITORWINDOWS_H
#define ENGINETEST_GUIEDITORWINDOWS_H

class GUIWindow;
class GUIEditorWindows {
public:
    GUIWindow *mainMenuWindow = nullptr;
    GUIWindow *animationMenuWindow = nullptr;
    GUIWindow *textureMenuWindow = nullptr;
    GUIWindow *materialMenuWindow = nullptr;
    GUIWindow *meshMenuWindow = nullptr;
    GUIWindow *objectMenuWindow = nullptr;
};

#endif //ENGINETEST_GUIEDITORWINDOWS_H

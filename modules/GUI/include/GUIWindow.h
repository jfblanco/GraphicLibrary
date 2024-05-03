#ifndef ENGINETEST_GUIWINDOW_H
#define ENGINETEST_GUIWINDOW_H

#include <vector>
#include <string>
#include <GUIBase.h>

class GUIWindow : public GUIBase {
public:
    std::vector<GUIBase> children;
    Uint16 width = 0;
    Uint16 height = 0;
    std::string title;

    GUIWindow(std::string title, Uint16 width, Uint16 height);
    ~GUIWindow();
};


#endif //ENGINETEST_GUIWINDOW_H

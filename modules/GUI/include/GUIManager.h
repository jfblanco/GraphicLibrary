#ifndef ENGINETEST_GUIMANAGER_H
#define ENGINETEST_GUIMANAGER_H

#include <map>
#include <string>

class GUIBase;
class GUIManager {
public:
    std::map<std::string, GUIBase*> guiElements;
};


#endif //ENGINETEST_GUIMANAGER_H

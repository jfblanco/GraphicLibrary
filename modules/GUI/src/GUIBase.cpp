#include "GUIBase.h"

GUIBase::GUIBase() = default;
GUIBase::~GUIBase() = default;

void GUIBase::addChild(GUIBase *child) {
    this->children.push_back(child);
}
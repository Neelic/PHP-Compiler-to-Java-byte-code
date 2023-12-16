#include "ClassAccessModList.hpp"

int ClassAccessModList::GLOBAL_ID = 0;

ClassAccessModList *ClassAccessModList::CreateNode(ClassAccessModNode *node) {
    auto *tmp = new ClassAccessModList();
    if (node != nullptr)
        tmp->vector.push_back(node);
    tmp->cur_id = ClassAccessModList::GLOBAL_ID++;
    return tmp;
}


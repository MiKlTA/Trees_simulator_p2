#include "tree_part_manager.h"



void TreePartManager::above(TreePart *tar, void (* handleOverlap)(TreePart *tp))
{
    float tarAn = fullAngle<glm::vec2, float>(tar->psCenter());
    
}

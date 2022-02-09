#include "root.h"




Root::Root(Planet *p, glm::vec2 pos)
    : TreePart(p, nullptr, new PhysicPoint{pos, {0.f, 0.f}}, 0.0f)
{
    
}

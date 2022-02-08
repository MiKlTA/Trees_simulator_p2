#include "root.h"




Root::Root(Planet *p, glm::vec2 pos)
    : TreePart(p, nullptr, new PhysicPoint{pos, {0.f, 0.f}}, 0.0f)
{
    
}



void Root::render(const glm::mat4 &view, const glm::mat4 &proj)
{
    for (auto p : m_childParts)
        p->render(view, proj);
}

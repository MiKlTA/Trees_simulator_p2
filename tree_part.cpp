#include "tree_part.h"



TreePart::TreePart(Planet *p, TreePart *par, PhysicPoint *mounting, float mass)
    : m_parentPart(par),
      m_childParts(),
      m_isBroken(false),
      
      m_planet(p),
      
      m_mounting(mounting),
      m_mass(mass),
      m_nodeMass(mass),
      m_growth(0.0f)
{
    if (par != nullptr)
        par->connect(this);
}

TreePart::~TreePart()
{
    if (m_parentPart != nullptr)
        m_parentPart->disconnect(this);
}



void TreePart::calcPhysics()
{
    _calcPhysics();
    for (auto p : m_childParts)
        p->calcPhysics();
}



void TreePart::continueGrow()
{
    if (m_growth + growSpeed() > 1.f)
    {
        m_growth = 1.f;
        for (auto p : m_childParts)
            p->continueGrow();
    }
    else
    {
        m_growth += growSpeed();
    }
}



void TreePart::destroyChildParts()
{
    for (auto p : m_childParts)
    {
        p->destroyChildParts();
        delete p;
    }
    m_childParts.clear();
}



void TreePart::calcMass()
{
    float mass = getCurMass();
    for (auto p : m_childParts)
    {
        p->calcMass();
        mass += p->getNodeMass();
    }
    m_nodeMass = mass;
}



void TreePart::render(const glm::mat4 &view, const glm::mat4 &proj)
{
    _render(view, proj);
    for (auto p : m_childParts)
        p->render(view, proj);
}



// private:



void TreePart::disconnect(TreePart *childPart)
{
    for (auto i = m_childParts.begin(); i < m_childParts.end(); ++i)
        if (*i == childPart)
        {
            m_childParts.erase(i);
            break;
        }
}

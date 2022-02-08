#include "tree_part.h"



TreePart::TreePart(Planet *p, TreePart *par, PhysicPoint *mounting, float mass)
    : m_parentPart(par),
      m_childParts(),
      m_planet(p),
      
      m_mounting(mounting),
      m_mass(mass),
      m_nodeMass(mass),
      m_growth(1.0f)
{
    if (par != nullptr)
        par->connect(this);
}

TreePart::~TreePart()
{
    if (m_parentPart != nullptr)
        m_parentPart->disconnect(this);
}



void TreePart::continueGrow()
{
    m_growth = std::min(m_growth + growSpeed(), 1.0f);
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
        mass += p->getMass();
    }
    m_nodeMass = mass;
}

float TreePart::getMass()
{
    return m_nodeMass;
}

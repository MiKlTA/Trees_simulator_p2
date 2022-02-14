#include "leaf.h"



Leaf::Leaf(
        Triangle *t, Planet *p, TreePart *par, PhysicPoint *mounting,
        glm::vec2 p1, glm::vec2 p2, float greenery
        )
    : TreePart(
          p, par, mounting,
          maxPossibleMass() * ((1.f - 0.1f) * greenery * greenery + 0.1f)
          ),
      m_triangle(t),
      
      m_startP1(p1),
      m_startP2(p2),
      m_p1(p1),
      m_p2(p2),
      m_greenery(greenery),
      
      m_triangleEnd1(),
      m_triangleEnd2()
{
    m_triangleEnd1 = new PhysicPoint;
    m_triangleEnd1->pos = mounting->pos + p1;
    m_triangleEnd1->vel = mounting->vel;
    
    m_triangleEnd2 = new PhysicPoint;
    m_triangleEnd2->pos = mounting->pos + p2;
    m_triangleEnd2->vel = mounting->vel;
}

Leaf::~Leaf()
{
    delete m_triangleEnd1;
    delete m_triangleEnd2;
}



// private:



void Leaf::_calcPhysics()
{
    // TODO: remove it
    if (m_growth < 1.0e-9)
        return;
    m_triangleEnd1->pos = mounting()->pos + m_p1;
    m_triangleEnd2->pos = mounting()->pos + m_p2;
    
    float mass = getNodeMass() - getCurMass() / 2.f;
    
    glm::vec2 d1 = m_startP1 - m_p1;
    glm::vec2 d2 = m_startP2 - m_p2;
    glm::vec2 d12 = (m_startP2 - m_startP1) - (m_p2 - m_p1);
    
    glm::vec2 p1Acceleration
            = getElasticity() * (d1 - d12) / getCurMass();
    glm::vec2 p2Acceleration
            = getElasticity() * (d2 + d12) / getCurMass();
    
    
}



void Leaf::_render(const glm::mat4 &view, const glm::mat4 &proj)
{
    
}



float Leaf::stretchAngleDelta()
{
    
}

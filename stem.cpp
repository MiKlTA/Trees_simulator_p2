#include "stem.h"



Stem::Stem(
        Rect *r, Planet *p, TreePart *par,
        PhysicPoint *mounting, glm::vec2 size, float thickness, float mass
           )
    : TreePart(p, par, mounting, mass),
      m_rect(r),
      
      m_startSize(size),
      m_thickness(thickness)
{
    m_segmentEnd = new PhysicPoint;
    m_segmentEnd->pos = par->mounting()->pos + size;
    m_segmentEnd->vel = par->mounting()->vel;
}

Stem::~Stem()
{
    delete m_segmentEnd;
}



void Stem::calcPhysics()
{
    if (m_childParts.empty())
        return;
    m_parentPart->mounting()->calcPos();
    glm::vec2 n = glm::normalize(size());
    glm::vec2 t = glm::vec2(glm::cross(
                                glm::vec3(0.0f, 0.0f, 1.0f),
                                glm::vec3(size(), 0.0f)
                                ));
    
    glm::vec2 g = m_planet->g(m_mounting->pos);
    glm::vec2 radialG, tangentG;
    radialG = glm::dot(g, n) * n;
    tangentG = g - radialG;
    
    float mass = getMass();
    
    glm::vec2 dr = size() - m_startSize;
    float da = glm::asin(
                glm::dot(
                    glm::cross(
                        glm::vec3(size(), 0.0f),
                        glm::vec3(m_startSize, 0.0f)
                        ),
                    glm::vec3(0.0f, 0.0f, 1.0f)
                    )
                );
    
    glm::vec2 resRadialF, resTangentF;
    resRadialF = (getElasticity() * glm::length(dr) - mass * g.r) * n;
    resTangentF = (getAngleElasticity() * da - mass * g.t) * glm::length(dr)* t;
    
    glm::vec2 nx(1.0f, 0.0f);
    glm::vec2 ny(0.0f, 1.0f);
    
    glm::vec2 resF;
    resF.x = glm::dot(resRadialF, nx) + glm::dot(resTangentF, nx);
    resF.y = glm::dot(resRadialF, ny) + glm::dot(resTangentF, ny);
    
    resF += m_planet->cross(m_mounting->pos) * m_planet->elasticity();
    
    glm::vec2 a(resF / mass);
    
    m_segmentEnd->calcVel(a);
    m_segmentEnd->calcPos();
    
    calcPhysics();
}



void Stem::render(const glm::mat4 &view, const glm::mat4 &proj)
{
    m_rect->lookAt(
                m_mounting->pos,
                m_segmentEnd->pos,
                thickness()
                   );
    m_rect->render(view, proj);
}



// private:


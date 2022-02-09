#include "stem.h"



Stem::Stem(
        Rect *r, Planet *p, TreePart *par,
        PhysicPoint *mounting, glm::vec2 size, float greenery
        )
    : TreePart(
          p, par, mounting,
          maxPossibleMass() * ((1.f - 0.1f) * greenery * greenery + 0.1f)
          ),
      m_rect(r),
      
      m_startSize(size),
      m_size(size),
      m_greenery(greenery)
{
    m_segmentEnd = new PhysicPoint;
    m_segmentEnd->pos = mounting->pos + size;
    m_segmentEnd->vel = mounting->vel;
}

Stem::~Stem()
{
    delete m_segmentEnd;
}



// private:



void Stem::_calcPhysics()
{
    // TODO: remove it
    if (m_growth < 1.0e-9)
        return;
    m_segmentEnd->pos = m_mounting->pos + size();
    
    glm::vec2 r = glm::normalize(size());
    glm::vec2 t = glm::vec2(glm::cross(
                                glm::vec3(0.0f, 0.0f, 1.0f),
                                glm::vec3(size(), 0.0f)
                                ));
    
    glm::vec2 g = m_planet->g(m_segmentEnd->pos);
    glm::vec2 radialG, tangentG;
    radialG = glm::dot(g, r) * r;
    tangentG = g - radialG;
    
    float mass = getNodeMass() - getCurMass() / 2.f;
    
    glm::vec2 dr = size() - m_startSize;
    float da = glm::asin(
                glm::cross(
                    glm::vec3(glm::normalize(size()), 0.0f),
                    glm::vec3(glm::normalize(m_startSize), 0.0f)
                    ).z
                );
    
    glm::vec2 resRadialF, resTangentF;
    resRadialF = mass * radialG - getElasticity() * dr;
    resTangentF = (getAngleElasticity() * da * t - mass * tangentG)
            * glm::length(size());
    
    glm::vec2 nx(1.0f, 0.0f);
    glm::vec2 ny(0.0f, 1.0f);
    
    glm::vec2 resF;
    resF.x = glm::dot(resRadialF, nx) + glm::dot(resTangentF, nx);
    resF.y = glm::dot(resRadialF, ny) + glm::dot(resTangentF, ny);
    
    resF += -m_planet->cross(m_segmentEnd->pos) * m_planet->elasticity();
    
    glm::vec2 a(resF / mass);
    
    m_segmentEnd->calcVel(a);
    m_segmentEnd->calcPos();
    m_size = m_segmentEnd->pos - m_mounting->pos;
    
    if (stretchDelta() > maxStretchDelta())
        m_isBroken = true;
}



void Stem::_render(const glm::mat4 &view, const glm::mat4 &proj)
{
    m_rect->lookAt(
                m_mounting->pos,
                m_segmentEnd->pos,
                thickness()
                   );
    m_rect->setColor(
                linearNInterp(
                    leafColor(),
                    woodColor(),
                    (1 - m_greenery) * growthFactor()
                    )
                + stretchDelta()/maxStretchDelta() * glm::vec3(1.0f, 0.0f, 0.0f)
                );
    m_rect->render(view, proj);
}



float Stem::maxThickness()
{
    float t = 1 - m_greenery;
    float l = minPossibleThickness();
    float g = maxPossibleThickness();
    return (g - l) * t*t + l;
}

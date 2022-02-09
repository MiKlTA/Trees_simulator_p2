#ifndef H_STEM
#define H_STEM



#include <vector>

#include "opengl.h"
#include "interpolation.h"
#include "rect.h"

#include "tree_part.h"



class Stem : public TreePart
{
public:
    Stem(
            Rect *r, Planet *p, TreePart *par, PhysicPoint *mounting,
            glm::vec2 size, float greenery
            );
    ~Stem();
    
    PhysicPoint * segmentEnd() {return m_segmentEnd;}
    
    float greeneryFactor()
    {return (1.f - 0.1f) * m_greenery * m_greenery + 0.1f;}
    
    
    
private:
    Rect *m_rect;
    
    glm::vec2 m_startSize;
    glm::vec2 m_size;
    float m_greenery;
    
    PhysicPoint *m_segmentEnd;
    
    
    
    void _calcPhysics() override;
    void _render(const glm::mat4 &view, const glm::mat4 &proj) override;
    
    float thickness() {return maxThickness() * growthFactor();}
    float maxThickness();
    float minPossibleThickness() {return 0.1f;}
    float maxPossibleThickness() {return 1.0f;}
    
    float maxMass() {return maxPossibleMass() * greeneryFactor();}
    static float maxPossibleMass() {return 200.f;}
    
    glm::vec2 size() {return m_size;}
    float stretching() {return glm::length(m_size) / glm::length(m_startSize);}
    float stretchDelta() {return glm::abs(1.0f - stretching());}
    float maxStretchDelta() {return 0.1f;}
    
    float getElasticity() {return 1.0f * thickness();}
    float getAngleElasticity() {return 1.0f * thickness();}
};



#endif // H_STEM

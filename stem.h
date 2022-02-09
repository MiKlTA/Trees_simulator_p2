#ifndef H_STEM
#define H_STEM



#include <vector>

#include "opengl.h"

#include "rect.h"

#include "tree_part.h"



class Stem : public TreePart
{
public:
    Stem(
            Rect *r, Planet *p, TreePart *par, PhysicPoint *mounting,
            glm::vec2 size, float thickness, float mass
            );
    ~Stem();
    
    PhysicPoint * segmentEnd() {return m_segmentEnd;}
    
    
    
private:
    Rect *m_rect;
    
    glm::vec2 m_startSize;
    float m_thickness;
    
    PhysicPoint *m_segmentEnd;
    
    
    
    void _calcPhysics() override;
    void _render(const glm::mat4 &view, const glm::mat4 &proj) override;
    
    float thickness() {return m_growth * m_thickness;}
    glm::vec2 size() {return m_mounting->pos - m_segmentEnd->pos;}
    
    float getElasticity() {return 0.01f * m_thickness;}
    static float getAngleElasticity() {return 0.01f;}
};



#endif // H_STEM

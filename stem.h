#ifndef H_STEM
#define H_STEM



#include "opengl.h"
#include "interpolation.h"
#include "angle_between_vectors.h"
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
    
    glm::vec2 psCenter() override {return mounting()->pos + size() / 2.0f;}
    
    
    
private:
    Rect *m_rect;
    
    glm::vec2 m_startSize;
    float m_greenery;
    
    PhysicPoint *m_segmentEnd;
    
    
    
    void _calcPhysics() override;
    void _render(const glm::mat4 &view, const glm::mat4 &proj) override;
    
    float thickness() {return maxThickness() * growthFactor();}
    float maxThickness();
    float minPossibleThickness() {return 0.1f;}
    float maxPossibleThickness() {return 1.0f;}
    
    float maxMass() {return maxPossibleMass() * greeneryFactor();}
    static float maxPossibleMass() {return 1000.f;}
    
    glm::vec2 size() {return m_segmentEnd->pos - mounting()->pos;}
    float stretching() {return glm::length(size()) / glm::length(m_startSize);}
    float stretchDelta() {return glm::abs(1.0f - stretching());}
    float maxStretchDelta() {return 0.1f;}
    float stretchAngleDelta();
    float maxStretchAngleDelta() {return 0.1f;}
    
    float getElasticity()
    {return 30.0f * thickness() * (1.f - greeneryFactor());}
    float getAngleElasticity()
    {return 10.0f * thickness() * (1.f - greeneryFactor());}
};



#endif // H_STEM

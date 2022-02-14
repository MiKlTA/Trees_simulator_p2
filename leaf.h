#ifndef H_LEAF
#define H_LEAF



#include "opengl.h"
#include "interpolation.h"
#include "triangle.h"

#include "tree_part.h"



class Leaf : public TreePart
{
public:
    Leaf(
            Triangle *t, Planet *p, TreePart *par, PhysicPoint *mounting,
            glm::vec2 p1, glm::vec2 p2, float greenery
            );
    ~Leaf();
    
    PhysicPoint * triangleEng1() {return m_triangleEnd1;}
    PhysicPoint * triangleEng2() {return m_triangleEnd2;}
    
    float greeneryFactor()
    {return (1.f - 0.1f) * m_greenery * m_greenery + 0.1f;}
    
    glm::vec2 psCenter() override {return centre();}
    
    
    
private:
    Triangle *m_triangle;
    
    glm::vec2 m_startP1;
    glm::vec2 m_startP2;
    glm::vec2 m_p1;
    glm::vec2 m_p2;
    float m_greenery;
    
    PhysicPoint *m_triangleEnd1;
    PhysicPoint *m_triangleEnd2;
    
    
    
    void _calcPhysics() override;
    void _render(const glm::mat4 &view, const glm::mat4 &proj) override;
    
    glm::vec2 startCentre() {return (m_startP1 + m_startP2) / 3.f;}
    glm::vec2 centre() {return (m_p1 + m_p2) / 3.f;}
    
    float maxMass() {return maxPossibleMass() * greeneryFactor();}
    static float maxPossibleMass() {return 200.f;}
    
    float stretching()
    {return glm::length(centre()) / glm::length(startCentre());}
    float stretchDelta() {return glm::abs(1.0f - stretching());}
    float maxStretchDelta() {return 0.1f;}
    float stretchAngleDelta();
    float maxStretchAngleDelta() {return 0.1f;}
    
    float getElasticity() {return 5.0f * (1.f - greeneryFactor());}
    float getAngleElasticity() {return 1.0f * (1.f - greeneryFactor());}
};



#endif // H_LEAF

#ifndef H_TREE_PART
#define H_TREE_PART



#include <vector>

#include "opengl.h"

#include "id_object.h"

#include "dna.h"
#include "planet.h"



struct PhysicPoint
{
    glm::vec2 pos;
    glm::vec2 vel;
    
    void calcPos() {pos += vel * dt();}
    void calcVel(glm::vec2 acc) {vel += acc * dt();}
    
    static float dt() {return 1.f;}
};



class TreePart : public IdObject
{
public:
    TreePart(Planet *p, TreePart *par, PhysicPoint *mounting, float mass);
    virtual ~TreePart();
    
    void calcPhysics();
    bool isBroken() {return m_isBroken;}
    
    void continueGrow();
    float growthFactor()
    {return (1.f - 0.15f) * m_growth * m_growth + 0.15f;}
    
    void destroyChildParts();
    
    void calcMass();
    float getNodeMass() {return m_nodeMass;}
    float getCurMass() {return m_mass * growthFactor();}
    PhysicPoint * mounting() {return m_mounting;}
    
    void render(const glm::mat4 &view, const glm::mat4 &proj);
    
protected:
    TreePart *m_parentPart;
    std::vector<TreePart *> m_childParts;
    bool m_isBroken;
    
    Planet *m_planet;
    
    PhysicPoint *m_mounting;
    float m_mass;
    float m_nodeMass;
    float m_growth;
    
    
    
    void connect(TreePart *childPart)
    {m_childParts.push_back(childPart);}
    void disconnect(TreePart *childPart);
    virtual void _calcPhysics() = 0;
    virtual void _render(const glm::mat4 &view, const glm::mat4 &proj) = 0;
    
    bool haveParent() {return m_parentPart != nullptr;}
    
    static float growSpeed() {return 0.01f;}
    static constexpr glm::vec3 seedColor() {return {0.87f, 0.78f, 0.65f};}
    static constexpr glm::vec3 leafColor() {return {0.13f, 0.55f, 0.13f};}
    static constexpr glm::vec3 woodColor() {return {0.25f, 0.15f, 0.07f};}
};



#endif // H_TREE_PART

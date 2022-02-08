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
    
    void calcPos() {pos += vel;}
    void calcVel(glm::vec2 acc) {vel += acc;}
};



class TreePart : public IdObject
{
public:
    TreePart(Planet *p, TreePart *par, PhysicPoint *mounting, float mass);
    virtual ~TreePart();
    
    virtual void calcPhysics() = 0;
    
    void continueGrow();
    
    void destroyChildParts();
    
    void calcMass();
    float getMass();
    PhysicPoint * mounting() {return m_mounting;}
    
    virtual void render(const glm::mat4 &view, const glm::mat4 &proj) = 0;
    
protected:
    TreePart *m_parentPart;
    std::vector<TreePart *> m_childParts;
    
    Planet *m_planet;
    
    PhysicPoint *m_mounting;
    float m_mass;
    float m_nodeMass;
    float m_growth;
    
    
    
    void connect(TreePart *childPart)
    {m_childParts.push_back(childPart);}
    void disconnect(TreePart *childPart)
    {
        for (auto i = m_childParts.begin(); i < m_childParts.end(); ++i)
            if (*i == childPart)
            {
                m_childParts.erase(i);
                break;
            }
    }
    
    float getCurMass() {return m_mass * m_growth;}
    
    bool haveParent() {return m_parentPart != nullptr;}
    
    static float growSpeed() {return 0.01f;}
};



#endif // H_TREE_PART

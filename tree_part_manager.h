#ifndef H_TREE_PART_MANAGER
#define H_TREE_PART_MANAGER



#include <set>

#include "angle_between_vectors.h"

#include "tree_part.h"



struct TreePartP
{
    TreePart *p;
    bool operator>(const TreePartP &tpp)
    {
        glm::vec2 v1, v2;
        v1 = p->psCenter();
        v2 = tpp.p->psCenter();
        float angle1 = fullAngle<glm::vec2, float>(v1);
        float angle2 = fullAngle<glm::vec2, float>(v2);
        return angle1 > angle2;
    }
};



class TreePartManager
{
public:
    using Container_t = std::set<TreePart *>;
    
    Container_t & parts() {return m_parts;}
    
    void above(TreePart *tar, void (* handleOverlap)(TreePart *tp));
    
private:
    Container_t m_parts;
    
    static constexpr float deltaAngle() {return glm::pi<float>() / 16.f;}
};



#endif // H_TREE_PART_MANAGER

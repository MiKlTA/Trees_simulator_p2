#ifndef H_TREE
#define H_TREE



#include <map>

#include "opengl.h"

#include "rect.h"
#include "triangle.h"

#include "planet.h"
#include "tree_part_manager.h"

#include "root.h"
#include "stem.h"



class Tree
{
public:
    Tree(Rect *r, Triangle *t, TreePartManager *tpm, Planet *p);
    
    void update();
    
    void render(const glm::mat4 &view, const glm::mat4 &proj);
    
private:
    Rect *m_rect;
    Triangle *m_triangle;
    
    std::map<int, TreePart *> m_parts;
    TreePartManager *m_tpManager;
    Planet *m_planet;
    
    TreePart *m_root;
    
    
    
    void collectEnergy();
    void spendEnergy();
};



#endif // H_TREE

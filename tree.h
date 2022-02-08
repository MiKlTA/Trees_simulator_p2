#ifndef H_TREE
#define H_TREE



#include "opengl.h"

#include "rect.h"
#include "triangle.h"

#include "planet.h"

#include "root.h"
#include "stem.h"



class Tree
{
public:
    Tree(Rect *r, Triangle *t, Planet *p);
    
    void update();
    
    void render(const glm::mat4 &view, const glm::mat4 &proj);
    
private:
    Rect *m_rect;
    Triangle *m_triangle;
    
    Planet *m_planet;
    
    TreePart *m_root;
};



#endif // H_TREE

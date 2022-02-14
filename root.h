#ifndef H_ROOT
#define H_ROOT



#include <vector>

#include "opengl.h"

#include "tree_part.h"



class Root : public TreePart
{
public:
    Root(Planet *p, glm::vec2 pos);
    
    glm::vec2 psCenter() override {return glm::vec2(0.f);}
    
private:
    void _calcPhysics() override {};
    void _render(const glm::mat4 &, const glm::mat4 &) override {};
};



#endif // H_ROOT

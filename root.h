#ifndef H_ROOT
#define H_ROOT



#include <vector>

#include "opengl.h"

#include "tree_part.h"



class Root : public TreePart
{
public:
    Root(Planet *p, glm::vec2 pos);
    
    void calcPhysics() override {};
    
    void render(const glm::mat4 &view, const glm::mat4 &proj) override;
    
private:
};



#endif // H_ROOT

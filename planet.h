#ifndef H_PLANET
#define H_PLANET



#include "opengl.h"

#include "circle.h"



class Planet
{
public:
    Planet(Circle *c, float radius);
    
    glm::vec2 g(glm::vec2 r);
    float light(glm::vec2 r);
    glm::vec2 cross(glm::vec2 r);
    
    void render(const glm::mat4 &view, const glm::mat4 &proj);
    
    static float elasticity() {return 0.001f;}
    
private:
    Circle *m_circle;
    
    float m_radius;
    
    static constexpr glm::vec3 color() {return glm::vec3(0.6f, 0.5f, 0.75f);}
    static float G() {return 0.001f;}
    static float light() {return 1.0f;}
};



#endif // H_PLANET

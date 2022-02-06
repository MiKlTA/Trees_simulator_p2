#ifndef H_CIRCLE
#define H_CIRCLE



#include "opengl.h"



class Circle
{
public:
    Circle(int details);
    
    void setPos(glm::vec2 p) {m_pos = p; updModelMat();}
    void setRadius(float r) {m_radius = r; updModelMat();}
    
    glm::vec2 getPos() {return m_pos;}
    float getRadius() {return m_radius;}
    
    
    
    void setColor(glm::vec3 color) {m_color = color;}
    glm::vec3 getColor() {return m_color;}
    
    
    
    void render(const glm::mat4 &view, const glm::mat4 &proj);
    
private:
    GLuint m_VBO, m_VAO;
    GLuint m_shadProg;
    GLuint m_modelLoc, m_viewLoc, m_projLoc, m_colorLoc;
    glm::mat4 m_model;
    glm::vec3 m_color;
    
    glm::vec2 m_pos;
    float m_radius;
    int m_details;
    
    void updModelMat();
    
    int getVerticesCount() {return 1 + 2 * m_details;}
    glm::vec2 getVertice(int i);
    GLfloat * calcVertices();
};



#endif // H_CIRCLE

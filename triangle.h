#ifndef H_TRIANGLE
#define H_TRIANGLE



#include "opengl.h"



class Triangle
{
public:
    Triangle();
    
    void setV(glm::vec2 p, int i) {m_posV[i] = p; updModelMat();}
    
    glm::vec2 getVPos(int i) {return m_posV[i];}
    
    
    
    void setColor(glm::vec3 color) {m_color = color;}
    glm::vec3 getColor() {return m_color;}
    
    
    
    void render(const glm::mat4 &view, const glm::mat4 &proj);
    
private:
    GLuint m_VBO, m_VAO;
    GLuint m_shadProg;
    GLuint m_modelLoc, m_viewLoc, m_projLoc, m_colorLoc;
    glm::mat4 m_model;
    glm::vec3 m_color;
    
    glm::vec2 m_posV[3];
    glm::vec2 m_pos;
    float m_scale;
    
    void updModelMat();
};



#endif // H_TRIANGLE

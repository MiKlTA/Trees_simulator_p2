#include "circle.h"

#include <iostream>
#include <fstream>



Circle::Circle(int details)
    : m_VBO(),
      m_VAO(),
      m_shadProg(),
      m_modelLoc(),
      m_viewLoc(),
      m_projLoc(),
      m_colorLoc(),
      m_model(1.0f),
      m_color(0.5f),
      
      m_pos(),
      m_radius(),
      m_details()
{
    m_pos = glm::vec2(0.0f);
    m_radius = 1.0f;
    m_details = details;
    
    std::ifstream ifs;
    ifs.open("circleShader.vert");
    if (!ifs.is_open())
    {
        std::cout << "file is not open!" << std::endl;
        return;
    }
    ifs.seekg(0, std::ios::end);
    GLuint fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    
    GLchar *vertexShaderSource = new GLchar[fileSize];
    ifs.read(vertexShaderSource, fileSize);
    ifs.close();
    
    ifs.open("circleShader.frag");
    if (!ifs.is_open())
    {
        std::cout << "file is not open!" << std::endl;
        return;
    }
    ifs.seekg(0, std::ios::end);
    fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    
    GLchar *fragmentShaderSource = new GLchar[fileSize];
    ifs.read(fragmentShaderSource, fileSize);
    ifs.close();
    
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
    glVertexAttribPointer(
                0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                reinterpret_cast<GLvoid *>(0)
                );
    glEnableVertexAttribArray(0);
    
    updModelMat();
    
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    
    m_shadProg = glCreateProgram();
    glAttachShader(m_shadProg, vertexShader);
    glAttachShader(m_shadProg, fragmentShader);
    glLinkProgram(m_shadProg);
    
    m_modelLoc = glGetUniformLocation(m_shadProg, "model");
    m_viewLoc = glGetUniformLocation(m_shadProg, "view");
    m_projLoc = glGetUniformLocation(m_shadProg, "proj");
    m_colorLoc = glGetUniformLocation(m_shadProg, "color");
}



void Circle::render(const glm::mat4 &view, const glm::mat4 &proj)
{
    glUseProgram(m_shadProg);
    glBindVertexArray(m_VAO);
    
    glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, &m_model[0][0]);
    glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(m_projLoc, 1, GL_FALSE, &proj[0][0]);
    glUniform3fv(m_colorLoc, 1, &m_color[0]);
    
    glDrawArrays(GL_TRIANGLE_FAN, 0, getVerticesCount());
}



// private:



void Circle::updModelMat()
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(
                GL_ARRAY_BUFFER,
                3 * getVerticesCount() * sizeof(GLfloat), calcVertices(),
                GL_STATIC_DRAW
                );
    
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, glm::vec3(m_pos, 0.0f));
    m_model = glm::scale(m_model, glm::vec3(m_radius));
}



glm::vec2 Circle::getVertice(int i)
{
    float angle = 2 * glm::pi<float>() * (i % m_details) / (m_details * 1.f);
    return {glm::cos(angle), glm::sin(angle)};
}

GLfloat * Circle::calcVertices()
{
    GLfloat * vertices = new GLfloat[3 * getVerticesCount()];
    vertices[0] = 0.f; vertices[1] = 0.f; vertices[2] = 0.f;
    for (int i = 1; i < getVerticesCount(); ++i)
    {
        glm::vec2 p = getVertice(i / 2);
        vertices[3 * i + 0] = p.x;
        vertices[3 * i + 1] = p.y;
        vertices[3 * i + 2] = 0.f;
    }
    
    return vertices;
}

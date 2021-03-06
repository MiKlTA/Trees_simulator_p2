#include "rect.h"

#include <iostream>
#include <fstream>



Rect::Rect()
    : m_VBO(),
      m_EBO(),
      m_VAO(),
      m_shadProg(),
      m_modelLoc(),
      m_viewLoc(),
      m_projLoc(),
      m_colorLoc(),
      m_model(1.0f),
      m_color(0.5f),
      
      m_pos(0.0f),
      m_size(1.0f)
{
    std::ifstream ifs;
    ifs.open("rectShader.vert");
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
    
    ifs.open("rectShader.frag");
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
    
    GLfloat vertices[] =
    {
        -0.5f,  -0.5f,    0.0f,
        0.5f,   -0.5f,    0.0f,
        -0.5f,   0.5f,    0.0f,
        0.5f,    0.5f,    0.0f,
    };
    
    GLuint indices[] =
    {
        0, 1, 2,
        1, 2, 3
    };
    
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(vertices), vertices,
                GL_STATIC_DRAW
                );
    
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                sizeof(indices), indices,
                GL_STATIC_DRAW
                );
    
    glVertexAttribPointer(
                0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                reinterpret_cast<GLvoid *>(0)
                );
    glEnableVertexAttribArray(0);
    
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



void Rect::lookAt(glm::vec2 from, glm::vec2 to, float thickness)
{
    glm::vec2 genVec = to - from;
    float length, angle;
    length = glm::length(genVec);
    angle = fullAngle<glm::vec2, float>(genVec);
    
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, glm::vec3(from + genVec / 2.0f, 0.0f));
    m_model = glm::rotate(m_model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
    m_model = glm::scale(m_model, glm::vec3(length, thickness, 1.0f));
}



void Rect::render(const glm::mat4 &view, const glm::mat4 &proj)
{
    glUseProgram(m_shadProg);
    glBindVertexArray(m_VAO);
    
    glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, &m_model[0][0]);
    glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(m_projLoc, 1, GL_FALSE, &proj[0][0]);
    glUniform3fv(m_colorLoc, 1, &m_color[0]);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}



// private:



void Rect::updModelMat()
{
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, glm::vec3(m_pos, 0.0f));
    m_model = glm::scale(m_model, glm::vec3(m_size, 1.0f));
}

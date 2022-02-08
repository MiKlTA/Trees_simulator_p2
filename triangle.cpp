#include "triangle.h"

#include <iostream>
#include <fstream>



Triangle::Triangle()
    : m_VBO(),
      m_VAO(),
      m_shadProg(),
      m_modelLoc(),
      m_viewLoc(),
      m_projLoc(),
      m_colorLoc(),
      m_model(1.0f),
      m_color(0.5f),
      
      m_posV(),
      m_pos(),
      m_scale()
{
    m_posV[0] = {-0.5f, -0.5f};
    m_posV[1] = {0.5f, -0.5f};
    m_posV[2] = {0.f, 0.5f};
    m_pos = glm::vec2(0.0f);
    m_scale = 1.0f;
    
    
    
    std::ifstream ifs;
    ifs.open("triangleShader.vert");
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
    
    ifs.open("triangleShader.frag");
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



void Triangle::render(const glm::mat4 &view, const glm::mat4 &proj)
{
    glUseProgram(m_shadProg);
    glBindVertexArray(m_VAO);
    
    glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, &m_model[0][0]);
    glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(m_projLoc, 1, GL_FALSE, &proj[0][0]);
    glUniform3fv(m_colorLoc, 1, &m_color[0]);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}



// private:



void Triangle::updModelMat()
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
    glm::vec2 v[3];
    for (int i = 0; i < 3; ++i)
        v[i] = m_posV[i];
    
    m_pos = v[0];
    v[1] -= v[0];
    v[2] -= v[0];
    v[0] = glm::vec2(0.f, 0.f);
    
    const glm::vec2 &far
            = (glm::length(v[1]) > glm::length(v[2]) ? v[1] : v[2]);
    float squareSideHalf = std::max(std::abs(far.x), std::abs(far.y));
    v[1] /= squareSideHalf;
    v[2] /= squareSideHalf;
    m_scale = squareSideHalf;
    
    GLfloat verts[9];
    for (int i = 0; i < 3; ++i)
    {
        verts[3 * i]      = v[i].x;
        verts[3 * i + 1]  = v[i].y;
        verts[3 * i + 2]  = 0.f;
    }
    
    glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(verts), verts,
                GL_DYNAMIC_DRAW
                );
    
    // this case is special,
    // and the matrices are multiplied in the code in this order only here!!!!
    m_model = glm::translate(glm::mat4(1.0f), glm::vec3(m_pos, 0.0f));
    m_model = glm::scale(m_model, glm::vec3(m_scale));
}

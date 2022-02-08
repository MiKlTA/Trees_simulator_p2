#ifndef H_WINDOW
#define H_WINDOW



#include <fstream>

#include "opengl.h"

#include "simulation_core.h"



class Window
{
public:
    static Window * inst();
    
    int getMonitorWidth() const {return m_monSize.x;};
    int getMonitorHeight() const {return m_monSize.y;};
    
    glm::vec2 comvertToWorldCoods(glm::ivec2 p);
    
    
    
    void startWindowCycle();
    
private:
    Window();
    ~Window();
    static Window *m_instance;
    
    GLFWwindow *m_window;
    glm::ivec2 m_monSize;
    
    glm::vec2 m_camPos;
    float m_camScale;
    glm::mat4 m_viewMat;
    glm::vec2 m_viewSize;
    glm::mat4 m_projMat;
    glm::vec2 m_mousePos;
    
    SimulationCore *m_simcore;
    
    
    
    void handleInputCameraMove();
    glm::ivec2 getMouseFieldPos();
    
    void updViewMat();
    void updProjMat();
    
    
    
    static void keyCallback(
            GLFWwindow *aWindow, int key, int scancode, int action, int mods
            );
    static void cursorPosCallback(GLFWwindow* , double x, double y);
    static void mouseButtonCallback(
            GLFWwindow* window, int button, int action, int mods
            );
    
    static constexpr glm::vec2 defaultCamPos() {return glm::vec2(0.f, 0.f);}
    static float defaultCamScale() {return 50.f;}
    
    static float dCamPos() {return 0.02f;}
    static float kCamScale() {return 1.02f;}
};



#endif // H_WINDOW

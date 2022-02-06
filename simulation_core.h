#ifndef H_SIMULATION_CORE
#define H_SIMULATION_CORE



#include "rect.h"
#include "triangle.h"
#include "circle.h"



class Window;



class SimulationCore
{
public:
    SimulationCore(Window *w);
    ~SimulationCore();
    
    void update();
    
    void render(const glm::mat4 &view, const glm::mat4 &proj);
    
    void onKeyPress(int key, int action, int mods);
    void onMouseMove(int x, int y);
    void onMouseButtonPress(int button, int action, int mods);
    
private:
    Window *m_window;
    
    Rect *m_rect;
    Triangle *m_triangle;
    Circle *m_circle;
};



#endif // H_SIMULATION_CORE

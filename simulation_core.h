#ifndef H_SIMULATION_CORE
#define H_SIMULATION_CORE



#include "rect.h"



class SimulationCore
{
public:
    SimulationCore();
    ~SimulationCore();
    
    void update();
    
    void render(const glm::mat4 &view, const glm::mat4 &proj);
    
private:
    Rect *m_rect;
};



#endif // H_SIMULATION_CORE

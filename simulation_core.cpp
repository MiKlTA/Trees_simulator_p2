#include "simulation_core.h"



SimulationCore::SimulationCore()
{
    m_rect = new Rect;
}

SimulationCore::~SimulationCore()
{
    
}



void SimulationCore::update()
{
    
}



void SimulationCore::render(const glm::mat4 &view, const glm::mat4 &proj)
{
    m_rect->setPos({0, 0});
    m_rect->setSize({1, 1});
    m_rect->setColor({1, 1, 0});
    m_rect->render(view, proj);
}

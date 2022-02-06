#include "simulation_core.h"

#include "window.h"

#include <iostream>



SimulationCore::SimulationCore(Window *w)
    : m_window(w)
{
    m_rect = new Rect;
    m_triangle = new Triangle;
    m_circle = new Circle(50);
    m_circle->setPos({1.f, 1.f});
}

SimulationCore::~SimulationCore()
{
    delete m_rect;
    delete m_triangle;
    delete m_circle;
}



void SimulationCore::update()
{
    
}



void SimulationCore::render(const glm::mat4 &view, const glm::mat4 &proj)
{
    m_triangle->render(view, proj);
    m_circle->render(view, proj);
}



void SimulationCore::onKeyPress(int key, int action, int mods)
{
    
}

void SimulationCore::onMouseMove(int x, int y)
{
    
}

void SimulationCore::onMouseButtonPress(int button, int action, int mods)
{
    
}

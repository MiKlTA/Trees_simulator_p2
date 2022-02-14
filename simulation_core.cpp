#include "simulation_core.h"

#include "window.h"

#include <iostream>



SimulationCore::SimulationCore(Window *w)
    : m_window(w)
{
    m_rect = new Rect;
    m_triangle = new Triangle;
    m_circle = new Circle(100);
    m_triangle->setV({0.f, 3.f}, 0);
    m_triangle->setV({1.f, 0.f}, 1);
    m_triangle->setV({-2.f, 1.f}, 2);
    
    m_planet = new Planet(m_circle, 50.f);
    m_tpManager = new TreePartManager;
    m_tree = new Tree(m_rect, m_triangle, m_tpManager, m_planet);
}

SimulationCore::~SimulationCore()
{
    delete m_rect;
    delete m_triangle;
    delete m_circle;
    
    delete m_planet;
}



void SimulationCore::update()
{
    m_tree->update();
}



void SimulationCore::render(const glm::mat4 &view, const glm::mat4 &proj)
{
    m_planet->render(view, proj);
    
    m_triangle->render(view, proj);
    
    m_tree->render(view, proj);
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

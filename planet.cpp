#include "planet.h"



Planet::Planet(Circle *c, float radius)
    : m_circle(c),
      m_radius(radius)
{
    c->setPos({0.f, 0.f});
    c->setRadius(radius);
    c->setColor(color());
}



glm::vec2 Planet::g(glm::vec2 r)
{
//    G == 1.0f
//    float R = glm::length(r);
//    if (R == 0.f)
//        R += 1.0e-9;
//    return -G() * r / (R * R * R);
    return (-glm::normalize(r)) * G();
}

float Planet::light(glm::vec2)
{
    return light();
}

glm::vec2 Planet::cross(glm::vec2 r)
{
    float R = glm::length(r);
    if (R > m_radius)
        return glm::vec2(0.f, 0.f);
    float dl = R - m_radius;
    return dl * (r / R);
}



void Planet::render(const glm::mat4 &view, const glm::mat4 &proj)
{
    m_circle->render(view, proj);
}

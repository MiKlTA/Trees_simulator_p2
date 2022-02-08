#include "tree.h"



Tree::Tree(Rect *r, Triangle *t, Planet *p)
    : m_rect(r),
      m_triangle(t),
      
      m_planet(p)
{
    m_root = new Root(p, {0.0f, 51.0f});
    Stem *s = new Stem(
                r, p, m_root, m_root->mounting(), {0.7f, 0.7f}, 0.3f, 1.0f
                );
}



void Tree::update()
{
    // m_root->continueGrow();
}



void Tree::render(const glm::mat4 &view, const glm::mat4 &proj)
{
    m_root->render(view, proj);
}

#include "tree.h"



Tree::Tree(Rect *r, Triangle *t, Planet *p)
    : m_rect(r),
      m_triangle(t),
      
      m_planet(p)
{
    m_root = new Root(p, {0.0f, 50.0f});
    Stem *s1 = new Stem(
                r, p, m_root, m_root->mounting(), {0.7f, 0.7f}, 0.1f, 1.0f
                );
    Stem *s2 = new Stem(
                r, p, s1, s1->segmentEnd(), {-1.0f, 0.0f}, 0.1f, 1.0f
                );
    Stem *s3 = new Stem(
                r, p, s2, s2->segmentEnd(), {0.5f, 1.5}, 0.1f, 1.0f
                );
}



void Tree::update()
{
    m_root->continueGrow();
    // m_root->calcPhysics();
}



void Tree::render(const glm::mat4 &view, const glm::mat4 &proj)
{
    m_root->render(view, proj);
}

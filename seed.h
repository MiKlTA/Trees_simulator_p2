//#ifndef H_SEED
//#define H_SEED



//#include <vector>

//#include "opengl.h"
//#include "triangle.h"

//#include "tree_part.h"

//#include "dna.h"



//class Seed : public TreePart
//{
//public:
//    Seed(
//            Triangle *t, Planet *p, TreePart *par, PhysicPoint *mounting,
//            glm::vec2 p1, glm::vec2 p2, Dna dna
//            );
//    ~Seed();
    
//    glm::vec2 psCenter() override {return m_segmentEnd->pos + m_size / 2.0f;}
    
    
    
//private:
//    Triangle *m_triangle;
    
//    glm::vec2 m_startP1;
//    glm::vec2 m_startP2;
//    glm::vec2 m_p1;
//    glm::vec2 m_p2;
//    Dna m_dna;
    
    
    
//    void _calcPhysics() override;
//    void _render(const glm::mat4 &view, const glm::mat4 &proj) override;
    
//    float maxMass() {return 100.0f;}
    
//    float stretching() {return glm::length(m_size) / glm::length(m_startSize);}
//    float stretchDelta() {return glm::abs(1.0f - stretching());}
//    float maxStretchDelta() {return 0.1f;}
    
//    float getElasticity() {return 1.0f * thickness();}
//};



//#endif // H_SEED

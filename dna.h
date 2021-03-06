#ifndef H_DNA
#define H_DNA



#include <vector>

#include <random>

#include <fstream>

#include "opengl.h"

#include "interpolation.h"



class DnaCodon
{
public:
    DnaCodon(int parentCodInd, int size, int angle)
        : 
          m_parentCodInd(parentCodInd),
          m_greenery(0.0f),
          m_isSeed(true),
          
          m_size(size),
          m_angle(angle)
    { }
    
    DnaCodon(int parentCodInd, int size, int angle, float greenery)
        : m_parentCodInd(parentCodInd),
          m_greenery(greenery),
          m_isSeed(false),
          
          m_size(size),
          m_angle(angle)
    { }
    
    DnaCodon(std::ifstream &in) {load(in);}
    
    
    
    int parentCodInd() {return m_parentCodInd;}
    int greenery() {return m_greenery;}
    bool isSeed() {return m_isSeed;}
    
    float size() {return m_size;}
    float angle() {return m_angle;}
    
    void changeParentCodInd(int parentCodInd) {m_parentCodInd = parentCodInd;}
    
    
    
    DnaCodon & operator=(const DnaCodon &c);
    
    void save(std::ofstream &out);
    void load(std::ifstream &in);
    
private:
    int m_parentCodInd;
    float m_greenery;
    bool m_isSeed;
    
    float m_size;
    float m_angle;
};



class Dna
{
public:
    Dna();
    
    DnaCodon codon() {return m_codons[m_curCodonI];}
    void nextCodon()
    {m_curCodonI = std::min<int>(m_curCodonI + 1, m_codons.size());}
    bool codonsAreOver() {return m_curCodonI >= int(m_codons.size());}
    
    void mutate();
    
    void save(std::ofstream &out);
    void load(std::ifstream &in);
    
    Dna & operator=(const Dna &dna);
    
private:
    std::vector<DnaCodon> m_codons;
    int m_curCodonI;
    
    
    
    bool canAddCodon(DnaCodon c);
    void addCodon(DnaCodon c);
    
    bool * getRemCodsArray(int remCodInd);
    bool canRemoveCodon();
    bool canRemoveCodon(int codInd);
    void removeCodon(int codInd);
    
    bool canChangeCodon();
    bool canChangeCodon(int tarCodInd, DnaCodon c);
    void changeCodon(int tarCodInd, DnaCodon c);
    
    DnaCodon randomizeCodon();
    
    static float maxSize() {return 2.0f;}
    static float minSize() {return 0.3f;}
    static int seedAppearChance() {return 10;}
    static int mutAddChance() {return 5;}
    static int mutRemChance() {return 1;}
    static int mutChangeChance() {return 2;}
    static int mutChanceSum()
    {return mutAddChance() + mutRemChance() + mutChangeChance();}
};



#endif // H_DNA

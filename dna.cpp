#include "dna.h"



// DnaCodon



DnaCodon & DnaCodon::operator=(const DnaCodon &c)
{
    m_parentCodInd = c.m_parentCodInd;
    m_greenery = c.m_greenery;
    m_isSeed = c.m_isSeed;
    
    m_size = c.m_size;
    m_angle = c.m_angle;
    
    return *this;
}



void DnaCodon::save(std::ofstream &out)
{
    out << m_parentCodInd << ' ';
    out << m_greenery   << ' ';
    out << m_isSeed << ' ';
    
    out << m_size   << ' ';
    out << m_angle  << ' ';
}

void DnaCodon::load(std::ifstream &in)
{
    in >> m_parentCodInd;
    in >> m_greenery;
    in >> m_isSeed;
    
    in >> m_size;
    in >> m_angle;
}



// Dna



Dna::Dna()
    : m_codons(),
      m_curCodonI(0)
{
    
}



void Dna::mutate()
{
    int rnd = std::rand() % mutChanceSum();
    if (rnd < mutAddChance())
    {
        while (true)
        {
            DnaCodon c(randomizeCodon());
            if (canAddCodon(c))
            {
                m_codons.push_back(c);
                break;
            }
        }
    }
    else if (rnd < mutAddChance() + mutRemChance())
    {
        if (!canRemoveCodon())
            return;
        
        while (true)
        {
            int codInd = std::rand() % m_codons.size();
            if (canRemoveCodon(codInd))
            {
                removeCodon(codInd);
                break;
            }
        }
    }
    else if (rnd < mutAddChance() + mutRemChance() + mutChangeChance())
    {
        if (!canChangeCodon())
            return;
        
        while (true)
        {
            DnaCodon c(randomizeCodon());
            int codInd = std::rand() % m_codons.size();
            if (canChangeCodon(codInd, c))
            {
                changeCodon(codInd, c);
                break;
            }
        }
    }
}



void Dna::save(std::ofstream &out)
{
    out << m_codons.size() << ' ';
    for (DnaCodon c : m_codons)
        c.save(out);
    out << m_curCodonI << ' ';
}

void Dna::load(std::ifstream &in)
{
    int size;
    in >> size;
    for (int i = 0; i < size; ++i)
    {
        m_codons.push_back(DnaCodon(in));
    }
    in >> m_curCodonI;
}



Dna & Dna::operator=(const Dna &dna)
{
    m_codons = dna.m_codons;
    m_curCodonI = 0;
    return *this;
}



// private::



bool Dna::canAddCodon(DnaCodon c)
{
    return !m_codons[c.parentCodInd()].isSeed();
}

void Dna::addCodon(DnaCodon c)
{
    m_codons.push_back(c);
}



bool * Dna::getRemCodsArray(int remCodInd)
{
    bool *willRemInds = new bool[m_codons.size()];
    for (int i = 0; i < int(m_codons.size()); ++i)
        willRemInds[i] = false;
    willRemInds[remCodInd] = true;
    
    for (int i = remCodInd + 1; i < int(m_codons.size()); ++i)
    {
        int parCodInd = m_codons[i].parentCodInd();
        willRemInds[i] |= willRemInds[parCodInd];
    }
    
    return willRemInds;
}

bool Dna::canRemoveCodon()
{
    return m_codons.size() > 3;
}

bool Dna::canRemoveCodon(int codInd)
{
    bool *willRemInds = getRemCodsArray(codInd);
    
    int remCount = 0;
    for (int i = 0; i < int(m_codons.size()); ++i)
        remCount += willRemInds[i];
        
    delete willRemInds;
    
    return int(m_codons.size()) - remCount >= 3;
}

void Dna::removeCodon(int codInd)
{
    bool *willRemInds = getRemCodsArray(codInd);
    
    for (int i = int(m_codons.size()) - 1; i >= 0; --i)
    {
        if (willRemInds[i])
            m_codons.erase(m_codons.begin() + i);
    }
    
    delete willRemInds;
}



bool Dna::canChangeCodon()
{
    return m_codons.size() > 3;
}

bool Dna::canChangeCodon(int tarCodInd, DnaCodon c)
{
    bool codHaveChild = false;
    for (int i = 0; i < int(m_codons.size()); ++i)
    {
        codHaveChild |= c.parentCodInd() == tarCodInd;
    }
    
    return !(c.isSeed() && codHaveChild);
}

void Dna::changeCodon(int tarCodInd, DnaCodon c)
{
    c.changeParentCodInd(m_codons[tarCodInd].parentCodInd());
    m_codons[tarCodInd] = c;
}



DnaCodon Dna::randomizeCodon()
{
    int parentCodInd = std::rand() % m_codons.size();
    float size = linearInterp<float, float>(
                minSize(), 0, maxSize(), RAND_MAX - 1, std::rand()
                );
    float angle
            = 2 * glm::pi<float>() * (std::rand() / float(RAND_MAX));
    
    if (std::rand() % seedAppearChance() == 0)
        return DnaCodon(parentCodInd, size, angle);
    else
        return DnaCodon(
                        parentCodInd, size, angle,
                        std::rand() / float(RAND_MAX)
                        );
}

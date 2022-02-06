#ifndef H_ID_OBJECT
#define H_ID_OBJECT



#include <random>
#include <set>



class IdObject
{
public:
    IdObject()
    {
        unsigned long long id;
        do
        {
            id = rand() * rand() * rand() * rand();
        }
        while (m_ids.find(id) != m_ids.end());
    }
    virtual ~IdObject()
    {
        m_ids.erase(m_ids.find(m_id));
    }
    
    unsigned long long id() {return m_id;}
    
private:
    static std::set<unsigned long long> m_ids;
    
    unsigned long long m_id;
};



std::set<unsigned long long> IdObject::m_ids = std::set<unsigned long long>();



#endif // H_ID_OBJECT

#ifndef H_ID_OBJECT
#define H_ID_OBJECT



#include <random>
#include <set>



class IdObject
{
public:
    IdObject();
    virtual ~IdObject();
    
    unsigned long long id() {return m_id;}
    
private:
    static std::set<unsigned long long> m_ids;
    
    unsigned long long m_id;
};



#endif // H_ID_OBJECT

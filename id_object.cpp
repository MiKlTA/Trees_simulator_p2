#include "id_object.h"



std::set<unsigned long long> IdObject::m_ids = std::set<unsigned long long>();



IdObject::IdObject()
{
    unsigned long long id;
    do
    {
        id = std::rand() * std::rand() * std::rand() * std::rand();
    }
    while (m_ids.find(id) != m_ids.end());
}

IdObject::~IdObject()
{
    m_ids.erase(m_ids.find(m_id));
}

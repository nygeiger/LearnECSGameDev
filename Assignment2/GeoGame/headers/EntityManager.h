#ifndef EntityManager_H
#define EntityManager_H

#include <memory>
#include <vector>
#include <map>

#include "./Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

/*
Factory class for entities
*/
class EntityManager {

    size_t m_totalEntities = 0;
    // std::vector<std::shared_ptr<Entity>> m_entitiesToAdd;
    EntityVec m_entities;
    EntityVec m_entitiesToAdd;
    EntityMap m_entityMap;
    // std::map<std::string, EntityVec> m_entityMap;
    
    void removeDeadEntities(EntityVec & vec);

    public:
        EntityManager();

        void update();

        std::shared_ptr<Entity> addEntity(const std::string & tag);

        const EntityVec & getEntities();
        const EntityVec & getEntities(const std::string & tag);
};

#endif
#ifndef ECS
#define ECS

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "../Constants.hpp"

using namespace std;

class Component;   // Contains a link to entity of which this is a part
class Entity;      // Contains all the components
class Manager;     // All Entites

using ComponentID = size_t;
using Group = size_t;

// ========================================================================================
inline ComponentID getNewComponentTypeID(){
    static ComponentID lastID = 0u;
    return lastID++;
}
// ========================================================================================
template <typename T> inline ComponentID getComponentTypeID() noexcept{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}
// ========================================================================================

// Using the Above two functions will ensure that for each typename T, a unique ID will be assigned
// For further clarification, look at "Example_For_GetComponentTypeID.cpp" in the same folder.

// Possible explanation -> static line will be compiled only 1 time and will be skipped on future occurences

// GeeksForGeeks 

// When a variable is declared as static, space for it gets allocated for the lifetime of the program. 
// Even if the function is called multiple times, space for the static variable is allocated only once and the value of variable in the previous call gets carried through the next function call. 


// Similar to const, difference being that we can use constexpr for any datatype ( including string, functions and classes ) 

// constexpr size_t maxGroups = 32;
// constexpr size_t maxComponents = 32;

// =================================================================================
// maxGroups and maxComponents are added to Constants.hpp file
// =================================================================================

// using bitset library improves the efficiency ( Demerit being, size of array should be know during compile time)
using ComponentBitset = bitset<MAX_COMPONENTS>;
using ComponentArray = array<Component*, MAX_COMPONENTS>;

using GroupBitset = bitset<MAX_GROUPS>;

class Component
{
    public:
        Entity* entity; // Each component has a link to the link it belongs to.
        virtual void init(){}   // Initialize the component
        virtual void update(){} // Update the component
        virtual void draw(){}   // By using "Virtual" keyword, we can overwrite the method in 
        virtual ~Component(){}  // parent class by overwriting the method in derived class.
                                // Can't use virtual keyword for constructor function                
};

class Entity
{
    private:
        Manager& manager;
        bool active = true; // To check if current entity is Active or not

// ========================================================================================
        
        vector< unique_ptr<Component> >  components; 

        // Unique_ptr
        // It allows exactly one owner of the underlying pointer.
        // Any attempt to make a copy of unique_ptr will cause a compile-time error.
        // Link to GeeksForGeeks -> https://www.geeksforgeeks.org/auto_ptr-unique_ptr-shared_ptr-weak_ptr-2/
        
        // So this ensures that each component is linked at most one time with each entity
// ========================================================================================
        ComponentArray  componentArray ; 
        ComponentBitset componentBitset;
        GroupBitset     groupBitset;
    
    public:
        
        // Constructor
        Entity(Manager& mManager) : manager(mManager) {}

        void update()
        {
            for(auto& c : components) c->update(); // Iterate over all the components linked to this Entity and Update them            
        }

        void draw()
        {
            for(auto& c : components) c->draw();   // Iterate and draw them
        }

        bool isActive() const 
        {
            return active;
        }
        
        void destroy() 
        { 
            active = false; 
        }

        bool hasGroup(Group mGroup)
        {
            return groupBitset[mGroup];
        }

        void addGroup(Group mGroup);
        void delGroup(Group mGroup)
        {
            groupBitset[mGroup] = false;
        }
        

        template<typename T> bool hasComponent() const
        {
            return componentBitset[getComponentTypeID<T>()];
        }

        template<typename T, typename... TArgs > T& addComponent(TArgs&&... mArgs)
        {
            // T* c( new T( forward<TArgs>(mArgs)... ) );
            T* c(new T(std::forward<TArgs>(mArgs)...));
            c->entity = this;
            unique_ptr<Component> uPtr{ c };
            components.emplace_back(move(uPtr)); // Will overwrite the pointer if any in the components vector

            componentArray[getComponentTypeID<T>()] = c;
            componentBitset[getComponentTypeID<T>()] = true;

            c-> init();
            return *c;
        }

        // FOR T&
        // https://isocpp.org/wiki/faq/const-correctness#ref-to-const         

        template<typename T> T& getComponent() const
        {
            // if(!hasComponent<T>())return nullptr;       
            auto ptr(componentArray[getComponentTypeID<T>()]);
            return *static_cast<T*>(ptr);
        }
        
        // Returns the component and not a pointer to the componenet.
};

class Manager
{
    private:
        vector< unique_ptr<Entity> > entities;
        array < vector<Entity*>, MAX_GROUPS > groupedEntites;

    public:
        void update()
        {
            for(auto& e: entities) e->update();
        }
        void draw()
        {
            for(auto& e: entities) e->draw();
        }
        void refresh()
        {   

            for(unsigned int i = 0; i< MAX_GROUPS; i++)
            {
                groupedEntites[i].erase( remove_if( begin(groupedEntites[i]), end(groupedEntites[i]),
                [i](Entity* mEntity)
                {
                    return !mEntity->isActive() || !mEntity->hasGroup(i);
                }),
                    end(groupedEntites[i])
                );
            }

            // Removes elements from a sequence using a predicate            
            entities.erase( remove_if( begin(entities), end(entities), 
            [](const unique_ptr<Entity> &mEntity)
            {
                return !mEntity->isActive(); // Will erase if evaluated to true
            }),
                std::end(entities)
            );
        }

        void AddToGroup(Entity* mEntity, Group mGroup)
        {
            groupedEntites[mGroup].emplace_back( mEntity);
        }

        vector<Entity*>& getGroup(Group mGroup)
        {
            return groupedEntites[mGroup];
        } 

        Entity& addEntity()
        {
            Entity* e = new Entity(*this);
            unique_ptr<Entity> uPtr{ e };
            entities.emplace_back(std::move(uPtr));
            return *e;
        }
};

#endif
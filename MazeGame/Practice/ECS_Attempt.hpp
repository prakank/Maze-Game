#ifndef ECS
#define ECS

#include<vector>
#include<memory>
#include<array>
#include<bitset>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;

constexpr ComponentID maxComponents = 32;

using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

inline ComponentID getComponentTypeID()
{
    static ComponentID lastID = 0;
    return lastID++;
}

template<typename T> ComponentID getComponentTypeID() noexcept
{
    static ComponentID type = getComponentTypeID();
    return type;
}

class Component
{
    public:
        Entity* entity;
        virtual void draw();
        virtual void update();        
        virtual ~Component();
        /*virtual Component();*/  // Constructor should always be non-virtual      

};

class Entity
{
    private:

        bool Active = true;
        std::vector< std::unique_ptr<Component>> components;
        ComponentBitset componentBitset;
        ComponentArray ComponentArray;

    public:
        
        bool isActive(){return Active;}
        void destroy(){Active = false;}
        void update()
        {
            for(auto& c: components)c->update();
            for(auto& c: components)c->draw();
        }

        void addComponent();
        bool hasComponent();
        Component getComponent();

        



    
};


#endif
#include <iostream>
#include <string>

class Entity
{
public:
    Entity()
    {
        x = 0;
        y = 0;
        name = "name";
    }
    Entity(std::string name):name(name)
    {

    }
    virtual std::string GetName()=0; // make GetName a virtual function
    void setX(float x){this->x = x;}
    void setY(float y){this->y = y;}
protected:
    float x, y;
    std::string name;
};

class Player: public Entity
{
public:
    std::string GetName() override
    {
        
        return name;
    }
};

int main()
{
    // entity e cannot be instantiated because it contains pure virtual function (interface), it is an abstract class
    // Entity e;  compile error here
    // Player class cannot be instantiated either if it does not inplements GetName()
    Player player;
    std::cout << player.GetName() << std::endl;
    return 0;
}
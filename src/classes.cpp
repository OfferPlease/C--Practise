#include <iostream>
/* When a child class is created, the constructor of its parent class will be called and then its own constructor will be called
by default
*/
class Entity
{
    public:
    Entity(){
        x = 0;
        y = 0;
        a = 0.1;
        std::cout << "the Default Entity constructor is called!" << std::endl;
    }
    Entity(float x, float y):x(x), y(y)
    {
        std::cout << "the constructor with parameter is called!" << std::endl;
    }
    void print(){
        std::cout << "x: " << x <<" "<< "y: " << y << std::endl;
    }

    void Move(float xa, float ya){
        x += xa;
        y += ya;
    }
    
    virtual void printName() const
    {
        std::cout << "Entity" << std::endl;
    }

    // virtual void printName()=0;

    ~Entity(){
        std::cout << "The Entiry destructor is called!" << std::endl;
    }
    void setX(float x)
    {
        this->x = x;
    }
    void setY(float y)
    {
        this->y = y;
    }
    void setA(float a)
    {
        this->a = a;
    }
    private:
    float x;
    float y;
    protected:
    float a;
};

class Player : public Entity
{
    private:
    const char* name;
    public:
    void printName() const override
    {
        std::cout<<name<<std::endl;
    }

    Player()
    {
        name = "Player";
        std::cout << "The defualt Player constructor is called!" << std::endl;
    }
    Player(const std::string& name)
    : name(name.c_str())
    {
        std::cout << "The Player constructor is called!" << std::endl;
    }

    void MoveA(float x, float y)
    {
        this->setX(x * a);
        this->setY(y * a);
    }

    ~Player()
    {
        std::cout << "The Player destructor is called" << std::endl;
    }
};

void func()
{
    Entity v;
    v.print();
}

void getEntityName(Entity* entity){
    entity->printName();
}

int main(){
    // player has access to all public member in Entity
    std::cout << sizeof(Player) << std::endl;
    std::cout << sizeof(Entity) << std::endl;
    Player player;
    player.Move(1,1);
    player.print();
    player.printName();
    // access to private member of Entity will cause compling error
    // player.x;
    // access to protected memver of Entity outside Player will cause compiling error
    // player.a;
    // but we can access protected member of Entity inside Player
    player.setA(2.0);
    player.MoveA(1.0, 2.0);
    player.print();
    Entity *e = new Entity(1.0f, 2.0f);
    Player *p = new Player("Sheldon");
    e->printName();
    p->printName();

    // refer to a player object like an entity
    // in this step the entity constructor and the player constructor will both be called
    Entity *ep = new Player("Rajsh"); 
    // but here "Entity" will be printed because ep will be treated as Entity object
    getEntityName(ep);

    // check if default constructor is called when creating an array of object
    Entity arrEntiry[3];
    arrEntiry[1].printName();

    Player arrPlayer[3];
    arrPlayer[1].printName();
    return 0;
}
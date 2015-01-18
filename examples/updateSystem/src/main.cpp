#include <iostream>

#include <MiraiProject/updateSystem/Updatable.hpp>
#include <MiraiProject/updateSystem/UpdateModule.hpp>

#include <SFML/System/Time.hpp>

using namespace std;
//We create a class which depends of mp::Updatable.
class SomeClass : public mp::Updatable
{
    public:
        SomeClass(std::string key = "default") : mp::Updatable(key)
        {

        };
        //Since void mp::Updatable::Update() is virtual, it's necessary to create this function.
        void update(sf::Time deltaTime)
        {
            std::cout << deltaTime.asSeconds() << std::endl;
        };

        //A random function.
        int addition(int a, int b)
        {
            return a+b;
        };
};

int main()
{
    SomeClass * a = new SomeClass("MiraiProject");
    SomeClass * b = new SomeClass();

    //Update all function which depend of mp::Updatable.
    mp::UpdateModule::update(sf::seconds(2.55486f), "default");

    //We delete b.
    delete b;

    //We call a random function.
    std::cout << a->addition(15,23) << std::endl;

    //Another Updatable.
    mp::UpdateModule::update(sf::seconds(3.5f), "MiraiProject");

    return 0;
}
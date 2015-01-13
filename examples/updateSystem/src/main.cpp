#include <iostream>
#include <MiraiProject/updateSystem/Updatable.hpp>
#include <MiraiProject/updateSystem/UpdateModule.hpp>

using namespace std;
//We create a class which depends of mp::Updatable.
class SomeClass : public mp::Updatable
{
	public:
		//Since void mp::Updatable::Update() is virtual, it's necessary to create this function.
		void Update(float delta_time)
		{
			std::cout << delta_time << std::endl;
		};
		
		//A random function.
		int addition(int a, int b)
		{
			return a+b;
		};
};

int main()
{
	SomeClass * a = new SomeClass();
	SomeClass * b = new SomeClass();
	
	//Update all function which depend of mp::Updatable.
	mp::UpdateModule::Update(2.55486f);
	
	//We delete b.
	delete b;
	
	//We call a random function.
	std::cout << a->addition(15,23) << std::endl;
	
	//Another Updatable.
	mp::UpdateModule::Update(3.5f);
	
	return 0;
}

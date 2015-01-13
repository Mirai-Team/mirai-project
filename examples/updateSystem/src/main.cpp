#include <iostream>
#include <MiraiProject/updateSystem/Updatable.hpp>
#include <MiraiProject/updateSystem/UpdateModule.hpp>

using namespace std;
class SomeClass : public mp::Updatable
{
	public:
		void Update(float delta_time)
		{
			std::cout << delta_time << std::endl;
		};
};

int main()
{
	SomeClass * a = new SomeClass();
	SomeClass * b = new SomeClass();
	mp::UpdateModule::Update(2.55486f);
	delete b;
	mp::UpdateModule::Update(3.5f);
	return 0;
}

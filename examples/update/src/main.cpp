#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

class Updatable;
class UpdateModule
{
	public:
		static void AddUpdater(shared_ptr<Updatable> updatable);
		static void Update(float delta_time);
	private:
		static vector<shared_ptr<Updatable>> updatelist;
};

vector<shared_ptr<Updatable>> UpdateModule::updatelist;

void UpdateModule::AddUpdater(shared_ptr<Updatable> updatable)
{
	updatelist.push_back(updatable);
}

class Updatable
{
	public:
		virtual void Update(float delta_time) = 0;
		Updatable();
		virtual ~Updatable();
};
Updatable::Updatable()
{
	shared_ptr<Updatable> ptr(this);
	UpdateModule::AddUpdater(ptr);
}
Updatable::~Updatable()
{
	
}

void UpdateModule::Update(float delta_time)
{
	for(unsigned int i = 0; i < updatelist.size(); i++)
		updatelist[i]->Update(delta_time);
}
class SomeClass : public Updatable
{
	public:
		void Update(float delta_time)
		{
			std::cout << delta_time << std::endl;
		};
};

int main()
{
	SomeClass a, b;
	UpdateModule::Update(05.f);
	return 0;
}

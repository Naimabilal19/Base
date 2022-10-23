#include <iostream>
#include <string>
using namespace std;

class Base
{
	int people_on_base;
	int vehicles_on_base;
	double petrol_on_base;
	double goods_on_base;
public:
	Base() = default;
	Base(int p, int v, double pt, double g)
	{
		people_on_base = p;
		vehicles_on_base = v;
		petrol_on_base = pt;
		goods_on_base = g;
	}
	void SetPeople(int a)
	{
		people_on_base = a;
	}
	int GetPeople()
	{
		return people_on_base;
	}

	void SetVehicles(int b)
	{
		vehicles_on_base = b;
	}
	int GetVehicles()
	{
		return vehicles_on_base;
	}

	void SetPetrol(int c)
	{
		petrol_on_base = c;
	}
	double GetPetrol()
	{
		return petrol_on_base;
	}

	void SetGoods(int d)
	{
		goods_on_base = d;
	}
	double GetGoods()
	{
		return goods_on_base;
	}

	void Print()
	{
		cout << "People_on_base " << people_on_base << endl;
		cout << "Vehicles_on_base " << vehicles_on_base << endl;
		cout << "Petrol_on_base " << petrol_on_base << endl;
		cout << "Goods_on_base " << goods_on_base << endl;
	}
};

class Vehicle
{
protected:
	double petrol;
	double volume;
public:
	Vehicle() = default;
	Vehicle(double petrol_amount, double tank_volume)
	{
		petrol = petrol_amount;
		volume = tank_volume;
	}
	void SetTankVolume(double tv)
	{
		volume = tv;
	}
	double getTankVolume()
	{
		return volume;
	}
	void SetPetrolVolume(double p)
	{
		petrol = p;
	}
	double getPetrolVolume()
	{
		return petrol;
	}
	virtual void arrive(Base& b)
	{
		b.SetPetrol(b.GetPeople() - 40);
		b.SetVehicles(b.GetVehicles() + 1);
		b.SetPeople(b.GetPeople() + 1);
	}
	virtual bool leave(Base& b, Vehicle& a)
	{
		if (b.GetPetrol() > 0)
		{
			double t = a.getTankVolume() - a.getPetrolVolume();
			if (t >= b.GetPetrol())
			{
				SetPetrolVolume(getPetrolVolume() + b.GetPetrol());
			}
			else
			{
				SetPetrolVolume(getPetrolVolume() + t);
			}
		}
		if (getPetrolVolume() >= 40 && b.GetPeople() >= 1)
		{
			b.SetPeople(b.GetPeople() - 1);
			b.SetVehicles(b.GetVehicles() - 1);
			return true;
		}
		else
		{
			return false;
		}
	}
	virtual void Print()
	{
		cout << "Petrol = " << petrol << endl;
		cout << "Tank = " << volume << endl;
	}
};

class Bus :public Vehicle
{
	int max_pass;
	int people;
public:
	Bus() = default;
	Bus(double p, double v, int m, int pl) :Vehicle(p, v)
	{
		max_pass = m;
		people = pl;
	}
	void SetPeopleCount(int a)
	{
		people = a;
	}
	int getPeopleCount()
	{
		return people;
	}
	void SetMaxPeople(int b)
	{
		max_pass = b;
	}
	int getMaxPeople()
	{
		return max_pass;
	}
	void Arrive(Base& b, Vehicle& a)
	{
		Vehicle::arrive(b);
		b.SetPeople(b.GetPeople() + getPeopleCount());
		SetPeopleCount(0);
	}
	bool Leave(Base& b, Vehicle& a)
	{
		if (b.GetPeople() >= 0)
		{
			int temp = getMaxPeople() - getPeopleCount();
			if (temp >= b.GetPeople())
			{
				SetPeopleCount(getPeopleCount() + b.GetPeople());
				b.SetPeople(0);
			}
			else
			{
				SetPeopleCount(getPeopleCount() + temp);
				b.SetPeople(b.GetPeople() - temp);
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	void Print()
	{
		Vehicle::Print();
		cout << "Max passengers = " << max_pass << endl;
		cout << "People = " << people << endl;
	}
	};

	class Truck :public Vehicle
	{
	protected:
		double cargo;
		double max_load;
	public:
		Truck() = default;
		Truck(double p, double v, double c, double m) :Vehicle(p, v)
		{
			cargo = c;
			max_load = m;
		}
		void setCurrentLoad(int a)
		{
			cargo = a;
		}
		double getCurrentLoad()
		{
			return cargo;
		}
		void setMaxLoad(double b)
		{
			max_load = b;
		}
		double getMaxLoad()
		{
			return max_load;
		}
		void arrive(Base& b, Vehicle& a)
		{
			Vehicle::arrive(b);
			b.SetGoods(b.GetGoods() + getMaxLoad());
			setCurrentLoad(0);
		}
		bool leave(Base& b, Vehicle& a)
		{

			if (b.GetGoods() > 0)
			{
				int temp = getMaxLoad() - getCurrentLoad();
				if (temp >= b.GetGoods())
				{
					setCurrentLoad(getCurrentLoad() + b.GetGoods());
					b.SetGoods(0);
				}
				else
				{
					setCurrentLoad(getCurrentLoad() + temp);
					b.SetGoods(b.GetGoods() - temp);
				}
				return true;
			}
			else
			{
				return false;
			}


		}
		void Print()
		{
			Vehicle::Print();
			cout << "Load: " << cargo << endl;
			cout << "Max_load: " << max_load << endl;
		}
	};

	int main()
	{
		Base obj(450, 600, 3100, 10);
		obj.Print();
		cout << endl;

		Vehicle* obj1 = new Truck(40, 500, 60, 210);
		obj1->Print();
		cout << endl;

		Vehicle* obj2 = new Bus(15, 50, 16, 8);
		obj2->Print();
		cout << endl;
	}

#include <iostream>
#include <vector>
#include <stack>
#include "helper.h"
#include <map>
class Shape
{
public:
	virtual void Draw() = 0;
	virtual ~Shape() {}

	//모든 도형은 자신의 복사본을 생성할 수 있어야한다.
	virtual Shape* Clone() = 0;
};

class Rect : public Shape
{
public:
	void Draw() override { std::cout << "Draw Rect" << std::endl; }
	
	Rect* Clone() override { return new Rect(*this); }

	static Shape* Create()
	{
		return new Rect;
	}
};

class Circle : public Shape
{
public:
	void Draw() override { std::cout << "Draw Circle" << std::endl; }
	Circle* Clone() override { return new Circle(*this); }
	static Shape* Create()
	{
		return new Circle;
	}

};

class ShapeFactory
{
	MAKE_SINGLETON(ShapeFactory)

	std::map<int, Shape* > prototype_map;//도형번호:견본
public:
	void Register(int key, Shape* sample)
	{
		prototype_map[key] = sample;
	}

	Shape* Create(int type)
	{
		Shape* p = nullptr;

		if (prototype_map[type] != nullptr)
		{
			p = prototype_map[type]->Clone();	//이렇게 객체를 복제하여 생성하는것을
												//Prototype 패턴이라고 한다.
		}
		return p;
	}
};

int main()
{
	std::vector<Shape*> v;

	ShapeFactory& factory = ShapeFactory::getInstance();

	Rect* redRect = new Rect;	//빨간색 사각형이라고 가정
	Rect* blueRect = new Rect;
	Circle* redCircle = new Circle;

	//공장에 자주 사용되는 객체의 견본(prototype)을 등록합니다.
	factory.Register(1, redRect);
	factory.Register(2, blueRect);
	factory.Register(3, redCircle);

	//factory.ShowSample(); //등록된 모든 견본 제품을 보여준다. 나중에 만들어 보기.

	while (1)
	{
		int cmd;
		std::cin >> cmd;

		if (cmd >= 1 && cmd <= 7)
		{
			Shape* p = factory.Create(cmd);
			if (p != nullptr)
				v.push_back(p);
		}
		else if (cmd == 9)
		{
			for (auto p : v)
				p->Draw();
		}
	}
}



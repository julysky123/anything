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
};

class ShapeFactory
{
	MAKE_SINGLETON(ShapeFactory)

		typedef Shape* (*CREATE_FUNCTION)();

	std::map<int, CREATE_FUNCTION> create_map;//도형번호:생성함수를 맵에 보관
public:
	void Register(int key, CREATE_FUNCTION f)
	{
		create_map[key] = f;
	}

	Shape* Create(int type)
	{
		Shape* p = nullptr;

		if (create_map[type] != nullptr)
		{
			p = create_map[type]();	//생성함수를 사용해서 도형객체 생성.
		}
		return p;
	}
};

class RegisterShape
{
public:
	RegisterShape(int key, Shape* (*f)())
	{
		ShapeFactory& factory = ShapeFactory::getInstance();
		factory.Register(key, f);
	}
};

//새로운 도형을 만들 때 지켜야 하는 규칙을 매크로로 제공하면 편리.
#define REGISTER_SHAPE(classname)					\
	static Shape* Create() { return new classname;}	\
	static RegisterShape rs;

#define REGISTER_IMPLEMENT(key, classname)			\
	RegisterShape classname::rs(key, &classname::Create);


class Rect : public Shape
{
public:
	void Draw() override { std::cout << "Draw Rect" << std::endl; }
	REGISTER_SHAPE(Rect)
};
REGISTER_IMPLEMENT(1,Rect)	//팩토리가 번호를 순차적으로 매기게 해도 됨.

class Circle : public Shape
{
public:
	void Draw() override { std::cout << "Draw Circle" << std::endl; }
	REGISTER_SHAPE(Circle)
};
REGISTER_IMPLEMENT(2, Circle)

class Triangle : public Shape
{
public:
	void Draw() override { std::cout << "Draw Triangle" << std::endl; }
	REGISTER_SHAPE(Triangle)
};
REGISTER_IMPLEMENT(3, Triangle)

int main()
{
	std::vector<Shape*> v;

	ShapeFactory& factory = ShapeFactory::getInstance();

	// factory.ShowRegisteredShape();//나중에 만들어보기.
	//공장에 생성함수만 등록하지 말고 클래스이름도 같이 보관하기.
	//# 매크로 사용하면됨.
	// 결과 : 1.Rect		2.Circle	3.Triangle

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



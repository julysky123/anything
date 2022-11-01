#include <stdio.h>
enum class ValType {DINT, DOUBLE};
enum class ObType {VARIABLE,LITERAL};
class Value {
	ValType _type;
protected:
	Value(ValType type) : _type(type) {}
public:
	virtual Value* operator+(Value*& ref) {
		return nullptr;
	}
};

class Dint : public Value {
	long long _val;
public:
	Dint(long long val) : _val(val), Value(ValType::DINT) {}
	Value* operator+ (Value*& ref) override {
		printf("dint : %lld\n", _val + ((Dint*)ref)->_val);
		return new Dint(_val + ((Dint*)ref)->_val);
	}

};

class Double : public Value {
	double _val;
public:
	Double(double val) : _val(val), Value(ValType::DOUBLE) {}
	Value* operator+ (Value*& ref) override {
		printf("double : %lf\n", _val + ((Double*)ref)->_val);
		return new Double(_val + ((Double*)ref)->_val);
	}
};


class Object {
protected:
	ObType _type;
	Object(Value* val, ObType type) : _val(val), _type(type) {}

public:
	Value* _val;
	virtual Object* operator+(Object& b) {
		printf("object +\n");
		return new Object(new Dint(1), ObType::VARIABLE);
	}
};

class Variable : public Object{
	
public:
	Variable(Value* val) : Object(val, ObType::VARIABLE){}
	Object* operator+(Object& b) override {
		
		return new Variable((*this->_val) + b._val);
	}

};


int main() {

	Object* var1 = new Variable(new Dint(3));

	Object* var2 = *var1 + *var1;
	
	Object* var3 = new Variable(new Double(3.5));
	Object* var4 = *var3 + *var3;

}

template<typename T> class RefBase
{
	mutable int refCount = 0;	
protected:

	~RefBase() { cout << "RefBase 파괴" << endl; }
public:

	void AddRef() const { ++refCount; }
	void Release() const
	{
		if (--refCount == 0)
		
			delete static_cast<const T*>(this);	
	}
};

template<typename T>
class AutoPtr {
	T* obj;
public:
	AutoPtr(T* p = nullptr) : obj(p) { if (obj)  obj->AddRef(); }
	AutoPtr(const AutoPtr<T>& ap) : obj(ap.obj) { if (obj)  obj->AddRef(); }
	~AutoPtr() {
		if (obj) obj->Release();
	}

	T* operator->() {return obj;}
	T& operator*() {return *obj;}
};

//사용 예제
int main()
{
  //직접 포인터 호출 금지.
	//Truck* p1 = new Truck;	//객체가 아니고 포인터. 관리하기 어려움.
	
	//참조계수를 자동으로 관리할 수 있는 스마트 포인터로 관리. (객체)
	//객체 생성시 addref
	//객체 소멸시 release
	AutoPtr<Truck> p1 = new Truck;
	AutoPtr<Truck> p2 = p1;
		
	p1->Go();

}

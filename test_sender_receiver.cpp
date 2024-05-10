#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <list>

using namespace std;
using EventHandler_AChanged=function<void(int)>;

class Sender{
private:
	int a;
	int b;
	list<EventHandler_AChanged> onChangeA;
public:
	Sender(): a(10),b(10){}
	virtual ~Sender(){}
	void setA(int _a){
		a=_a; 
		for(EventHandler_AChanged f: onChangeA){
			f(a);
		}
	}
	void setB(int _b){b=_b;}
	void addReceiver(EventHandler_AChanged r){onChangeA.push_back(r);}
};
class Receiver{
private:
	int c;
public:
	Receiver(): c(0){}
	virtual ~Receiver(){}
	void OnChangeA(int newA){ c+=newA;
		cout<<"receiver: a in Sender changed. c is "<<
		 c<<endl;
		}
	
};
int main()
{
	Receiver r;
	Sender a;
	a.setA(90);
	EventHandler_AChanged f=std::bind(r.OnChangeA,&r,
		std::placeholders::_1);
	a.addReceiver(f);
	a.setB(40);
	a.setA(10);
	a.setA(20);
}
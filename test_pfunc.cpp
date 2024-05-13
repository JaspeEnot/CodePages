#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <list>

using namespace std;

class TestClass{
private:
	int v;
	string s;
public:
	TestClass(){v=0;s="aaaaaa\n";}
	int f(int _v){v+=_v; cout<<v<<endl; return v;}
	void SumString(string a, string b, string c){ s+=a; s+=b; s+=c; }
	string GetS(){return s;} 
	void g(int _v){v+=10;}
};
template< class TObj, class TFunc >
class PFunc
{
	private:
		TObj* obj;
		TFunc func;
	public:
		PFunc(): obj(nullptr){}
		virtual ~PFunc(){ obj=nullptr; }
		template<class ...T>
		auto operator()(T... v){ return ((*obj).*func)(v...); }

		static PFunc<TObj,TFunc> Make(TObj& obj, TFunc func){
			PFunc<TObj,TFunc> pF;
			pF.obj=&obj;
			pF.func=func;
			return pF;
		}
};
auto MakeFunc(auto func)
{
	auto f1=[=](auto a){return func(a);};
	return f1;
}
template< class TObj, class TFunc >
auto MakePFunc(TObj& obj, TFunc func){
	return PFunc<TObj,TFunc>::Make(obj,func);
}

void runInt(auto f,int v)
{
	f(v);
}
template<class ...T>
void run(auto f,T... v)
{
	f(v...);
}

TestClass b;
auto sumString=MakePFunc(b,b.SumString);
using PStringFunc=decltype(sumString);
class TestPStringFunc{
private:
	PStringFunc pf1;
public:
	TestPStringFunc(){}
	virtual ~TestPStringFunc(){}
	void run_pf1()
	{
		pf1("\nuu","vv","fs");
	}
	void set_pf(PStringFunc& p)
	{
		pf1=p;
	}
};
	
int main()
{
	TestClass a;
	auto f1=MakePFunc(a,a.f);
	f1(10);
	f1(100);
	f1(5);
	auto sumString=MakePFunc(a,a.SumString);
	sumString("test ","a",",b\n");
	string s=a.GetS();
	cout<<s<<endl;
	runInt(f1,200);
	run(sumString,"aaa "," ----- ", "0000\n");
	s=a.GetS();
	
	PFunc<TestClass, void (TestClass::*)(string,string,string)> fNamed=sumString;
	
	using PStringFunc=decltype(sumString);
	PStringFunc aa=sumString;
	fNamed("aa","bb","cc");
	s=a.GetS();
	cout<<s<<endl;
	
	TestPStringFunc test;
	test.set_pf(fNamed);
	test.run_pf1();
	s=a.GetS();
	cout<<s<<endl;
}
/*
	auto f4=[a=a](int v){return a.f(v);};
	f4(100);

	auto f2=a.f;
	//v(4);
	f1(4);
	auto g1=MakePFunc(a,a.g);
	run(g1,5);
	f1(0);*/
	//std::function<int(int)> f3=f1.MakeStdFunction<int,int>();
	
	//f3(4);
// PFunc
		//template<class T1,class T2>
		//void operator()(T1 v1,T2 v2){(obj.*func)(v1,v2); }
		/*template<class T1,class T2>
		std::function<T1(T2)> MakeStdFunction()
		{
			auto f=[this](T2 v)->T1{ T1 res=(*this)(v); return res; };
			std::function<T1(T2)> func=f;
			return f;				
		}*/
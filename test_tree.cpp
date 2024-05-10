#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <list>

using namespace std;

template<class T>
class TreeNode{
private:
	T value;
	std::vector<TreeNode<T> > nodes;
public:
	TreeNode(){}
	TreeNode(const T& a){value=a;}
	virtual ~TreeNode(){
	}
	T& Value(){return value;}
	TreeNode<T>& AddChild(const T& value)
	{
		TreeNode<T> a(value);
		nodes.push_back(a);
		return nodes[nodes.size()-1];
	}
	int ChildCount()
	{
		return nodes.size();
	}
	TreeNode<T>& Child(int id)
	{
		return nodes[id];
	}
	T& ChildValue(int id)
	{
		return nodes[id].value;
	}
};
template<class T>
void RunOnTree(std::function<void(T&)> fNode,TreeNode<T>& root,int maxLevel=-1,int level=0)
{
	if(level>=maxLevel&&maxLevel>0)
		return;
	for( int i=0;i<root.ChildCount();i++)
	{
		TreeNode<T> curr=root.Child(i);
		fNode(curr.Value());
		RunOnTree(fNode,curr,maxLevel,level+1);
	}
}
template<class T>
void PrintTree(TreeNode<T>& root,int maxLevel=-1,int level=0)
{
	if(level>=maxLevel&&maxLevel>0)
		return;
	cout<<"level == "<<level<<endl;
	for( int i=0;i<root.ChildCount();i++)
	{
		TreeNode<T> curr=root.Child(i);
		cout<<"child "<<i<<"=="<<curr.Value()<<endl;
		PrintTree(curr,maxLevel,level+1);
	}
}
using TreeString=TreeNode<string>;
int main()
{
	TreeString tree;
	TreeString& a=tree.AddChild("aa");
	TreeString& a1=a.AddChild("aa11");
	TreeString& a2=a.AddChild("aa22");
	TreeString& b=tree.AddChild("bb");
	TreeString& c=tree.AddChild("cc");
	int count=tree.ChildCount();
	TreeString& getA=a.Child(0);
	PrintTree(tree); 
	std::function<void(string&)> fNode=[](string& s){cout<<s<<endl;};
	RunOnTree(fNode,tree);
}
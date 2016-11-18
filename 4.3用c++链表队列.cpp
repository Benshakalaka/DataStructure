#include <iostream>                          //用类 来实现队列
#include <string>
using namespace std;
/*class X
{
	string name;
public:
	X(string &);
	void show();
};
X::X(string &b)
{
	name=b;
}
void X::show()
{
	cout << name;
}*/
class T
{
	struct C
	{
		string name;
		struct C *next;
	};
	C *head;
	C *rear;
	int cur;
	public:
		T();
		bool insert(string &);
		bool out();
		void treaverse();
};
T::T()
{
	head=NULL;
	rear=NULL;
	cur=0;
}
bool T::insert(string &x)
{
	struct C *new_one=new (struct C);
	if(new_one==NULL)
		return  false;
	new_one->name=x;
	new_one->next=NULL;
	cur++;
	if(head==NULL)
	{
		head=new_one;
		rear=head;
	}
	else
	{
		rear->next=new_one;
		rear=new_one;
	}
	return true;
}
bool T::out()
{
	cur--;
	if(cur==0)
	{
		delete head;
		cout << head->name<<" has been deleted\n";
		head=rear=NULL;
	}
	else
	{
		C *r=head;
		head=r->next;
		cout << r->name <<" has been deleted !\n";
		delete r;
	}
	return true;
}
void T::treaverse()
{
	C *current=head;
	while(current!=rear)
	{
		cout <<current->name<<"-----";
		current=current->next;
	}
	cout << rear->name<<endl;
}
int main()
{
	T a;
	a.insert(string("zhang"));
	a.insert(string("zhao"));
	a.insert(string("haha"));
	a.treaverse();
	a.out();
	a.out();
	a.treaverse();
	a.insert(string("ccc"));
	a.treaverse();
	return 0;
}
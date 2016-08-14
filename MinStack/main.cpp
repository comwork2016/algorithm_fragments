#include <iostream>

using namespace std;

struct MinStackElement
{
	int data;
	int min;
};

struct MinStack{
	MinStackElement* elemList;
	int size;
	int top;
};

MinStack InitMinStack(int maxSize)
{
	MinStack stack;
	stack.size = maxSize;
	stack.top = 0;
	stack.elemList = new MinStackElement[maxSize];
	return stack;
}

void DeleteMinStack(MinStack stack)
{
	delete[] stack.elemList;
}

void push(MinStack& stack,int d)
{
	if(stack.top == stack.size)
	{
		cout<<"out of stack space!"<<endl;
		return;
	}
	MinStackElement elem = stack.elemList[stack.top];
	elem.data =d;
	elem.min = stack.top == 0?d:stack.elemList[stack.top-1].min;
	if(elem.min > d)
	{
		elem.min = d;
	}
	stack.elemList[stack.top] = elem;
	stack.top++;
}

int pop(MinStack& stack)
{
	if(stack.top == 0)
	{
		cout<<"stack is empty!"<<endl;
	}
	return stack.elemList[--stack.top].data;
}

int min(MinStack stack)
{
	
	if(stack.top == 0)
	{
		cout<<"stack is empty!"<<endl;
	}
	return stack.elemList[stack.top-1].min;
}

int main()
{
	MinStack s = InitMinStack(10);
	int nums[] = {10,7,3,3,8,5,2,6};
	for(int i=0;i<8;i++)
	{
		push(s,nums[i]);
	}
	cout<<"min is "<<min(s)<<endl;
	cout<<pop(s)<<endl;
	cout<<"min is "<<min(s)<<endl;
	cout<<pop(s)<<endl;
	cout<<"min is "<<min(s)<<endl;
	cout<<pop(s)<<endl;
	cout<<"min is "<<min(s)<<endl;
	return 0;
}
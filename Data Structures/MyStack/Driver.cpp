#include "MyStack.h"

int main()
{
	std::cout << "Hello World" << std::endl;
	MyStack<int> S1;
	S1.pop();
	S1.push(100);
	S1.push(500);
	S1.push(5500);
	S1.push(5600);
	S1.push(5700);
	S1.erase(1000);
	std::cout << S1 << std::endl;

	MyStack<int> S2 = S1;
	MyStack<int> S3;
	S3 = S2;
	std::cout << S3 << std::endl;

	MyStack<int>* S4 = new MyStack<int>(S3);
	delete S4;

	S3.pop();
}
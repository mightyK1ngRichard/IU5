#pragma once
#include <iostream>           

template <class T, class FRIEND>
class ListNode
{
private:
	T data;          
	ListNode* next;  
	ListNode() { next = NULL; }
	friend FRIEND;
};


template <class T>
class Stack
{
	typedef class ListNode <T, Stack <T>> Node;
	Node* top;
public:
	Stack() { top = nullptr; };
	Stack(Stack<T>& stack) {
		std::cout << "copy constructor\n";
		Node* new_data = new Node();

		while (!stack.Empty()) {
			new_data->data = stack.top->data;
			this->Push(new_data->data);
			stack.Pop();
			new_data->next = stack.top;
		}
	}
	~Stack() { while (!Empty()) Pop(); };

	bool Empty();	   
	bool Push(T n);		
	bool Pop();		  
	T Top_inf();		
	void Read();
	Stack<T>& operator = (Stack<T>& Stack);
};
void Apportion(Stack<int>& stack, const int number);
size_t Menu();

template <class T>
bool Stack<T>::Empty() {
	return top == nullptr;
}

template <class T>
void Stack<T>::Read() {
	if (Empty()) { std::cout << "The list is empty!\n\n"; return; }
	while (!Empty()) {
		std::cout << top->data << std::endl;
		Pop();
	}
}

template <class T>
bool Stack<T>::Push(T number) {
	Node* new_data = new Node();
	new_data->data = number;
	new_data->next = top;
	top = new_data;	
	return 1; 
}

template <class T>
bool Stack<T>::Pop() {
	if (Empty()) return 0;
	Node* num = top->next;
	delete top;
	top = num;
	return 1;
}

template <class T>
Stack<T>& Stack<T>::operator = (Stack<T>& stack) {
	if (this != &stack) {
		std::cout << "Assignment  operator\n";
		Node* new_data = new Node();

		while (!stack.Empty()) {
			new_data->data = stack.top->data;
			this->Push(new_data->data);
			stack.Pop();
			new_data->next = stack.top;
		}
	}

	else
		std::cout << "self-assignment \n";
	return *this;
}

template <class T>
T Stack<T>::Top_inf() {
	if (Empty()) return 0;
	return top->data;
}

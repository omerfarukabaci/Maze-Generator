#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstring>
#include "stack.h"

using namespace std;

void Stack::create(){
	head = NULL;
}
void Stack::push(DataType *newelement){
	Node *toadd = new Node;
	toadd->data = *newelement;
	toadd->next = head;
	head = toadd;
	counter++;
}

DataType Stack::pop(){
	Node *topnode;
	DataType temp;
	topnode = head;
	head = head->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}

bool Stack::isempty(){
	return head == NULL;
}

void Stack::close() {
	Node *p;
	while (head) {
		p = head;
		head = head->next;
		delete p;
	}
}
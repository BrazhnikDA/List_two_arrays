#pragma once

class Node
{
public:
	int data;
	Node* Next;

	Node(int _data = 0, Node* pNext = nullptr);
};

Node::Node(int _data, Node* pNext)
{
	this->data = _data;
	this->Next = pNext;
}
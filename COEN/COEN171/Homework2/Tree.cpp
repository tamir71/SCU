// Tamir Enkhjargal
// SCU - COEN 171
// Homework 2 - Tree.cpp

#include <cstddef>

template <class N>
class Node {
	private:
		N value;
		N *left;
		N *right;
	public:
		Node(N anObject) {
			value = anObject;
		}
		bool member(const N &anObject);
		void insert(const N &anObject);
};

template <class T>
class Tree {
	private:
		T *root;
	public:
		bool member(const T &anObject);
		void insert(const T &anObject);
};

template <class N>
bool Node<N>::member(const N &anObject) {
	if(anObject < value) {
		if(left == NULL)
			return false;
		else
			return left->member(anObject);
	}
	else if(anObject > value) {
		if(right == NULL)
			return false;
		else
			return right->member(anObject);
	}
	return true;
}

template <class N>
void Node<N>::insert(const N &anObject) {
	if(anObject < value) {
		if(left == NULL)
			left = new Node(anObject);
		else
			left->insert(anObject);
	}
	else if(anObject > value) {
		if(right == NULL)
			right = new Node(anObject);
		else
			right->insert(anObject);
	}
}

template <class T>
bool Tree<T>::member(const T &anObject) {
	if(root == NULL)
		return false;
	else root->member(anObject);
}

template <class T>
void Tree<T>::insert(const T &anObject) {
	if(root == NULL)
		root = new Node<T>(anObject);
	else
		root->insert(anObject);
}

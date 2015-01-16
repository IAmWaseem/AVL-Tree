#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>

template <class T>
struct AVLTreeNode {
	T				Key;
	AVLTreeNode*	LeftChild;
	AVLTreeNode*	RightChild;
	AVLTreeNode*	Parent;
	char			BalanceFactor;
};

template <class T>
class AVLTree {
	private:
		AVLTreeNode<T>* Root;
	public:
		AVLTree();
		~AVLTree();
		void Insert(AVLTreeNode<T>* Node);
		void RestoreAVL(AVLTreeNode<T>* Ancestor, AVLTreeNode<T>* Node);
		void AdjustBalanceFactors(AVLTreeNode<T>* End, AVLTreeNode<T>* Start);
		void RotateLeft(AVLTreeNode<T>* Node);
		void RotateRight(AVLTreeNode<T>* Node);
		void AdjustLeftRight(AVLTreeNode<T>* End, AVLTreeNode<T>* Start);
		void AdjustRightLeft(AVLTreeNode<T>* End, AVLTreeNode<T>* Start);
		//void Delete(T Key);
		void PrintTree();
		AVLTreeNode<T>* CreateNewNode(T Key);
	private:
		void ClearTree(AVLTreeNode<T>* Node);
		void Print(AVLTreeNode<T>* Node);
};

#endif

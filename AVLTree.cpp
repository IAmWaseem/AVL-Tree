#include "AVLTree.h"

template <class T>
AVLTree<T>::AVLTree() {
	Root = (AVLTreeNode<T>*)0;
}

template <class T>
AVLTree<T>::~AVLTree() {
	ClearTree(Root);
}

template <class T>
void AVLTree<T>::ClearTree(AVLTreeNode<T>* Node) {
	if (Node) {
		ClearTree(Node->LeftChild);
		ClearTree(Node->RightChild);
		delete Node;
	}
}

template <class T>
void AVLTree<T>::Insert(AVLTreeNode<T>* Node) {
	AVLTreeNode<T>* Temp = Root;
	AVLTreeNode<T>* Back = (AVLTreeNode<T>*)0;
	AVLTreeNode<T>* Ancestor = (AVLTreeNode<T>*)0;
	if (Root == (AVLTreeNode<T>*)0) {
		Root = Node;
		return;
	}
	while (Temp != (AVLTreeNode<T>*)0) {
		Back = Temp;
		if (Temp->BalanceFactor != '=') {
			Ancestor = Temp;
		}
		if (Node->Key < Temp->Key) {
			Temp = Temp->LeftChild;
		}
		else {
			Temp = Temp->RightChild;
		}
	}
	Node->Parent = Back;
	if (Node->Key < Back->Key) {
		Back->LeftChild = Node;
	}
	else {
		Back->RightChild = Node;
	}
	this->RestoreAVL(Ancestor, Node);
}

template <class T>
void AVLTree<T>::RestoreAVL(AVLTreeNode<T>* Ancestor, AVLTreeNode<T>* Node) {
	if (Ancestor == (AVLTreeNode<T>*)0) {
		if (Node->Key < Root->Key) {
			Root->BalanceFactor = 'L';
		}
		else {
			Root->BalanceFactor = 'R';
		}
		AdjustBalanceFactors(Root, Node);
	}
	else if (((Ancestor->BalanceFactor == 'L') && (Node->Key > Ancestor->Key)) || ((Ancestor->BalanceFactor == 'R') && (Node->Key < Ancestor->Key))) {
		Ancestor->BalanceFactor = '=';
		AdjustBalanceFactors(Ancestor, Node);
	}
	else if ((Ancestor->BalanceFactor == 'R') && (Node->Key > Ancestor->RightChild->Key)) {
		Ancestor->BalanceFactor = '=';
		RotateLeft(Ancestor);
		AdjustBalanceFactors(Ancestor->Parent, Node);
	}
	else if ((Ancestor->BalanceFactor == 'L') && (Node->Key < Ancestor->LeftChild->Key)) {
		Ancestor->BalanceFactor = '=';
		RotateRight(Ancestor);
		AdjustBalanceFactors(Ancestor->Parent, Node);
	}
	else if ((Ancestor->BalanceFactor == 'L') && (Node->Key > Ancestor->LeftChild->Key)) {
		RotateLeft(Ancestor->LeftChild);
		RotateRight(Ancestor);
		AdjustLeftRight(Ancestor, Node);
	}
	else {
		RotateRight(Ancestor->RightChild);
		RotateLeft(Ancestor);
		AdjustRightLeft(Ancestor, Node);
	}
}

template <class T>
void AVLTree<T>::AdjustBalanceFactors(AVLTreeNode<T>* End, AVLTreeNode<T>* Start) {
	AVLTreeNode<T>* Temp = Start->Parent;
	while (Temp != End) {
		if (Start->Key < Temp->Key) {
			Temp->BalanceFactor = 'L';
		}
		else {
			Temp->BalanceFactor = 'R';
		}
		Temp = Temp->Parent;
	}
}

template <class T>
void AVLTree<T>::RotateLeft(AVLTreeNode<T>* Node) {
	AVLTreeNode<T>* Temp = Node->RightChild;
	Node->RightChild = Temp->LeftChild;
	if (Temp->LeftChild) {
		Temp->LeftChild->Parent = Node;
	}
	if (!Node->Parent) {
		Root = Temp;
		Temp->Parent = (AVLTreeNode<T>*)0;
	}
	else if (Node->Parent->LeftChild == Node) {
		Node->Parent->LeftChild = Temp;
	}
	else {
		Node->Parent->RightChild = Temp;
	}
	Temp->LeftChild = Node;
	Node->Parent = Temp;
}

template <class T>
void AVLTree<T>::RotateRight(AVLTreeNode<T>* Node) {
	AVLTreeNode<T>* Temp = Node->LeftChild;
	Node->LeftChild = Temp->RightChild;
	if (Temp->RightChild) {
		Temp->RightChild->Parent = Node;
	}
	if (!Node->Parent) {
		Root = Temp;
		Temp->Parent = (AVLTreeNode<T>*)0;
	}
	else if (Node->Parent->LeftChild == Node) {
		Node->Parent->LeftChild = Temp;
	}
	else {
		Node->Parent->RightChild = Temp;
	}
	Temp->RightChild = Node;
	Node->Parent = Temp;
}

template <class T>
void AVLTree<T>::AdjustLeftRight(AVLTreeNode<T>* End, AVLTreeNode<T>* Start) {
	if (End == Root) {
		End->BalanceFactor = '=';
	}
	else if (Start->Key < End->Parent->Key) {
		End->BalanceFactor = 'R';
		AdjustBalanceFactors(End->Parent->LeftChild, Start);
	}
	else {
		End->BalanceFactor = '=';
		End->Parent->LeftChild->BalanceFactor = 'L';
		AdjustBalanceFactors(End, Start);
	}
}

template <class T>
void AVLTree<T>::AdjustRightLeft(AVLTreeNode<T>* End, AVLTreeNode<T>* Start) {
	if (End == Root) {
		End->BalanceFactor = '=';
	}
	else if (Start->Key > End->Parent->Key) {
		End->BalanceFactor = 'L';
		AdjustBalanceFactors(End->Parent->RightChild, Start);
	}
	else {
		End->BalanceFactor = '=';
		End->Parent->RightChild->BalanceFactor = 'R';
		AdjustBalanceFactors(End, Start);
	}
}

template <class T>
void AVLTree<T>::PrintTree() {
	std::cout << "Printing Tree..." << std::endl;
	std::cout << "Root Node: " << Root->Key << " Balance Factor: " << Root->BalanceFactor << std::endl << std::endl;
	Print(Root);
}

template <class T>
void AVLTree<T>::Print(AVLTreeNode<T>* Node) {
	if (Node) {
		std::cout << "Node: " << Node->Key << " Balance Factor: " << Node->BalanceFactor << std::endl << std::endl;
		if (Node->LeftChild) {
			std::cout << "\tMoving Left" << std::endl;
			Print(Node->LeftChild);
			std::cout << "Returning to Node " << Node->Key << " from its Left Subtree" << std::endl;
		}
		else {
			std::cout << "\tLeft Subtree is Empty" << std::endl;
		}
		std::cout << "Node: " << Node->Key << " Balance Factor: " << Node->BalanceFactor << std::endl << std::endl;
		if (Node->RightChild) {
			std::cout << "\tMoving Right" << std::endl;
			Print(Node->RightChild);
			std::cout << "Returning to Node " << Node->Key << " from its Right Subtree" << std::endl;
		}
		else {
			std::cout << "\tRight Subtree is Empty" << std::endl;
		}
	}
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::CreateNewNode(T Key) {
	AVLTreeNode<T>* Node = new AVLTreeNode<T>();
	Node->Key = Key;
	Node->LeftChild = (AVLTreeNode<T>*)0;
	Node->RightChild = (AVLTreeNode<T>*)0;
	Node->Parent = (AVLTreeNode<T>*)0;
	Node->BalanceFactor = '=';
	return Node;
}

template class AVLTree<int>;
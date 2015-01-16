#include "AVLTree.h"

int main() {
	AVLTree<int>* tree = new AVLTree<int>();
	AVLTreeNode<int>* a = tree->CreateNewNode(2);
	AVLTreeNode<int>* b = tree->CreateNewNode(3);
	AVLTreeNode<int>* c = tree->CreateNewNode(4);
	AVLTreeNode<int>* d = tree->CreateNewNode(1);
	AVLTreeNode<int>* e = tree->CreateNewNode(0);
	tree->Insert(a);
	tree->Insert(b);
	tree->Insert(c);
	tree->Insert(d);
	tree->Insert(e);
	tree->PrintTree();
	system("pause");
	return 0;
}
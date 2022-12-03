#pragma once
#include <iostream>
#include <string>
#include "AVL.h"
#include <cstdlib>
#include <queue>



// the included display function is not my work. It was
// borrowed from https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c


using namespace std;

AVL::~AVL()
{
	_destroyNodes(root_);
}

void AVL::insert(int data)
{
	_insert(root_, data);
}

void AVL::display()
{
	_display("", root_, false);
}

void AVL::find(int data)
{
	_find(root_, data);
}

bool AVL::isBalanced()
{
	if(_isBalanced(root_) == 0)
		return true;
	else {
		return false;
	}
	
}

bool AVL::isSorted()
{
	if (_isSorted(root_) == 0)
		return true;
	else {
		return false;
	}
}

int AVL::getHeight(int data)
{
	TreeNode* temp = _find(root_, data);
	return temp->height;

}

void AVL::remove(int data)
{
	_remove(root_, data);
}

void AVL::inOrder()
{
	_inOrder(root_);
}

AVL::TreeNode* AVL::_find(TreeNode*& ptr, int data)
{
	if (ptr == nullptr)
		;

	else if (data == ptr->data)
		return ptr;

	else if (data > ptr->data) {
		_find(ptr->right, data);
		
	}
	else if (data < ptr->data) {
		_find(ptr->left, data);
		
	}
		
}

void AVL::_destroyNodes(TreeNode*& ptr)
{
	if (ptr!=nullptr) {
		_destroyNodes(ptr->left);
		_destroyNodes(ptr->right);
		delete ptr;
	}
}

void AVL::_inOrder(TreeNode* ptr)
{
	if (ptr == NULL)
		return;

	/* first recur on left child */
	_inOrder(ptr->left);

	/* then print the data of node */
	cout << ptr->data << " ";

	/* now recur on right child */
	_inOrder(ptr->right);

}



void AVL::_rotateRight(TreeNode*& curr){
	
	if (curr->left->right != nullptr) {
		TreeNode* temp = curr;
		curr = curr->left;
		temp->left = curr->right;
		curr->right = temp;
		_updateHeight(curr->right);
		_updateHeight(curr);
	}


	else {
		_rotateTheSTICKTOTHERIGHT(curr);
	}
}

void AVL::_rotateLeft(TreeNode*& curr)
{
	if (curr == nullptr) {
		return;
	}
	else if (curr->right->left != nullptr) {
		TreeNode* temp = curr;
		curr = curr->right;
		temp->right = curr->left;
		curr->left = temp;
		_updateHeight(curr->left);
		_updateHeight(curr);
	}

	else {
		_rotateTheStickTOTHELEFT(curr);
	}

}

void AVL::_rotateLeftRight(TreeNode*& curr)
{
	_rotateLeft(curr->left);
	_rotateRight(curr);
}

void AVL::_rotateRightLeft(TreeNode*& curr)
{
	_rotateRight(curr->right);
	_rotateLeft(curr);
}


void AVL::_rotateTheStickTOTHELEFT(TreeNode*& curr)
{
	TreeNode* temp = curr;
	curr = curr->right;
	temp->right = nullptr;
	curr->left = temp;
	_updateHeight(curr->left);
	_updateHeight(curr);
}

void AVL::_rotateTheSTICKTOTHERIGHT(TreeNode*& curr)
{
	
	TreeNode* temp = curr;
	curr = curr->left;
	temp->left = nullptr;
	curr->right = temp;

	_updateHeight(curr -> right);
	_updateHeight(curr);

}

void  AVL::_updateHeight(TreeNode*& curr)
{
	//lets combine update height and balance
	int result;
	int lh = 0;
	int rh = 0;
	int balanceF;

	if (curr == nullptr) {
		;
	}

	else if ((curr->left == nullptr && curr->right == nullptr)) {
		result = 0;
		curr->height = result;
	}

	else if ((curr->left == nullptr) && (curr->right != nullptr)) {
		rh = curr->right->height;
		result =  max(rh, 0) + 1;
		curr->height = result;
	}

	else if ((curr->left != nullptr) && (curr->right == nullptr)) {
		//cout << " I RAN " << endl;
		lh = curr->left->height;
		result =  max(lh, 0) + 1;
		curr->height = result;
	}

	else if ((curr->left != nullptr) && (curr->right != nullptr)) {
		lh = curr->left->height;
		rh = curr->right->height;
		result = max(rh, lh) + 1;
		curr->height = result;
	}
	/**/
	else {
		cout << " ELSE RAN!!! _UPDATEHEIGHT FUNCTION !!" << endl;
	}
}

int AVL::getBalanceFactor(TreeNode*& ptr)
{

	int balanceF = 0;
	int right = 0;
	int left = 0;

	if (ptr->left == nullptr && ptr->right == nullptr) {
		return 0;
	}

	else if (ptr->left != nullptr && ptr->right != nullptr) {
		right = ptr->right->height;
		left = ptr->left->height;
		balanceF = right - left;
	}
	else if (ptr->left == nullptr && ptr->right != nullptr) {
		right = ptr->right->height;
		left = -1;
		balanceF = right - left;
	}
	else if (ptr->left != nullptr && ptr->right == nullptr) {
		right = -1;
		left = ptr->left->height;
		balanceF = right - left;
	}

	return balanceF;
	
}

void AVL::_balance(TreeNode*& curr){

	int balanceF = getBalanceFactor(curr); 

	//cout << "    current data IS       " << curr->data << "     CURR BALANCE FACTOR IS " << balanceF <<  " CURRENT HEIGHT IS " << curr -> height  << endl;

	if (curr == nullptr)
	{
		;
	}

	else if (balanceF  == 2) {
		int rChildBalF = getBalanceFactor(curr->right);
		if (rChildBalF == 0 || rChildBalF == 1) {
			_rotateLeft(curr);
		}  
		else {
			_rotateRightLeft(curr);

		}
	}

	else if (balanceF == -2) {
		int lChildBalF = getBalanceFactor(curr->left);
		if (lChildBalF == 0 || lChildBalF == -1) {
			_rotateRight(curr);
		}
		else {
			_rotateLeftRight(curr);
		}

	}
}

void AVL::_display(const std::string& prefix, const TreeNode* node, bool isLeft)
{
	if (node != nullptr)
	{
		std::cout << prefix;
		std::cout << (isLeft ? "|--" : "L--");
		// print the value of the node
		std::cout << node->data << endl;
		// enter the next tree level - left and right branch
		_display(prefix + (isLeft ? "|   " : "    "), node->right, true);
		_display(prefix + (isLeft ? "|   " : "    "), node->left, false);
	}
}


void AVL::_insert(TreeNode*& ptr, int data)
{
	if (ptr == nullptr) {
		ptr = new TreeNode(data, "string");
		//cout << ptr->data << endl;
		_updateHeight(ptr);
		_balance(ptr);

	}

	else if (data > ptr->data) {
		_insert(ptr->right, data);
		_updateHeight(ptr);
		_balance(ptr);
	}

	else if (data < ptr->data) {
		_insert(ptr->left, data);
		_updateHeight(ptr);
		_balance(ptr);
	}
}

bool  AVL::_isBalancedHelper(TreeNode*& ptr)
{
	bool temp;

	if (ptr == nullptr)
		;

	else {
		_isBalancedHelper(ptr->left);
		_isBalancedHelper(ptr->right);
		if (_isBalanced(ptr) < -1 || _isBalanced(ptr) > 1) {
			return 1;
		}
		
	}
	
}

bool  AVL::_isSorted(TreeNode*& ptr) {
	//IFF NULL DO NOTHING AND return to function CALL.
	if (ptr == nullptr)
		;
	else if (ptr->right == nullptr || ptr->left == nullptr)
		;

	else if (ptr->right->data < ptr->data)
		return 1;

	else if (ptr->left->data > ptr->data)
		return 1;

	else {
		_isSorted(ptr->right);
		_isSorted(ptr->left);
		return 0;
	}
}

AVL::TreeNode*  AVL::_findMin(TreeNode* ptr)
{
	if (root_ == nullptr)
		return NULL;
	else if (ptr->left == nullptr)
		return ptr;
	else
		_findMin(ptr->left);
}

AVL::TreeNode* AVL::_findMax(TreeNode* ptr)
{
	if (root_ == nullptr)
		return NULL;
	else if (ptr->right == nullptr)
		return ptr;
	else
		_findMax(ptr->right);
}

void AVL::_remove(TreeNode*& curr, int data)
{
	//REMOVE IS REALLY JUST FIND.....
	TreeNode* temp;
	TreeNode* iop;

	if (curr == nullptr) {
		return;
	}
	else if (curr->data == data) {
		//cout << curr->data << endl;
		_getIop(curr);
		_updateHeight(curr);
		//_balance(curr);
	}
	
	//if ROOT is less than node data
	else if (data < curr->data) {
		_remove(curr->left, data);
		_updateHeight(curr);
		//_balance(curr);
	}

	else if (data > curr->data) {
		_remove(curr->right, data);
		_updateHeight(curr);
		//_balance(curr);
	}


}

void AVL::_getIop(TreeNode*& ptr)
{
	TreeNode* temp = ptr;

	if (ptr == nullptr) {
		return;
	}

	// NODE with 0 Children..We don't need to call _swap because
	// all we have to do is delete it and walk away. (then _remove function is waiting for _getIOP to return) 
	// and then recursively call update Height & balance)
	else if ((ptr->left == nullptr && ptr->right == nullptr)) {
	ptr = nullptr;
	delete temp;
	}

	//Node where we can't go left to get IOP...then we traverse all the way right// and then get IOP!
	// we also MUST recursively update height and check balance as soon function call returns and we reccur UP the tree!
	else if (ptr->left == nullptr && ptr->right != nullptr) {
		_getIop(ptr->right);
		_swap(temp, ptr);
		_updateHeight(ptr);
		_balance(ptr);
	}

	else {
		//I can set ptr = ptr -> left because _remove is waiting for function to return 
		//once it does, it will call update height and balance on the node we want deleted.
		_getIOPFull(ptr->left, ptr);

	}

}
void AVL::_getIOPFull(TreeNode*& ptr, TreeNode*& original) {
	//TreeNode*& _original = original;

	if (ptr == nullptr) {
		return;
	}
	else {
		_getIOPFull(ptr->right, original);
		//function returned. Now we call SWAP!
		_swap(original, ptr);
		_updateHeight(ptr);
		_balance(ptr);
	}

}

void AVL::_swap(TreeNode*& original, TreeNode*& IOP) {
	//testing original with using a REFRENCE

	TreeNode* temp = original;
	TreeNode* _iopCopy = IOP;


	//if the IOP we're looking to swap has one LEFT node, swap the TWO NODES, THEN DELETE!
	if (IOP->left != nullptr && IOP -> right == nullptr){

		IOP = IOP->left;
		_iopCopy->left = nullptr;
		IOP->left = _iopCopy;
		_iopCopy->left == nullptr;
		original = _iopCopy;

		original->left = temp->left;
		original->right = temp->right;

		temp = nullptr;
		delete temp;
	}

	else if (IOP->left == nullptr && IOP->right == nullptr) {
		
		original = _iopCopy;

		_iopCopy->left = original->left;
		_iopCopy->right = original->right;

		temp = nullptr;
		delete temp;

	}
	

}



int AVL::_isBalanced(TreeNode*& ptr)
{
	// ptr is root....
	//we finished insert so we know all the heights.....

	int temp = getBalanceFactor(ptr);
	

	if (temp > 1 || temp < -1)
		return 1;
	else {
		return 0;
	}
	
}

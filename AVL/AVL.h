#pragma once
#include <string>

using namespace std;


class AVL {
public:
	~AVL();
	AVL() : root_(nullptr) {}
	void insert(int data);
	void display();
	void find(int data);
	bool isBalanced();
	bool isSorted();
	int getHeight(int data);
	void remove(int data);
	void inOrder();

private:
	class TreeNode {
	public:
		string key;
		int height;
		int data;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int d, string k) : data(d), key(k), left(nullptr), right(nullptr), height(0) {}

	};
	TreeNode* root_;
	TreeNode* _find(TreeNode*& ptr, int data);
	void _destroyNodes(TreeNode*& ptr);

	void _inOrder(TreeNode* ptr);
	void _rotateRight(TreeNode*& curr);
	void _rotateLeft(TreeNode*& curr);
	void _rotateLeftRight(TreeNode*& curr);
	void _rotateRightLeft(TreeNode*& curr);
	void _balance(TreeNode*& curr);
	void _rotateTheStickTOTHELEFT(TreeNode*& curr);
	void _rotateTheSTICKTOTHERIGHT(TreeNode*& curr);
	void _updateHeight(TreeNode*& curr);
	int getBalanceFactor(TreeNode*& curr);
	void _display(const std::string& prefix, const TreeNode* node, bool isLeft);
	void _insert(TreeNode*& ptr, int data);
	bool _isBalancedHelper(TreeNode*& ptr);
	int _isBalanced(TreeNode*& ptr);
	bool _isSorted(TreeNode*& ptr);
	TreeNode* _findMin(TreeNode* ptr);
	TreeNode* _findMax(TreeNode* ptr);
	void _remove(TreeNode*& ptr, int data);
	void _getIop(TreeNode*& ptr);
	void _swap(TreeNode*& curr, TreeNode *&iop);
	void _getIOPFull(TreeNode*& curr, TreeNode*& original);

	};

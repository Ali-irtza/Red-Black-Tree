//#include <iostream>
//using namespace std;
//#include <queue>
//
//enum Color { RED, BLACK,DOUBLE_BLACK };
//
//class Node {
//public:
//	int data;
//	Color color;
//	Node *left, *right, *parent;
//
//	Node(int data) {
//		this->data = data;
//		left = right = parent = nullptr;
//		this->color = RED;
//	}
//};
//
//class RedBlackTree {
//private:
//	Node* root;
//
//protected:
//	void rotateLeft(Node *&, Node *&);
//	void rotateRight(Node *&, Node *&);
//	void fixInsertion(Node *&, Node *&);
//	void fixDeletion(Node *&, Node *&);
//	Node* BSTInsert(Node* root, Node* pt);
//	Node* BSTDelete(Node* root, int data);
//	Node* minValueNode(Node* node);
//	Node* maxValueNode(Node* node);
//	Node* search(Node* root, int data);
//	int height(Node* node);
//	int diameter(Node* node);
//	void inorderHelper(Node* root);
//	void preorderHelper(Node* root);
//	void postorderHelper(Node* root);
//	Node* findSuccessor(Node* root, int data);
//	Node* findPredecessor(Node* root, int data);
//
//public:
//	RedBlackTree() { root = nullptr; }
//	void insert(const int &n);
//	void deleteNode(const int &data);
//	bool search(const int &data);
//	void inorder();
//	void preorder();
//	void postorder();
//	int height();
//	int diameter();
//	int min();
//	int max();
//	Node* successor(int data);
//	Node* predecessor(int data);
//};
//
//// Function to rotate left
//void RedBlackTree::rotateLeft(Node *&root, Node *&pt) {
//	Node *pt_right = pt->right;
//
//	pt->right = pt_right->left;
//
//	if (pt->right != nullptr)
//		pt->right->parent = pt;
//
//	pt_right->parent = pt->parent;
//
//	if (pt->parent == nullptr)
//		root = pt_right;
//
//	else if (pt == pt->parent->left)
//		pt->parent->left = pt_right;
//
//	else
//		pt->parent->right = pt_right;
//
//	pt_right->left = pt;
//	pt->parent = pt_right;
//}
//
//// Function to rotate right
//void RedBlackTree::rotateRight(Node *&root, Node *&pt) {
//	Node *pt_left = pt->left;
//
//	pt->left = pt_left->right;
//
//	if (pt->left != nullptr)
//		pt->left->parent = pt;
//
//	pt_left->parent = pt->parent;
//
//	if (pt->parent == nullptr)
//		root = pt_left;
//
//	else if (pt == pt->parent->left)
//		pt->parent->left = pt_left;
//
//	else
//		pt->parent->right = pt_left;
//
//	pt_left->right = pt;
//	pt->parent = pt_left;
//}
//
//// Function to maintain Red-Black Tree properties after insertion
//void RedBlackTree::fixInsertion(Node *&root, Node *&pt) {
//	Node *parent_pt = nullptr;
//	Node *grand_parent_pt = nullptr;
//
//	while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
//		parent_pt = pt->parent;
//		grand_parent_pt = pt->parent->parent;
//
//		if (parent_pt == grand_parent_pt->left) {
//			Node *uncle_pt = grand_parent_pt->right;
//
//			if (uncle_pt != nullptr && uncle_pt->color == RED) {
//				grand_parent_pt->color = RED;
//				parent_pt->color = BLACK;
//				uncle_pt->color = BLACK;
//				pt = grand_parent_pt;
//			}
//			else {
//				if (pt == parent_pt->right) {
//					rotateLeft(root, parent_pt);
//					pt = parent_pt;
//					parent_pt = pt->parent;
//				}
//				rotateRight(root, grand_parent_pt);
//				std::swap(parent_pt->color, grand_parent_pt->color);
//				pt = parent_pt;
//			}
//		}
//		else {
//			Node *uncle_pt = grand_parent_pt->left;
//
//			if (uncle_pt != nullptr && uncle_pt->color == RED) {
//				grand_parent_pt->color = RED;
//				parent_pt->color = BLACK;
//				uncle_pt->color = BLACK;
//				pt = grand_parent_pt;
//			}
//			else {
//				if (pt == parent_pt->left) {
//					rotateRight(root, parent_pt);
//					pt = parent_pt;
//					parent_pt = pt->parent;
//				}
//				rotateLeft(root, grand_parent_pt);
//				std::swap(parent_pt->color, grand_parent_pt->color);
//				pt = parent_pt;
//			}
//		}
//	}
//	root->color = BLACK;
//}
//
//// Function to maintain Red-Black Tree properties after deletion
//void RedBlackTree::fixDeletion(Node *&root, Node *&x) {
//	if (x == nullptr)
//		return;
//
//	if (x == root) {
//		root = nullptr;
//		return;
//	}
//
//	if (x->color == RED || (x->left != nullptr && x->left->color == RED) || (x->right != nullptr && x->right->color == RED)) {
//		Node *child = (x->left != nullptr) ? x->left : x->right;
//
//		if (x == x->parent->left) {
//			x->parent->left = child;
//			if (child != nullptr) child->parent = x->parent;
//			child->color = BLACK;
//			delete(x);
//		}
//		else {
//			x->parent->right = child;
//			if (child != nullptr) child->parent = x->parent;
//			child->color = BLACK;
//			delete(x);
//		}
//	}
//	else {
//		Node *sibling = nullptr;
//		Node *parent = nullptr;
//		Node *ptr = x;
//		ptr->color = DOUBLE_BLACK;
//		while (ptr != root && ptr->color == DOUBLE_BLACK) {
//			parent = ptr->parent;
//			if (ptr == parent->left) {
//				sibling = parent->right;
//				if (sibling->color == RED) {
//					sibling->color = BLACK;
//					parent->color = RED;
//					rotateLeft(root, parent);
//				}
//				else {
//					if ((sibling->left != nullptr && sibling->left->color == BLACK) || sibling->left == nullptr) {
//						if ((sibling->right != nullptr && sibling->right->color == BLACK) || sibling->right == nullptr) {
//							sibling->color = RED;
//							if (parent->color == RED)
//								parent->color = BLACK;
//							else
//								parent->color = DOUBLE_BLACK;
//							ptr = parent;
//						}
//						else {
//							if (sibling->right != nullptr)
//								sibling->right->color = BLACK;
//							sibling->color = RED;
//							rotateRight(root, sibling);
//							sibling = parent->right;
//						}
//					}
//					if (sibling != nullptr) {
//						sibling->color = parent->color;
//						parent->color = BLACK;
//						if (sibling->right != nullptr)
//							sibling->right->color = BLACK;
//						rotateLeft(root, parent);
//						break;
//					}
//				}
//			}
//			else {
//				sibling = parent->left;
//				if (sibling->color == RED) {
//					sibling->color = BLACK;
//					parent->color = RED;
//					rotateRight(root, parent);
//				}
//				else {
//					if ((sibling->left != nullptr && sibling->left->color == BLACK) || sibling->left == nullptr) {
//						if ((sibling->right != nullptr && sibling->right->color == BLACK) || sibling->right == nullptr) {
//							sibling->color = RED;
//							if (parent->color == RED)
//								parent->color = BLACK;
//							else
//								parent->color = DOUBLE_BLACK;
//							ptr = parent;
//						}
//						else {
//							if (sibling->left != nullptr)
//								sibling->left->color = BLACK;
//							sibling->color = RED;
//							rotateLeft(root, sibling);
//							sibling = parent->left;
//						}
//					}
//					if (sibling != nullptr) {
//						sibling->color = parent->color;
//						parent->color = BLACK;
//						if (sibling->left != nullptr)
//							sibling->left->color = BLACK;
//						rotateRight(root, parent);
//						break;
//					}
//				}
//			}
//		}
//		if (x == x->parent->left)
//			x->parent->left = nullptr;
//		else
//			x->parent->right = nullptr;
//		delete(x);
//		root->color = BLACK;
//	}
//}
//
//// Function to insert a new node with given data
//void RedBlackTree::insert(const int &data) {
//	Node *pt = new Node(data);
//	root = BSTInsert(root, pt);
//	fixInsertion(root, pt);
//}
//
//// Function to delete a node with given data
//void RedBlackTree::deleteNode(const int &data) {
//	root = BSTDelete(root, data);
//}
//
//// Function to search a node with given data
//bool RedBlackTree::search(const int &data) {
//	return search(root, data) != nullptr;
//}
//
//// Function to perform inorder traversal
//void RedBlackTree::inorder() {
//	inorderHelper(root);
//	cout << endl;
//}
//
//// Function to perform preorder traversal
//void RedBlackTree::preorder() {
//	preorderHelper(root);
//	cout << endl;
//}
//
//// Function to perform postorder traversal
//void RedBlackTree::postorder() {
//	postorderHelper(root);
//	cout << endl;
//}
//
//// Function to get the height of the tree
//int RedBlackTree::height() {
//	return height(root);
//}
//
//// Function to get the diameter of the tree
//int RedBlackTree::diameter() {
//	return diameter(root);
//}
//
//// Function to get the minimum value in the tree
//int RedBlackTree::min() {
//	Node* node = minValueNode(root);
//	return node ? node->data : -1;
//}
//
//// Function to get the maximum value in the tree
//int RedBlackTree::max() {
//	Node* node = maxValueNode(root);
//	return node ? node->data : -1;
//}
//
//// Function to find the successor of a node with given data
//Node* RedBlackTree::successor(int data) {
//	return findSuccessor(root, data);
//}
//
//// Function to find the predecessor of a node with given data
//Node* RedBlackTree::predecessor(int data) {
//	return findPredecessor(root, data);
//}
//
//// Function to insert a new node in BST
//Node* RedBlackTree::BSTInsert(Node* root, Node* pt) {
//	if (root == nullptr)
//		return pt;
//
//	if (pt->data < root->data) {
//		root->left = BSTInsert(root->left, pt);
//		root->left->parent = root;
//	}
//	else if (pt->data > root->data) {
//		root->right = BSTInsert(root->right, pt);
//		root->right->parent = root;
//	}
//
//	return root;
//}
//
//// Function to delete a node from BST
//Node* RedBlackTree::BSTDelete(Node* root, int data) {
//	if (root == nullptr)
//		return root;
//
//	if (data < root->data)
//		root->left = BSTDelete(root->left, data);
//	else if (data > root->data)
//		root->right = BSTDelete(root->right, data);
//	else {
//		if (root->left == nullptr || root->right == nullptr)
//			return root->left ? root->left : root->right;
//		Node* temp = minValueNode(root->right);
//		root->data = temp->data;
//		root->right = BSTDelete(root->right, temp->data);
//	}
//	return root;
//}
//
//// Function to find the node with minimum value in BST
//Node* RedBlackTree::minValueNode(Node* node) {
//	Node* current = node;
//
//	while (current && current->left != nullptr)
//		current = current->left;
//
//	return current;
//}
//
//// Function to find the node with maximum value in BST
//Node* RedBlackTree::maxValueNode(Node* node) {
//	Node* current = node;
//
//	while (current && current->right != nullptr)
//		current = current->right;
//
//	return current;
//}
//
//// Function to search a node with given data in BST
//Node* RedBlackTree::search(Node* root, int data) {
//	if (root == nullptr || root->data == data)
//		return root;
//
//	if (root->data < data)
//		return search(root->right, data);
//
//	return search(root->left, data);
//}
//
//// Helper function for inorder traversal
//void RedBlackTree::inorderHelper(Node* root) {
//	if (root == nullptr)
//		return;
//
//	inorderHelper(root->left);
//	std::cout << root->data << " ";
//	inorderHelper(root->right);
//}
//
//// Helper function for preorder traversal
//void RedBlackTree::preorderHelper(Node* root) {
//	if (root == nullptr)
//		return;
//
//	std::cout << root->data << " ";
//	preorderHelper(root->left);
//	preorderHelper(root->right);
//}
//
//// Helper function for postorder traversal
//void RedBlackTree::postorderHelper(Node* root) {
//	if (root == nullptr)
//		return;
//
//	postorderHelper(root->left);
//	postorderHelper(root->right);
//	std::cout << root->data << " ";
//}
//
//// Function to get the height of the tree
//int RedBlackTree::height(Node* node) {
//	if (node == nullptr)
//		return 0;
//	int leftHeight = height(node->left);
//	int rightHeight = height(node->right);
//	return std::max(leftHeight, rightHeight) + 1;
//}
//
//// Function to get the diameter of the tree
//int RedBlackTree::diameter(Node* node) {
//	if (node == nullptr)
//		return 0;
//
//	int leftHeight = height(node->left);
//	int rightHeight = height(node->right);
//
//	int leftDiameter = diameter(node->left);
//	int rightDiameter = diameter(node->right);
//
//	return std::max(leftHeight + rightHeight + 1, std::max(leftDiameter, rightDiameter));
//}
//
//// Function to find the successor of a node with given data
//Node* RedBlackTree::findSuccessor(Node* root, int data) {
//	Node* current = search(root, data);
//	if (current == nullptr)
//		return nullptr;
//
//	if (current->right != nullptr)
//		return minValueNode(current->right);
//OP
//	Node* successor = nullptr;
//	Node* ancestor = root;
//	while (ancestor != current) {
//		if (current->data < ancestor->data) {
//			successor = ancestor;
//			ancestor = ancestor->left;
//		}
//		else
//			ancestor = ancestor->right;
//	}
//	return successor;
//}
//
//// Function to find the predecessor of a node with given data
//Node* RedBlackTree::findPredecessor(Node* root, int data) {
//	Node* current = search(root, data);
//	if (current == nullptr)
//		return nullptr;
//
//	if (current->left != nullptr)
//		return maxValueNode(current->left);
//
//	Node* predecessor = nullptr;
//	Node* ancestor = root;
//	while (ancestor != current) {
//		if (current->data > ancestor->data) {
//			predecessor = ancestor;
//			ancestor = ancestor->right;
//		}
//		else
//			ancestor = ancestor->left;
//	}
//	return predecessor;
//}
//
//int main() 
//{
//	RedBlackTree tree;
//	int choice;
//	double value;
//	do
//	{
//		cout << "0-Exit\n1-Insertion\n2-Deletion\n3-Searching\n4-Inorder Traversal\n5-Preorder Traversal\n6-Postorder Traversal\n7-Height Of Tree\n8-Diameter Of Tree\n9-Minimum Value\n10-Maximum Value\n11-Successor\n12-Predecessor" << endl;
//		cout << "Enter your choice" << endl;
//		cin >> choice;
//		switch (choice)
//		{
//		case 0:
//		{
//				  break;
//		}
//		case 1:
//		{
//				  cout << "Enter the Value you want to Insert" << endl;
//				  cin >> value;
//				  tree.insert(value);
//				  break;
//		}
//		case 2:
//		{
//				  cout << "Enter the Value you want to delete" << endl;
//				  cin >> value;
//				  tree.deleteNode(value);
//				  break;
//		}
//		case 3:
//		{
//				  cout << "Enter the Value you want to Search" << endl;
//				  cin >> value;
//				  cout << "Searching for " << value << ": " << (tree.search(value) ? "Found" : "Not Found") << endl;
//				  break;
//		}
//		case 4:
//		{
//				  cout << "Inorder Traversal: ";
//				  tree.inorder();
//				  break;
//		}
//		case 5:
//		{
//				  cout << "Preorder traversal: ";
//				  tree.preorder();
//				  break;
//		}
//		case 6:
//		{
//				  cout << "Postorder traversal: ";
//				  tree.postorder();
//				  break;
//		}
//		case 7:
//		{
//				  cout << "Height: " << tree.height() << endl;
//				  break;
//		}
//		case 8:
//		{
//				  cout << "Diameter: " << tree.diameter() << endl;
//				  break;
//		}
//		case 9:
//		{
//				  int minVal = tree.min();
//				  cout << "Minimum value: " << minVal << endl;
//				  break;
//		}
//		case 10:
//		{
//				   int maxVal = tree.max();
//				   cout << "Maximum value: " << maxVal << endl;
//				   break;
//		}
//		case 11:
//		{
//				   cout << "Enter the Key you want to find the successor" << endl;
//				   cin >> value;
//				   Node* succ = tree.successor(value);
//				   if (succ) cout << "Successor of " << value << ": " << succ->data << endl;
//				   break;
//		}
//		case 12:
//		{
//				   cout << "Enter the key you want to find the predecessor" << endl;
//				   cin >> value;
//				   Node* pred = tree.predecessor(value);
//				   if (pred) cout << "Predecessor of " << value << ": " << pred->data << endl;
//				   break;
//		}
//		default:
//		{
//					break;
//		}
//		}
//	}
//	while (choice!=0);
//	cin.get();
//	return 0;
//}

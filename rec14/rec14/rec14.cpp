#include <iostream>
using namespace std;

struct TNode {
	TNode(int data = 0, TNode * left = nullptr, TNode * right = nullptr)
		: data(data), left(left), right(right) {}
	int data;
	TNode* left, * right;
};

struct Node {
	Node(int data = 0, Node* next = nullptr):data(data),next(next) {}
	int data;
	Node* next;
};
struct emptyTree :exception {
	const char* what() {
		return "the tree is empty!";
	}
};

bool evenOne(int x) {
	if (x == 1) {
		return false;
	}
	if (x == 0) {
		return true;
	}
	else {
		bool result = evenOne(x / 2);
		if (x % 2 == 1) {
			result = !result;
		}
		return result;
	}
}

Node* sumList(const Node* node1,const Node* node2) {
	if (node1 && node2) {
		return new Node(node1->data + node2->data, sumList(node1->next, node2->next));
	}
	if (node1) {
		return new Node(node1->data, sumList(node1->next, node2));
	}
	if (node2) {
		return new Node(node2->data, sumList(node1, node2->next));
	}
	else {
		return nullptr;
	}
}
int max(TNode* root) {
	if (!root) {
		throw emptyTree();
	}
	int maxleft;
	int maxright;
	if (!root->left && !root->right) {
		return root->data;
	}
	if(!root->left) {
		maxright = max(root->right);
		if (root->data > maxright) {
			return root->data;
		}
		else {
			return maxright;
		}
	}
	if (!root->right) {
		maxleft = max(root->left);
		if (root->data > maxleft) {
			return root->data;
		}
		else {
			return maxleft;
		}
	}
	else {
		maxright = max(root->right);
		maxleft = max(root->left);
		int max = root->data;
		if (maxright > max) {
			max = maxright;
		}
		if (maxleft > max) {
			max = maxleft;
		}
		return max;
	}
}

bool palindrome(const char* cl, int index) {
	if (index == 1 || index == 0) {
		return true;
	}
	return palindrome(cl+1, index - 2) && cl[0]==cl[index-1];
}


int main() {
	cout << evenOne(17) << endl;
	cout << evenOne(2) << endl;

	Node a1(1), b1(2, &a1), c1(3, &b1), d1(4), e1(5,&d1);
	Node* f1 = sumList(&c1, &e1);
	
	while (f1) {
		cout << "|"<<f1->data<<"|" << endl;
		f1 = f1->next;
	}
	TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
	TNode g();
	try {
		max(nullptr);
	}
	catch(emptyTree& oor){
		cout << oor.what();
	}
	cout << max(&f) << endl;
	char s[] = "racecarl";
	if (palindrome(s, 8)) { cout << "Yes!\n"; }
}




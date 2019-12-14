#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>;
using namespace std;

/*
  functions for use with CS2124 rec11
  -jbs
*/

// Node to be used a part of linked list
struct Node {
	Node(int data = 0, Node * next = nullptr) : data(data), next(next) {}
	
	int data;
	Node* next;
};

// listAddHead: adds a data item to the beginning of a [possibly empty] list
void listAddHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
	while (headPtr) {
		Node* next = headPtr->next;
		delete headPtr;
		headPtr = next;
	}
}



// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like. 
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
	Node* result = nullptr;
	for (size_t index = vals.size(); index > 0; --index) {
		listAddHead(result, vals[index - 1]);
	}
	return result;
}

void listDisplay(Node* headPtr){
	Node* ptr = headPtr;
	if (ptr == nullptr) {
		cout << "nullptr";
	}
	while (ptr!=nullptr) {
		cout << ptr->data<<" ";
		ptr = ptr->next;
	}
	cout << endl;
}

void splice(Node*& headPtr1, Node*& headPtr2) {
	Node* ptr = headPtr2;
	ptr = ptr->next;
	headPtr2->next = headPtr1;
	while (headPtr1->next != nullptr) {
		headPtr1 = headPtr1->next;
	}
	headPtr1->next = ptr;
}


Node* isSublist(Node* headPtr1, Node* headPtr2) {
	while (headPtr1) {

		Node* current1 = headPtr1;
		Node* current2 = headPtr2;
		while (current1 && current2 && current1->data == current2->data) {
			if (!current2->next) {
				return headPtr1;
				cout << "returning!" << endl;
			}
			current1 = current1-> next;
			current2 = current2-> next;
		}
		headPtr1 = headPtr1->next;
	}
	return nullptr;
	cout << "returned nullptr!" << endl;
}

Node* sharedListBruteForce(Node* headPtr1,Node* headPtr2) {
	Node* original2 = headPtr2;
	while (headPtr1) {
		while (headPtr2) {
			if (headPtr1 == headPtr2) {
				return headPtr1;
			}
			headPtr2 = headPtr2->next;
		}
		headPtr1 = headPtr1->next;
		headPtr2 = original2;	
	}
	return nullptr;
}




Node* sharedListUsingSet(Node* headPtr1, Node* headPtr2) {
	unordered_set<Node*> stuff;
	while (headPtr1) {
		stuff.insert(headPtr1);
		headPtr1 = headPtr1->next;
	}
	while (headPtr2) {
		if (stuff.find(headPtr2) != stuff.end()) {
			return headPtr2;
		}
		headPtr2 = headPtr2->next;
		
	}
	return nullptr;
}

Node* sharedListUsingSetS(Node* headPtr1, Node* headPtr2) {
	int length1=0;
	int length2=0;
	Node* original1 = headPtr1;
	Node* original2 = headPtr2;
	while (headPtr1) {
		length1++;
		headPtr1 = headPtr1->next;
	}
	while (headPtr2) {
		length2++;
		headPtr2 = headPtr2->next;
	}
	headPtr1 = original1;
	headPtr2 = original2;
	if (length1 > length2) {
		for (int i = 0;i < length1 - length2;i++) {
			headPtr1 = headPtr1->next;
		}
	}
	else {
		for (int i = 0;i < length2 - length1;i++) {
			headPtr2 = headPtr2->next;
		}
	}
	while(headPtr1){
		if (headPtr1 == headPtr2 && headPtr1 != nullptr) {
			return headPtr1;
		}
		headPtr1 = headPtr1->next;
		headPtr2 = headPtr2->next;
	}
	
	return nullptr;

}
int main() {
	Node* a= new Node(1);
	listAddHead(a, 9);
	listAddHead(a, 5);
	listAddHead(a, 7);
	Node* b = new Node(2);
	listAddHead(b, 3);
	listAddHead(b, 6);
	listDisplay(a);
	listDisplay(b);
	splice(b, a->next);
	listDisplay(a);

	/*vector<int> veca = { 1,1,2,3,1 };
	vector<int> vecb = { 1,2,3 };
	Node* headPtrA = listBuild(veca);
	listDisplay(headPtrA);
	Node* headPtrB = listBuild(vecb);
	listDisplay(headPtrB);
	cout<<isSublist(headPtrA,headPtrB)->data<<endl;*/
	cout << "Part two:" << endl;
	cout << "target 1,2,3,2,3,2,4,5,6" << endl;
	vector<int> veca = { 1,2,3,2,3,2,4,5,6 };
	vector<int> vecb = { 1 };
	vector<int> vecc = { 3,9 };
	vector<int> vecd = { 2,3 };
	vector<int> vece = { 2,4,5,6 };
	vector<int> vecf = { 2,3,2,4 };
	vector<int> vecg = { 5,6,7 };
	vector<int> vech = { 6 };
	Node* headPtrA = listBuild(veca);
	Node* headPtrB = listBuild(vecb);
	Node* headPtrC = listBuild(vecc);
	Node* headPtrD = listBuild(vecd);
	Node* headPtrE = listBuild(vece);
	Node* headPtrF = listBuild(vecf);
	Node* headPtrG = listBuild(vecg);
	Node* headPtrH = listBuild(vech);
	listDisplay(isSublist(headPtrA, headPtrB));
	listDisplay(isSublist(headPtrA, headPtrC));
	listDisplay(isSublist(headPtrA, headPtrD));
	listDisplay(isSublist(headPtrA, headPtrE));
	listDisplay(isSublist(headPtrA, headPtrF));
	listDisplay(isSublist(headPtrA, headPtrG));
	listDisplay(isSublist(headPtrA, headPtrH));

	cout << "part 3" << endl;
	vector<int> veci = { 2,3,4,5 };
	vector<int> vecj = { 2,3,3 };
	Node* headPtrI = listBuild(veci);
	Node* headPtrJ = listBuild(vecj);
	headPtrJ->next->next->next= headPtrI->next->next;
	cout << sharedListBruteForce(headPtrI,headPtrJ)->data<<endl; 
	cout << sharedListUsingSet(headPtrI, headPtrJ)->data<<endl;
	cout << sharedListUsingSetS(headPtrI, headPtrJ)->data << endl;
}
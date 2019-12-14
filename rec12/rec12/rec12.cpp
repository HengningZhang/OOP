#include<iostream>
#include<string>
using namespace std;



class List {
	struct Node;
	
	friend ostream& operator<<(ostream& os, const List& rhs) {
		cout << "[";
		Node* temp = rhs.header;
		if(temp){
			cout << temp->data;
			temp = temp->next;
		}
		
		while (temp) {
			cout << ", " << temp->data;
			temp = temp->next;
		}
		cout << "]" << endl;
		return os;
	}
public:

	class iterator {
		friend List;
		friend bool operator==(const List::iterator& lhs, const List::iterator& rhs) {

			return lhs.beginner == rhs.beginner;
		}
		friend bool operator!=(const List::iterator& lhs, const List::iterator& rhs) {
			return lhs.beginner != rhs.beginner;
		}
	public:
		iterator(Node* node) {
			beginner = node;
		}
		iterator& operator=(const iterator& rhs) {
			beginner = rhs.beginner;
		}
		iterator& operator++() {
			if (beginner) beginner = beginner->next;
			return *this;
		}
		iterator& operator--() {
			if(beginner) beginner = beginner->prev;
			return *this;
		}
		
		int& operator*() {
			return beginner->data;
		}
		int operator*() const {
			return beginner->data;
		}
	private:
		Node* beginner;
	};
	List() :header(nullptr),trailer(nullptr),thesize(0){}
	void push_back(int data) {
		if (header==nullptr) {
			header = new Node(data);
			trailer = header;
		}
		else {
			trailer->next = new Node(data,nullptr,trailer);
			trailer = trailer->next;
			
		}
		thesize=thesize+1;
	}

	int pop_back() {
		if (!header) {
			cout << "the list you want to popback is empty!";
			return 0;
		}
		int temp = trailer->data;
		if (header == trailer) {
			delete header;
			header = nullptr;
			trailer = nullptr;
			thesize = 0;
		}
		else {
			trailer = trailer->prev;
			delete trailer->next;
			trailer->next = nullptr;
			thesize--;
		}
		return temp;
	}

	const int& front() const {
		return header->data;
	}
	int& front() {
		return header->data;
	}
	const int& back() const {
		return trailer->data;
	}
	int& back() {
		return trailer->data;
	}
	size_t size() const{
		return thesize;
	}

	void push_front(int data) {
		if (!header) {
			header = new Node(data);
			trailer = header;
		}
		else {
			header->prev = new Node(data,header,nullptr);
			header = header->prev;
		}
		thesize++;
	}

	int pop_front() {
		if (!header) {
			cout << "the list you want to pop from is empty" << endl;
			return 0;
		}
		int temp = header->data;
		if (header == trailer) {
			delete header;
			header = nullptr;
			trailer = nullptr;
		}
		else {
			header = header->next;
			delete header->prev;
			header->prev = nullptr;
		}
		thesize--;
		return temp;
	}
	void clear() {
		while (header) {
			pop_back();
		}
	}
	int operator[](size_t index)const{
		Node* temp = header;
		for (size_t i = 0;i < index;i++) {
			temp = temp->next;
		}
		return temp->data;
	}
	int& operator[](size_t index) {
		Node* temp = header;
		for (size_t i = 0;i < index;i++) {
			temp = temp->next;
		}
		return temp->data;
	}
	iterator begin(){
		iterator iter(header);
		return iter;
	}
	
	iterator end(){
		iterator iter(nullptr);
		return iter;
	}
	

	iterator insert(iterator iter,int data) {
		if (iter.beginner == header) {
			push_front(data);
			iterator newiter = begin();
			return newiter;
		}
		if (iter.beginner == nullptr) {
			push_back(data);
			iterator newiter(trailer);
			return newiter;
		}
		else {
			iter.beginner->prev = new Node(data, iter.beginner, iter.beginner->prev);
			iter.beginner->prev->prev->next = iter.beginner->prev;
			iterator newiter(iter.beginner->prev);
			return newiter;
		}
	}

	iterator erase(iterator iter) {
		if (!iter.beginner) {
			return iterator(nullptr);
		}
		if (iter.beginner == trailer) {
			pop_back();
			return iterator(nullptr);
		}
		if (iter.beginner == header) {
			pop_front();
			return iterator(header);
		}
		else {
			iter.beginner->prev->next = iter.beginner->next;
			iter.beginner->next->prev = iter.beginner->prev;
			Node* temp = iter.beginner->next;
			thesize--;
			delete iter.beginner;
			return iterator(temp);
		}


	}

	/*List(const List& rhs){
		header = nullptr;
		trailer = nullptr;
		thesize = 0;
		for (size_t i = 0; i < thesize-1;i++) {
			push_back(rhs[i]);
			cout << rhs[i] << endl;
		}
	}
	List& operator==(const List& rhs) {
		header = nullptr;
		trailer = nullptr;
		thesize = 0;
		for (size_t i = 0; i < thesize -1;i++) {
			push_back(rhs[i]);
			cout << rhs[i] << endl;
		}
		return *this;
	}
	~List() {
		clear();
	}*/
private:
	struct Node {
		Node(int num,Node* next=nullptr, Node* prev= nullptr) :data(num), next(next), prev(prev) {}
		int data;
		Node* next;
		Node* prev;
	};
	
	Node* header;
	Node* trailer;
	size_t thesize;
};
//bool operator==(const List::iterator& lhs,const List::iterator& rhs) {
//	return lhs.beginner == rhs.beginner;
//}
//bool operator!=(const List::iterator& lhs,const List::iterator& rhs) {
//	return lhs.beginner != rhs;
//}
// Task 1

void printListInfo(const List& myList) {
	cout << "size: " << myList.size()
		<< ", front: " << myList.front()
		<< ", back(): " << myList.back()
		<< ", list: " << myList << endl;
}

 //The following should not compile. Check that it does not.
 //void changeFrontAndBackConst(const List& theList){
 //    theList.front() = 17;
 //    theList.back() = 42;
 //}

void changeFrontAndBack(List& theList) {
	theList.front() = 17;
	theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
	for (size_t i = 0; i < myList.size(); ++i) {
		cout << myList[i] << ' ';
	}
	cout << endl;
}

// Task 8
void doNothing(List aList) {
	cout << "In doNothing\n";
	printListInfo(aList);
	cout << endl;
	cout << "Leaving doNothing\n";
}

int main() {

	// Task 1
	cout << "\n------Task One------\n";
	List myList;
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList.push_back(" << i * i << ");\n";
		myList.push_back(i * i);
		printListInfo(myList);
	}
	cout << "===================\n";

	cout << "Modify the first and last items, and display the results\n";
	changeFrontAndBack(myList);
	printListInfo(myList);
	cout << "===================\n";

	cout << "Remove the items with pop_back\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_back();
	}
	cout << "===================\n";

	// Task 2
	cout << "\n------Task Two------\n";
	cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList2.push_front(" << i * i << ");\n";
		myList.push_front(i * i);
		printListInfo(myList);
	}
	cout << "===================\n";
	cout << "Remove the items with pop_front\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_front();
	}
	cout << "===================\n";

	// Task 3
	cout << "\n------Task Three------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		myList.push_back(i * i);
	}
	printListInfo(myList);
	cout << myList.front() << endl;
	cout << "Now clear\n";
	myList.clear();
	cout << "Size: " << myList.size() << ", list: " << myList << endl;
	cout << "===================\n";

	// Task 4
	cout << "\n------Task Four------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i)  myList.push_back(i * i);
	cout << "Display elements with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
	cout << endl;
	cout << "Add one to each element with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
	cout << "And print it out again with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
	cout << endl;
	cout << "Now calling a function, printListSlow, to do the same thing\n";
	printListSlow(myList);
	cout << "Finally, for this task, using the index operator to modify\n"
		<< "the data in the third item in the list\n"
		<< "and then using printListSlow to display it again\n";
	myList[2] = 42;
	printListSlow(myList);


	// Task 5
	cout << "\n------Task Five------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i)  myList.push_back(i * i);
	printListInfo(myList);
	cout << "Now display the elements in a ranged for\n";
	for (int x : myList) cout << x << ' ';
	cout << endl;
	cout << "And again using the iterator type directly:\n";
	// Note you can choose to nest the iterator class or not, your choice.
	//for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
	for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
		cout << *iter << ' ';
	}
	cout << endl;
	cout << "WOW!!! (I thought it was cool.)\n";

	// Task 6
	cout << "\n------Task Six------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
	printListInfo(myList);
	cout << "Filling an empty list with insert at begin(): "
		<< "i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i * i);
	printListInfo(myList);
	// ***Need test for insert other than begin/end***
	cout << "===================\n";

	// Task 7
	cout << "\n------Task Seven------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
	cout << "Erasing the elements in the list, starting from the beginning\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.erase(myList.begin());
	}
	// ***Need test for erase other than begin/end***
	cout << "===================\n";

	// Task 8
	cout << "\n------Task Eight------\n";
	cout << "Copy control\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
	printListInfo(myList);
	cout << "Calling doNothing(myList)\n";
	doNothing(myList);
	cout << "Back from doNothing(myList)\n";
	printListInfo(myList);

	cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
	List listTwo;
	for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i * i);
	printListInfo(listTwo);
	cout << "listTwo = myList\n";
	listTwo = myList;
	cout << "myList: ";
	printListInfo(myList);
	cout << "listTwo: ";
	printListInfo(listTwo);
	cout << "===================\n";
}
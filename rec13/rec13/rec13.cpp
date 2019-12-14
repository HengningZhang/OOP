// rec13_test.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

void print(const list<int>& lis) {//task9
	for (list<int>::const_iterator i = lis.begin();i != lis.end();i++) {
		cout << *i << " ";
	}
	cout << endl;
}
void printr(const list<int>& lis) {//task10
	for (int i : lis) {
		cout << i << " ";
	}
	cout << endl;
}
void printauto(const list<int>& lis) {//task11
	for (auto i = lis.begin();i != lis.end();i++) {
		cout << *i << " ";
	}
	cout << endl;
}
list<int>::const_iterator find(const list<int>& lis, int target) {//task12
	for (list<int>::const_iterator i = lis.begin();i != lis.end();i++) {
		if (*i == target) {
			return i;
		}
	}
	return lis.end();
}

auto findauto(const list<int>& lis, int target) {//task13
	for (auto i = lis.begin();i != lis.end();i++) {
		if (*i == target) {
			return i;
		}
	}
	return lis.end();
}

bool iseven(int num) {//task 15
	return num % 2 == 0;
}

class wyw {//task 16
public:
	bool operator()(int num) const {
		return num % 2 == 0;
	}
};

list<int>::const_iterator ourFind(const list<int>::const_iterator& iter1, const list<int>::const_iterator& iter2, int target) {//task19
	cout << "myFind" << endl;
	for (list<int>::const_iterator i = iter1;i != iter2;i++) {
		if (*i == target) {
			return i;
		}
	}
	return iter2;
}
template<typename T, typename U>
T ourFindT(const T iter1, const T iter2, U target) {//task20
	//cout << "myFindT" << endl;
	for (T i = iter1;i != iter2;i++) {
		if (*i == target) {
			return i;
		}
	}
	return iter2;
}
int main() {
	// 1. Create a vector with some values and display using ranged for
	cout << "Task 1:\n";
	vector<int> vec = { 5,4,3,2,1 };
	for (int i : vec) {
		cout << i << ",";
	}
	cout << endl;
	cout << "\n=======\n";

	// 2. Initalize a list as a copy of values from the vector
	cout << "Task 2:\n";
	list<int> lis(vec.begin(), vec.end());
	for (int i : lis) {
		cout << i << ",";
	}
	cout << endl;
	cout << "\n=======\n";

	// 3. Sort the original vector.  Display both the vector and the list
	cout << "Task 3:\n";
	for (size_t i = 0;i < vec.size() - 1;i++) {
		for (size_t j = 0; j < vec.size() - 1;j++) {
			if (vec[j] > vec[j + 1]) {
				int temp = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = temp;
			}
		}
	}
	cout << "vec:";
	for (int i : vec) {
		cout << i << "," ;
	}
	cout << endl;
	cout << "lis:";
	for (int i : lis) {
		cout << i << ",";
	}
	cout << endl;
	cout << "\n=======\n";


	//// 4. print every other element of the vector.
	cout << "Task 4:\n";
	for (size_t i = 0;i < vec.size();++++i) {
		cout << vec[i] << ",";
	}
	cout << endl;
	cout << "\n=======\n";

	//// 5. Attempt to print every other element of the list using the
	////    same technique.
	cout << "Task 5:\n";
	/*for (size_t i = 0;i < lis.size();i++) {
		cout << lis[i] << ",";
	}*/
	cout << endl;
	cout << "\n=======\n";

	////
	//// Iterators
	////

	//// 6. Repeat task 4 using iterators.  Do not use auto;
	cout << "Task 6:\n";
	for (vector<int>::iterator i = vec.begin();i != vec.end();++i) {
		cout << *i << " ";
	}
	cout << endl;
	cout << "\n=======\n";

	//// 7. Repeat the previous task using the list.  Again, do not use auto.
	////    Note that you cannot use the same simple mechanism to bump
	////    the iterator as in task 6.
	cout << "Task 7:\n";
	for (list<int>::iterator i = lis.begin();i != lis.end();i++) {
		cout << *i << " ";
	}
	cout << endl;
	cout << "\n=======\n";

	//// 8. Sorting a list
	cout << "Task 8:\n";
	lis.sort();
	for (list<int>::iterator i = lis.begin();i != lis.end();i++) {
		cout << *i << " ";
	}
	cout << endl;
	cout << "\n=======\n";

	//// 9. Calling the function to print the list

	cout << "Task 9:\n";
	print(lis);
	cout << "=======\n";

	//// 10. Calling the function that prints the list, using ranged-for
	cout << "Task 10:\n";
	printr(lis);
	cout << "=======\n";

	////
	//// Auto
	////

	//// 11. Calling the function that, using auto, prints alterate
	//// items in the list
	cout << "Task 11:\n";
	printauto(lis);
	cout << "=======\n";


	//// 12.  Write a function find that takes a list and value to search for.
	////      What should we return if not found
	cout << "Task 12:\n";
	
	cout << *find(lis, 1) << endl;

	if (find(lis, 6) == lis.end()) {
		cout << "not in list" << endl;
	}
	cout << "=======\n";

	//// 13.  Write a function find that takes a list and value to search for.
	////      What should we return if not found
	cout << "Task 13:\n";
	cout << *findauto(lis, 1) << endl;
	if (findauto(lis, 6) == lis.end()) {
		cout << "not in list" << endl;
	}
	cout << "=======\n";

	////
	//// Generic Algorithms
	////

	//// 14. Generic algorithms: find
	cout << "Task 14:\n";
	cout << *find(lis.begin(), lis.end(), 1) << endl;
	if (find(lis.begin(), lis.end(), 6) == lis.end()) {
		cout << "not in list" << endl;
	}
	cout << "=======\n";

	//// 15. Generic algorithms: find_if
	cout << "Task 15:\n";
	cout << *find_if(lis.begin(),lis.end(),iseven)<<endl;
	cout << "=======\n";

	//// 16. Functor
	cout << "Task 16:\n";
	cout<< *find_if(lis.begin(), lis.end(), wyw()) << endl;
	cout << "=======\n";

	//// 17. Lambda
	cout << "Task 17:\n";
	[] { cout << "Hello Lambda!"; }();
	[](int a, int b) { cout << a + b << endl; } (4, 5);
	int result = [](int a, int b) { return a + b; }(4,5);
	cout << "the result is: " << result << endl;
	int result2 = [](int a, int b) -> int { return a + b; } (4, 5);
	cout << "the result is: " << result2 << endl;
	cout << *find_if(lis.begin(), lis.end(), [](int num) {return num % 2 == 0;}) << endl;
	cout << "=======\n";

	//// 18. Generic algorithms: copy to an array
	cout << "Task 18:\n";
	int arr[5];
	copy(lis.begin(), lis.end(), arr);
	for (int i : arr) {
		cout << i << ";";
	}

	cout << endl;

	cout << *find(arr, arr+5, 1) << endl;
	if (find(arr, arr + 5, 6) == arr+5) {
		cout << "not in list" << endl;
	}
	cout << "=======\n";

	////
	//// Templated Functions
	////

	//// 19. Implement find as a function for lists
	cout << "Task 19:\n";
	cout << *ourFind(lis.begin(), lis.end(), 1) << endl;
	if (ourFind(lis.begin(), lis.end(), 6) == lis.end()) {
		cout << "not in list" << endl;
	}
	cout << "=======\n";

	//// 20. Implement find as a templated function
	cout << "Task 20:\n";
	cout << *ourFindT(lis.begin(), lis.end(), 1) << endl;
	if (ourFindT(lis.begin(), lis.end(), 6) == lis.end()) {
		cout << "not in list" << endl;
	}
	cout << "=======\n";

	////
	//// Associative collections
	////

	//// 21. Using a vector of strings, print a line showing the number
	////     of distinct words and the words themselves.
	cout << "Task 21:\n";
	vector<string> vecs;
	ifstream f("pooh-nopunc.txt");
	string temp;
	while (f >> temp) {
		if (ourFindT(vecs.begin(), vecs.end(), temp) == vecs.end()) {
			vecs.push_back(temp);
		}
	}
	cout << vecs.size() << "distinct words" << endl;
	cout << "\n=======\n";
	f.close();
	//// 22. Repeating previous step, but using the set
	cout << "Task 22:\n";
	set<string> sets;
	f.open("pooh-nopunc.txt");
	while (f >> temp) {
		if (sets.find(temp) == sets.end()) {
			sets.insert(temp);
		}
	}
	cout <<sets.size() << "distinct words" << endl;
	cout << "\n=======\n";
	f.close();
	cout << "=======\n";

	//// 23. Word co-occurence using map
	cout << "Task 23:\n";
	map<string,vector<int>> wordMap;
	f.open("pooh-nopunc.txt");
	int i = 0;
	while (f >> temp) {
		wordMap[temp].push_back(i);
		i++;
	}
	for (const auto& word : wordMap) {
		cout << word.first << ":";
		for (int i : word.second) {
			cout << i << ",";
		}
		cout << endl;
	}
	cout << "\n=======\n";
	f.close();
	cout << "=======\n";
}

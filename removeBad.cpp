#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std; 

vector <int> destroyedOnes; 
class Movie {
private:
	int m_rating; 
public: 
	Movie(int r) : m_rating(r) {}
	~Movie() { destroyedOnes.push_back(m_rating); }
	int rating() const { return m_rating; }
};

// remove themovies in li with a rating below 50 and detroy them 
void removeBad(vector <Movie*>& v) {
	vector <Movie*> tempV;
	for (int i = 0; i < v.size(); i++) {
		if (v[i]->rating() < 50)
			destroyedOnes.push_back(v[i]->rating());
		else
			tempV.push_back(v[i]); 
	}
	v = tempV; 
}

void removeBad(list <Movie*>& li) {
	list <Movie*> tempList; 
	for (auto itr = li.begin(); itr != li.end(); itr++) {
		if ((*itr)->rating() < 50)
			destroyedOnes.push_back((*itr)->rating());
		else
			tempList.push_back(*itr); 
	}
	li = tempList; 
}

void removeOdds(vector <int>& v) {
	vector <int> tempV; 
	for (int i = 0; i < v.size(); i++) {
		if (v[i] % 2 == 0)
			tempV.push_back(v[i]); 
	}
	v = tempV; 
}

void removeOdds(list <int>& li) {
	list <int> tempList;
	for (auto itr = li.begin(); itr != li.end(); itr++) {
		if (*itr % 2 == 0)
			tempList.push_back(*itr);
	}
	li = tempList;
} 

void testList() {
	int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	list<int> x(a, a + 8); // construct x from the array
	assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	removeOdds(x);
	assert(x.size() == 4);
	vector<int> v(x.begin(), x.end()); // construct v from x
	sort(v.begin(), v.end());
	int expect[4] = { 2, 4, 6, 8 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
}

void testVector(){
	int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	vector<int> x(a, a + 8); // construct x from the array
	assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	removeOdds(x);
	assert(x.size() == 4);
	sort(x.begin(), x.end());
	int expect[4] = { 2, 4, 6, 8 };
	for (int k = 0; k < 4; k++)
		assert(x[k] == expect[k]);
}

void testMovieList(){
	int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
	list<Movie*> x;
	for (int k = 0; k < 8; k++)
		x.push_back(new Movie(a[k]));
	assert(x.size() == 8 && x.front()->rating() == 85 &&
		x.back()->rating() == 10);
	removeBad(x);
	assert(x.size() == 4 && destroyedOnes.size() == 4);
	vector<int> v;
	for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
	{
		Movie* mp = *p;
		v.push_back(mp->rating());
	}
	sort(v.begin(), v.end());
	int expect[4] = { 70, 80, 85, 90 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
	sort(destroyedOnes.begin(), destroyedOnes.end());
	int expectGone[4] = { 10, 15, 20, 30 };
	for (int k = 0; k < 4; k++)
		assert(destroyedOnes[k] == expectGone[k]);
}
void testMovieVector() {
	int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
	vector<Movie*> x;
	for (int k = 0; k < 8; k++)
		x.push_back(new Movie(a[k]));
	assert(x.size() == 8 && x.front()->rating() == 85 &&
		x.back()->rating() == 10);
	removeBad(x);
	assert(x.size() == 4 && destroyedOnes.size() == 4);
	vector<int> v;
	for (int k = 0; k < 4; k++)
		v.push_back(x[k]->rating());
	sort(v.begin(), v.end());
	int expect[4] = { 70, 80, 85, 90 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
	sort(destroyedOnes.begin(), destroyedOnes.end());
	int expectGone[4] = { 10, 15, 20, 30 };
	for (int k = 0; k < 4; k++)
		assert(destroyedOnes[k] == expectGone[k]);
}

//int main(void) {
//	testList(); 
//	cout << "TestList for removeOdds passed :) " << endl;
//
//	testVector(); 
//	cout << "\nTestVector for removeOdds passed :) " << endl; 
//
//	//testMovieList(); 
//	//cout << "\nTestMovieList passed :) " << endl; 
//
//	testMovieVector(); 
//	cout << "\ntestMovieVector passed :)" << endl;
//
//}
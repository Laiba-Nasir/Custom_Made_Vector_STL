using namespace std; 
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <string> 
#include <cassert> 
#include <algorithm> 
#include <csignal> 
#include <vector>


int loadDictionary(istream& dictfile, vector <string>& dict);
int permute(string word, vector <string>& dictV, vector <string>& resultsV);
void display(vector <string>& resultsV);
void testtwo(int n);

const int MAXRESULTS = 20;    // Max matches that can be found
const int MAXDICTWORDS = 10; // Max words that can be read in

//int main(void) {
//	cout << "\n========= TESTING ANAGRAM ===========\n"; 
//	for (int i = 1; i <= 10; i++) {
//		testtwo(i);
//		cout << "Passed case " << i << endl;
//	}
//}

void display(vector <string>& resultsV) {
	// display the size of each string found in resultsV
	for (int i = 0; i < resultsV.size(); i++) {
		cout << resultsV[i] << " ==> " << resultsV[i].size() << endl;
	}
}

int permute(string word, vector <string>& dictV, vector <string>& resultsV) {
	// 1st check if word is in dictionary 
	bool inDictionary = false;
	for (int i = 0; i < dictV.size(); i++) {
		if (dictV[i] == word) {
			inDictionary = true;
			break;
		}
	}
	if (!inDictionary) {
		sort(word.begin(), word.end());
		for (int i = 0; i < dictV.size(); i++) {
			string origStr = dictV[i];
			sort(dictV[i].begin(), dictV[i].end());
			if (word == dictV[i]) {
				resultsV.push_back(origStr);
				return resultsV.size(); 
			}
		}
		cout << "\nNo matches found for " << word << endl;
		return 0;
	}

	// 2nd if the word is in dictionary, make anagrams 
	string str = word;
	while (true) {
		next_permutation(str.begin(), str.end());
		if (str == word) {
			resultsV.push_back(str);
			break;
		}
		resultsV.push_back(str);
		//	cout << str << endl; 
	}

	// check to make sure that that resultsV content is in dictV
	vector <string> tempV;
	bool match;
	for (int i = 0; i < resultsV.size(); i++) {
		match = false;
		for (int j = 0; j < dictV.size(); j++) {
			if (resultsV[i] == dictV[j]) {
				match = true;
				tempV.push_back(resultsV[i]);
			}
		}
	}
	resultsV = tempV;

	if (resultsV.size() > MAXRESULTS)
		return MAXRESULTS; 
	return tempV.size();
}

int loadDictionary(istream& dictfile, vector <string>& dict) {
	// put each string into dictV, returns the # of words in dict
	int i = 0; 
	string str;
	while (getline(dictfile, str) && i < MAXDICTWORDS) {
		if (str != "") {
			dict.push_back(str);
			i++;
		}
	}
	return dict.size();
}


void testtwo(int n)
{
	vector<string> dictionary;
	vector<string> results;

	switch (n)
	{
	default: {
		cout << "Bad argument" << endl;
	} break; case  1: {
		istringstream
			iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod\n");
		int numResults = loadDictionary(iss, dictionary);
		sort(dictionary.begin(), dictionary.end());
		assert(numResults == 9 && dictionary[0] == "act" &&
			dictionary[1] == "art" && dictionary[numResults - 1] == "tar");
	} break; case  2: {
		// File is empty, Checks that file is empty and loadDictionary returns 0.
			istringstream iss("");
		int numResults = loadDictionary(iss, dictionary);
		assert(numResults == 0);
	} break; case  3: {
		// Input file is larger than the dictionary size 
		istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod\ntoo\nmany\nwords\n"); 
		int numResults = loadDictionary(iss, dictionary);
		sort(dictionary.begin(), dictionary.end());
		assert(numResults == 10 && dictionary[MAXDICTWORDS -1] == "too");
	} break; case  4: {
		// If a certain word with repeated letter is shown in results more than once - still accept.
			vector<string> dictionary{ "one", "oone", "ne","e", "too" };
			int numResults = permute("oto", dictionary, results);
			assert(numResults == 1 && results[0] == "too");
	} break; case  5: {
		// No fraction of a permutation is being searched in dictionary
			vector<string> dictionary{ "one", "oone", "ne",
"e", "neoo", "oneo" };
		int numResults = permute("neo", dictionary,
			results);
		assert(numResults == 1 && results[0] == "one");
	} break; case  6: {
		// Checking that no error occurs if more than MAXRESULTS are found.
			vector<string> dictionary{ "true",  "treu", "teru",
"teur", "ture", "tuer", "rtue", "rteu", "retu","reut", "ruet",
"rute", "utre", "uter", "uetr", "uert", "urte", "uret", "etru",
"etur", "ertu", "erut", "eurt", "eutr" };
		// All 24 permutations 
		int numResults = permute("true", dictionary,
			results);
		assert(numResults == MAXRESULTS);
	} break; case  7: {
		// Checking one word was found, no duplicates. 
		vector<string> dictionary{ "ppp" };
		int numResults = permute("ppp", dictionary,
			results);
		assert(numResults == 1 && results[0] == "ppp");
	} break; case  8: {
		streambuf* oldCoutStreamBuf = cout.rdbuf();
		ostringstream strCout;
		cout.rdbuf(strCout.rdbuf());
		vector<string> results{ "cat", "act" };
		display(results);
		cout.rdbuf(oldCoutStreamBuf);
		string temp = strCout.str();
		bool match1 = temp.find("act") != string::npos;
		bool match2 = temp.find("cat") != string::npos;
		assert(match1 && match2);
	} break; case  9: {
		istringstream iss("tier\nrite\nbate\ntire\nttir");
		int numWords = loadDictionary(iss, dictionary);
		sort(dictionary.begin(), dictionary.end());
		assert(numWords == 5 && dictionary[0] == "bate");
		int numResults = permute("tier", dictionary,
			results);
		assert(numResults == 3 && (results[2] == "tire" ||
			results[2] == "tier" || results[2] == "rite"));
	} break; case  10: {
		vector<string> example{ "kool", "moe", "dee" };
		int numResults = permute("look", example, results);
		assert(numResults == 1 && results[0] == "kool");
	} break;
	}
}
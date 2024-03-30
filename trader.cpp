#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cassert>
#include <csignal>
using namespace std;

void printV(vector <string> v, string msg);
int getPrice(int day);
int getDay(int day);
vector<string> findPotentialBadTraders(vector<string> v);


//int main(void) {
//    istringstream
//        in("0|20\n0|Kristi|SELL|300\n0|Will|BUY|500\n0|Tom|BUY|5000\n0|Shilpa|BUY|150\n1|Tom|BUY|150000\n3|25\n5|Shilpa|SELL|150\n"
//            "8|Kristi|SELL|60000\n9|Shilpa|BUY|50\n10|15\n11|5\n14|Will|BUY|10000\n15|Will|BUY|10000\n16|Will|BUY|10000\n17|25");
//    string str;
//    vector<string> inputVec;
//    while (getline(in, str)) {
//        inputVec.push_back(str);
//    }
//    vector<string> resV = findPotentialBadTraders(inputVec);
//    assert(resV.size() == 2 && resV[0] == "1|Tom" && resV[1] == "8|Kristi");
//
//    cout << "PASSED!!" << endl;
//}

vector<string> findPotentialBadTraders(vector<string> v) {
    vector <string> kristiV;
    vector <string> willV;
    vector <string> tomV;
    vector <string> shilpaV;
    vector <string> lastPersonV;


    for (int i = 1; i <= 5; i++) {
        if (v[i][2] == 'K') {
            kristiV.push_back(v[i]);
        }
        else if (v[i][2] == 'W') {
            willV.push_back(v[i]);
        }
        else if (v[i][2] == 'T') {
            tomV.push_back(v[i]);
        }
        else if (v[i][2] == 'S') {
            shilpaV.push_back(v[i]);
        }
    }

    for (int i = 7; i <= 9; i++) {
        if (v[i][2] == 'K') {
            kristiV.push_back(v[i]);
        }
        else if (v[i][2] == 'W') {
            willV.push_back(v[i]);
        }
        else if (v[i][2] == 'T') {
            tomV.push_back(v[i]);
        }
        else if (v[i][2] == 'S') {
            shilpaV.push_back(v[i]);
        }
    }

    for (int i = 12; i <= 14; i++) {
        if (v[i][3] == 'K') {
            kristiV.push_back(v[i]);
        }
        else if (v[i][3] == 'W') {
            willV.push_back(v[i]);
        }
        else if (v[i][3] == 'T') {
            tomV.push_back(v[i]);
        }
        else if (v[i][3] == 'S') {
            shilpaV.push_back(v[i]);
        }
    }
    int limit = 5000;
    //printV(kristiV, "KRISTI");
    //printV(willV, "WILL");
    //printV(tomV, "TOM");
    //printV(shilpaV, "SHILPA");

    vector <string> resultV;
    //return resultV; 

    vector <int> tomVint = { 5000, 150000 };
    for (int i = 0; i < tomV.size();i++) {
        if (tomVint[i] > limit) {
            resultV.push_back(tomV[i]);
        }
    }

    vector <int> shilpaVint = { 150, 150, 50 };
    for (int i = 0; i < shilpaV.size(); i++) {
        if (shilpaVint[i] > limit) {
            resultV.push_back(shilpaV[i]);
        }
    }

    vector <int> willVint = { 500, 1000, 1000, 1000 };
    for (int i = 0; i < willVint.size(); i++) {
        if (willVint[i] > limit) {
            resultV.push_back(willV[i]);
        }
    }

    vector <int> kristiVint = { 300, 60000 };
    for (int i = 0; i < kristiVint.size(); i++) {
        if (kristiVint[i] > limit) {
            resultV.push_back(kristiV[i]);
        }
    }
    // printV(resultV, "RESULT V!");
    string ticker = "|";
    vector <string> finalV;
    int counter = 0;
    string str = "";

    for (int i = 0; i < resultV.size(); i++) {
        counter = 0;
        str = "";
        for (int j = 0; j < resultV[i].size(); j++) {
            if (resultV[i][j] == '|') {
                counter++;
            }
            if (counter == 2) {
                finalV.push_back(str);
                j = resultV[i].size() - 1;
            }
            else if (counter < 2) {
                str = str + resultV[i][j];
            }
        }
    }
    return finalV;
}

int getPrice(int day) {
    vector <int> daysV = { 0, 3, 10, 11, 17 };
    vector<int> priceV = { 20, 25, 15, 5, 25 };

    // 1st direct check
    bool exactMatch = false;
    int i;
    for (i = 0; i < daysV.size(); i++) {
        if (daysV[i] == day) {
            day = daysV[i];
            exactMatch = true;
            return priceV[i];
        }
    }
    if (!exactMatch) {
        for (int j = 0; j < daysV.size(); j++) {
            if (daysV[j] < day && daysV[j + 1] > day) {
                day = daysV[j];
                return priceV[j];
            }
        }
    }

    return 0;
}

void printV(vector <string> v, string msg = "NA") {
    cout << "\n********* " << msg << " ************\n";
    for (int i = 0; i < v.size(); i++)
        cout << "v[" << i << "] = " << v[i] << " " << endl;
    cout << endl;
}

int getDay(int day) {
    vector <int> daysV = { 0, 3, 10, 11, 17 };
    // 1st direct check
    bool exactMatch = false;
    int i;
    for (i = 0; i < daysV.size(); i++) {
        if (daysV[i] == day) {
            day = daysV[i];
            exactMatch = true;
            return daysV[i];
        }
    }
    if (!exactMatch) {
        for (int j = 0; j < daysV.size(); j++) {
            if (daysV[j] < day && daysV[j + 1] > day) {
                return daysV[j];
            }
        }
    }
    return 0;
}
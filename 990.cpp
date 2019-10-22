//
// Created by jlouis on 10/11/2019.
//

/*Given an array equations of strings that represent relationships between variables, each string equations[i] has length 4 and takes one of two different forms: "a==b" or "a!=b".  Here, a and b are lowercase letters (not necessarily different) that represent one-letter variable names.

Return true if and only if it is possible to assign integers to variable names so as to satisfy all the given equations.



Example 1:

Input: ["a==b","b!=a"]
Output: false
Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.  There is no way to assign the variables to satisfy both equations.

Example 2:

Input: ["b==a","a==b"]
Output: true
Explanation: We could assign a = 1 and b = 1 to satisfy both equations.

Example 3:

Input: ["a==b","b==c","a==c"]
Output: true

Example 4:

Input: ["a==b","b!=c","c==a"]
Output: false

Example 5:

Input: ["c==c","b==d","x!=z"]
Output: true



Note:

    1 <= equations.length <= 500
    equations[i].length == 4
    equations[i][0] and equations[i][3] are lowercase letters
    equations[i][1] is either '=' or '!'
    equations[i][2] is '='

*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    bool equationsPossible(vector<string> &equations) {
        vector<string> toCheck{};

        for (const string &e : equations) {
            switch (e[1]) {
                case '=' :
                    if (equalityCheck(e))
                        continue;
                    else
                        return false;
                case '!' :
                    toCheck.push_back(e);
                    break;
                default:
                    cerr << "ERROR" << endl;
            }

        }

        for (const string &f : toCheck) {
            if (!inequalityCheck(f))
                return false;
        }

        return true;
    }

private:
    int series = 0;
    unordered_map<char, int> variableMap{};

    bool equalityCheck(const string &s) {
        auto firstVar = variableMap.find(s[0]), secondVar = variableMap.find(s[3]);

        if (firstVar == variableMap.end()) {
            if (secondVar == variableMap.end()) {
                variableMap.insert({s[0], series});
                variableMap.insert({s[3], series});
                series++;
            } else {
                variableMap.insert({s[0], secondVar->second});
            }
        } else if (secondVar == variableMap.end()) {
            variableMap.insert({s[3], firstVar->second});
        } else { //both variables have values
            // change all vars with value of first and second to value of series
            auto firstVarValue = firstVar->second, secondVarValue = secondVar->second;
            for (auto &var : variableMap) {
                if (var.second == firstVarValue)
                    var.second = secondVarValue;
            }
        }
        return true;
    }

    bool inequalityCheck(const string &s) {
        auto firstVar = variableMap.find(s[0]), secondVar = variableMap.find(s[3]);

        if (firstVar == variableMap.end())
            variableMap.insert({s[0], series++});

        if (secondVar == variableMap.end())
            variableMap.insert({s[3], series++});

        firstVar = variableMap.find(s[0]);
        secondVar = variableMap.find(s[3]);

        return firstVar->second != secondVar->second;
    }
};

int main() {
    auto obj = Solution();
    vector<string> eqs{"c==c", "f!=a", "f==b", "b==c"};
    cout << (obj.equationsPossible(eqs) ? "True" : "False");
}
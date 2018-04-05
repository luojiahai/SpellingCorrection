#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
#include <numeric>
#include <fstream>

#include "levenshtein.h"
#include "analyser.h"

using namespace std;

void get(vector<string>*, const string&);

int main(int argc, char const *argv[]) {
    if (argc < 4) {
        cout << "Missing arguments" << endl;
        cout << "Usage: {DICTIONARY_PATH} {MISSPELL_PATH} {CORRECT_PATH}" << endl;
        return EXIT_FAILURE;
    }

    vector<string> dictionary;
    vector<string> misspell;
    vector<string> correct;
    get(&dictionary, argv[1]);
    get(&misspell, argv[2]);
    get(&correct, argv[3]);

    Analyser analyser;

    Levenshtein levenshtein;
    levenshtein.run(misspell, dictionary, &analyser);

    analyser.analyse(correct);

    return EXIT_SUCCESS;
}

void get(vector<string>* vec, const string& file_name) {
    ifstream file(file_name);
    string line;
    if (file.is_open()) {
        while (getline(file,line)) {
            vec->push_back(line);
        }
        file.close();
    }
}

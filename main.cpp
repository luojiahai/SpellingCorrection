#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
#include <numeric>
#include <fstream>

#include "levenshtein.h"
#include "ngram.h"
#include "analyser.h"

using namespace std;

void get(vector<string>*, const string&);

int main(int argc, char const *argv[]) {
    if (argc < 5) {
        cout << "MissingArgumentsException: Missing arguments" << endl;
        cout << "Usage: {DICTIONARY_PATH} {MISSPELL_PATH} {CORRECT_PATH} {levenshtein | ngram}" << endl;
        return EXIT_FAILURE;
    }

    string method = argv[4];
    transform(method.begin(), method.end(), method.begin(), ::tolower);
    if (method.compare("levenshtein") & method.compare("ngram")) {
        cout << "MethodNotExistException: Method not exist" << endl;
        cout << "Usage: {DICTIONARY_PATH} {MISSPELL_PATH} {CORRECT_PATH} {levenshtein | ngram}" << endl;
        return EXIT_FAILURE;
    }

    cout << "application started" << endl;
    cout << "method: " + method << endl;
    cout << "----------------------------------" << endl;

    vector<string> dictionary;
    vector<string> misspell;
    vector<string> correct;
    get(&dictionary, argv[1]);
    get(&misspell, argv[2]);
    get(&correct, argv[3]);

    cout << "----------------------------------" << endl;

    Analyser analyser;
    if (!method.compare("levenshtein")) {
        Levenshtein levenshtein;
        levenshtein.run(misspell, dictionary, &analyser);
    } else if (!method.compare("ngram")) {
        Ngram ngram;
        ngram.run(misspell, dictionary, &analyser);
    }
    analyser.analyse(correct);

    cout << "done!" << endl;

    return EXIT_SUCCESS;
}

void get(vector<string>* vec, const string& file_name) {
    cout << "reading file: " + file_name << endl;
    ifstream file(file_name);
    string line;
    if (file.is_open()) {
        while (getline(file,line)) {
            vec->push_back(line);
        }
        file.close();
    }
}

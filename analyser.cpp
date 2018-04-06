#include <iostream>
#include <vector>
#include <numeric>
#include <string>

#include "analyser.h"

using namespace std;

void Analyser::add(const string& misspelled_word, const vector<string>& predicted) {
    Predict predict;
    predict.misspelled_word = misspelled_word;
    predict.predicted = predicted;
    Analyser::data.push_back(predict);
}

void Analyser::analyse(const vector<string>& correct) {
    int totalWords = Analyser::data.size();
    int totalPredicts = 0;
    int totalCorrects = 0;
    for (int i = 0; i < totalWords; ++i) {
        auto predict = Analyser::data[i];
        auto correct_word = correct[i];
        for (const auto& predicted_word: predict.predicted) {
            if (!predicted_word.compare(correct_word)) {
                totalCorrects++;
            }
            totalPredicts++;
        }
    }
    for (int i = 0; i < totalWords; ++i) {
        auto predict = Analyser::data[i];
        auto correct_word = correct[i];
        cout << "----------------------------------" << endl;
        cout << "misspelled_word: " + predict.misspelled_word << endl;
        cout << "correct_word: " + correct_word << endl;
        cout << "predicted_words: " << endl;
        for (const auto& str: predict.predicted) {
            cout << "    -> " + str << endl;
        }
    }
    cout << "----------------------------------" << endl;
    cout << "totalWords: " + to_string(totalWords) << endl;
    cout << "totalPredicts: " + to_string(totalPredicts) << endl;
    cout << "totalCorrects: " + to_string(totalCorrects) << endl;
    cout << "----------------------------------" << endl;
    cout << "precision: " + to_string(1.0*totalCorrects/totalPredicts) << endl;
    cout << "recall: " + to_string(1.0*totalCorrects/totalWords) << endl;
    cout << "----------------------------------" << endl;
    cout << "done!" << endl;
}

#include <iostream>
#include <vector>

#include "ngram.h"
#include "analyser.h"

using namespace std;

void Ngram::run(const vector<string>& misspell, const vector<string>& dictionary, Analyser* analyser) {
    vector<string> min_words;
    int min_score = INT16_MAX;
    for (const auto& str1: misspell) { 
        min_words.clear();
        min_score = INT16_MAX;
        for (const auto& str2: dictionary) {
            int score = Ngram::ngram_distance(2, str1, str2);
            if (score == min_score) {
                min_words.push_back(str2);
            } else if (score < min_score) {
                min_score = score;
                min_words.clear();
                min_words.push_back(str2);
            }
        }
        analyser->add(str1, min_words);
		cout << "ngram searching: " + str1 << endl;
    }
}

int Ngram::ngram_distance(const int& n, const string& s1, const string& s2) {
    vector<string> s1_ngrams = Ngram::get_ngrams(n, s1);
    vector<string> s2_ngrams = Ngram::get_ngrams(n, s2);
    vector<string> intersection;
    sort(s1_ngrams.begin(), s1_ngrams.end());
    sort(s2_ngrams.begin(), s2_ngrams.end());
    set_intersection(s1_ngrams.begin(),
                     s1_ngrams.end(),
                     s2_ngrams.begin(),
                     s2_ngrams.end(),
                     back_inserter(intersection));
    // cout << s1 + " " + s2 << endl;
    // cout << "-------ss1----------" << endl;
    // for (const auto& ss1: s1_ngrams) {
    //     cout << ss1 << endl;
    // }
    // cout << "-------ss2----------" << endl;
    // for (const auto& ss2: s2_ngrams) {
    //     cout << ss2 << endl;
    // }
    // cout << "-------inter--------" << endl;
    // for (const auto& inter: intersection) {
    //     cout << inter << endl;
    // }
    int score = s1_ngrams.size() + s2_ngrams.size() - 2 * intersection.size();
    // cout << score << endl;
    // cout << "--------------------" << endl;
    return score;
}

vector<string> Ngram::get_ngrams(const int& n, const string& str) {
    vector<string> ngrams;
    for (int i = 0; i <= str.size()-n+2; ++i) {
        string substring;
        bool flag = false;
        for (int j = 0; j < n; ++j) {
            if (i == 0 && !flag) { 
                substring.push_back('#'); 
                ++j;
                flag = true;
            }
            substring.push_back(str[i+j-1]);
            if ((i+j-1 == str.size()) && !flag) {
                substring.push_back('#');
                ++j;
                flag = true;
            }
        }
        ngrams.push_back(substring);
        substring.clear();
        flag = false;
    }
    return ngrams;
}
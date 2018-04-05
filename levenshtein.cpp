#include <iostream>
#include <vector>
#include <numeric>

#include "levenshtein.h"
#include "analyser.h"

using namespace std;

void Levenshtein::run(const vector<string>& misspell, const vector<string>& dictionary, Analyser* analyser) {
    vector<string> min_words;
    int min_score = INT16_MAX;
    for (const auto& str1: misspell) { 
        min_words.clear();
        min_score = INT16_MAX;
        for (const auto& str2: dictionary) {
            int score = Levenshtein::levenshtein_distance(str1, str2);
            if (score == min_score) {
                min_words.push_back(str2);
            } else if (score < min_score) {
                min_score = score;
                min_words.clear();
                min_words.push_back(str2);
            }
        }
        analyser->add(str1, min_words);
		cout << "searching: " + str1 << endl;
    }
}

unsigned int Levenshtein::edit_distance(const string& s1, const string& s2) {
	const size_t len1 = s1.size(), len2 = s2.size();
	vector<vector<unsigned int>> d(len1 + 1, vector<unsigned int>(len2 + 1));

	d[0][0] = 0;
	for(unsigned int i = 1; i <= len1; ++i) { d[i][0] = i; }
	for(unsigned int i = 1; i <= len2; ++i) { d[0][i] = i; }

	for(unsigned int i = 1; i <= len1; ++i) {
		for(unsigned int j = 1; j <= len2; ++j) {
            d[i][j] = min({ 
                d[i - 1][j] + 1, // deletion
                d[i][j - 1] + 1, // insertion
                d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) // replace or match
            });
        }
    }
	return d[len1][len2];
}

int Levenshtein::levenshtein_distance(const string &s1, const string &s2) {
	// To change the type this function manipulates and returns, change
	// the return type and the types of the two variables below.
	int s1len = s1.size();
	int s2len = s2.size();
	
	auto column_start = (decltype(s1len))1;
	
	auto column = new decltype(s1len)[s1len + 1];
	iota(column + column_start - 1, column + s1len + 1, column_start - 1);
	
	// cout << "-----------------------------" << endl;
	for (auto x = column_start; x <= s2len; x++) {
		column[0] = x;
		auto last_diagonal = x - column_start;
		// cout << "last_diagonal: ";
		// cout << last_diagonal << endl;
		for (auto y = column_start; y <= s1len; y++) {
			auto old_diagonal = column[y];
			auto possibilities = {
				column[y] + 1,
				column[y - 1] + 1,
				last_diagonal + (s1[y - 1] == s2[x - 1]? 0 : 1)
			};
			column[y] = min(possibilities);
			last_diagonal = old_diagonal;
			// cout << "column_y: ";
			// cout << column[y] << endl;
		}
	}
	auto result = column[s1len];
	delete[] column;
	return result;
}

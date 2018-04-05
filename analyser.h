#ifndef ANALYSER_H
#define ANALYSER_H

#include <vector>

using namespace std;

struct Predict {
    string misspelled_word;
    vector<string> predicted;
};

class Analyser {
    private:
        vector<Predict> data;
        float precision;
        float recall;
    public:
        void add(const string&, const vector<string>&);
        void analyse(const vector<string>&);
};

#endif

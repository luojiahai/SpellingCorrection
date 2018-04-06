#ifndef NGRAM_H
#define NGRAM_H

#include <vector>

#include "analyser.h"

class Ngram {
    private:
        vector<string> get_ngrams(const int&, const string&);
    public:
        void run(const vector<string>&, const vector<string>&, Analyser*);
        int ngram_distance(const int&, const string&, const string&);
};

#endif
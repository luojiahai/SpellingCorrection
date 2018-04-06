#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <vector>

#include "analyser.h"

using namespace std;

class Levenshtein {
    public:
        void run(const vector<string>&, const vector<string>&, Analyser*);
        unsigned int levenshtein_distance_old(const string&, const string&);
        int levenshtein_distance(const string&, const string&);
};

#endif

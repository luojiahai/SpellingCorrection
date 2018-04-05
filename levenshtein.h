#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <vector>
#include <map>

#include "analyser.h"

using namespace std;

class Levenshtein {
    public:
        void run(const vector<string>&, const vector<string>&, Analyser*);
        unsigned int edit_distance(const string&, const string&);
        int levenshtein_distance(const string&, const string&);
};

#endif

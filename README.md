This implementation using C++11
Make sure you have installed the GCC complier that supports C++11

Complie:
g++ -std=c++11 main.cpp levenshtein.cpp ngram.cpp analyser.cpp -o main

Usage: 
./main {DICTIONARY_PATH} {MISSPELL_PATH} {CORRECT_PATH} {levenshtein | ngram}

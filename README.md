g++ -std=c++11 main.cpp levenshtein.cpp ngram.cpp analyser.cpp -o main

Usage: ./main {DICTIONARY_PATH} {MISSPELL_PATH} {CORRECT_PATH} {levenshtein | ngram}

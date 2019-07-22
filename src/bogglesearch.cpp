#include "bogglegui.h"
#include <string>
#include "strlib.h"
#include "grid.h"
#include "lexicon.h"
#include "set.h"
using namespace std;

bool humanWordSearch(Grid<char>& board, Lexicon& dictionary, string word);
bool humanWordSearchHelper(const Grid<char>& board, Grid<bool>& marked, string currentWord, string targetWord);
bool searchNeighbors(const Grid<char>& board, Grid<bool>& marked, string currentWord, string targetWord, int row, int col);
void mark(Grid<bool>& marked, int row, int col);
void unmark(Grid<bool>& marked, int row, int col);

bool humanWordSearch(Grid<char>& board, Lexicon& dictionary, string word) {
    if (word.size() < BoggleGUI::MIN_WORD_LENGTH ||
            !dictionary.contains(word)) {
        return false;
    }
    Grid<bool> marked(board.numRows(), board.numCols(), false);
    BoggleGUI::clearHighlighting();
    return humanWordSearchHelper(board, marked, "", toUpperCase(word));
}

bool humanWordSearchHelper(const Grid<char>& board, Grid<bool>& marked, string currentWord, string targetWord) {
    // choose
    for (int r = 0; r < board.numRows(); r ++) {
        for (int c = 0; c < board.numCols(); c ++) {
            char currentChar = board[r][c];
            string newWord = currentWord + charToString(currentChar);
            cout << newWord << endl;
            if (startsWith(targetWord, newWord)) {
                mark(marked, r, c);
                // explore neighbors
                if (searchNeighbors(board, marked, newWord, targetWord, r, c)) {
                    return true;
                } else {
                    unmark(marked, r, c);
                }
            }
        }
    }
    return false;
}

bool searchNeighbors(const Grid<char>& board, Grid<bool>& marked, string currentWord, string targetWord, int row, int col) {
    for (int r = row - 1; r <= row + 1; r ++) {
        for (int c = col - 1; c <= col + 1; c ++) {
            if (board.inBounds(r, c)) {
                char currentChar = board[r][c];
                string newWord = currentWord + charToString(currentChar);
                if (newWord == targetWord) {
                    cout << newWord << endl;
                    mark(marked, r, c);
                    return true;
                }
                if (!marked[r][c] && startsWith(targetWord, newWord)) {
                    cout << newWord << endl;
                    mark(marked, r, c);
                    if (searchNeighbors(board, marked, newWord, targetWord, r, c)) {
                        return true;
                    } else {
                        unmark(marked, r, c);
                    }
                }
            }
        }
    }
    return false;
}

void unmark(Grid<bool>& marked, int row, int col) {
    marked[row][col] = false;
    BoggleGUI::setHighlighted(row, col, false);
}

void mark(Grid<bool>& marked, int row, int col) {
    marked[row][col] = true;
    BoggleGUI::setHighlighted(row, col, true);
}

Set<string> computerWordSearch(Grid<char>& board, Lexicon& dictionary, Set<string>& humanWords) {
    Set<string> words;
    // TODO
    return words;
}

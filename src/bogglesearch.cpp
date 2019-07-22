#include "bogglegui.h"
#include <string>
#include "strlib.h"
#include "grid.h"
#include "lexicon.h"
#include "set.h"
using namespace std;

bool humanWordSearch(Grid<char>& board, Lexicon& dictionary, string word);
bool searchNeighbors(const Grid<char>& board, Grid<bool>& marked, string currentWord, string targetWord, int row, int col);
void mark(Grid<bool>& marked, int row, int col);
void unmark(Grid<bool>& marked, int row, int col);

bool humanWordSearch(Grid<char>& board, Lexicon& dictionary, string word) {
    // Handle word not found in dictionary and word length too low
    if (word.size() < BoggleGUI::MIN_WORD_LENGTH ||
            !dictionary.contains(word)) {
        return false;
    }
    // Initialize marked grid to be filled with false
    Grid<bool> marked(board.numRows(), board.numCols(), false);
    // Clear previous highlighting
    BoggleGUI::clearHighlighting();

    // Iterate over decisions
    for (int r = 0; r < board.numRows(); r ++) {
        for (int c = 0; c < board.numCols(); c ++) {
            // choose
            char currentChar = board[r][c];
            string newWord = charToString(currentChar);
            if (startsWith(word, newWord)) {
                mark(marked, r, c);
                // explore neighbors
                if (searchNeighbors(board, marked, newWord, word, r, c)) {
                    // add score
                    // Words of 4 or fewer letters are worth 1 point.
                    // 5-letter words are worth 2 points.
                    // 6-letter words are worth 3 points.
                    // 7-letter words are worth 5 points.
                    // Words longer than 7 letters are worth 11 points.
                    if (word.size() <= 4) {
                        BoggleGUI::scorePointsHuman(1);
                    } else if (word.size() == 5) {
                        BoggleGUI::scorePointsHuman(2);
                    } else if (word.size() == 6) {
                        BoggleGUI::scorePointsHuman(3);
                    } else if (word.size() == 7) {
                        BoggleGUI::scorePointsHuman(5);
                    } else if (word.size() > 7) {
                        BoggleGUI::scorePointsHuman(11);
                    }
                    return true;
                } else {
                    // move to next starting character
                    unmark(marked, r, c);
                }
            }
        }
    }
    // no decisions left to make, the target word is not found
    return false;
}

bool searchNeighbors(const Grid<char>& board, Grid<bool>& marked, string currentWord, string targetWord, int row, int col) {
    // explore eight adjacent neighbors
    for (int r = row - 1; r <= row + 1; r ++) {
        for (int c = col - 1; c <= col + 1; c ++) {
            if (board.inBounds(r, c)) {
                // choose
                char currentChar = board[r][c];
                string newWord = currentWord + charToString(currentChar);
                if (newWord == targetWord) {
                    mark(marked, r, c);
                    return true;
                }
                if (!marked[r][c] && startsWith(targetWord, newWord)) {
                    mark(marked, r, c);
                    if (searchNeighbors(board, marked, newWord, targetWord, r, c)) {
                        return true;
                    } else {
                        // backtrack to choose another neighbor
                        unmark(marked, r, c);
                    }
                }
            }
        }
    }
    // all neighbors failed to match the target word
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

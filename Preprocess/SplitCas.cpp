#include "SplitCas.h"

std::vector<std::string> splitCas(std::ifstream& casfile) {
    std::vector<std::string> result;
    std::stack<int> parenthesisStack;
    std::ostringstream currentBlock;
    char ch;

    // Read the file character by character
    while (casfile.get(ch)) {
        if (ch == '(') {
            // Start of a new block or nested block
            if (!parenthesisStack.empty()) {
                // Append the '(' to the current block if it's not the outermost one
                currentBlock << ch;
            }
            // Push the index of the start of the current block (or an empty one)
            parenthesisStack.push(result.size());
            // If the result vector is empty or the last block is empty, add a new empty block
            if (result.empty() || result.back().empty()) {
                result.push_back("");
            }
        }
        else if (ch == ')') {
            // End of a block or nested block
            int startIndex = parenthesisStack.top();
            parenthesisStack.pop();
            // Append the ')' to the current block
            currentBlock << ch;
            // If this ')' closes the outermost block, move the current block to result
            if (parenthesisStack.empty()) {
                result[startIndex] = currentBlock.str();
                currentBlock.str(""); // Clear the stringstream's content
                currentBlock.clear(); // Clear the stringstream's state
            }
        }
        else {
            // If it's not a parenthesis, just append to the current block
            currentBlock << ch;
        }
    }

    // No need to remove empty strings here because we only add non-empty blocks to result
    // when an outermost parenthesis is closed.
    casfile.close();
    return result;
}
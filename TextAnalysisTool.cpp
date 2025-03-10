#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Function to tokenize a text into words, removing punctuation and converting to lowercase
std::vector<std::string> tokenizeText(const std::string& text) {
    std::vector<std::string> words;
    std::string word;
    // Iterate through each character in the text
    for (char c : text) {
        // Check if the character is alphabetic
        if (isalpha(c)) {
            // Convert the character to lowercase and append it to the current word
            word.push_back(tolower(c));
        } else if (!word.empty()) {
            // If the character is not alphabetic and the current word is not empty, add the word to the vector
            words.push_back(word);
            // Clear the current word for the next word
            word.clear();
        }
    }
    // Add the last word if there's any remaining at the end of the text
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

int main() {
    std::string fileName = "sample.txt"; // Replace with your file name

    // Open and read the text file
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Couldn't open the file." << std::endl;
        return 1;
    }

    // Read the entire file content into a string
    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // Tokenize the text content into individual words
    std::vector<std::string> words = tokenizeText(text);

    // Count occurrences of each word
    std::vector<std::pair<std::string, int>> wordOccurrences;
    for (const std::string& word : words) {
        bool found = false;
        // Iterate through wordOccurrences to find if the word exists
        for (auto& pair : wordOccurrences) {
            // If word already exists in wordOccurrences, increment its count
            if (pair.first == word) {
                pair.second++;
                found = true;
                break;
            }
        }
        // If word doesn't exist in wordOccurrences, add it with count 1
        if (!found) {
            wordOccurrences.emplace_back(word, 1);
        }
    }

    // Find the longest word
    std::string longestWord;
    for (const std::string& word : words) {
        // Update longestWord if current word is longer
        if (word.length() > longestWord.length()) {
            longestWord = word;
        }
    }

    // Print unique words and their occurrences
    std::cout << "Unique Words and Their Occurrences:" << std::endl;
    for (const auto& pair : wordOccurrences) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }

    // Print the longest word
    if (!longestWord.empty()) {
        std::cout << "Longest word: " << longestWord << std::endl;
    }

    // Print all words stored in vector
    std::cout << "Words stored in vector:" << std::endl;
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    return 0;
}

#include <fstream>
#include "zipf.hpp"
#include <iostream>
#include <sstream>



std::vector<char> readBook(std::string fileName) {
    // Create a vector to store the characters
    std::vector<char> result;
    
    // Open the file
    std::ifstream file(fileName);
    
    // Check if file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return result;
    }
    
    // Read file character by character
    char ch;
    while (file.get(ch)) {
        // Convert to lowercase
        ch = tolower(ch);
        
        // If it's an alphabetic character, add it to the vector
        if (std::isalpha(ch)) {
            result.push_back(ch);
        }
        // If it's not alphabetic, add a space (but avoid multiple consecutive spaces)
        else if (!result.empty() && result.back() != ' ') {
            result.push_back(' ');
        }
    }
    
    // Close the file
    file.close();
    
    return result;
}


std::map<std::string, int> computeWordFrequency(const std::vector<char>& book) {
    // Create a map to store word frequencies
    std::map<std::string, int> frequencies;
    
    // Create a string from the vector of characters
    std::string text(book.begin(), book.end());
    
    // Create a stringstream from the text
    std::stringstream ss(text);
    
    // Read word by word
    std::string word;
    while (ss >> word) {  // This automatically splits on whitespace
        // Skip empty words
        if (!word.empty()) {
            // Increment frequency counter for this word
            frequencies[word]++;
        }
    }
    
    return frequencies;
}

int countUniqueWords(const std::vector<char>& book) {
    // Convert vector of chars to string
    std::string text(book.begin(), book.end());
    
    // Create stringstream from text
    std::stringstream ss(text);
    
    // Create a set to store unique words
    std::set<std::string> uniqueWords;
    
    // Read word by word
    std::string word;
    while (ss >> word) {
        // Skip empty words
        if (!word.empty()) {
            // Insert word into set
            // If word already exists, insert will do nothing
            uniqueWords.insert(word);
        }
    }
    
    // Return number of unique words
    return uniqueWords.size();
}


std::multimap<int, std::string, std::greater<int>> sortFrequencies(const std::map<std::string, int>& frequencies) {
    // Create multimap with greater comparator (for descending order)
    std::multimap<int, std::string, std::greater<int>> sorted;
    
    // Iterate through the word frequencies map
    for (const auto& pair : frequencies) {
        // Insert into multimap with frequency as key and word as value
        // This reverses the original map's key-value pairs
        sorted.insert({pair.second, pair.first});
    }
    
    return sorted;
}


void writeFrequencyFile(const std::multimap<int, std::string, std::greater<int>>& sorted, const std::string& outputFile) {
    // Open output file
    std::ofstream outFile(outputFile);
    
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << outputFile << std::endl;
        return;
    }
    
    // Write header
    outFile << "# rank frequency word\n";
    
    // Write data
    int rank = 1;  // Start from rank 1
    for (const auto& pair : sorted) {
        outFile << rank << " " 
                << pair.first << " "  // frequency
                << pair.second        // word
                << "\n";
        rank++;
    }
    
    outFile.close();
}

void findHapaxLegomena(const std::multimap<int, std::string, std::greater<int>>& sorted) {
    // Vector to store words that appear only once
    std::vector<std::string> hapaxWords;
    
    // Find words with frequency of 1
    for (const auto& pair : sorted) {
        if (pair.first == 1) {  // If frequency is 1
            hapaxWords.push_back(pair.second);
        }
        else if (pair.first > 1) {
            // Since multimap is sorted in descending order,
            // once we see frequency > 1, we can continue collecting words
            continue;
        }
    }
    
    // Print results
    std::cout << "\nHápax Legomena Analysis:\n";
    std::cout << "------------------------\n";
    std::cout << "Total words that appear only once: " << hapaxWords.size() << "\n\n";
    
    // Print sample of hapax legomena (first 15 words)
    std::cout << "Sample of words that appear only once:\n";
    int count = 0;
    for (const auto& word : hapaxWords) {
        if (count >= 15) break;  // Show only first 15 words
        std::cout << std::setw(4) << (count + 1) << ". " << word << "\n";
        count++;
    }
}

BookStats getBookStatistics(const std::multimap<int, std::string, std::greater<int>>& sorted) {
    BookStats stats = {0, 0, 0};
    
    // Count unique words (size of multimap)
    stats.uniqueWords = sorted.size();
    
    // Count total words and hapax legomena
    for (const auto& pair : sorted) {
        stats.totalWords += pair.first;  // Add frequency
        if (pair.first == 1) {
            stats.hapaxCount++;
        }
    }
    
    return stats;
}
#include "zipf.hpp"
#include <iostream>

void processBook(const std::string& filename, const std::string& outputFile) {
    // Read the book
    std::vector<char> book = readBook(filename);
    
    // Get word frequencies
    auto frequencies = computeWordFrequency(book);
    
    // Sort frequencies
    auto sorted = sortFrequencies(frequencies);
    
    // Write to file for plotting
    writeFrequencyFile(sorted, outputFile);
    
    // Print Hapax Legomena for this book
    std::cout << "\nAnalysis for " << filename << ":\n";
    findHapaxLegomena(sorted);
  BookStats stats = getBookStatistics(sorted);
    
    // Print statistics
    std::cout << "\nStatistics for " << filename << ":\n";
    std::cout << "Total words: " << stats.totalWords << "\n";
    std::cout << "Unique words: " << stats.uniqueWords << "\n";
    std::cout << "Hapax legomena: " << stats.hapaxCount << " (" 
              << (stats.hapaxCount * 100.0 / stats.uniqueWords) << "% of unique words)\n";
}

int main() {
    // Process both books
    std::cout << "Processing Moby Dick...\n";
    processBook("data/moby-dick.txt", "frequencies_moby.txt");
    
    std::cout << "\nProcessing Anthem...\n";
    processBook("data/anthem.txt", "frequencies_anthem.txt");
    
    std::cout << "\nGenerating comparison plot...\n";
    return 0;
}
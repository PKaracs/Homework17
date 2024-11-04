#ifndef ZIPF_HPP
#define ZIPF_HPP

#include <vector>
#include <string>
#include <map>
#include <set>

std::vector<char> readBook(std::string fileName);
std::map<std::string, int> computeWordFrequency(const std::vector<char>& book);
int countUniqueWords(const std::vector<char>& book);
std::multimap<int, std::string, std::greater<int>> sortFrequencies(const std::map<std::string, int>& frequencies);
void writeFrequencyFile(const std::multimap<int, std::string, std::greater<int>>& sorted, const std::string& outputFile);
void findHapaxLegomena(const std::multimap<int, std::string, std::greater<int>>& sorted);

struct BookStats {
    int totalWords;
    int uniqueWords;
    int hapaxCount;
};

BookStats getBookStatistics(const std::multimap<int, std::string, std::greater<int>>& sorted);

#endif
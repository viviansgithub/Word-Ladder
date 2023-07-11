#ifndef WORD_LADDER_HPP_
#define WORD_LADDER_HPP_

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>

class WordLadder {
private:
  std::unordered_map<std::string, std::unordered_set<std::string>> adjList;
  std::unordered_set<std::string> vertices;

public:
  WordLadder();
  explicit WordLadder(const std::string& filename);

  void addVertex(const std::string& a);
  void addEdge(const std::string& a, const std::string& b);
  bool isEdge(const std::string& a, const std::string& b) const;
  bool isVertex(const std::string& a) const;
  void removeVertex(const std::string& a);
  std::vector<std::string> getShortestPath(const std::string& origin, const std::string& dest);
  std::map<std::string, int> listComponents();

private:
  bool isOneLetterDifference(const std::string& word1, const std::string& word2);
  std::unordered_set<std::string> getNeighbors(const std::string& word);
  std::vector<std::string> performBFS(const std::string& origin, const std::string& dest);
};

#endif // WORD_LADDER_HPP_

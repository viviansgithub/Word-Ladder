#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <map>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include "wordLadder.hpp"

WordLadder::WordLadder() = default;

WordLadder::WordLadder(const std::string& inputFile) {
  std::ifstream infile(inputFile);
  std::string word;
  while (infile >> word) {
    addVertex(word);
  }
}

void WordLadder::addVertex(const std::string& word) {
  if (vertices.count(word) == 0) {
    vertices.insert(word);
    adjList[word] = {};
  }
}

void WordLadder::addEdge(const std::string& a, const std::string& b) {
  if (isVertex(a) && isVertex(b)) {
    adjList[a].insert(b);
    adjList[b].insert(a);
  }
}

void WordLadder::removeVertex(const std::string& a) {
  if (isVertex(a)) {
    for (const auto& neighbor : adjList[a]) {
      adjList[neighbor].erase(a);
    }
    adjList.erase(a);
    vertices.erase(a);
  }
}

bool WordLadder::isEdge(const std::string& a, const std::string& b) const {
  if (isVertex(a) && isVertex(b)) {
    return adjList.at(a).count(b) > 0;
  }
  return false;
}

bool WordLadder::isVertex(const std::string& a) const {
  return vertices.count(a) > 0;
}

bool WordLadder::isOneLetterDifference(const std::string& word1, const std::string& word2) {
  int diffCount = 0;
  for (size_t i = 0; i < word1.length(); ++i) {
    if (word1[i] != word2[i]) {
      ++diffCount;
      if (diffCount > 1)
        return false; // More than one letter difference
    }
  }
  return diffCount == 1;
}

std::unordered_set<std::string> WordLadder::getNeighbors(const std::string& word) {
  std::unordered_set<std::string> neighbors;
  for (const auto& vertex : vertices) {
    if (isOneLetterDifference(word, vertex)) {
      neighbors.insert(vertex);
    }
  }
  return neighbors;
}

std::vector<std::string> WordLadder::performBFS(const std::string& origin, const std::string& dest) {
  std::queue<std::string> queue;
  std::unordered_map<std::string, std::string> previous;
  std::unordered_set<std::string> visited;

  queue.push(origin);
  visited.insert(origin);

  while (!queue.empty()) {
    std::string current = queue.front();
    queue.pop();

    if (current == dest) {
      std::vector<std::string> path;
      while (current != origin) {
        path.push_back(current);
        current = previous[current];
      }
      path.push_back(origin);
      std::reverse(path.begin(), path.end());
      return path;
    }

    std::unordered_set<std::string> neighbors = getNeighbors(current);
    for (const auto& neighbor : neighbors) {
      if (visited.count(neighbor) == 0) {
        queue.push(neighbor);
        visited.insert(neighbor);
        previous[neighbor] = current;
      }
    }
  }

  return {};
}

std::vector<std::string> WordLadder::getShortestPath(const std::string& origin, const std::string& dest) {
  if (!isVertex(origin) || !isVertex(dest))
    return {};

  return performBFS(origin, dest);
}

std::map<std::string, int> WordLadder::listComponents() {
  std::map<std::string, int> components;
  std::unordered_set<std::string> visited;

  for (const auto& vertex : vertices) {
    if (visited.count(vertex) == 0) {
      std::queue<std::string> queue;
      queue.push(vertex);
      visited.insert(vertex);
      int count = 0;

      while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();
        count++;

        std::unordered_set<std::string> neighbors = getNeighbors(current);
        for (const auto& neighbor : neighbors) {
          if (visited.count(neighbor) == 0) {
            queue.push(neighbor);
            visited.insert(neighbor);
          }
        }
      }

      components[vertex] = count;
    }
  }

  return components;
}


#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "wordLadder.hpp"

class LadderTest : public ::testing::Test {
 protected:
  WordLadder G {"4words.txt"};
};

TEST_F(LadderTest, isEdgeTrue) {
  // first letter differs
  EXPECT_TRUE(G.isEdge("boom", "doom"));
  EXPECT_TRUE(G.isEdge("doom", "boom"));
  // second letter differs
  EXPECT_TRUE(G.isEdge("aced", "aged"));
  EXPECT_TRUE(G.isEdge("aged", "aced"));
  // third letter differs
  EXPECT_TRUE(G.isEdge("woof", "wolf"));
  EXPECT_TRUE(G.isEdge("wolf", "woof"));
  // fourth letter differs
  EXPECT_TRUE(G.isEdge("look", "loot"));
  EXPECT_TRUE(G.isEdge("loot", "look"));
}

TEST_F(LadderTest, isEdgeFalse) {
  // differ on two letters
  EXPECT_FALSE(G.isEdge("hill", "hike"));
  EXPECT_FALSE(G.isEdge("hike", "hill"));
  // distance one with fake word
  EXPECT_FALSE(G.isEdge("axes", "ates"));
  EXPECT_FALSE(G.isEdge("ates", "axes"));
  // cehck that calling isEdge does not insert anything
  EXPECT_FALSE(G.isEdge("axes", "ates"));
  EXPECT_FALSE(G.isEdge("ates", "axes"));
  EXPECT_FALSE(G.isVertex("ates"));
}

TEST_F(LadderTest, isVertexTrue) {
  // word with no neighbours should still be a vertex
  EXPECT_TRUE(G.isVertex("adze"));
  EXPECT_TRUE(G.isVertex("afro"));
  EXPECT_TRUE(G.isVertex("isms"));
  EXPECT_TRUE(G.isVertex("meow"));
}

TEST_F(LadderTest, isVertexFalse) {
  // fake words are not vertices
  EXPECT_FALSE(G.isVertex("dkll"));
  // calling isVertex does not insert word
  EXPECT_FALSE(G.isVertex("dkll"));
  // another example
  EXPECT_FALSE(G.isVertex("moye"));
  EXPECT_FALSE(G.isVertex("moye"));
}

TEST_F(LadderTest, addVertexNotPresent) {
  // I think yeet should be in the list
  G.addVertex("yeet");
  EXPECT_TRUE(G.isVertex("yeet"));
  // no edges yet
  EXPECT_FALSE(G.isEdge("yeet", "meet"));
}

TEST_F(LadderTest, addEdges) {
  G.addVertex("yeet");
  G.addEdge("meet", "yeet");
  EXPECT_TRUE(G.isEdge("yeet", "meet"));
  EXPECT_TRUE(G.isEdge("meet", "yeet"));
  G.addEdge("yeet", "feet");
  EXPECT_TRUE(G.isEdge("feet", "yeet"));
  EXPECT_TRUE(G.isEdge("yeet", "feet"));
}

TEST_F(LadderTest, removeVertex) {
  G.removeVertex("sign");
  EXPECT_FALSE(G.isEdge("sign", "sigh"));
  EXPECT_FALSE(G.isEdge("sigh", "sign"));
  EXPECT_FALSE(G.isVertex("sign"));
  EXPECT_TRUE(G.isVertex("sigh"));
}

TEST_F(LadderTest, removeVertexNotPresent) {
  G.removeVertex("udks");
  // check that removing does not add
  EXPECT_FALSE(G.isVertex("udks"));
}

TEST_F(LadderTest, distanceOne) {
  std::vector<std::string> path = G.getShortestPath("ache", "achy");
  ASSERT_EQ(path.size(), 2u);
  ASSERT_EQ(path.front(), "ache");
  ASSERT_EQ(path.back(), "achy");
}

TEST_F(LadderTest, fourFive) {
  std::vector<std::string> path = G.getShortestPath("four", "five");
  ASSERT_LE(path.size(), 7u);
  ASSERT_GE(path.size(), 5u);
  ASSERT_EQ(path.front(), "four");
  ASSERT_EQ(path.back(), "five");
}

TEST_F(LadderTest, catsDogs) {
  std::vector<std::string> path = G.getShortestPath("cats", "dogs");
  ASSERT_EQ(path.size(), 4u);
  ASSERT_EQ(path.front(), "cats");
  ASSERT_EQ(path.back(), "dogs");
}

TEST_F(LadderTest, cowsMilk) {
  std::vector<std::string> path = G.getShortestPath("cows", "milk");
  ASSERT_LE(path.size(), 6u);
  ASSERT_GE(path.size(), 5u);
  ASSERT_EQ(path.front(), "cows");
  ASSERT_EQ(path.back(), "milk");
}

TEST_F(LadderTest, bandChin) {
  std::vector<std::string> path = G.getShortestPath("band", "chin");
  ASSERT_LE(path.size(), 7u);
  ASSERT_GE(path.size(), 5u);
  ASSERT_EQ(path.front(), "band");
  ASSERT_EQ(path.back(), "chin");
}

TEST_F(LadderTest, dyadAndAble) {
  std::string origin {"dyad"};
  std::string dest {"able"};
  std::vector<std::string> path = G.getShortestPath(origin, dest);
  // not connected
  ASSERT_EQ(path.size(), 0u);
}

TEST_F(LadderTest, bangAndPlow) {
  std::string origin {"bang"};
  std::string dest {"plow"};
  std::vector<std::string> path = G.getShortestPath(origin, dest);
  ASSERT_LE(path.size(), 8u);
  ASSERT_GE(path.size(), 5u);
}

TEST_F(LadderTest, palsAndDrop) {
  std::string origin {"pals"};
  std::string dest {"drop"};
  std::vector<std::string> path = G.getShortestPath(origin, dest);
  ASSERT_LE(path.size(), 6u);
  ASSERT_GE(path.size(), 5u);
}

TEST_F(LadderTest, noonAndRube) {
  std::string origin {"noon"};
  std::string dest {"rube"};
  std::vector<std::string> path = G.getShortestPath(origin, dest);
  ASSERT_LE(path.size(), 7u);
  ASSERT_GE(path.size(), 5u);
}

TEST_F(LadderTest, catsAndPawn) {
  std::string origin {"cats"};
  std::string dest {"pawn"};
  std::vector<std::string> path = G.getShortestPath(origin, dest);
  ASSERT_EQ(path.size(), 4u);
}

TEST_F(LadderTest, dewsAndKohl) {
  // there is no path between "dews" and "kohl"
  std::vector<std::string> path = G.getShortestPath("dews", "kohl");
  ASSERT_TRUE(path.empty());
}

TEST_F(LadderTest, numberOfComponents) {
  std::map<std::string, int> c = G.listComponents();
  // There are 103 connected components
  ASSERT_EQ(c.size(), 103u);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

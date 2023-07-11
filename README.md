Word Ladder is a word game where I am given two words and must transform one into the other by changing one letter at a time, such that each change results in a valid word.  For example, if we want to change "four" into "five" we can do so in 6 steps via: four-tour-torr-tore-tire-fire-five (torr is a unit of pressure).  Given two words, we want to find the minimum number of moves it takes to change one into another, or determine that it is not possible to do so. The game can be played online here : https://fourword.xyz/.  We will use the same list of valid four letter words (the provided file 4words.txt) that is used by this website.

Given a list of valid four letter words, we can construct an associated graph.  There is a vertex for every word on the list.  Two vertices are connected by an edge if and only if they differ by just one letter.  In other words, if two vertices are connected by an edge, we can move from one to the other in one step in a word ladder.  Finding the optimal solution to a word ladder then amounts to finding a shortest path in this graph.  In this challenge, I wrote a function that given two four letter words will find a shortest path between them, that is will optimally solve the word ladder game (or say that there is no path between the words) for any two given input words.

I had the freedom to choose the data structure I wanted to use to store the word graph, was able to make any additions to wordLadder.hpp I needed to accommodate my design (this includes member variables and member functions) and could also add any other libraries I needed.  My member functions were implemented in wordLadder.cpp.

In addition to finding shortest paths, I was asked to implement several other primitives on this graph.  Let's look first at the easy member functions in wordLadder.hpp , which are addVertex, addEdge, isVertex, isEdge, and removeVertex.  All of addVertex, addEdge, isVertex, isEdge should work in O(logN) time where N is the number of vertices.  removeVertex should work in time O(DlogN) where D is the number of neighbors of the vertex being removed.

class WordLadder {
 private:
  // put whatever member variables you want to represent the graph here

 public:
  // default constructor doesn't have to do anything
  WordLadder();
  // construct word graph from words given in filename
  explicit WordLadder(const std::string& filename);

  // add vertex a to the graph with no neighbours if a is
  // not already a vertex.  Otherwise, do nothing.
  void addVertex(const std::string& a);
  // if both a and b are vertices in the graph then add
  // an edge between them.  Otherwise do nothing.
  void addEdge(const std::string& a, const std::string& b);
  // check if there is an edge between words a and b
  bool isEdge(const std::string& a, const std::string& b) const;
  // check if a is a vertex
  bool isVertex(const std::string& a) const;
  // remove vertex a from the graph
  void removeVertex(const std::string& a);
  ...
};

Most of these are self-explanatory.  One design decision made which I had to follow is that addEdge(a, b) will only add an edge between a and b if they are both already vertices in the graph.

The main event is to implement the getShortestPath function.  The running time of this function should be O(E), where E is the number of edges in the graph.  Note that if there is no path between the two input words then I should return an empty vector.

  // solve the word ladder problem between origin and dest.
  // output a vector whose first element is origin, last element is dest,
  // and where each intermediate word is a valid word and differs from the
  // previous one by a single letter. Moreover the size of this vector
  // should be as small as possible, i.e. it lists vertices on a shortest
  // path from origin to dest. If there is no path between origin and dest
  // return an empty vector.
  std::vector<std::string>
  getShortestPath(const std::string& origin, const std::string& dest);

Another interesting function to implement is listComponents.  This returns a std::map<std::string, int>.  The size of this map is the number of connected components in the graph.  For each connected component there is a std::pair<std::string, int> where the first element of the pair is an example word in that connected component, and the int is the number of words in that connected component.  The example word can be any word in the connected component.  The running time of this function should be O(E+NlogN) where E is the number of edges and N is the number of vertices.

  // compute all the connected components in the graph.  The output is
  // a std::map<std::string, int>.  The size of the map should be the
  // number of connected components.  For each connected component give the
  // name of a word in the connected component (the std::string part of the
  // pair) and the number of words in that connected component (the int part).
  std::map<std::string, int> listComponents();

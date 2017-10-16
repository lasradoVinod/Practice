
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;
class Trie {
  bool end_of_word = false;
  using ptr_type = Trie *; 
                           
  ptr_type children[256];

  ptr_type &child_ptr(unsigned char c) {
    return children[c];
  }
public:
  bool contains(const char *str);

 bool contains(const std::string &s) {
    return contains(s.c_str());
  }

 void insert(const char *str);
  void insert(const std::string &s) {
    insert(s.c_str());
  }

 Trie();
  ~Trie();
};

// Please implement these methods
Trie::Trie() {
    for (int i = 0; i < 256 ;i++ )
    {
        children[i] = NULL;
    }
}

bool Trie::contains(const char *str) {
    ptr_type p;
    while(*str != '\0')
    {
        p = child_ptr((unsigned char)*str);
        if (p == NULL)
        {
            return false;
        }
        str ++;
    }
    return p->end_of_word;
}

void Trie::insert(const char *str) {   
    ptr_type p;
    
    while(*str != '\0')
    {
        p = child_ptr((unsigned char)*str);
        if (p == NULL)
        {
            p = children[(unsigned char)*str] = new Trie();
        }
        str ++;
    }
    p->end_of_word = true;
}

Trie::~Trie() {
    
}

int main() {
  std::string s;
  Trie t;
  while (std::getline(std::cin, s)) {
    char c = s[0];
    s.erase(s.begin(), s.begin() + 1);
    switch (c) {
    case 'C':
      if (t.contains(s)) {
        std::cout << "true" << std::endl;
      } else {
        std::cout << "false" << std::endl;
      }
      break;
    case 'A':
      t.insert(s);
      break;
    };
  }
  return 0;
}
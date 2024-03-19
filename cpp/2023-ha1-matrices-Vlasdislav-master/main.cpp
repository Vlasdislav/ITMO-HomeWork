#include <iostream>
#include <cstring>
#include <map>
#include <functional>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstdio>
 
#include "matrices.hpp"
 
const char* X = "X.txt";
 
std::map<std::string,
          std::function<void(const std::string&,
                              const std::string&)>> mp = {
  { "--add", add },
  { "--mult", mult }
};
 
void createX(std::string file) {
  std::ifstream in(file);
  size_t n, m;
  in >> n >> m;
  std::ofstream out(X, std::ios::trunc);
  out << n << ' ' << m << std::endl;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      out << 0 << ' ';
    }
    out << std::endl;
  }
}
 
int main(int argc, char** argv) {
  if (argc <= 1) {
    std::cerr << "error: format isn\'t correct\n";
    exit(1);
  }
  std::string op = "--add";
  bool firstTime = true;
  for (int i = 1; i < argc; ++i) {
    if (mp.count(argv[i])) {
      op = argv[i];
    } else {
      if (firstTime) {
        createX(argv[i]);
        firstTime = false;
      }
      if (op == "") {
        std::cerr << "error: format isn\'t correct\n";
        exit(1);
      }
      mp[op](X, argv[i]);
      op = "";
    }
  }
  if (op != "") {
    std::cerr << "error: format isn\'t correct\n";
    exit(1);
  }
  // Вывод результата в терминал
  std::ifstream in(X);
  size_t n, m;
  in >> n >> m;
  std::remove(X);
  std::cout << n << ' ' << m << std::endl;
  double elem;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      in >> elem;
      std::cout << round(elem) << ' ';
    }
    std::cout << std::endl;
  }
}
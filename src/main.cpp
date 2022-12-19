#include "Matrix.h"
#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

// TODO bacit u smece
int main(void) {
  auto v = vector<vector<int>>();
  int x = 2;
  int y = 3;
  for (int i = 0; i < x; i ++ ) {
    for (int j = 0; j < y; ++j) {
      int a;
      scanf("%d", &a);
      if (j == 0)v.push_back(vector<int>());
      v[i].push_back(a);
    }
  }
  auto m = matrix::Matrix(v);

  printf("DONE %d\n", m.countFigures());
  for (int i = 0; i < x; i ++ ) {
    for (int j = 0; j < y; ++j) {
      printf("%d ", v[i][j]);
    }
    printf("\n");
  }
  return 0;
}
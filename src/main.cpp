#include "Matrix.h"
#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;


int main(void) {
  vector<vector<int>> v = {{1,0,1,0,1},
                           {0,1,0,1,0},
                           {1,0,1,0,1},
                           {0,1,0,1,0},
                           {1,0,1,0,1}};

 auto m = matrix::Matrix(v);
printf("Matrix \n");
m.print();
 printf("DONE %d\n", m.countFigures());
m.print();

auto f = matrix::FastMatrix(v);
printf("\n\nFAST Matrix \n");
f.print();
 printf("DONE %d\n", f.countFigures());
f.print();


auto l = matrix::LeanMatrix(v);
printf("\n\nLEAN Matrix \n");
l.print();
 printf("DONE %d\n", l.countFigures());
l.print();

return 0;
}


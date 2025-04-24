#include <stdio.h>
#include <stdlib.h>

int main() {
  char* p1 = malloc(250);
  char* p2 = malloc(120);
  printf("Diff is %ld\n", p2 - p1);
  return 0;
}
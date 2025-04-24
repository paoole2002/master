#include <iostream>
#include <immintrin.h>

#define print(x) std::cout << x << std::endl

int main() {
  double v1[20];
  double v2[20];
  double final[20];
  for (int i = 0; i < 20; i++) {
    v1[i] = i % 4 * 1.;
    v2[i] = 2.;
  }

  __m256d a;
  __m256d b;
  __m256d prod;
  __m256d partial = _mm256_set1_pd(0.0);
  double sum = 0.;
  for (int i = 0; i < 20; i += 4) {
    a = _mm256_loadu_pd(&v1[i]);
    b = _mm256_loadu_pd(&v2[i]);
    prod = _mm256_mul_pd(a, b);
    partial = _mm256_add_pd(partial, prod);
    double c[4];
    _mm256_storeu_pd(c, partial);
    for (int l = 0; l < 4; l++) {
      sum += c[l];
      print(c[l]);
    }
  }
  
  

  print(sum);

  // for (int i = 0; i < 20; i++) {
  //   std::cout << final[i] << ",";
  // }
  // std::cout << std::endl;
}

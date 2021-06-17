#include <bits/stdc++.h>

struct SPF{
private:
  std::vector<int> data;
public:
  SPF(int max_value) : data(max_value + 1, 0) {
    for (int i = 2; i <= max_value; ++i){
      if (data[i] != 0) continue;
      for (int j = i; j <= max_value; j += i)
        data[j] = i;
    }
  }
  bool isPrime(int v){
    return data[v] == v;
  }
  int getSPF(int v){
    return data[v];
  }
  std::vector<int> primeFactor(int v, bool allow_duplicate = true){
    std::vector<int> ret;
    while (v > 1){
      int p = getSPF(v);
      ret.push_back(p);
      v /= p;
      if (!allow_duplicate){
        while (v % p == 0)
          v /= p;
      }
    }
    return ret;
  }
};
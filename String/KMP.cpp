#include <bits/stdc++.h>

struct kmp{
private:
    int n;
    std::string pattern;
    std::vector<int> table;

public:
    kmp() {}
    kmp(std::string& pattern) : pattern(pattern){
        n = int(pattern.length());
        table.resize(n, 0);
        int j = 0;
        for (int i = 1; i < n; ++i){
            if (pattern[i] == pattern[j])
                table[i] = ++j; 
            else {
                if (j != 0){
                    j = table[j - 1];
                    --i;
                }
                else table[i] = 0;
            }
        }
    }

    std::string get_pattern(void){ return pattern; }

    std::vector<int> get_table(void){ return table; }

    int search(std::string& str, int start_idx = 0){
        int i = start_idx, j = 0;
        while (i < int(str.length())){
            if (pattern[j] == str[i]){
                ++i; ++j;
            }
            if (j == n){
                return i - j;
            }
            else if (i < int(str.length()) && pattern[j] != str[i]){
                if (j != 0) j = table[j - 1];
                else ++i;
            }
        }
        return -1;
    }

    std::vector<int> find_all(std::string& str){
        std::vector<int> ret;
        int i = 0, j = 0;
        while (i < int(str.length())){
            if (pattern[j] == str[i]){
                ++i; ++j;
            }
            if (j == n){
                ret.push_back(i - j);
                j = table[j - 1];
            }
            else if (i < int(str.length()) && pattern[j] != str[i]){
                if (j != 0) j = table[j - 1];
                else ++i;
            }
        }
        return ret;
    }
};

/* solution https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B */

int main(void){
    std::string T, P;
    std::cin >> T >> P;
    kmp p(P);
    std::vector<int> table = p.get_table();
    std::vector<int> idx = p.find_all(T);
    for (int i : idx) std::cout << i << std::endl;
    return 0;
}
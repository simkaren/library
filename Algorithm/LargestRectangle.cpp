#include <bits/stdc++.h>

// ヒストグラム中の最大長方形の面積を求める
template<typename T>
long long largest_rectangle(std::vector<T> height){
    std::stack<int> st;
    height.push_back(0);
    std::vector<int> left(height.size());  
    long long ret = 0;
    for(int i = 0; i < (int)height.size(); i++) {
        while(!st.empty() && height[st.top()] >= height[i]) {
            ret = std::max(ret, (long long)(i - left[st.top()] - 1) * height[st.top()]);
            st.pop();
        }
        left[i] = st.empty() ? -1 : st.top();
        st.emplace(i);
    }
    return ret;
}

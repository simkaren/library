#include <bits/stdc++.h>

// m[i]:=min{v[j] | i<=j<i+w}‚È‚ém‚ð•Ô‚·
template<typename T>
std::vector<T> slide_minimum(const std::vector<T>& v, int w){
    std::deque<T> deq;
    std::vector<T> ret;
    for (int i = 0; i < int(v.size()); ++i){
        while (!deq.empty() && v[deq.back()] >= v[i])
            deq.pop_back();
        deq.push_back(i);
        if (i - w + 1 >= 0){
            ret.push_back(v[deq.front()]);
            if (deq.front() == i - w + 1)
                deq.pop_front();
        }
    }
    return ret;
}

// M[i]:=max{v[j] | i<=j<i+w}‚È‚éM‚ð•Ô‚·
template<typename T>
std::vector<T> slide_maximum(const std::vector<T>& v, int w){
    std::deque<T> deq;
    std::vector<T> ret;
    for (int i = 0; i < int(v.size()); ++i){
        while (!deq.empty() && v[deq.back()] <= v[i])
            deq.pop_back();
        deq.push_back(i);
        if (i - w + 1 >= 0){
            ret.push_back(v[deq.front()]);
            if (deq.front() == i - w + 1)
                deq.pop_front();
        }
    }
    return ret;
}
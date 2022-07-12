// Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
#include "Header.h"
#include <algorithm>

int main() {
    /*vector<int> vec;
  
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    
    vec.clear();
    std::cout << vec;*/
    vector<int> vec;
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);

    std::sort(vec.begin(), vec.end(),
        [](const int& a, const int& b) { return a < b; });

    std::cout << vec << std::endl;
    return 0;
}

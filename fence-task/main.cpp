//
//  main.cpp
//  fence-task
//
//  Created by Rom Dr on 25/04/2019.
//  Copyright © 2019 Rom Dr. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

struct IntPair {
    int left;
    int right;
};

IntPair getSizes(string const& input);

int main(int argc, const char * argv[]) {
    // input q and n
    string input_sizes;
    getline(cin, input_sizes);
    IntPair sizes = getSizes(input_sizes);
    int n = sizes.left;
    int q = sizes.right;
    cout << "DEBUG " << n << " " << q << " " << endl;
    
    // input array
    return 0;
}

IntPair getSizes(string const& input) {
    size_t space_pos = input.find(" ");
    int n = stoi(input.substr(0, space_pos));
    int q = stoi(input.substr(space_pos, input.length() - 1));
    return IntPair{n, q};
}

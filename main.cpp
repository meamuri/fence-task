//
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct IntPair {
    int left;
    int right;
};

struct Section {
    int* relatedWithSectionPainters;
    int paintersCount;
};

IntPair inputToPair(string const& input);
int solve(int n, int q, vector<IntPair> const* painters);

int main(int argc, const char * argv[]) {
    // input q and n
    string input;
    getline(cin, input);
    IntPair sizes = inputToPair(input);
    int n = sizes.left;
    int q = sizes.right;

    // input array
    vector<IntPair> painters(q);
    for (int i = 0; i < q; ++i) {
        getline(cin, input);
        IntPair pair = inputToPair(input);
        painters[i] = (pair);
    }

    int res = solve(n, q, &painters);
    cout << res;
    
    painters.clear();
    return 0;
}

int solve(int n, int q, vector<IntPair> const* painters) {
    auto* sections = new Section[n];
    for (int i = 0; i < n; ++i) {
        sections[i].relatedWithSectionPainters = new int[q];
        sections[i].paintersCount = 0;
    }
    
    // Make an array a of n vectors where a_i contains all the painters who paint the i-th panel
    for (int i = 0; i < q; ++i) {
        for (int j = painters->at(i).left - 1; j <= painters->at(i).right - 1; ++j) {
            ++sections[j].paintersCount;
            sections[j].relatedWithSectionPainters[sections[j].paintersCount] = i;
        }
    }

    // Find 'total', the total number of painted panels using all of the painters.
    int total = 0;
    for (int i = 0; i < n; ++i) {
        if (sections[i].paintersCount > 0) {
            ++total;
        }
    }
    
    // make a 2D array 'count' that is initialized to 0. Here,
    // 'count[i][j]' is 'the number of sections that have no one painting them if i and j are removed.
    
    int** count = new int*[q];
    for (int i = 0; i < q; ++i) {
        count[i] = new int[q];
        for (int j = 0; j < q; ++j) {
            count[i][j] = 0;
        }
    }
    
    // So, loop over all elements of a. If a[i].size()==2, then count[a[i][0]][a[i][1]]++ and count[a[i][1]][a[i][0]]++.
    // If a[i].size()==1, then for all j ≠ a[i][0], perform count[a[i][0]][j]++ and count[j][a[i][0]]++.
    for (int i = 0; i < n; ++i) {
        if (sections[i].paintersCount == 2) {
            count[sections[i].relatedWithSectionPainters[0]][sections[i].relatedWithSectionPainters[1]]++;
            count[sections[i].relatedWithSectionPainters[i]][sections[i].relatedWithSectionPainters[0]]++;
        } else if (sections[i].paintersCount == 1) {
            for (int j = 0; j < sections[i].paintersCount; ++j) {
                if (j != sections[i].relatedWithSectionPainters[0]) {
                    count[sections[i].relatedWithSectionPainters[0]][j]++;
                    count[j][sections[i].relatedWithSectionPainters[0]]++;
                }
            }
        }
    }
    
    // Then, simply find the minimum value of count[i][j], and subtract that from total to get your answer
    int min = count[0][1];
    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < q; ++j) {
            if (i != j && count[i][j] < min) {
                min = count[i][j];
            }
        }
    }
    
    int res = total - min;
    
    // free memory
    for (int i = 0; i < q; ++i) {
        delete[] count[i];
    }
    delete[] count;
    
    for (int i = 0; i < n; ++i) {
        delete[] sections[i].relatedWithSectionPainters;
    }
    delete[] sections;
    
    return res;
}

IntPair inputToPair(string const& input) {
    size_t space_pos = input.find(' ');
    int n = stoi(input.substr(0, space_pos));
    int q = stoi(input.substr(space_pos, input.length() - 1));
    return {n, q};
}

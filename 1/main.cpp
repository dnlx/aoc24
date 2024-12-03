#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

void quicksort(std::vector<int>&, int, int);
int partition(std::vector<int>&, int, int);

int main() {
    std::string file_name = "input.txt";

    std::ifstream input_stream(file_name);

    if (!input_stream) {
        std::cerr << "WHATTTTT?`??";
    }

    std::vector<std::string> text;
    std::string line;

    while (std::getline(input_stream, line)) {
        text.push_back(line);
    }


    // Do actual splitting here
    // Assume strings are delimted by "   " and end with the number and nothing afterwards
    std::vector<int> left;
    std::vector<int> right;

    for (int i=0; i<text.size(); i++) {
        int start_del = text[i].find("   ");
        int str_len = text[i].size();
        left.push_back(std::stoi(text[i].substr(0, start_del)));
        right.push_back(std::stoi(text[i].substr(start_del+3, str_len)));
    }
    quicksort(left, 0, left.size());
    quicksort(right, 0, right.size());

    // for (int i=0; i<left.size(); i++) {
    //    std::cout << left[i] << std::endl;
    // }

    if (left.size() != right.size()) {
        std::cerr << "OH NO!!" << std::endl;
    }

    // Solution to ex 1
    int distance = 0;

    for (int i=0; i<left.size(); i++) {
        distance = distance + abs(left[i] - right[i]);
    }
    std::cout << "The distance is: " << distance << std::endl;


    // Now we need to count and do weird multiplication..
    // Calculate: left[i] * #occurences in right
    // Since we ordered already, we can use the ordered list.


    int similarity = 0;

    typedef std::map<int, unsigned int> CounterMap;
    CounterMap counts;
    for (int i=0; i<right.size(); i++) {
        CounterMap::iterator it(counts.find(right[i]));
        if (it != counts.end()) {
            it->second++;
        } else {
            counts[right[i]] = 1;
        }

    }

    for (int i=0; i<left.size(); i++) {
        CounterMap::iterator it(counts.find(left[i]));
        if (it != counts.end()) {
            similarity = similarity +  (left[i] * counts[left[i]]);
        }
    }

    std::cout << "The similarity is: " << similarity << std::endl;


}

void quicksort(std::vector<int>& A, int p, int q) {
    int r;
    if (p<q) {
        r = partition(A, p, q);
        quicksort(A, p,r);
        quicksort(A, r+1, q);
    }
}

int partition(std::vector<int>& A, int p, int q) {
    int x = A[p];
    int i = p;
    int j;

    for (j=p+1; j<q; j++) {
        if (A[j] <= x) {
            i = i+1;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i], A[p]);
    return i;
}







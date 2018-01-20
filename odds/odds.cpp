#include <iostream>
#include <vector>

using namespace std;

vector < int > oddNumbers(int l, int r) {

    int next;
    int count;
    
    // Get the first number to return in the array
    if (l % 2 == 1) {
        next = l;
    }
    else {
        next = l + 1;
    }

    // Get the count of numbers to return in the array
    count = (r - l + 1) / 2;
    
    if ((r - l + 1) % 2 == 1) {
        if (l % 2 == 1) {
            count++;
        }
    }
    
    vector<int> result(count);
    for (int i = 0; i < count; i++) {
        result[i] = next;
        next += 2;
    }

    return result;
}

// Given 2 numbers denoting a range of integers (left and right, both
// inclusive), prints all the odd numbers in that range
int main() {
	int left;
	int right;

	cin >> left;
	cin >> right;

	vector<int> result = oddNumbers(left, right);

	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	return 0;
}

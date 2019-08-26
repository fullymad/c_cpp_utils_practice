/******************************************************************************
https://www.hackerrank.com/challenges/candies/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dynamic-programming
******************************************************************************/
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

// Complete the candies function below.
long candies(int n, vector<int> arr) {
	long		totalCandies = 0;
	int			curCandies = 0;

	for (int i = 0; i < n; i++) {
		//Higher rank
		if (i == 0 || arr[i] > arr[i - 1]) {
			curCandies += 1;
			totalCandies += curCandies;
		}
		// Same rank
		else if (arr[i] == arr[i -1]) {
			curCandies = 1;
			totalCandies += curCandies;
		}
		// Lower rank
		else {
			// Save candies given to previous (higher ranked) child
			int prevCandies = curCandies;

			// Get sequence of children with decreasing ranks
			// Example: Current 7, Next: 6, 5, 6 (so 2 more children found)
			int lowerChildren = 0;
			for (int j = i + 1; j < n; j++) {
				if (arr[j] < arr[j - 1]) {
					lowerChildren++;
				}
				else {
					break;
				}
			}

			// Lowest ranked will get 1, increase by 1 for others
			// Example sequence 7, 5, 2 will get 3 + 2 + 1 candies in all
			// Use 'long' since result of multiplication will be long
			long totalChildren = lowerChildren + 1;
			totalCandies += ( (totalChildren * (totalChildren + 1)) / 2 );

			// Previous (higher ranked) child should have at least 1 more
			// than current
			if (prevCandies <= totalChildren) {
				totalCandies += (totalChildren - prevCandies + 1);
			}

			curCandies = 1; // Last of lower ranked children will get 1
			i += lowerChildren; // Skip the pre-processed children
		}
	}

	return totalCandies;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item;
        cin >> arr_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        arr[i] = arr_item;
    }

    long result = candies(n, arr);

    fout << result << "\n";

    fout.close();

    return 0;
}

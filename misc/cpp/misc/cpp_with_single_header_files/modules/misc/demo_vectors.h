#include <iostream>
#include <vector>
#include <string>
 
// namespace misc {

int demo_vectors()
{
    using namespace std;

    printf(
        "\nVECTOR DEMO\n"
        "--------------------------\n"
    );


	vector<int> ix = {1, 2, 4, 8, 16};
	vector<string> fruits = {"orange", "apple", "raspberry", "omw"};
	vector<char> empty;
 
    ix.push_back(25);
    ix.push_back(13);
 
    // Iterate and print values of vector
    cout << "[ ";
    for(int i : ix) {
        cout << i << " " ;
    }
    cout << "]\n";

    cout << "[ ";
    for(auto f : fruits) {
        cout << "{" << f << "} ";
    }
    cout << "]\n";

    return 0;
}

// }
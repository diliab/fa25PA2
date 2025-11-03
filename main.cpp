//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;


// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);


int main() {

    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;

}



// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {

    // TODO:
    // 1. Create a MinHeap object.
    MinHeap heap;
    // 2. Push all leaf node indices into the heap
    for (int i = 0; i < nextFree; i++) {
        heap.push(i, weightArr);
    }

    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)
    while (heap.size > 1) {
        int left = heap.pop(weightArr);
        int right = heap.pop(weightArr);

        int parent = nextFree++;
        charArr[parent] = '#';

        weightArr[parent] = weightArr[left] + weightArr[right];

        leftArr[parent] = left;
        rightArr[parent] = right;
        //new subtree back into loop
        heap.push(parent, weightArr);
    }
    return heap.pop(weightArr);


}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.

    //using the stack<pair<int std library to simulate DFS traversal
    stack< pair <int, string>> str;
    str.push({root, ""});

    //while string is not empty (aka the dummy root string is there)
    while (!str.empty()) {
        auto [v, path] = str.top();
        str.pop();

        //checking to see if v is a leaf
        bool isleaf = leftArr[v] == -1 && rightArr[v] == -1;
        if (isleaf) {
            //charting the path
            int index = charArr[v] - 'a';

            //single node only, check if path is empty
            codes[index] = path.empty() ? "0" : path;
        }
        else {
            if (rightArr[v] != -1) {
                str.push({rightArr[v], path + "1"});
            }
            if (leftArr[v] != -1) {
                str.push({leftArr[v], path + "0"});
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }
        cout << "\nEncoded message:\n";

        ifstream file(filename);
        char ch;
        while (file.get(ch)) {
            if (ch >= 'A' && ch <= 'Z')
                ch = ch - 'A' + 'a';
            if (ch >= 'a' && ch <= 'z')
                cout << codes[ch - 'a'];
        }
        cout << "\n";
        file.close();
    }


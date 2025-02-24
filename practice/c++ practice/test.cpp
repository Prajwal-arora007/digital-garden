#include <iostream>
#include <iomanip> // For output formatting with int128_t
using namespace std;

// Helper function to print int128_t numbers
void printInt128(int128_t num) {
    if (num == 0) {
        cout << "0";
        return;
    }
    string result;
    while (num > 0) {
        result.push_back('0' + num % 10);
        num /= 10;
    }
    reverse(result.begin(), result.end());
    cout << result;
}

int main() {
    const int limit = 1000000; // Number of Fibonacci numbers to generate

    // Initialize the first two Fibonacci numbers
    int128_t a = 0;
    int128_t b = 1;

    cout << "Fibonacci sequence up to " << limit << " numbers:" << endl;

    // Print the first Fibonacci number
    cout << "1: ";
    printInt128(a);
    cout << endl;

    // Generate and print the Fibonacci sequence
    for (int i = 2; i <= limit; ++i) {
        cout << i << ": ";
        printInt128(b);
        cout << endl;

        // Calculate the next Fibonacci number
        int128_t temp = a + b;
        a = b;
        b = temp;
    }

    return 0;
}
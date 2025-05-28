#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include <thread>
#include <cctype>

using namespace std;

// ------------------------ Math & Number Functions ------------------------

// 1. Compute the factorial recursively.
long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// 2. Compute the nth Fibonacci number recursively.
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 3. Compute power (base^exponent) recursively.
long calcPower(int base, int exponent) {
    if (exponent == 0) return 1;
    return base * calcPower(base, exponent - 1);
}

// 4. Check if a number is prime.
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

// 5. Compute gcd using Euclid’s algorithm.
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// 6. Compute lcm using gcd.
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

// 7. Sum the digits of a number.
int sumOfDigits(int n) {
    n = abs(n);
    int sum = 0;
    while(n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

// ------------------------ Vector & Sorting Functions ------------------------

// 8. Compute the sum of a vector of doubles.
double computeSum(const vector<double>& v) {
    return accumulate(v.begin(), v.end(), 0.0);
}

// 9. Bubble sort implementation.
void bubbleSort(vector<int>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = 0; j < v.size() - 1; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

// 10. Merge two sorted subvectors.
void merge(vector<int>& v, int left, int mid, int right) {
    vector<int> temp;
    int i = left, j = mid + 1;
    while(i <= mid && j <= right) {
        if (v[i] < v[j])
            temp.push_back(v[i++]);
        else
            temp.push_back(v[j++]);
    }
    while(i <= mid) {
        temp.push_back(v[i++]);
    }
    while(j <= right) {
        temp.push_back(v[j++]);
    }
    for (int k = left; k <= right; k++) {
        v[k] = temp[k - left];
    }
}

// 11. Recursive merge sort.
void mergeSortRec(vector<int>& v, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortRec(v, left, mid);
    mergeSortRec(v, mid + 1, right);
    merge(v, left, mid, right);
}

void mergeSort(vector<int>& v) {
    mergeSortRec(v, 0, v.size() - 1);
}

// 12. Reverse a vector.
void reverseVector(vector<int>& v) {
    reverse(v.begin(), v.end());
}

// 13. Count the number of primes in an integer vector.
int countPrimes(const vector<int>& v) {
    int count = 0;
    for (int num : v) {
        if (isPrime(num))
            count++;
    }
    return count;
}

// 14. Compute the average of vector<int>.
double computeAverage(const vector<int>& v) {
    if (v.empty()) return 0.0;
    return static_cast<double>(accumulate(v.begin(), v.end(), 0)) / v.size();
}

// 15. Generate a vector of random numbers.
vector<int> generateRandomNumbers(size_t count, int minVal, int maxVal) {
    vector<int> numbers;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(minVal, maxVal);
    for (size_t i = 0; i < count; i++) {
        numbers.push_back(dist(gen));
    }
    return numbers;
}

// ------------------------ String Functions ------------------------

// 16. Convert a string to uppercase.
string toUpperCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// 17. Reverse a string.
string reverseString(const string& s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    return rev;
}

// ------------------------ Simulated Workload / Utility Functions ------------------------

// 18. Simulate a workload by performing several computations.
void simulateWorkload(int iterations) {
    for (int i = 0; i < iterations; i++) {
        // Calling math functions
        volatile long long f = factorial(10);        // factorial of 10
        volatile int fib = fibonacci(15);              // 15th Fibonacci
        volatile long power = calcPower(2, 8);           // 2^8
        volatile bool prime = isPrime(29);
        volatile int div = gcd(48, 18);
        volatile int mult = lcm(12, 15);
        volatile int digitsSum = sumOfDigits(12345);

        // Working with vectors and sorting
        vector<int> vec = generateRandomNumbers(100, 1, 1000);
        bubbleSort(vec);
        mergeSort(vec);
        reverseVector(vec);
        volatile int primeCount = countPrimes(vec);
        volatile double avg = computeAverage(vec);

        // String manipulations
        string sample = "Embedded BPF Profiling";
        string upperStr = toUpperCase(sample);
        string revStr = reverseString(sample);

        // Sum of doubles from a vector
        vector<double> dVec(vec.begin(), vec.end());
        volatile double dSum = computeSum(dVec);

        // Sleep for a short amount of time to simulate delay.
        this_thread::sleep_for(chrono::milliseconds(5));
    }
}

// 19. A chain-call utility that calls other functions.
void chainFunctionLevel3(int n) {
    volatile int r = fibonacci(n % 10 + 5); // small computation
    volatile long fact = factorial(n % 10);
}

void chainFunctionLevel2(int n) {
    chainFunctionLevel3(n);
    volatile long powVal = calcPower(2, n % 10);
}

void chainFunctionLevel1(int n) {
    chainFunctionLevel2(n);
    volatile bool prime = isPrime(n);
}

// 20. A dummy function to add extra depth (recursive chain).
void extraDepthFunction(int n) {
    if (n <= 0) return;
    chainFunctionLevel1(n);
    extraDepthFunction(n - 1);
}

// ------------------------ Extra Deep Call Chain Functions ------------------------
// Forward declarations for the deep chain functions.
void deepChain1(int level);
void deepChain2(int level);
void deepChain3(int level);
void deepChain4(int level);
void deepChain5(int level);
void deepChain6(int level);
void deepChain7(int level);
void deepChain8(int level);
void deepChain9(int level);
void deepChain10(int level);

void deepChain1(int level) {
    if (level <= 0) return;
    volatile int v = factorial(level % 5 + 3);
    deepChain2(level - 1);
}

void deepChain2(int level) {
    if (level <= 0) return;
    volatile int v = fibonacci(level % 7 + 3);
    deepChain3(level - 1);
}

void deepChain3(int level) {
    if (level <= 0) return;
    volatile long v = calcPower(2, level % 5 + 2);
    deepChain4(level - 1);
}

void deepChain4(int level) {
    if (level <= 0) return;
    volatile bool flag = isPrime(level);
    deepChain5(level - 1);
}

void deepChain5(int level) {
    if (level <= 0) return;
    volatile int v = gcd(level * 3, level + 7);
    deepChain6(level - 1);
}

void deepChain6(int level) {
    if (level <= 0) return;
    volatile int v = lcm(level + 2, level % 3 + 4);
    deepChain7(level - 1);
}

void deepChain7(int level) {
    if (level <= 0) return;
    volatile int v = sumOfDigits(level * 1234);
    deepChain8(level - 1);
}

void deepChain8(int level) {
    if (level <= 0) return;
    vector<int> vec = generateRandomNumbers(20, 1, 100);
    bubbleSort(vec);
    deepChain9(level - 1);
}

void deepChain9(int level) {
    if (level <= 0) return;
    string s = "DeepChainCall";
    string rev = reverseString(s);
    deepChain10(level - 1);
}

void deepChain10(int level) {
    if (level <= 0) return;
    volatile double d = computeSum(vector<double>{1.1, 2.2, 3.3});
    deepChain1(level - 1);
}

// ------------------------ Main Function ------------------------

int main() {
    cout << "Starting eBPF Profiling Symbolization Test Application" << endl;

    // Initial individual function computation tests (optional).
    cout << "Initial tests:" << endl;
    cout << "  Factorial(10): " << factorial(10) << endl;
    cout << "  Fibonacci(15): " << fibonacci(15) << endl;
    cout << "  2^8: " << calcPower(2, 8) << endl;
    cout << "  Is 97 prime? " << (isPrime(97) ? "Yes" : "No") << endl;
    cout << "  GCD(48, 18): " << gcd(48, 18) << endl;
    cout << "  LCM(12, 15): " << lcm(12, 15) << endl;
    cout << "  Sum of digits of 123456: " << sumOfDigits(123456) << endl;
    cout << "Running infinite loop workload. Use CTRL+C to exit." << endl;

    // Infinite loop to continuously simulate workload.
    while (true) {
        simulateWorkload(50);
        extraDepthFunction(5);
        // Call the deep chain to create even longer stack traces.
        deepChain1(10);
    }

    return 0;
}

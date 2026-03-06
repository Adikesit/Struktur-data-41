#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n) {
    if(n <= 1) return false;
    for(int i = 2; i < n; i++) {
        if(n % i == 0) return false;
    }

    return true;
}

void findPrimes(int kiri, int kanan) {
    bool found = false;
    for(int i = kiri; i <= kanan; i++) {
        if(isPrime(i)) {
            cout << i << " ";
            found = true;
        }
    }

    if(!found) cout << "tidak ada bilangan prima di antara" << kiri << " dan" << kanan;
}

int main() {
    int kiri, kanan;
    cin >> kiri >> kanan;

    findPrimes(kiri, kanan);

    return 0;
}


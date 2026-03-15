#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  int number[n];
  int total = 0;
  float rata2;
  for (int i = 0; i < n; i++) {
    cout << "Angka " << i + 1 << ": ";
    cin >> number[i];
    total += number[i];
  }

  rata2 = total / (float)n;

  cout << "Data yang dimasukkan: " << endl;
  for (int i = 0; i < n; i++) {
    cout << number[i];
    if (i != n - 1)
      cout << ", ";
  }
  cout << "\n";

  cout << "Jumlah semua angka: " << total << "\n";
  cout << "Rata-rata: " << rata2 << "\n";
}

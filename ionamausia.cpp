#include <bits/stdc++.h>
using namespace std;

int main(){
	cout << "Masukan Nama anda: ";
	string nama;
	cin >> nama;
	
	cout <<"Masukan tahun lahir anda: ";
	int tahun_lahir, usia;
	cin >> tahun_lahir;
	usia = 2026 - tahun_lahir;
	
	cout << "Halo " << nama << " Usia mu adalah " << usia << " Tahun";
}

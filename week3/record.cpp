#include <bits/stdc++.h>
using namespace std;

struct mahasiswa {
	string nama, nim, prodi;
	float ipk;
};

int main(){
	mahasiswa mah1;
	mah1.nim = "5025251041";
	mah1.nama = "Muhammad Adinata Parikesit";
	mah1.prodi = "Teknik Informatika";
	mah1.ipk = 4.00;
	
	cout << "Nama : " << mah1.nama << endl;
	cout << "NRP : " << mah1.nim << endl;
	cout << "Prodi : " << mah1.prodi << endl;
	cout << "IPK : " << mah1.ipk << endl;
}

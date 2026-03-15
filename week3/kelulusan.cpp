#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cout << "Masukan jumlah Mahasiswa : ";
	cin >> n;
	
	int arr[n];
	
	for(int i = 0; i < n; i++){
		cout << "Masukan Nilai Mahasiswa ke-" << i+1 << " : ";
		cin >> arr[i];
	}
	
	cout << "\nStatus Kelulusan\n";
	
	for(int i = 0; i < n; i++){
		if(arr[i] > 75){
			cout << "Mahasiswa " << i+1 << " : Lulus" << endl;
		}else{
			cout << "Mahasiswa " << i+1 << " : Tidak Lulus " << endl; 
		}
	}
}

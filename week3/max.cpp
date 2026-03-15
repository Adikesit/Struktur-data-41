#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cout << "Jumlah angka : " ;
	cin >> n;
	int arr[n];
	
	cout << "Masukan nilai : ";
	
	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}
	
	int max = arr[0];
	
	for(int i = 1; i < n; i ++){
		if(arr[i] > max){
			max = arr[i];
		}
	}
	
	cout << "Max : " <<max;
}

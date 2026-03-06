#include <bits/stdc++.h>s
using namespace std;

int getmin(int arr[], int n){
	int nilai = arr[0];
	
	for(int i = 0; i < n; i++){
		if(arr[i] < nilai){
			nilai = arr[i];
		}
	}
	return nilai;
}
int getmax(int arr[], int n){
	int nilai = arr[0];
	
	for(int i = 0; i < n; i++){
		if(arr[i] > nilai){
			nilai = arr[i];
		}
	}
	return nilai;
}

int main(){
	int n;
	cin >> n;
	
	int arr[n];
	
	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}
	
	int xmin = getmin(arr, n);
	int xmax = getmax(arr, n);
	
	cout << "Nilai terkecil adalah: " << xmin << endl;
	cout << "Nilai terbesar adalah: " << xmax;
}

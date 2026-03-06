#include <bits/stdc++.h>
using namespace std;

void isvokal(char x){
	char a = tolower(x);
	if(a == 'a' || a == 'i' || a == 'u' || a == 'e' || a == 'o'){
		cout << x << " Adalah Huruf Vokal";
	}else{
		cout << x << " Adalah Huruf Konsonan";
	}
}

int main(){
	char huruf;
	cin >> huruf;
	
	isvokal(huruf);
}

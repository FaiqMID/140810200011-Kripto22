/*
  Nama              : Faiq Muhammad
  NPM               : 140810200011
  Kelas             : B
  Deskripsi program : Enkripsi dan dekripsi menggunakan Shift Cipher
*/

#include <iostream>
#include <string>
using namespace std;

string enkripsi(string plain_text, int key){
	string cipher_text = "";	
	for(int i = 0; i < plain_text.size(); i++){
		if(plain_text[i] != ' '){
			if(isupper(plain_text[i])){
				cipher_text += char(int(plain_text[i] + key - 65) % 26 + 65); //65 = A-Z
			} else {
				cipher_text += char(int(plain_text[i] + key - 97) % 26 + 97); //97 = a-z
			}
		} else{
			cipher_text += plain_text[i];
		}
		
	}
	return cipher_text;
}

string dekripsi(string cipher_text, int key){
	string plain_text="";	
	for(int i = 0; i < cipher_text.size(); i++){
		if(cipher_text[i] != ' '){
			if(isupper(cipher_text[i])){
				plain_text += char((int(cipher_text[i] - key - 65) % 26 + 26) % 26 + 65);
			} else {
				plain_text+=  char((int(cipher_text[i] - key - 97) % 26 + 26) % 26 + 97);
			}
		} else{
			plain_text += cipher_text[i];
		}
	}
	return plain_text;
}

int main(){
	string plain_text;
  	int key;

	cout << "Masukkan plain text: ";
	getline(cin, plain_text);

	cout << "Masukkan key: ";
	cin >> key;
  
	string cipher_text = enkripsi(plain_text, key);
	
	cout << "\nEnkripsi: \n";
	cout << "Cipher text : " << cipher_text << endl;
	
	cout << "\nDekripsi:\n";
	cout << "Plain Text : "<< dekripsi(cipher_text, key) << endl;
}
/*
  Nama              : Faiq Muhammad
  NPM               : 14081020011
  Kelas             : B
  Deskripsi Program : Enkripsi dan dekripsi menggunakan Viginere Cipher
*/

#include <iostream>
#include <string>

using namespace std;

class Viginere {
  public:
    string key;

    void setKey(string key){
      for (int i = 0; i < key.size(); ++i) {
        if (key[i] >= 'A' && key[i] <= 'Z'){
          this->key += key[i];
        } else if (key[i] >= 'a' && key[i] <= 'z'){
          this->key += key[i] + 'A' - 'a';
        }
      }
    }

    string enkripsi(string t) {
      string cipher;
      for (int i = 0, j = 0; i < t.length(); ++i) {
        char ch = t[i];
        if (ch >= 'a' && ch <= 'z'){
          ch += 'A' - 'a';
        } else if (ch < 'A' || ch > 'Z'){
          continue;
        }
        cipher += (ch + key[j] - 2 * 'A') % 26 + 'A';
        j = (j + 1) % key.length();
      }
      return cipher;
    }
    string dekripsi(string t) {
      string plain;
      for (int i = 0, j = 0; i < t.length(); ++i) {
        char ch = t[i];
        if (ch >= 'a' && ch <= 'z'){
          ch += 'A' - 'a';
        } else if (ch < 'A' || ch > 'Z'){
          continue;
        }
        plain += (ch - key[j] + 26) % 26 + 'A';
        j = (j + 1) % key.length();
      }
      return plain;
    }
};

int main() {
  string key = "", msg = "";
  Viginere cipher;
  
  cout << "Masukkan pesan = "; cin >> msg;
  cout << "Masukkan key = "; cin >> key;
  cipher.setKey(key);

  string ciphertext = cipher.enkripsi(msg);
  cout << "\nEnkripsi: " << ciphertext << endl;
  
  string plaintext = cipher.dekripsi(ciphertext);
  cout << "Dekripsi: " << plaintext << endl;
  
}
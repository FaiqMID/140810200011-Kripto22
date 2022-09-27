#include <iostream>
#include <string>

using namespace std;
 
int key[3][3];
 
int mod26(int x){
  return x >= 0 ? (x%26) : 26-(abs(x)%26); 
}
 
int determinant(int m[3][3], int n){
  int det;
  if (n == 2){
    det = m[0][0] * m[1][1] - m[0][1]*m[1][0];
  } else det = 0;

  return mod26(det);
}
 
int invDet(int R, int D = 26){
  int i = 0;
  int p[100] = {0,1};
  int q[100] = {0};
 
  while (R != 0){
    q[i] = D/R;
    int oldD = D;
    D = R;
    R = oldD % R;
    if(i > 1){
      p[i] = mod26(p[i-2] - p[i-1]*q[i-2]);
    }
    i++;
  }
  if (i == 1) return 1;
  else return p[i] = mod26(p[i-2] - p[i-1]*q[i-2]);
}

int gcd(int m, int n){
  if (n > m)
    swap(m,n);
    
  do {
    int temp = m % n;
    m = n;
    n = temp;
  } while (n != 0);
    
  return m;
}
 
void perkalianMatrix(int a[1000][3], int a_rows, int a_cols, int b[1000][3], int b_rows, int b_cols, int res[1000][3]){
  for (int i = 0; i < a_rows; i++){
    for (int j = 0; j < b_cols; j++){
      for (int k = 0; k < b_rows; k++){
        res[i][j] += a[i][k]*b[k][j];
      }
      res[i][j] = mod26(res[i][j]);
    }
  }
}

void findInverse(int m[3][3], int n, int m_inverse[3][3]){
  int adj[3][3] = {0};
  int detInv = invDet(determinant(m, n));
 
  if (n == 2){
    adj[0][0] = m[1][1];
    adj[1][1] = m[0][0];
    adj[0][1] = -m[0][1];
    adj[1][0] = -m[1][0];
  }
 
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      m_inverse[i][j] = mod26(adj[i][j] * detInv);
    }
  }
}
 
string enkripsi(string pt, int n){
  int plain[1000][3] = {0};
  int cipher[1000][3] = {0};
  int ptIter = 0;
 
  while (pt.length()%n != 0){
    pt += "x";
  }
  int row = (pt.length()) / n;
 
  for (int i = 0; i < row; i++){
    for (int j = 0; j < n; j++){
      plain[i][j] = pt[ptIter++]-'a';
    }
  }
  perkalianMatrix(plain, row, n, key, n, n, cipher);
 
  string ct = "";
  for (int i = 0; i < row; i++){
    for (int j = 0; j < n; j++){
      ct += (cipher[i][j] + 'a');
    }
  }
  return ct;
}

string dekripsi(string ct, int n){
  int plain[1000][3] = {0};
  int cipher[1000][3] = {0};
  int ctIter = 0;
 
  int row = ct.length() / n;
 
  for (int i = 0; i < row; i++){
    for (int j = 0; j < n; j++){
      cipher[i][j] = ct[ctIter++]-'a';
    }
  }
 
  int k_inverse[3][3] = {0};
  findInverse(key, n, k_inverse);
  perkalianMatrix(cipher, row, n, k_inverse, n, n, plain);
 
  string pt = "";
  for (int i = 0; i < row; i++){
    for (int j = 0; j < n; j++){
      pt += (plain[i][j] + 'a');
    }
  }
  return pt;
}

void searchKey(string plaintext, string ciphertext){
  string plainteks,cipherteks;
  int key[2][2], det, detInv, adj[2][2], plainteksInv[2][2], plainMatrix[2][2], cipMatrix[2][2], counter = 0;
  int p,c;
  int transpose[2][2];
    
  //matriks plaintext
  counter = 0;
  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 2; j++){
      p = toupper(plainteks[counter]) - 65;
      plainMatrix[i][j] = p;
      counter++;
    }
  }

  counter = 0;

  //matriks ciphertext
  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 2; j++){
      c = toupper(cipherteks[counter]) - 65;
      cipMatrix[i][j] = c;
      counter++;
    }
  }
    
    // determinant
  det = (plainMatrix[0][0] * plainMatrix[1][1]) - (plainMatrix[0][1] * plainMatrix[1][0]);
  if (gcd(det,26) == 1){
    detInv = invDet(det, 26);
    adj[0][0] = plainMatrix[1][1];
    adj[0][1] = (-1)*plainMatrix[0][1];
    adj[1][0] = (-1)*plainMatrix[1][0];
    adj[1][1] = plainMatrix[0][0];
      
    for (int i = 0; i < 2; i++){
      for (int j = 0; j < 2; j++){
        plainteksInv[i][j] = detInv * adj[i][j];
        if (plainteksInv[i][j] < 0){
          plainteksInv[i][j] = 26 - (abs(plainteksInv[i][j])%26); 
        } else {
          plainteksInv[i][j] = plainteksInv[i][j];
          plainteksInv[i][j] = plainteksInv[i][j] % 26;
        }
      } 
    }
        
    //Search key
    for (int i = 0; i < 2; i++){
      for (int j = 0; j < 2; j++){
        key [i][j] = 0;
          for (int k = 0; k < 2; k++){
            key[i][j] += (plainteksInv[i][k] * cipMatrix[k][j]);
          }
          key[i][j] %= 26;
      }
    }
        
 
    for (int i = 0; i < 2; i++){
      for (int j = 0; j < 2; j++){
        transpose[j][i] = key[i][j];
      }
    }
    
    for (int i = 0; i < 2; i++){
      for (int j = 0; j < 2; j++){
        cout << (transpose[i][j]) << "\t";
      }
      cout << endl;
    }       
  } else {
    cout << "Kunci tidak ditemukan\n\n";
  }
}

int main(){
  int n;
  string plain_text;
  cout << "Masukkan plaintext: " ;
  cin >> plain_text;
                    
  cout << "Masukkan ordo matriks: ";
  cin >> n;
 
  for (int i = 0; i < n; i++){
    cout << "Baris " << i+1 << endl;
    for(int j = 0; j < n; j++){
      cout << "col "<< j+1 << ": "; cin >> key[i][j];
    }
  }
 
  string cipher_text = enkripsi(plain_text, n);

  cout << "\nEnkripsi: \n";
  cout << "Cipher text : " << cipher_text << endl;

  cout << "\nDekripsi: \n";
  cout << "Plain Text : "<< dekripsi(cipher_text, n) << endl;

  cout << "\nPencarian kunci: \n";
  cout << "Plain Text : "; searchKey(plain_text, cipher_text);
  
  return 0;
}
#include <iostream>
#include <vector>
using namespace std;

void generateWalshMatrix(vector<vector<int>>& matrix, int size, int top, int left, bool invert) {
    if (size == 1) {
        matrix[top][left] = invert ? -1 : 1;
        return;
    }
    int halfSize = size / 2;
    generateWalshMatrix(matrix, halfSize, top, left, invert);
    generateWalshMatrix(matrix, halfSize, top, left + halfSize, invert);
    generateWalshMatrix(matrix, halfSize, top + halfSize, left, invert);
    generateWalshMatrix(matrix, halfSize, top + halfSize, left + halfSize, !invert);
}
void printWalshMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    generateWalshMatrix(matrix, n, 0, 0, false);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << (matrix[i][j] == 1 ? " 1 " : "-1 ") << " ";
        }
        cout << endl;
    }
}
void removeRow(vector<vector<int>>& matrix, int rowIndex) {
    if (rowIndex >= 0 && rowIndex < matrix.size()) {
        matrix.erase(matrix.begin() + rowIndex);  
    }
    else {
        cout << "Индекс строки выходит за пределы матрицы." << endl;
    }
}
char bitsToChar(const vector<int>& bits) {
    int asciiValue = 0;

    for (int i = 0; i < bits.size(); ++i) {
        
        asciiValue += bits[i] * pow(2, 7 - i);
    }

    return static_cast<char>(asciiValue);
}
void  CDMA_alg(int n) {
   
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    vector<int> code(n);
    vector<vector<int>> Codes(4);  

    // Генерация матрицы Уолша
    generateWalshMatrix(matrix, n, 0, 0, false);

    int remainingRows = n;  
    int start = 0;

    for (int k = 0; k < 4; k++) {
        
        int x = rand() % remainingRows;

        Codes[k] = matrix[x];

        removeRow(matrix, x);
        remainingRows--;  
    }
   /*
   cout << "Секретные коды станций А B C D: " << endl;
    for (const auto& code : Codes) {
        for (int val : code) {
            cout << (val == 1 ? " 1 " : "-1 ") << " ";
        }
        cout << endl;
    }*/
    cout << "Выберите приемник для прослушивания станции:" << endl;
    cout << "1 - приемник станции А" << endl;
    cout << "2 - приемник станции B" << endl;
    cout << "3 - приемник станции C" << endl;
    cout << "4 - приемник станции D" << endl;
    int P;
    cin >> P;
    switch (P)
    {
    case 1:
        cout << "Секретное сообщение от станции А = ";
        
        for (int val : Codes[0]) {
            cout << (val == 1 ? " 1 " : "-1 ") << " ";
        }
        cout << endl;
        break;
    case 2:
        cout << "Секретное сообщение от станции B = ";
        
        for (int val : Codes[1]) {
            cout << (val == 1 ? " 1 " : "-1 ") << " ";
        }
        cout << endl;
        break;
    case 3:
        cout << "Секретное сообщение от станции C = ";
    
        for (int val : Codes[2]) {
            cout << (val == 1 ? " 1 " : "-1 ") << " ";
        }
        cout << endl;
        break;
    case 4:
        cout << "Секретное сообщение от станции D = ";
        for (int val : Codes[3]) {
            cout << (val == 1 ? " 1 " : "-1 ") << " ";
        }
        cout << endl;
        break;
    }
    string wordA = "01000111 01001111 01000100 ";
    string wordB = "01000011 01000001 01010100 ";
    string wordC = "01001000 01000001 01001101 ";
    string wordD = "01010011 01010101 01001110 ";
    vector<char> message(4);
    vector<int> Signal(8);
    vector<vector<int>> tempCodes(4);
    int sum=0;
    int bit=0;
    vector<int> bits(8);
    vector<char>resultWord(3);
    int b = 0;
    for (int i = 0; i < wordA.length(); i++) { 
        message[0] = wordA.at(i);
        message[1] = wordB.at(i);
        message[2] = wordC.at(i);
        message[3] = wordD.at(i);
        tempCodes = Codes;
        for (int j = 0; j < 4; j++) {
            if (message[j] == '0') {
                for (int h = 0; h < 8; h++) {
                    tempCodes[j][h] *= -1;
                }
            }
            if (message[j] == ' ') {
                for (int h = 0; h < 8; h++) {
                    tempCodes[j][h] = 0;
                }
            }
        }
        /*cout << "tempCodes " << endl;
        for (const auto& code : tempCodes) {
            for (int val : code) {
                cout << (val == 1 ? " 1 " : "-1 ") << " ";
            }
            cout << endl;
        }*/
        
        for (int j = 0; j < 8; j++) {
            for (int h = 0; h < 4; h++) {
                sum += tempCodes[h][j];
                
            }
            Signal[j] = sum;
            sum = 0;
            
        }
           
        cout << "Получен сигнал: ";
        for (int m = 0; m < 8; m++) {
            cout << Signal[m]<<" ";
        }
        cout << endl;
        
        for (int j = 0; j < 8; j++) {
            bit += Signal[j] * Codes[P-1][j];
            
        }
        cout << "Расшифровка сигнала, получение двоичного символа буквы: " << bit / 8 << endl;
        if (bit/8 == -1) {
            
            bits[b] = 0;
            
            b++;
        }
        else {
            if (bit/8 == 1) {
                bits[b] = bit / 8;
                b++;
            }
            else {
                cout << "" << endl;
                cout << "Получена буква: "<< bitsToChar(bits) << endl;
                cout << "" << endl;
                
                resultWord.push_back(bitsToChar(bits));
                
                b = 0;
            }
        }
        bit = 0;
    }
    cout << "Полученное слово: ";
    for (char letter : resultWord) {
        cout << letter;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "");
    srand(static_cast<unsigned>(time(0)));
    int n;
    cout << "Введите размер матрицы Уолша (степень двойки): ";
    cin >> n;
    if ((n & (n - 1)) != 0) {
        cout << "Ошибка: n должно быть степенью двойки." << endl;
        return 1;
    }
    printWalshMatrix(n);
    CDMA_alg(n);
    return 0;
}
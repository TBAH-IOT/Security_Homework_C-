#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class RC4_Custom {
private:
    vector<int> S;
    int i, j;
    int N; // Độ dài vector trạng thái (trong bài này là 10)

public:
    // Khởi tạo thuật toán với Vector S và Khóa K tùy chỉnh
    RC4_Custom(vector<int> initial_S, vector<int> key) {
        S = initial_S;
        N = S.size();
        i = j = 0;

        // Giai đoạn KSA (Key Scheduling Algorithm)
        int j_ksa = 0;
        for (int i_ksa = 0; i_ksa < N; i_ksa++) {
            j_ksa = (j_ksa + S[i_ksa] + key[i_ksa % key.size()]) % N;
            swap(S[i_ksa], S[j_ksa]);
        }

        // Reset i, j sau khi KSA kết thúc để chuẩn bị cho PRGA
        i = 0;
        j = 0;
    }

    // Giai đoạn PRGA (Pseudo-Random Generation Algorithm) - Tạo 1 byte dòng khóa
    unsigned char generateNextByte() {
        i = (i + 1) % N;
        j = (j + S[i]) % N;
        swap(S[i], S[j]);
        int t = (S[i] + S[j]) % N;
        return (unsigned char)S[t];
    }

    // Hàm mã hóa chuỗi văn bản
    void encryptAndPrint(string plaintext) {
        cout << "--- Qua trinh ma hoa ---" << endl;
        cout << left << setw(15) << "Ky tu (m)" << setw(15) << "Ma ASCII" << setw(15) << "Key(t)" << "Ban ma (Hex)" << endl;
        cout << string(60, '-') << endl;

        for (char &c : plaintext) {
            unsigned char k = generateNextByte();
            unsigned char cipherByte = (unsigned char)c ^ k;

            cout << left << setw(15) << c
                 << setw(15) << (int)(unsigned char)c
                 << setw(15) << (int)k
                 << hex << uppercase << setw(2) << (int)cipherByte << endl;
        }
    }
};

int main() {
    // 1. Thiết lập thông số từ đề bài
    vector<int> initial_S = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> K = {2, 4, 1, 7};
    string message = "cybersecurity";

    cout << "Thuat toan RC4 - Mon: An toan thong tin" << endl;
    cout << "Message: " << message << endl;
    cout << "Seed Key: [2, 4, 1, 7]" << endl << endl;

    // 2. Khởi tạo đối tượng RC4
    RC4_Custom rc4(initial_S, K);

    // 3. Thực thi mã hóa và in kết quả
    rc4.encryptAndPrint(message);

    return 0;
}

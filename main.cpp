#include <iostream>
#include <iomanip>

using namespace std;

typedef uint32_t poly;

// Tìm bậc của đa thức
int get_degree(poly p) {
    int deg = -1;
    while (p > 0) {
        p >>= 1;
        deg++;
    }
    return deg;
}

// Chia đa thức trên GF(2): a(x) = q(x)b(x) + r(x)
void poly_div(poly a, poly b, poly &q, poly &r) {
    q = 0;
    r = a;
    int deg_b = get_degree(b);
    int deg_r = get_degree(r);

    while (deg_r >= deg_b && r != 0) {
        int shift = deg_r - deg_b;
        q ^= (1 << shift);
        r ^= (b << shift);
        deg_r = get_degree(r);
    }
}

// Nhân đa thức trên GF(2)
poly poly_mul(poly a, poly b) {
    poly res = 0;
    for (int i = 0; i <= get_degree(b); i++) {
        if ((b >> i) & 1) res ^= (a << i);
    }
    return res;
}

// Thuật toán Euclidean mở rộng
poly extended_euclidean(poly a, poly m) {
    if (a == 0) return 0;

    poly r0 = m, r1 = a;
    poly v0 = 0, v1 = 1; // v là hệ số thỏa mãn r = ... + v*a

    cout << "Buoc trung gian (r = m*u + a*v):" << endl;
    cout << setw(10) << "q" << setw(10) << "r" << setw(10) << "v" << endl;
    cout << "------------------------------------" << endl;

    while (r1 != 0) {
        poly q, r2;
        poly_div(r0, r1, q, r2);

        // v2 = v0 - q*v1 (trong GF(2) là v0 ^ poly_mul(q, v1))
        poly v2 = v0 ^ poly_mul(q, v1);

        cout << setw(10) << q << setw(10) << r2 << setw(10) << v2 << endl;

        r0 = r1;
        r1 = r2;
        v0 = v1;
        v1 = v2;
    }

    if (r0 == 1) return v0;
    return 0; // Khong co nghich dao
}

int main() {
    poly m = 0b10000001001; // x^10 + x^3 + 1 = 1033
    poly tests[] = {523, 1015};

    for (poly a : tests) {
        cout << "--- Tim nghich dao cua a = " << a << " ---" << endl;
        poly inv = extended_euclidean(a, m);
        cout << "\nKet qua: " << a << "^-1 = " << inv << endl << endl;
    }

    return 0;
}

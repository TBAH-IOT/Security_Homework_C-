# Tìm Nghịch Đảo Nhân Trong Trường GF(2^10) bằng Thuật Toán Euclidean Mở Rộng

Dự án này triển khai thuật toán **Euclidean mở rộng (Extended Euclidean Algorithm - EEA)** để tìm nghịch đảo nhân của một số trong trường hữu hạn $GF(2^{10})$. 

## Bài toán
- **Trường hữu hạn:** $GF(2^{10})$
- **Đa thức tối giản (Irreducible Polynomial):** $m(x) = x^{10} + x^3 + 1$ 
  - Mã nhị phân: `10000001001`
  - Giá trị thập phân: `1033`
- **Mục tiêu:** Tìm $a^{-1}$ sao cho $a \cdot a^{-1} \equiv 1 \pmod{m(x)}$.

## ⚙️ Đặc điểm thuật toán
Vì làm việc trên trường $GF(2^n)$, các phép toán số học thông thường được thay thế bằng các phép toán trên đa thức nhị phân:
* **Phép cộng/trừ:** Sử dụng toán tử `XOR` (`^`).
* **Phép nhân/chia:** Thực hiện chia đa thức theo kiểu long division nhưng dùng `XOR` thay cho phép trừ truyền thống.
* **In kết quả:** Chương trình in ra bảng giá trị trung gian của từng bước tính toán (thương $q$, số dư $r$, và hệ số $v$).

## Hướng dẫn sử dụng

### 1. Biên dịch
Sử dụng trình biên dịch `g++`:
```bash
g++ -o main main.cpp
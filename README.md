# ⚔️ QuanLyNhanVatVaVuKhi (Character & Weapon Management)

![C++](https://img.shields.io/badge/Language-C++17-00599C.svg?style=flat-square&logo=c%2B%2B)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat-square&logo=windows)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=flat-square)

Đây là đồ án Console C++ xây dựng theo tiêu chuẩn **Lập trình Hướng đối tượng (OOP)**, mô phỏng một hệ thống quản lý **Nhân vật** và **Vũ khí** trong game. Chương trình cung cấp giao diện console đẹp mắt, đầy đủ tính năng trang bị, hiển thị thẻ bài nhân vật, và mô phỏng trận đấu turn-based.

---

## 🎯 Mục tiêu dự án

Dự án được xây dựng nhằm ứng dụng và thể hiện rõ nét các trụ cột của Lập trình Hướng đối tượng:
- **Đóng gói (Encapsulation):** Bảo vệ dữ liệu thuộc tính thông qua `private` và cung cấp Getter/Setter an toàn.
- **Kế thừa (Inheritance):** Thiết lập cấu trúc phân tầng giữa lớp cơ sở và các lớp dẫn xuất.
- **Đa hình (Polymorphism):** Sử dụng hàm ảo (`virtual`) để ghi đè các phương thức tấn công tùy theo loại vũ khí.
- **Quản lý vòng đời đối tượng:** Cài đặt đầy đủ Constructor, Copy Constructor, Destructor và cơ chế cấp phát động an toàn (Deep Copy).

---

## 🏗️ Cấu trúc hệ thống lớp (Class Diagram)

### 1. Lớp Trừu Tượng `VuKhi` (Base Class)
- **Thuộc tính:** `tenVuKhi`, `satThuongCoBan`, `tocDoRaDon`
- **Phương thức:** `TanCong()`, `SatThuong(int t)` (Hàm ảo)

Được kế thừa bởi 3 lớp dẫn xuất chuyên biệt:
- 🗡️ **`Kiem`**: Sát thương tính theo số nhát chém. Giới hạn bởi `doBen` (Độ bền).
- 🔫 **`Sung`**: Sát thương tính theo đạn bắn ra. Phụ thuộc `soLuongDanTrongOng` và `tocDoThayBang`.
- 🔮 **`PhepThuat`**: Sát thương ma thuật phụ thuộc thời gian niệm chú. Giới hạn bởi `nangLuongTieuHao`.

### 2. Lớp `NhanVat`
- **Thuộc tính:** `tenNhanVat`, `mau`, `nangLuong`, `VuKhi* vk`
- **Chức năng:** Trang bị vũ khí, nhận sát thương, và kích hoạt tấn công. 
- Mối quan hệ: Tương tác với `VuKhi` thông qua quan hệ **Composition/Aggregation** bằng con trỏ đa hình.

---

## ✨ Các tính năng nổi bật

1. **Quản lý danh sách đối tượng:** Thêm nhân vật, thêm vũ khí vào kho từ bàn phím hoặc đọc file cấu hình text.
2. **Giao diện bảng biểu (Tabular UI):** Danh sách nhân vật và kho đồ được hiển thị dưới dạng bảng ngang (`STT`, `Tên`, `Chỉ số`, ...) vô cùng gọn gàng và dễ nhìn.
3. **Hiển thị Thẻ bài (Card UI):** Xem chi tiết nhân vật/vũ khí dưới dạng thẻ bài (card) dọc, với viền màu sắc phân biệt rõ ràng (Xanh lá cho Nhân vật, Cyan cho Vũ khí).
4. **Mô phỏng chiến đấu (Turn-based Combat):** 
   - Lựa chọn ngẫu nhiên lượt đánh trước.
   - Hiển thị trực quan 2 thẻ bài nhân vật **song song (side-by-side)** trong cùng một màn hình console để theo dõi trạng thái.
   - Báo cáo log sát thương chi tiết và thông báo kết quả sinh tồn bằng màu sắc sinh động.

---

## 🛠️ Công nghệ & Kỹ thuật sử dụng

- **Ngôn ngữ:** `C++` (C++17)
- **Chuẩn hiển thị Console:** Hỗ trợ `UTF-8`
- **Thư viện tiêu chuẩn:** `<iostream>`, `<iomanip>`, `<vector>`, `<string>`, `<fstream>`, `<sstream>`, `<cmath>`, `<ctime>`, `<cstdlib>`
- **Giao diện Windows API:** Sử dụng `<windows.h>` để can thiệp `SetConsoleTextAttribute`, `SetConsoleOutputCP` tạo màu sắc và định vị con trỏ/căn lề động.

---

## 🚀 Hướng dẫn biên dịch và sử dụng

### 1. Môi trường yêu cầu
- Trình biên dịch: `g++` (MinGW) hoặc Visual Studio.
- Hệ điều hành: **Windows** (bắt buộc do có tương tác với Windows API để tạo màu sắc console).

### 2. Biên dịch & Chạy
Mở Terminal / Command Prompt tại thư mục chứa file `main.cpp` và chạy chuỗi lệnh sau:

```bash
g++ main.cpp -o app.exe && app.exe
```

### 3. Trải nghiệm chương trình
1. Nhấn phím **1** để nạp dữ liệu mẫu nhanh (Tạo 1 nhân vật và 3 vũ khí).
2. Nhấn phím **5** hoặc **6** để xem giao diện bảng ngang tổng quan và chọn xem chi tiết thẻ bài.
3. Nhấn phím **8** để trải nghiệm cơ chế mô phỏng chiến đấu: Các nhân vật sẽ tung chiêu và hiển thị thẻ bài song song y hệt các tựa game Turn-based RPG thực thụ!

---
*Dự án hoàn thiện để phục vụ môn học Lập trình Hướng Đối Tượng (OOP).*

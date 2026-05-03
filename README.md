# ⚔️ QuanLyNhanVatVaVuKhi (Character & Weapon Management)

![C++](https://img.shields.io/badge/Language-C++17-00599C.svg?style=flat-square&logo=c%2B%2B)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat-square&logo=windows)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=flat-square)

Đây là đồ án Console C++ xây dựng theo tiêu chuẩn **Lập trình Hướng đối tượng (OOP)**, mô phỏng một hệ thống quản lý **Nhân vật** và **Vũ khí** trong game. Chương trình cung cấp giao diện console đẹp mắt, đầy đủ tính năng trang bị, hiển thị thẻ bài nhân vật, và mô phỏng trận đấu turn-based.

---

## 🎯 Mục tiêu dự án

Dự án được xây dựng nhằm ứng dụng và thể hiện rõ nét các trụ cột của Lập trình Hướng đối tượng:
- **Đóng gói (Encapsulation):** Bảo vệ dữ liệu thuộc tính thông qua `private` và cung cấp Getter/Setter an toàn.
- **Kế thừa (Inheritance):** Thiết lập cấu trúc phân tầng giữa lớp cơ sở `VuKhi` và 3 lớp dẫn xuất chuyên biệt.
- **Đa hình (Polymorphism):** Sử dụng hàm ảo (`virtual`) và `dynamic_cast` để ghi đè các phương thức tấn công tùy theo loại vũ khí.
- **Quản lý vòng đời đối tượng:** Cài đặt đầy đủ Constructor, Copy Constructor, `operator=`, Destructor và cơ chế cấp phát động an toàn (Deep Copy).

---

## 🏗️ Cấu trúc hệ thống lớp (Class Diagram)

### 1. Lớp Trừu Tượng `VuKhi` (Abstract Base Class)
- **Thuộc tính (private):** `tenVuKhi`, `satThuongCoBan`, `tocDoRaDon`
- **Phương thức ảo thuần túy:** `TanCong()`, `SatThuong(int t)`

Được kế thừa bởi 3 lớp dẫn xuất chuyên biệt:

| Lớp | Thuộc tính riêng | Cơ chế sát thương |
|---|---|---|
| 🗡️ **`Kiem`** | `doBen` (số lần chém tối đa) | Số nhát chém theo thời gian, giới hạn bởi `doBen`. `doBen` giảm sau mỗi lần dùng. |
| 🔫 **`Sung`** | `soLuongDanToiDa`, `soLuongDanTrongOng`, `tocDoThayBang` | Bắn từng viên đạn; hết băng (`soLuongDanTrongOng = 0`) thì dừng `tocDoThayBang` giây để nạp lại, lặp đến hết `t`. |
| 🔮 **`PhepThuat`** | `loaiPhep`, `nangLuongTieuHao` | Số lần thi phép theo thời gian, đồng thời bị giới hạn bởi `nangLuong` (Mana) của `NhanVat`. |

### 2. Lớp `NhanVat`
- **Thuộc tính (private):** `tenNhanVat`, `mau` (HP), `nangLuong` (Mana), `VuKhi* vk`
- **Vòng đời đối tượng:** Copy Constructor và `operator=` thực hiện **Deep Copy** thông qua hàm `SaoChepVuKhi()` để mỗi nhân vật sở hữu vũ khí độc lập, tránh double-free.
- **Mối quan hệ:** Tương tác với `VuKhi` qua con trỏ đa hình (Composition), quản lý bộ nhớ qua `new`/`delete`.

---

## ✨ Các tính năng nổi bật

1. **Quản lý danh sách đối tượng:** Thêm nhân vật, thêm vũ khí vào kho từ bàn phím hoặc đọc từ file text định dạng `|`.
2. **Giao diện bảng biểu (Tabular UI):** Danh sách nhân vật và kho đồ được hiển thị dưới dạng bảng ngang (`STT`, `Tên`, `Chỉ số`, ...), sử dụng hàm `tinhByteThua()` để căn cột đúng với ký tự UTF-8 tiếng Việt.
3. **Hiển thị Thẻ bài (Card UI):** Xem chi tiết nhân vật/vũ khí dưới dạng thẻ bài (card) dọc, với viền màu sắc phân biệt rõ ràng (Xanh lá cho Nhân vật, Cyan cho Vũ khí).
4. **Trang bị vũ khí linh hoạt:** Nhân vật có thể trang bị vũ khí có sẵn trong kho (nhận **bản sao**) hoặc tạo vũ khí mới (tự động thêm vào kho rồi trang bị bản sao), đảm bảo vũ khí gốc trong kho không bị thay đổi.
5. **Mô phỏng chiến đấu (Turn-based Combat):**
   - Lựa chọn ngẫu nhiên lượt đánh trước.
   - Hiển thị trực quan 2 thẻ bài nhân vật **song song (side-by-side)** trong cùng một màn hình console để theo dõi trạng thái.
   - Hỗ trợ đánh nhiều lượt liên tiếp, tự động kết thúc khi có nhân vật bị hạ gục (HP ≤ 0).
   - Báo cáo log sát thương chi tiết và thông báo kết quả sinh tồn bằng màu sắc sinh động.

---

## 🛠️ Công nghệ & Kỹ thuật sử dụng

- **Ngôn ngữ:** `C++` (C++17), biên dịch với `-O2 -Wall -Wextra`
- **Chuẩn hiển thị Console:** Hỗ trợ `UTF-8` (`SetConsoleOutputCP(65001)`)
- **Thư viện tiêu chuẩn:** `<iostream>`, `<iomanip>`, `<vector>`, `<string>`, `<limits>`, `<fstream>`, `<sstream>`, `<algorithm>`, `<cmath>`, `<ctime>`, `<cstdlib>`
- **Giao diện Windows API:** Sử dụng `<windows.h>` để can thiệp `SetConsoleTextAttribute`, `SetConsoleOutputCP`, `SetConsoleCP` nhằm tạo màu sắc console.

---

## 🚀 Hướng dẫn biên dịch và sử dụng

### 1. Môi trường yêu cầu
- Trình biên dịch: `g++` (MinGW, hỗ trợ C++17 trở lên) hoặc Visual Studio.
- Hệ điều hành: **Windows** (bắt buộc do sử dụng Windows API để tạo màu sắc console).

### 2. Biên dịch & Chạy

**Cách 1 — Dùng script `build.bat` (khuyến nghị):**
```bat
build.bat
```

**Cách 2 — Biên dịch thủ công qua Terminal:**
```bash
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o run.exe && run.exe
```

### 3. Menu chương trình

| Phím | Chức năng |
|:---:|---|
| `1` | Tạo dữ liệu mẫu (3 nhân vật: Arthur, Rambo, Merlin + 3 vũ khí: Excalibur, M4A1, Trường lửa) |
| `2` | Thêm nhân vật mới (nhập từ bàn phím) |
| `3` | Thêm vũ khí mới vào kho (nhập từ bàn phím) |
| `4` | Thêm vũ khí từ file text (định dạng `LOAI\|ten\|stcb\|tdrd\|...`) |
| `5` | Hiển thị danh sách nhân vật + xem chi tiết thẻ bài từng nhân vật |
| `6` | Hiển thị danh sách vũ khí trong kho + xem chi tiết thẻ bài từng vũ khí |
| `7` | Trang bị / thay thế vũ khí cho nhân vật |
| `8` | Mô phỏng chiến đấu turn-based giữa 2 nhân vật |
| `0` | Thoát chương trình |

### 4. Định dạng file vũ khí (`vukhi.txt`)

```
KIEM|<tên>|<sát thương>|<tốc độ ra đòn>|<độ bền>
SUNG|<tên>|<sát thương>|<tốc độ bắn>|<dung tích băng>|<tốc độ thay băng>
PHEPTHUAT|<tên>|<sát thương>|<tốc độ ra phép>|<loại phép>|<mana tiêu hao/lần>
```

**Ví dụ (`vukhi.txt`):**
```
KIEM|Long Kiem|50.5|1.2|10
SUNG|AWM Sniper|120.0|2.5|5|3.5
PHEPTHUAT|Thien Thach|200.0|4.0|Lua|50
KIEM|Doan Dao|15.0|0.5|100
SUNG|Luc Bac|20.0|0.8|12|1.5
PHEPTHUAT|Tia Set|150.0|3.0|Thien nhien|30
```

---

*Dự án hoàn thiện để phục vụ môn học Lập trình Hướng Đối Tượng (OOP) — HCMUE.*

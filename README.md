# OOP_QuanLyNhanVatVaVuKhi

## Giới thiệu
Đây là đồ án Console C++ xây dựng theo hướng đối tượng, mô phỏng hệ thống quản lý **nhân vật** và **vũ khí**.  
Chương trình cho phép tạo nhân vật, trang bị vũ khí, hiển thị thông tin, mô phỏng tấn công và sao chép đối tượng để minh họa các tính chất quan trọng của lập trình hướng đối tượng.

Dự án được xây dựng nhằm thể hiện các nội dung:
- Đóng gói dữ liệu
- Kế thừa
- Đa hình
- Constructor / Copy constructor / Destructor
- Nạp chồng toán tử nhập xuất
- Ứng dụng console có menu
- Định dạng xuất với `iomanip`
- Màu chữ console bằng `windows.h`

---

## Mục tiêu bài toán
Xây dựng một chương trình quản lý nhân vật trong game đơn giản, trong đó:
- Mỗi nhân vật có tên, máu, năng lượng và một vũ khí
- Vũ khí có nhiều loại khác nhau
- Mỗi loại vũ khí có cách tính sát thương riêng
- Nhân vật có thể tấn công mục tiêu trong một khoảng thời gian `t`

---

## Các lớp trong chương trình

### 1. Lớp `VuKhi`
Là lớp cơ sở trừu tượng, mô tả các thuộc tính chung của mọi vũ khí:
- `tenVuKhi`
- `satThuongCoBan`
- `tocDoRaDon`

Các phương thức chính:
- getter / setter
- constructor mặc định
- constructor có tham số
- copy constructor
- virtual destructor
- `TanCong()`
- `SatThuong(int t)`

### 2. Lớp `Kiem`
Kế thừa từ `VuKhi`.

Thuộc tính riêng:
- `doBen`

Chức năng:
- Tính sát thương dựa trên số lần chém trong thời gian `t`
- Mỗi lần chém làm giảm độ bền kiếm

### 3. Lớp `Sung`
Kế thừa từ `VuKhi`.

Thuộc tính riêng:
- `soLuongDanTrongOng`
- `tocDoThayBang`

Chức năng:
- Tính sát thương theo số viên đạn bắn được trong thời gian `t`
- Có xét đến thời gian thay băng đạn

### 4. Lớp `PhepThuat`
Kế thừa từ `VuKhi`.

Thuộc tính riêng:
- `loaiPhep`
- `nangLuongTieuHao`

Chức năng:
- Tính sát thương phép theo thời gian ra đòn
- Có liên quan đến năng lượng tiêu hao của nhân vật

### 5. Lớp `NhanVat`
Thuộc tính:
- `tenNhanVat`
- `mau`
- `nangLuong`
- `VuKhi* vk`

Chức năng:
- Trang bị vũ khí
- Nhận sát thương
- Tấn công mục tiêu
- Sao chép sâu vũ khí khi copy đối tượng

---

## Quan hệ giữa các lớp
- `Kiem`, `Sung`, `PhepThuat` **kế thừa** từ `VuKhi`
- `NhanVat` **có một** vũ khí thông qua con trỏ `VuKhi*`

Điều này giúp chương trình thể hiện rõ:
- **Kế thừa**: các loại vũ khí dùng chung thuộc tính của lớp `VuKhi`
- **Đa hình**: `NhanVat` chỉ cần giữ `VuKhi*` nhưng vẫn có thể dùng được `Kiem`, `Sung`, `PhepThuat`

---

## Tính năng chính
Chương trình hiện hỗ trợ các chức năng sau:
1. Tạo dữ liệu mẫu
2. Thêm nhân vật mới
3. Hiển thị danh sách nhân vật
4. Trang bị / thay vũ khí cho nhân vật
5. Nhân vật tấn công mục tiêu
6. Sao chép nhân vật bằng copy constructor
7. Thoát chương trình

---

## Điểm nổi bật OOP trong bài
- Thuộc tính được đóng gói bằng `private`
- Có getter / setter đầy đủ
- Có constructor mặc định
- Có constructor tham số
- Có copy constructor
- Có destructor
- Có nạp chồng toán tử `>>` và `<<`
- Có kế thừa giữa lớp cha và lớp con
- Có override hàm ảo
- Có đa hình thông qua `VuKhi*`

---

## Công nghệ sử dụng
- **Ngôn ngữ:** C++
- **Chuẩn biên dịch:** C++17
- **Thư viện chính:**
  - `iostream`
  - `iomanip`
  - `vector`
  - `limits`
  - `cmath`
  - `algorithm`
  - `windows.h`

---

## Giao diện console
Chương trình sử dụng:
- `setw`, `left`, `fixed`, `setprecision` để định dạng đẹp
- `SetConsoleTextAttribute()` để đổi màu chữ trong console Windows

---

## Hướng dẫn biên dịch và chạy

### Cách 1: Nếu nộp bản 1 file
Lưu mã nguồn thành `main.cpp`, sau đó biên dịch:

```bash
g++ main.cpp -o app && app.exe
```

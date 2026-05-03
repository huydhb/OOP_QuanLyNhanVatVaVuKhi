#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <string>
#include <windows.h>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;
// ========================= TIEN ICH HIEN THI =========================
/// @brief Enum định nghĩa các mã màu chữ cho Windows Console.
enum MauChu {
    MAU_CYAN = 3,
    MAU_MAC_DINH = 7,
    MAU_XANH_DUONG = 9,
    MAU_XANH_LA = 10,
    MAU_DO = 12,
    MAU_VANG = 14,
    MAU_TIM = 13,
    MAU_TRANG_SANG = 15
};

/// @brief Đặt màu chữ cho Windows Console.
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/// @brief Khôi phục màu chữ mặc định.
void resetColor() {
    setColor(MAU_MAC_DINH);
}

/// @brief In tiêu đề có viền, căn giữa và tô màu.
void TieuDe(const string& s, int color = MAU_XANH_DUONG) {
    setColor(color);
    cout << "\n============================================================\n";
    int padding = (60 - s.length()) / 2;
    if (padding > 0) {
        cout << string(padding, ' ') << s << '\n';
    } else {
        cout << s << '\n';
    }
    cout << "============================================================\n";
    resetColor();
}

/// @brief In thông báo thành công (màu xanh lá).
void InThongBao(const string& s) {
    setColor(MAU_XANH_LA);
    cout << s << '\n';
    resetColor();
}

/// @brief In cảnh báo (màu vàng).
void InCanhBao(const string& s) {
    setColor(MAU_VANG);
    cout << s << '\n';
    resetColor();
}

/// @brief In thông báo lỗi (màu đỏ).
void InLoi(const string& s) {
    setColor(MAU_DO);
    cout << s << '\n';
    resetColor();
}

/**
 * @brief Tính số byte thừa trong chuỗi UTF-8.
 *
 * Trong UTF-8, các byte continuation (byte nối) có dạng 10xxxxxx.
 * Hàm đếm số byte đó để bù trừ khi dùng setw() căn cột,
 * vì setw() tính theo byte chứ không theo số ký tự hiển thị.
 *
 * @param s Chuỗi UTF-8 cần tính.
 * @return Số byte thừa (mỗi ký tự tiếng Việt có dấu thường thừa 2 byte).
 */
int tinhByteThua(const string& s) {
    int extra = 0;
    for (size_t i = 0; i < s.length(); ++i) {
        if ((s[i] & 0xC0) == 0x80) {
            extra++;
        }
    }
    return extra;
}

// ========================= LOP VUKHI =========================
/**
 * @class VuKhi
 * @brief Lớp trừu tượng đại diện cho một loại vũ khí chung.
 * 
 * Đóng vai trò là lớp cơ sở (Base Class) cho các loại vũ khí cụ thể.
 * Định nghĩa các thuộc tính cơ bản như tên, sát thương và tốc độ ra đòn,
 * cùng với các phương thức ảo thuần túy (pure virtual) để đa hình hóa hành vi tấn công.
 */
class VuKhi {
private:
    string tenVuKhi;
    float satThuongCoBan;
    float tocDoRaDon;

public:
    // 1. get - set
    string getTenVuKhi() const { return tenVuKhi; }
    void setTenVuKhi(string _tenVuKhi) { tenVuKhi = _tenVuKhi; }
    float getSatThuongCoBan() const { return satThuongCoBan; }
    void setSatThuongCoBan(float _satThuongCoBan) { satThuongCoBan = _satThuongCoBan; }
    float getTocDoRaDon() const { return tocDoRaDon; }
    void setTocDoRaDon(float _tocDoRaDon) { tocDoRaDon = _tocDoRaDon; }

    // 2. constructor
    VuKhi(string _tenVuKhi = "", float _satThuongCoBan = 0, float _tocDoRaDon = 1) {
        tenVuKhi = _tenVuKhi;
        satThuongCoBan = _satThuongCoBan;
        tocDoRaDon = _tocDoRaDon;
    }
    VuKhi(const VuKhi &v) {
        tenVuKhi = v.tenVuKhi;
        satThuongCoBan = v.satThuongCoBan;
        tocDoRaDon = v.tocDoRaDon;
    } 
    // 3. destructor
    virtual ~VuKhi() {};

    // 4. virtual method
    virtual void TanCong() = 0;
    virtual float SatThuong(int t) = 0;
};


// ========================= LOP KIEM =========================
/**
 * @class Kiem
 * @brief Lớp đại diện cho vũ khí cận chiến (Kiếm).
 * 
 * Kế thừa từ VuKhi, bổ sung thêm cơ chế độ bền (doBen).
 * Tổng sát thương gây ra bị giới hạn bởi độ bền hiện tại của kiếm.
 */
class Kiem : public VuKhi {
private:
    int doBen;

public:
    // 1. get - set
    int getDoBen() const { return doBen; }
    void setDoBen(int _doBen) { doBen = _doBen; }

    // 2. constructor
    Kiem(int _doBen = 0, string _tenVuKhi = "", float _satThuongCoBan = 0, float _tocDoRaDon = 1) 
        : VuKhi(_tenVuKhi, _satThuongCoBan, _tocDoRaDon) {
        doBen = _doBen;
    }
    Kiem(const Kiem &k) : VuKhi(k) {
        doBen = k.doBen;
    }
    virtual ~Kiem() {};
    
    // 3. in - out
    friend istream& operator>>(istream& in, Kiem& k) {
        string ten;
        float stcb, tdrd;
        int db;

        cout << "Nhập tên kiếm: ";
        getline(in >> ws, ten);
        cout << "Nhập sát thương cơ bản: ";
        in >> stcb;
        cout << "Nhập tốc độ ra đòn (giây/lần): ";
        in >> tdrd;
        cout << "Nhập độ bền (số lần chém tối đa): ";
        in >> db;

        k.setTenVuKhi(ten);
        k.setSatThuongCoBan(stcb);
        k.setTocDoRaDon(tdrd);
        k.setDoBen(db);
        return in;
    }

    friend ostream& operator<<(ostream& out, Kiem k) {
        setColor(MAU_CYAN); out << "  +---------------------------------------+\n  | ";
        resetColor(); out << left << setw(22 + tinhByteThua("Loại vũ khí:")) << "Loại vũ khí:" << setw(16 + tinhByteThua("Kiếm")) << "Kiếm";
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(22 + tinhByteThua("Tên vũ khí:")) << "Tên vũ khí:" << setw(16 + tinhByteThua(k.getTenVuKhi())) << k.getTenVuKhi();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(22 + tinhByteThua("Sát thương cơ bản:")) << "Sát thương cơ bản:" << fixed << setprecision(2) << setw(16) << k.getSatThuongCoBan();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(22 + tinhByteThua("Tốc độ ra đòn:")) << "Tốc độ ra đòn:" << fixed << setprecision(2) << setw(16) << k.getTocDoRaDon();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(22 + tinhByteThua("Độ bền:")) << "Độ bền:" << setw(16) << k.getDoBen();
        setColor(MAU_CYAN); out << "|\n  +---------------------------------------+";
        resetColor();
        return out;
    }

    // 4. virtual method
    void TanCong() override {
        setColor(MAU_XANH_LA);
        cout << "  [Kiếm] Thực hiện một chuỗi chém liên hoàn.\n";
        resetColor();
    }

    float SatThuong(int t) override {
        if (getTocDoRaDon() <= 0 || t <= 0 || doBen <= 0) return 0;

        int soLanChemTheoThoiGian = static_cast<int>(floor(t / getTocDoRaDon()));
        int soLanChem = min(doBen, soLanChemTheoThoiGian);
        float satThuong = soLanChem * getSatThuongCoBan();

        // Sau khi sử dụng, doBen giảm theo số lần chém thực tế
        doBen -= soLanChem;
        return satThuong;
    }
};


// ========================= LOP SUNG =========================
/**
 * @class Sung
 * @brief Lớp đại diện cho vũ khí tầm xa (Súng).
 *
 * Kế thừa từ VuKhi. Mô phỏng cơ chế xả đạn thực tế:
 *   - soLuongDanToiDa    : dung tích băng (cố định, VD AK47=30, AWM=5).
 *   - soLuongDanTrongOng : đạn HIỆN TẠI trong băng (trạng thái thay đổi).
 *   - tocDoThayBang      : giây để nạp 1 băng đầy.
 * Logic SatThuong(t): bắn từng viên, hết băng (X/Max → 0/Max) thì
 * dừng tocDoThayBang giây nạp lại, rồi tiếp tục cho đến hết t.
 */
class Sung : public VuKhi {
private:
    int soLuongDanToiDa;    // Dung tích băng (không đổi)
    int soLuongDanTrongOng; // Đạn hiện tại trong băng (trạng thái thay đổi)
    float tocDoThayBang;    // Giây để nạp 1 băng đầy

public:
    // 1. get - set
    int getSoLuongDanToiDa() const { return soLuongDanToiDa; }
    void setSoLuongDanToiDa(int _v) { soLuongDanToiDa = (_v > 0) ? _v : 1; }
    int getSoLuongDanTrongOng() const { return soLuongDanTrongOng; }
    void setSoLuongDanTrongOng(int _v) { soLuongDanTrongOng = (_v >= 0) ? _v : 0; }
    float getTocDoThayBang() const { return tocDoThayBang; }
    void setTocDoThayBang(float _v) { tocDoThayBang = _v; }

    // 2. constructor
    Sung(int _soLuongDanToiDa = 30, float _tocDoThayBang = 2.0f,
         string _tenVuKhi = "", float _satThuongCoBan = 0, float _tocDoRaDon = 1)
        : VuKhi(_tenVuKhi, _satThuongCoBan, _tocDoRaDon) {
        soLuongDanToiDa    = (_soLuongDanToiDa > 0) ? _soLuongDanToiDa : 1;
        soLuongDanTrongOng = soLuongDanToiDa; // Bắt đầu với băng đạn đầy
        tocDoThayBang      = _tocDoThayBang;
    }
    Sung(const Sung &s) : VuKhi(s) {
        soLuongDanToiDa    = s.soLuongDanToiDa;
        soLuongDanTrongOng = s.soLuongDanTrongOng;
        tocDoThayBang      = s.tocDoThayBang;
    }
    virtual ~Sung() {};
    
    //3. in - out
    friend istream& operator>>(istream& in, Sung& s) {
        string ten;
        float stcb, tdrd, tdthay;
        int slToiDa;

        cout << "Nhập tên súng: ";
        getline(in >> ws, ten);
        cout << "Nhập sát thương cơ bản (1 viên): ";
        in >> stcb;
        cout << "Nhập tốc độ ra đòn (giây/viên): ";
        in >> tdrd;
        cout << "Nhập dung tích băng đạn (số viên tối đa): ";
        in >> slToiDa;
        cout << "Nhập tốc độ thay băng (giây): ";
        in >> tdthay;

        s.setTenVuKhi(ten);
        s.setSatThuongCoBan(stcb);
        s.setTocDoRaDon(tdrd);
        s.setSoLuongDanToiDa(slToiDa);
        s.soLuongDanTrongOng = slToiDa; // Nạp đầy băng đạn khi tạo mới
        s.setTocDoThayBang(tdthay);
        return in;
    }

    friend ostream& operator<<(ostream& out, Sung s) {
        string danHienThi = to_string(s.soLuongDanTrongOng) + "/" + to_string(s.soLuongDanToiDa);
        setColor(MAU_CYAN); out << "  +---------------------------------------+\n  | ";
        resetColor(); out << left << setw(22 + tinhByteThua("Loại vũ khí:")) << "Loại vũ khí:" << setw(16 + tinhByteThua("Súng")) << "Súng";
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(22 + tinhByteThua("Tên vũ khí:")) << "Tên vũ khí:" << setw(16 + tinhByteThua(s.getTenVuKhi())) << s.getTenVuKhi();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(22 + tinhByteThua("Sát thương cơ bản:")) << "Sát thương cơ bản:" << fixed << setprecision(2) << setw(16) << s.getSatThuongCoBan();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(22 + tinhByteThua("Tốc độ ra đòn:")) << "Tốc độ ra đòn:" << fixed << setprecision(2) << setw(16) << s.getTocDoRaDon();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(22 + tinhByteThua("Đạn trong băng:")) << "Đạn trong băng:" << setw(16 + tinhByteThua(danHienThi)) << danHienThi;
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(22 + tinhByteThua("Tốc độ thay băng:")) << "Tốc độ thay băng:" << fixed << setprecision(2) << setw(16) << s.tocDoThayBang;
        setColor(MAU_CYAN); out << "|\n  +---------------------------------------+";
        resetColor();
        return out;
    }

    //4. virtual method
    void TanCong() override {
        setColor(MAU_VANG);
        cout << "  [Súng] Xả đạn liên tục vào mục tiêu.\n";
        resetColor();
    }

/**
     * @brief Tính sát thương gây ra trong khoảng thời gian t (giây).
     *
     * Mô phỏng logic bắn từng viên:
     *   - Mỗi viên đạn mất [tocDoRaDon] giây để bắn ra.
     *   - Khi [soLuongDanTrongOng] bằng 0 -> mất [tocDoThayBang] giây để nạp đầy lại.
     *   - Quá trình lặp lại cho đến khi hết thời gian t.
     * Lưu ý: Cập nhật số lượng đạn còn lại trong băng sau khi kết thúc t giây.
     */
    float SatThuong(int t) override {
        if (getTocDoRaDon() <= 0 || t <= 0) return 0;

        float thoiGianConLai = static_cast<float>(t);
        int tongDanBan = 0;

        // Nếu băng đạn đang rỗng, phải nạp đạn trước khi bắt đầu bắn
        if (soLuongDanTrongOng == 0) {
            if (thoiGianConLai <= tocDoThayBang) return 0;
            thoiGianConLai -= tocDoThayBang;
            soLuongDanTrongOng = soLuongDanToiDa;
        }

        // Vòng lặp: Thực hiện mô phỏng bắn cho đến khi hết thời gian t
        while (thoiGianConLai > 0) {
            // Thời gian cần thiết để bắn hết số đạn hiện đang có trong băng
            float thoiGianBanHetBang = soLuongDanTrongOng * getTocDoRaDon();

            if (thoiGianConLai < thoiGianBanHetBang) {
                // Không đủ thời gian để bắn hết cả băng -> tính số viên đạn bắn được trong phần thời gian còn lại
                int vienBan = static_cast<int>(floor(thoiGianConLai / getTocDoRaDon()));
                tongDanBan += vienBan;
                soLuongDanTrongOng -= vienBan;
                break;
            }

            // Bắn hết toàn bộ số đạn hiện có trong băng hiện tại
            tongDanBan += soLuongDanTrongOng;
            thoiGianConLai -= thoiGianBanHetBang;
            soLuongDanTrongOng = 0;

            // Thực hiện thay băng đạn: Nếu hết thời gian trong lúc đang thay đạn thì dừng
            if (thoiGianConLai <= tocDoThayBang) break;
            thoiGianConLai -= tocDoThayBang;
            soLuongDanTrongOng = soLuongDanToiDa;
        }

        return tongDanBan * getSatThuongCoBan();
    }
};



// ========================= LOP PHEPTHUAT =========================
/**
 * @class PhepThuat
 * @brief Lớp đại diện cho vũ khí ma thuật.
 * 
 * Kế thừa từ VuKhi. Sức mạnh phép thuật không bị giới hạn bởi đạn hay độ bền,
 * nhưng bù lại sẽ tiêu hao năng lượng (Mana) của nhân vật mỗi lần thi triển.
 */
class PhepThuat : public VuKhi {
private:
    string loaiPhep;
    int nangLuongTieuHao;

public:
    // 1. get - set
    string getLoaiPhep() const { return loaiPhep; }
    void setLoaiPhep(string _loaiPhep) { loaiPhep = _loaiPhep; }
    int getNangLuongTieuHao() const { return nangLuongTieuHao; }
    void setNangLuongTieuHao(int _nangLuongTieuHao) { nangLuongTieuHao = _nangLuongTieuHao; }
    
    // 2. constructor
    PhepThuat(string _loaiPhep = "", int _nangLuongTieuHao = 0, string _tenVuKhi = "", float _satThuongCoBan = 0, float _tocDoRaDon = 1) 
        : VuKhi(_tenVuKhi, _satThuongCoBan, _tocDoRaDon) {
        loaiPhep = _loaiPhep;
        nangLuongTieuHao = _nangLuongTieuHao;
    }
    PhepThuat(const PhepThuat &p) : VuKhi(p) {
        loaiPhep = p.loaiPhep;
        nangLuongTieuHao = p.nangLuongTieuHao;
    }
    virtual ~PhepThuat() {};

    //3. in - out   
    friend istream& operator>>(istream& in, PhepThuat& p) {
        string ten, loai;
        float stcb, tdrd;
        int nlth;

        cout << "Nhập tên phép thuật: ";
        getline(in >> ws, ten);
        cout << "Nhập sát thương cơ bản: ";
        in >> stcb;
        cout << "Nhập tốc độ ra đòn (giây/lần): ";
        in >> tdrd;
        cout << "Nhập loại phép: ";
        getline(in >> ws, loai);
        cout << "Nhập năng lượng tiêu hao mỗi lần: ";
        in >> nlth;

        p.setTenVuKhi(ten);
        p.setSatThuongCoBan(stcb);
        p.setTocDoRaDon(tdrd);
        p.setLoaiPhep(loai);
        p.setNangLuongTieuHao(nlth);
        return in;
    }

    friend ostream& operator<<(ostream& out, PhepThuat p) {
        setColor(MAU_CYAN); out << "  +---------------------------------------+\n  | ";
        resetColor(); out << left << setw(22 + tinhByteThua("Loại vũ khí:")) << "Loại vũ khí:" << setw(16 + tinhByteThua("Phép Thuật")) << "Phép Thuật";
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(22 + tinhByteThua("Tên vũ khí:")) << "Tên vũ khí:" << setw(16 + tinhByteThua(p.getTenVuKhi())) << p.getTenVuKhi();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(22 + tinhByteThua("Sát thương cơ bản:")) << "Sát thương cơ bản:" << fixed << setprecision(2) << setw(16) << p.getSatThuongCoBan();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(22 + tinhByteThua("Tốc độ ra đòn:")) << "Tốc độ ra đòn:" << fixed << setprecision(2) << setw(16) << p.getTocDoRaDon();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(22 + tinhByteThua("Loại phép:")) << "Loại phép:" << setw(16 + tinhByteThua(p.loaiPhep)) << p.loaiPhep;
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(22 + tinhByteThua("Năng lượng tiêu hao:")) << "Năng lượng tiêu hao:" << setw(16) << p.nangLuongTieuHao;
        setColor(MAU_CYAN); out << "|\n  +---------------------------------------+";
        resetColor();
        return out;
    }

    // 4. virtual method
    void TanCong() override {
        setColor(MAU_TIM);
        cout << "  [Phép Thuật] Tung ra các đòn ma thuật uy lực.\n";
        resetColor();
    }

    float SatThuong(int t) override {
        if (getTocDoRaDon() <= 0 || t <= 0) return 0;

        int soLanRaPhepTheoThoiGian = static_cast<int>(floor(t / getTocDoRaDon()));
        return soLanRaPhepTheoThoiGian * getSatThuongCoBan();
    }
};


// ========================= CAC HAM VE VU KHI =========================
/**
 * @brief In toàn bộ vũ khí trong kho
 */

/// @brief Xóa bộ đệm nhập (stdin) để tránh lỗi đọc dữ liệu thừa.
void XoaBoDemNhap() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/// @brief Hiển thị toàn bộ danh sách vũ khí trong kho dưới dạng bảng.
void HienThiDanhSachVK(const vector<VuKhi*>& ds) {
    if (ds.empty()) {
        InCanhBao("Danh sách vũ khí đang trống.");
        return;
    }

    TieuDe("DANH SÁCH CÁC LOẠI VŨ KHÍ TRONG KHO", MAU_XANH_LA);

    setColor(MAU_DO);
    cout << "+====+==============+====================+===========+===============+\n";
    cout << "|"; resetColor(); cout << left << setw(4) << "STT";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(14 + tinhByteThua(" Loại Vũ Khí")) << " Loại Vũ Khí";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(20 + tinhByteThua(" Tên Vũ Khí")) << " Tên Vũ Khí";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(11 + tinhByteThua(" Sát Thương")) << " Sát Thương";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(15 + tinhByteThua(" Tốc Độ Ra Đòn")) << " Tốc Độ Ra Đòn";
    setColor(MAU_DO); cout << "|\n";
    cout << "+====+==============+====================+===========+===============+\n";
    
    for (size_t i = 0; i < ds.size(); ++i) {
        setColor(MAU_DO); cout << "| "; resetColor(); cout << left << setw(3) << i + 1;
        
        if (ds[i] == nullptr) {
            setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(13) << "NULL";
            setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(19 + tinhByteThua("Không tồn tại")) << "Không tồn tại";
            setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(10) << "";
            setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(14) << "";
            setColor(MAU_DO); cout << "|\n";
            continue;
        }

        string loaiVK = "Không Rõ";
        if (dynamic_cast<const Kiem*>(ds[i])) loaiVK = "Kiếm";
        else if (dynamic_cast<const Sung*>(ds[i])) loaiVK = "Súng";
        else if (dynamic_cast<const PhepThuat*>(ds[i])) loaiVK = "Phép Thuật";

        setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(13 + tinhByteThua(loaiVK)) << loaiVK;
        setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(19 + tinhByteThua(ds[i]->getTenVuKhi())) << ds[i]->getTenVuKhi();
        setColor(MAU_DO); cout << "| "; resetColor(); cout << fixed << setprecision(2) << setw(10) << ds[i]->getSatThuongCoBan();
        setColor(MAU_DO); cout << "| "; resetColor(); cout << fixed << setprecision(2) << setw(14) << ds[i]->getTocDoRaDon();
        setColor(MAU_DO); cout << "|\n";
    }
    cout << "+====+==============+====================+===========+===============+\n";
    resetColor();
}

/**
 * @brief Hiển thị danh sách vũ khí và cho phép người dùng xem chi tiết từng vũ khí.
 */
void XemChiTietVuKhi(const vector<VuKhi*>& ds) {
    if (ds.empty()) {
        InCanhBao("Danh sách vũ khí đang trống.");
        return;
    }

    HienThiDanhSachVK(ds);

    int chon = -1;
    while (true) {
        setColor(MAU_VANG);
        cout << "\nNhập STT vũ khí để xem chi tiết (0 để quay lại): ";
        resetColor();
        cin >> chon;
        
        if (!cin) {
            XoaBoDemNhap();
            continue;
        }
        if (chon == 0) break;
        if (chon > 0 && chon <= static_cast<int>(ds.size())) {
            cout << "\n";
            if (ds[chon - 1] == nullptr) {
                InLoi("Vũ khí không tồn tại.");
                continue;
            }
            setColor(MAU_VANG);
            cout << " >> [Chi tiết Vũ khí " << chon << "] <<\n";
            resetColor();
            if (const Kiem* k = dynamic_cast<const Kiem*>(ds[chon - 1])) {
                cout << *k << '\n';
            } else if (const Sung* s = dynamic_cast<const Sung*>(ds[chon - 1])) {
                cout << *s << '\n';
            } else if (const PhepThuat* p = dynamic_cast<const PhepThuat*>(ds[chon - 1])) {
                cout << *p << '\n';
            }
            setColor(MAU_CYAN);
            cout << "\n  Nhấn Enter để tiếp tục...";
            resetColor();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        } else {
            InLoi("STT không hợp lệ.");
        }
    }
}

/**
 * @brief Tạo vũ khí mới dựa trên lựa chọn của người dùng.
 */
VuKhi* TaoVuKhiTheoLuaChon() {
    int chon;

    setColor(MAU_XANH_DUONG);
    cout << "Chọn loại vũ khí:\n";
    cout << "1. Kiếm\n";
    cout << "2. Súng\n";
    cout << "3. Phép Thuật\n";
    resetColor();

    setColor(MAU_VANG);
    cout << "Nhập lựa chọn: ";
    resetColor();
    cin >> chon;

    VuKhi* moi = nullptr;

    switch (chon) {
        case 1: {
            Kiem* k = new Kiem();
            cin >> *k;
            moi = k;
            break;
        }
        case 2: {
            Sung* s = new Sung();
            cin >> *s;
            moi = s;
            break;
        }
        case 3: {
            PhepThuat* p = new PhepThuat();
            cin >> *p;
            moi = p;
            break;
        }
        default:
            InLoi("Lựa chọn không hợp lệ. Không tạo vũ khí.");
            break;
    }

    return moi;
}

/**
 * @brief Thêm vũ khí mới vào kho.
 * @return Con trỏ vũ khí vừa được thêm vào kho.
 */
VuKhi* ThemVuKhi(vector<VuKhi*>& ds) {
    TieuDe("THÊM VŨ KHÍ", MAU_VANG);
    VuKhi* vk = TaoVuKhiTheoLuaChon();

    if (vk == nullptr) {
        InLoi("Thêm vũ khí thất bại.");
        return nullptr;
    }

    ds.push_back(vk);
    InThongBao("Đã thêm vũ khí thành công.");
    return vk; 
}

/**
 * @brief Đọc danh sách vũ khí từ file text.
 *
 * Định dạng mỗi dòng:
 * KIEM|tenVuKhi|satThuongCoBan|tocDoRaDon|doBen
 * SUNG|tenVuKhi|satThuongCoBan|tocDoRaDon|soLuongDanToiDa|tocDoThayBang
 * PHEPTHUAT|tenVuKhi|satThuongCoBan|tocDoRaDon|loaiPhep|nangLuongTieuHao
 */
void ThemVuKhiTuFile(vector<VuKhi*>& ds) {
    string duongDanFile, thuocTinhVuKhi;
    cin.ignore();
    cin.clear();
    cout << "Format: LOAI|tenVuKhi|satThuongCoBan|tocDoRaDon|thuocTinhRieng1|thuocTinhRieng2\n";
    cout << "Nhập đường dẫn file txt: ";
    getline(cin, duongDanFile);

    ifstream inp (duongDanFile);
    if (inp.good()) {
        while (getline(inp, thuocTinhVuKhi)){
            try {
                stringstream ss(thuocTinhVuKhi);
                string loaiVuKhi, tenVuKhi, satThuongCoBanSTR, tocDoRaDonSTR;
                float satThuongCoBan, tocDoRaDon;

                getline(ss, loaiVuKhi, '|');
                getline(ss, tenVuKhi, '|');
                getline(ss, satThuongCoBanSTR, '|');
                getline(ss, tocDoRaDonSTR, '|');
                satThuongCoBan = stof(satThuongCoBanSTR);
                tocDoRaDon = stof(tocDoRaDonSTR);
                
                if (loaiVuKhi == "KIEM") {
                    string doBenSTR;
                    int doBen;
                    getline(ss, doBenSTR, '|');
                    doBen = stoi(doBenSTR);

                    Kiem* vk = new Kiem(doBen, tenVuKhi, satThuongCoBan, tocDoRaDon);
                    VuKhi* moi = vk;
                    ds.push_back(moi);
                }

                else if (loaiVuKhi == "SUNG") {
                    string soLuongDanToiDaSTR, tocDoThayBangSTR;
                    int soLuongDanToiDa;
                    float tocDoThayBang;
                    getline(ss, soLuongDanToiDaSTR, '|');
                    getline(ss, tocDoThayBangSTR, '|');
                    soLuongDanToiDa = stoi(soLuongDanToiDaSTR);
                    tocDoThayBang   = stof(tocDoThayBangSTR);

                    // soLuongDanTrongOng tự động = soLuongDanToiDa (băng đầy khi tạo)
                    Sung* vk = new Sung(soLuongDanToiDa, tocDoThayBang, tenVuKhi, satThuongCoBan, tocDoRaDon);
                    ds.push_back(vk);
                }
                else if (loaiVuKhi == "PHEPTHUAT") {
                    string loaiPhep, nangLuongTieuHaoSTR;
                    int nangLuongTieuHao;

                    getline(ss, loaiPhep, '|');
                    getline(ss, nangLuongTieuHaoSTR, '|');
                    nangLuongTieuHao = stoi(nangLuongTieuHaoSTR);

                    PhepThuat* vk = new PhepThuat(loaiPhep, nangLuongTieuHao, tenVuKhi, satThuongCoBan, tocDoRaDon);
                    VuKhi* moi = vk;
                    ds.push_back(moi);
                }
                else {
                    InLoi("Loại vũ khí không hợp lệ: " + loaiVuKhi);
                    continue;
                }
                InThongBao("Đã thêm vũ khí thành công.");
            }
            catch (...) {
                InLoi("Không thể nhập vũ khí này.");
                continue;
            }
        }
        InThongBao("Hoàn tất thêm vũ khí từ file.");
    }
    else {
        cout << duongDanFile << endl;
        InLoi("Đường dẫn không tồn tại.");
    }
} 

/**
 * @brief Tạo bản sao của một vũ khí dựa trên kiểu động thực tế.
 *
 * Hàm dùng dynamic_cast để xác định loại vũ khí gốc và tạo ra bản sao tương ứng.
 * Thiết kế này giúp mỗi nhân vật sở hữu một vũ khí riêng, tránh dùng chung
 * trực tiếp object trong kho.
 *
 * @param src Con trỏ tới vũ khí nguồn.
 * @return Con trỏ tới bản sao mới tạo; trả về nullptr nếu src rỗng hoặc kiểu không hỗ trợ.
 */

VuKhi* SaoChepVuKhi(const VuKhi* src) {
    if (src == nullptr) return nullptr;

    if (const Kiem* k = dynamic_cast<const Kiem*>(src)) {
        return new Kiem(*k);
    }
    if (const Sung* s = dynamic_cast<const Sung*>(src)) {
        return new Sung(*s);
    }
    if (const PhepThuat* p = dynamic_cast<const PhepThuat*>(src)) {
        return new PhepThuat(*p);
    }
    return nullptr;
}

/**
 * @brief Cho người dùng chọn 1 vũ khí từ kho và trả về bản sao của vũ khí đó.
 */
VuKhi* ChonVuKhiTuDanhSach(vector<VuKhi*>& ds) {
    if (ds.empty()) {
        InCanhBao("Danh sách vũ khí trống.");
        return nullptr;
    }

    HienThiDanhSachVK(ds);

    int idx;
    setColor(MAU_VANG);
    cout << "Chọn vũ khí cho nhân vật (1-" << ds.size() << "): ";
    resetColor();
    cin >> idx;

    if (!cin || idx < 1 || idx > static_cast<int>(ds.size())) {
        XoaBoDemNhap();
        InLoi("Chỉ số vũ khí không hợp lệ.");
        return nullptr;
    }

    if (ds[idx - 1] == nullptr) {
        InLoi("Vũ khí không tồn tại.");
        return nullptr;
    }

    return SaoChepVuKhi(ds[idx - 1]);
}

// ========================= LOP NHANVAT =========================
/**
 * @class NhanVat
 * @brief Lớp đại diện cho một thực thể nhân vật trong trò chơi.
 * 
 * Quản lý trạng thái sinh tồn (máu), khả năng thi triển kỹ năng (năng lượng)
 * và quản lý vòng đời của vũ khí đang trang bị. Bao gồm các logic chiến đấu với mục tiêu.
 */
class NhanVat {
private:
    string tenNhanVat;
    float mau;
    int nangLuong;
    VuKhi* vk;

public:
    //1. get - set
    string getTenNhanVat() const {
        return tenNhanVat;
    }
    float getMau() const {
        return mau;
    }
    int getNangLuong() const {
        return nangLuong;
    }
    VuKhi* getVuKhi() const {
        return vk;
    }
    

    void setTenNhanVat(string _tenNhanVat) {
        tenNhanVat = _tenNhanVat;
    }
    
    void setMau(float _mau) {
        mau = (_mau >= 0) ? _mau : 0;
    }

    void setNangLuong(int _nangLuong) {
        nangLuong = (_nangLuong >= 0) ? _nangLuong : 0;
    }

    void setVuKhi(VuKhi* _vk) {
        if (vk != _vk) {
            delete vk;
            vk = _vk;
        }
    }

    //2. constructor
    NhanVat() : tenNhanVat(""), mau(0), nangLuong(0), vk(nullptr) {}

    NhanVat(string tenNhanVat, float mau, int nangLuong, VuKhi* vk)
        : tenNhanVat(tenNhanVat), mau((mau >= 0) ? mau : 0), nangLuong((nangLuong >= 0) ? nangLuong : 0), vk(vk) {}

    NhanVat(const NhanVat& other)
        : tenNhanVat(other.tenNhanVat), mau(other.mau), nangLuong(other.nangLuong), vk(SaoChepVuKhi(other.vk)) {}
    
    NhanVat& operator=(const NhanVat& other) {
        if (this != &other) {
            tenNhanVat = other.tenNhanVat;
            mau = other.mau;
            nangLuong = other.nangLuong;
            delete vk;
            vk = SaoChepVuKhi(other.vk);
        }
        return *this;
    }

    ~NhanVat() {
        delete vk;
        vk = nullptr;
    }
    
    //3. in - out
    friend istream& operator>>(istream& in, NhanVat& nv) {
    string ten;
    float mau;
    int nangLuong;
    cout << "Nhập tên nhân vật: ";
    getline(in >> ws, ten);
    cout << "Nhập máu (HP): ";
    in >> mau;
    cout << "Nhập năng lượng (Mana): ";
    in >> nangLuong;

    nv.setTenNhanVat(ten);
    nv.setMau(mau);
    nv.setNangLuong(nangLuong);
    nv.setVuKhi(nullptr);
    return in;
    }
    
    friend ostream& operator<<(ostream& out, NhanVat nv) {
        setColor(MAU_XANH_LA); out << "+=========================================+\n| ";
        resetColor(); out << left << setw(22 + tinhByteThua("Tên nhân vật:")) << "Tên nhân vật:" << setw(16 + tinhByteThua(nv.tenNhanVat)) << nv.tenNhanVat;
        setColor(MAU_XANH_LA); out << "|\n| ";
        resetColor(); out << setw(22 + tinhByteThua("Máu (HP):")) << "Máu (HP):" << fixed << setprecision(2) << setw(16) << nv.mau;
        setColor(MAU_XANH_LA); out << "|\n| ";
        resetColor(); out << setw(22 + tinhByteThua("Năng lượng (Mana):")) << "Năng lượng (Mana):" << setw(16) << nv.nangLuong;
        setColor(MAU_XANH_LA); out << "|\n| ";
        
        string trangThai = (nv.mau > 0) ? "Còn sống" : "Đã bị hạ gục";
        resetColor(); out << setw(22 + tinhByteThua("Trạng thái:")) << "Trạng thái:" << setw(16 + tinhByteThua(trangThai)) << trangThai;
        setColor(MAU_XANH_LA); out << "|\n| ";
        resetColor(); out << setw(22 + tinhByteThua("Vũ khí trang bị:")) << "Vũ khí trang bị:";
        
        if (nv.vk == nullptr) {
            out << setw(16 + tinhByteThua("Không có")) << "Không có";
            setColor(MAU_XANH_LA); out << "|\n+=========================================+\n";
            resetColor();
            return out;
        } else {
            out << setw(16) << "";
            setColor(MAU_XANH_LA); out << "|\n";
            resetColor();
        }

        if (const Kiem* k = dynamic_cast<const Kiem*>(nv.vk)) {
            out << *k << '\n';
        } else if (const Sung* s = dynamic_cast<const Sung*>(nv.vk)) {
            out << *s << '\n';
        } else if (const PhepThuat* p = dynamic_cast<const PhepThuat*>(nv.vk)) {
            out << *p << '\n';
        }
        setColor(MAU_XANH_LA); out << "+=========================================+";
        resetColor();
        return out;
    }
    //4. extend method
    void TrangBi(VuKhi* v) {
        setVuKhi(v);
    }

    void NhanSatThuong(float st) {
        if (st < 0) st = 0;
        mau -= st;
        if (mau < 0) {
            mau = 0;
        }
    }

    /**
     * @brief Thực hiện chuỗi hành động tấn công lên một mục tiêu trong một khoảng thời gian.
     * 
     * Hàm này xử lý các ràng buộc phức tạp như: 
     * 1. Nguồn sát thương (phải có vũ khí).
     * 2. Trạng thái bản thân (phải còn sống).
     * 3. Cơ chế năng lượng (nếu dùng phép thuật thì phải đủ năng lượng hao phí).
     * 
     * @param b Tham chiếu đến nhân vật mục tiêu bị tấn công.
     * @param t Khung thời gian thực hiện chuỗi hành động tấn công (tính bằng giây).
     */
    void TanCongMucTieu(NhanVat& b, int t) {
        if (vk == nullptr) {
            InLoi("  [!] " + tenNhanVat + " chưa có vũ khí để tấn công.");
            return;
        }
        if (mau <= 0) {
            InLoi("  [!] " + tenNhanVat + " đã bị hạ gục nên không thể tấn công.");
            return;
        }
        if (b.mau <= 0) {
            InLoi("  [!] " + b.tenNhanVat + " đã bị hạ gục.");
            return;
        }
        if (t <= 0) {
            InLoi("  [!] Thời gian tấn công phải > 0.");
            return;
        }
        
        float satThuong = 0;
        // Xử lí riêng cho PhepThuat vì công thức UML cần năng lượng của NhanVat
        if (PhepThuat* p = dynamic_cast<PhepThuat*>(vk)) {
            if (p->getTocDoRaDon() > 0 && p->getNangLuongTieuHao() > 0) {
                int soLanRaPhepTheoThoiGian = static_cast<int>(floor(t / p->getTocDoRaDon()));
                int soLanRaPhepTheoNangLuong = nangLuong / p->getNangLuongTieuHao();
                int soLanRaPhep = min(soLanRaPhepTheoThoiGian, soLanRaPhepTheoNangLuong);
                satThuong = soLanRaPhep * p->getSatThuongCoBan();
                int nangLuongDaDung = soLanRaPhep * p->getNangLuongTieuHao();
                nangLuong -= nangLuongDaDung;
            } else {
                satThuong = p->SatThuong(t);
            }
        } else {
            satThuong = vk->SatThuong(t);
        }
        
        vk->TanCong();
        b.NhanSatThuong(satThuong);
        
        setColor(MAU_VANG);
        cout << "  >>> ";
        setColor(MAU_XANH_DUONG);
        cout << tenNhanVat;
        setColor(MAU_TRANG_SANG);
        cout << " gây ra ";
        setColor(MAU_DO);
        cout << fixed << setprecision(2) << satThuong;
        setColor(MAU_TRANG_SANG);
        cout << " sát thương lên ";
        setColor(MAU_XANH_DUONG);
        cout << b.tenNhanVat << "!\n\n";
        resetColor();
    }
};


// ========================= CAC HAM MENU =========================
void LamMoiManHinh() {
    system("cls");
}

/// @brief Hiển thị danh sách nhân vật dưới dạng bảng tóm tắt.
void HienThiDanhSach(const vector<NhanVat>& ds) {
    if (ds.empty()) {
        InCanhBao("Danh sach nhan vat dang rong.");
        return;
    }

    TieuDe("DANH SÁCH NHÂN VẬT", MAU_XANH_LA);

    setColor(MAU_DO);
    cout << "+====+====================+========+========+====================+\n";
    cout << "|"; resetColor(); cout << left << setw(4) << "STT";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(20 + tinhByteThua(" Tên Nhân Vật")) << " Tên Nhân Vật";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(8 + tinhByteThua(" Máu")) << " Máu";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(8 + tinhByteThua(" N.Lượng")) << " N.Lượng";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(20 + tinhByteThua(" Vũ Khí (Tên)")) << " Vũ Khí (Tên)";
    setColor(MAU_DO); cout << "|\n";
    cout << "+====+====================+========+========+====================+\n";
    
    for (size_t i = 0; i < ds.size(); ++i) {
        setColor(MAU_DO); cout << "| "; resetColor(); cout << left << setw(3) << i + 1;
        setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(19 + tinhByteThua(ds[i].getTenNhanVat())) << ds[i].getTenNhanVat();
        setColor(MAU_DO); cout << "| "; resetColor(); cout << fixed << setprecision(2) << setw(7) << ds[i].getMau();
        setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(7) << ds[i].getNangLuong();
        setColor(MAU_DO); cout << "| "; resetColor(); 
        
        string tenVK = "Không có";
        if (ds[i].getVuKhi() != nullptr) {
            tenVK = ds[i].getVuKhi()->getTenVuKhi();
        }
        cout << setw(19 + tinhByteThua(tenVK)) << tenVK;
        setColor(MAU_DO); cout << "|\n";
    }
    cout << "+====+====================+========+========+====================+\n";
    resetColor();
}

/// @brief Hiển thị danh sách và cho phép người dùng xem chi tiết từng nhân vật.
void XemChiTietNhanVat(const vector<NhanVat>& ds) {
    if (ds.empty()) {
        InCanhBao("Danh sách nhân vật đang trống.");
        return;
    }

    HienThiDanhSach(ds);

    int chon = -1;
    while (true) {
        setColor(MAU_VANG);
        cout << "\nNhập STT nhân vật để xem chi tiết (0 để quay lại): ";
        resetColor();
        cin >> chon;
        
        if (!cin) {
            XoaBoDemNhap();
            continue;
        }
        if (chon == 0) break;
        if (chon > 0 && chon <= static_cast<int>(ds.size())) {
            cout << "\n";
            setColor(MAU_VANG);
            cout << " >> [Chi tiết Nhân vật " << chon << "] <<\n";
            resetColor();
            cout << ds[chon - 1] << "\n";
            setColor(MAU_CYAN);
            cout << "\n  Nhấn Enter để tiếp tục...";
            resetColor();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        } else {
            InLoi("STT không hợp lệ.");
        }
    }
}

/**
 * @brief Khởi tạo dữ liệu mẫu gồm 3 nhân vật và 3 vũ khí đại diện 3 loại.
 *
 * Xóa toàn bộ dữ liệu cũ (giải phóng bộ nhớ) trước khi tạo mới.
 * @param ds Danh sách nhân vật.
 * @param dsVK Kho vũ khí.
 */
void TaoDuLieuMau(vector<NhanVat>& ds, vector<VuKhi*>& dsVK) {
    // Xóa dữ liệu cũ nếu có
    for (VuKhi* vk : dsVK) {
        delete vk;
    }
    dsVK.clear();
    ds.clear();

    // Tạo danh sách vũ khí mẫu
    dsVK.push_back(new Kiem(
        25,             // Độ bền
        "Excalibur",    // Tên vũ khí
        22.0f,          // Sát thương cơ bản
        1.2f            // Tốc độ ra đòn
    ));

    dsVK.push_back(new Sung(
        30,             // Số đạn trong băng
        2.5f,           // Thời gian thay băng
        "M4A1",         // Tên vũ khí
        12.0f,          // Sát thương cơ bản
        3.0f            // Tốc độ bắn
    ));

    dsVK.push_back(new PhepThuat(
        "Hoa cau",      // Loại phép
        12,             // Mana tiêu thụ mỗi giây
        "Truong lua",   // Tên phép
        28.0f,          // Sát thương cơ bản
        1.0f            // Tốc độ ra phép
    ));

    // Tạo danh sách nhân vật mẫu
    ds.push_back(NhanVat(
        "Arthur",
        500.0f,                 // Máu cao vì là đấu sĩ cận chiến
        150,                    // Năng lượng vừa phải
        SaoChepVuKhi(dsVK[0])
    ));

    ds.push_back(NhanVat(
        "Rambo",
        420.0f,                 // Máu trung bình khá
        180,                    // Năng lượng khá
        SaoChepVuKhi(dsVK[1])
    ));

    ds.push_back(NhanVat(
        "Merlin",
        350.0f,                 // Máu thấp hơn vì là pháp sư
        300,                    // Mana cao để dùng phép
        SaoChepVuKhi(dsVK[2])
    ));
    
    InThongBao("Đã tạo 3 nhân vật mẫu và 3 vũ khí mẫu trong kho.");
}

/// @brief Thêm một nhân vật mới vào danh sách bằng cách nhập từ bàn phím.
void ThemNhanVat(vector<NhanVat>& ds) {
    TieuDe("THÊM NHÂN VẬT", MAU_VANG);
    NhanVat nv;
    cin >> nv;
    ds.push_back(nv);
    InThongBao("Đã thêm nhân vật thành công.");
}

/**
 * @brief Trang bị hoặc thay thế vũ khí cho nhân vật.
 * @details 
 * - Nếu chọn vũ khí đã có trong kho: Nhân vật sẽ nhận một BẢN SAO (clone) của vũ khí đó.
 * - Nếu tạo vũ khí mới: Vũ khí này sẽ được thêm vào kho đồ trước, sau đó nhân vật 
 * sẽ nhận một BẢN SAO của nó để sử dụng.
 * @note Điều này đảm bảo vũ khí gốc trong kho không bị thay đổi thuộc tính khi nhân vật sử dụng.
 */
void TrangBiChoNhanVat(vector<NhanVat>& ds, vector<VuKhi*>& dsVK) {
    if (ds.empty()) {
        InCanhBao("Chưa có nhân vật nào.");
        return;
    }

    HienThiDanhSach(ds);

    int idx, opt;
    VuKhi* moi;
    setColor(MAU_VANG);
    cout << "Chọn chỉ số nhân vật cần trang bị (1-" << ds.size() << "): ";
    resetColor();
    cin >> idx;

    if (idx < 1 || idx > static_cast<int>(ds.size())) {
        InLoi("Chỉ số không hợp lệ.");
        return;
    }

    cout << "1. Trang bị vũ khí có sẵn\n"
         << "2. Trang bị vũ khí mới\n";
    
    cout << "Nhập lựa chọn: ";
    cin >> opt;
    switch (opt) {
        case 1:
            moi = ChonVuKhiTuDanhSach(dsVK); 
            break;
        case 2: {
            // Tạo vũ khí mới, lưu vào kho, sau đó nhân vật nhận bản sao.
            // Cách này tránh lỗi chia sẻ chung 1 con trỏ giữa kho và nhân vật.
            VuKhi* vkKho = ThemVuKhi(dsVK);  
            moi = SaoChepVuKhi(vkKho);      
            break;
        }
        default:
        InLoi("Chỉ số không hợp lệ.");
            return;
    }

    if (moi == nullptr) {
        InLoi("Không thể trang bị vũ khí.");
        return;
    }

    ds[idx - 1].TrangBi(moi);
}

/**
 * @brief Tách một chuỗi nhiều dòng thành vector các chuỗi dòng đơn.
 */
vector<string> splitLines(const string& s) {
    vector<string> lines;
    stringstream ss(s);
    string line;
    while (getline(ss, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        lines.push_back(line);
    }
    return lines;
}

/**
 * @brief In một dòng văn bản dài 43 ký tự, áp dụng màu sắc phù hợp với loại dòng.
 * @param line Nội dung dòng cần in.
 * @param mauKhung Mã màu dùng cho viền ngoài.
 */
void InDongCoMau(string line, int mauKhung) {
    if (line.empty()) {
        cout << string(43, ' ');
        return;
    }
    if (line.find("+===") != string::npos) {
        setColor(mauKhung); cout << left << setw(43) << line; resetColor();
    }
    else if (line.find("+---") != string::npos) {
        setColor(MAU_CYAN); cout << left << setw(43) << line; resetColor();
    }
    else if (line.find("| ") == 0) {
        setColor(mauKhung); cout << "| "; resetColor();
        string content = line.substr(2);
        if (!content.empty() && content.back() == '|') content.pop_back();
        cout << left << setw(40) << content;
        setColor(mauKhung); cout << "|"; resetColor();
    }
    else if (line.find("  | ") == 0) {
        setColor(MAU_CYAN); cout << "  | "; resetColor();
        string content = line.substr(4);
        if (!content.empty() && content.back() == '|') content.pop_back();
        cout << left << setw(38) << content;
        setColor(MAU_CYAN); cout << "|"; resetColor();
    }
    else {
        cout << left << setw(43) << line;
    }
}

/**
 * @brief Hiển thị thông tin 2 nhân vật song song cạnh nhau để dễ so sánh.
 */
void HienThiHaiNhanVatSongSong(const NhanVat& nv1, const NhanVat& nv2) {
    stringstream ss1, ss2;
    ss1 << nv1;
    ss2 << nv2;
    
    vector<string> lines1 = splitLines(ss1.str());
    vector<string> lines2 = splitLines(ss2.str());
    
    size_t maxLines = max(lines1.size(), lines2.size());
    
    setColor(MAU_VANG);
    cout << " >> [Nhân vật 1]" << string(31, ' ') << " >> [Nhân vật 2]\n";
    resetColor();

    for (size_t i = 0; i < maxLines; ++i) {
        string l1 = (i < lines1.size()) ? lines1[i] : "";
        string l2 = (i < lines2.size()) ? lines2[i] : "";
        
        InDongCoMau(l1, MAU_XANH_LA);
        cout << "    "; 
        InDongCoMau(l2, MAU_XANH_DUONG); 
        cout << "\n";
    }
    cout << "\n";
}

/**
 * @brief Mô phỏng trận chiến giữa 2 nhân vật, mỗi lượt nhập thời gian tấn công.
 *
 * Người dùng chọn 2 nhân vật, sau đó mỗi vòng nhập thời gian t(giây).
 * Thứ tự tấn công được quyết định ngẫu nhiên mỗi lượt.
 */
void TanCong(vector<NhanVat>& ds) {
    if (ds.size() < 2) {
        InCanhBao("Cần ít nhất 2 nhân vật để mô phỏng tấn công.");
        return;
    }

    HienThiDanhSach(ds);

    int a, b;

    setColor(MAU_VANG);
    cout << "Chọn nhân vật thứ nhất (1-" << ds.size() << "): ";
    resetColor();
    cin >> a;

    setColor(MAU_VANG);
    cout << "Chọn nhân vật thứ hai (1-" << ds.size() << "): ";
    resetColor();
    cin >> b;

    if (!cin || a < 1 || a > static_cast<int>(ds.size()) ||
        b < 1 || b > static_cast<int>(ds.size()) || a == b) {
        XoaBoDemNhap();
        InLoi("Lựa chọn không hợp lệ.");
        return;
    }

    int luaChonTiepTuc = 1;

    while (luaChonTiepTuc == 1) {
        int t;

        setColor(MAU_VANG);
        cout << "Nhập thời gian tấn công t (giây): ";
        resetColor();
        cin >> t;

        if (!cin || t <= 0) {
            XoaBoDemNhap();
            InLoi("Thời gian tấn công phải là số nguyên > 0.");
            continue;
        }

        TieuDe("KẾT QUẢ TẤN CÔNG", MAU_DO);
        
        int turn = rand() % 2;
        if (turn == 0) {
            InThongBao(" -> " + ds[a - 1].getTenNhanVat() + " giành được quyền tấn công trước!");
            ds[a - 1].TanCongMucTieu(ds[b - 1], t);
            if (ds[b - 1].getMau() > 0) {
                ds[b - 1].TanCongMucTieu(ds[a - 1], t);
            }
        } else {
            InThongBao(" -> " + ds[b - 1].getTenNhanVat() + " giành được quyền tấn công trước!");
            ds[b - 1].TanCongMucTieu(ds[a - 1], t);
            if (ds[a - 1].getMau() > 0) {
                ds[a - 1].TanCongMucTieu(ds[b - 1], t);
            }
        }

        TieuDe("TRẠNG THÁI SAU LƯỢT TẤN CÔNG", MAU_XANH_LA);

        HienThiHaiNhanVatSongSong(ds[a - 1], ds[b - 1]);

        if (ds[a - 1].getMau() <= 0 && ds[b - 1].getMau() <= 0) {
            InThongBao("Cả hai nhân vật đã bị hạ gục. Kết thúc trận đấu.");
            setColor(MAU_CYAN);
            resetColor();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }
        if (ds[a - 1].getMau() <= 0) {
            InThongBao(ds[a - 1].getTenNhanVat() + " đã bị hạ gục. Kết thúc trận đấu.");
            setColor(MAU_CYAN);
            resetColor();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }
        if (ds[b - 1].getMau() <= 0) {
            InThongBao(ds[b - 1].getTenNhanVat() + " đã bị hạ gục. Kết thúc trận đấu.");
            setColor(MAU_CYAN);
            resetColor();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }

        setColor(MAU_VANG);
        cout << "1. Tấn công tiếp\n0. Kết thúc tấn công\nLựa chọn: ";
        resetColor();
        cin >> luaChonTiepTuc;

        if (!cin) {
            XoaBoDemNhap();
            luaChonTiepTuc = 0;
        }
    }
}

void InMenu() {
    TieuDe("CHƯƠNG TRÌNH QUẢN LÝ NHÂN VẬT - VŨ KHÍ", MAU_TIM);

    setColor(MAU_XANH_DUONG);
    cout << left
         << setw(6) << "1." << "Tạo dữ liệu mẫu \n"
         << setw(6) << "2." << "Thêm nhân vật\n"
         << setw(6) << "3." << "Thêm vũ khí\n"
         << setw(6) << "4." << "Thêm vũ khí mới từ file\n"
         << setw(6) << "5." << "Hiển thị danh sách nhân vật\n"
         << setw(6) << "6." << "Hiển thị danh sách các loại vũ khí trong kho\n"
         << setw(6) << "7." << "Trang bị / thay vũ khí cho nhân vật\n"
         << setw(6) << "8." << "Nhân vật tấn công mục tiêu\n"
         << setw(6) << "0." << "Thoát\n";
    resetColor();

    setColor(MAU_VANG);
    cout << "Nhập lựa chọn: ";
    resetColor();
}

vector<NhanVat> danhSach;
vector<VuKhi*> danhSachVK;

// ========================= MAIN =========================
int main() {
    srand(static_cast<unsigned>(time(0)));
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    int luaChon;

    do {
        InMenu();

        cin >> luaChon;
        if (!cin) {
            XoaBoDemNhap();
            InLoi("Vui lòng nhập số hợp lệ.");
            continue;
        }

        switch (luaChon) {
            case 1:
                TaoDuLieuMau(danhSach, danhSachVK);
                break;
            case 2:
                ThemNhanVat(danhSach);
                break;
            case 3:
                ThemVuKhi(danhSachVK);
                break;
            case 4:
                ThemVuKhiTuFile(danhSachVK);
                break;
            case 5:
                XemChiTietNhanVat(danhSach);
                break;
            case 6:
                XemChiTietVuKhi(danhSachVK);
                break;
            case 7:
                TrangBiChoNhanVat(danhSach, danhSachVK);
                break;
            case 8:
                TanCong(danhSach);
                break;
            case 0:
                InThongBao("Tạm biệt!");
                break;
            default:
                InLoi("Lựa chọn không hợp lệ.");
        }

        if (luaChon != 0) {
            setColor(MAU_CYAN);
            cout << "\nNh\u1ea5n Enter \u0111\u1ec3 ti\u1ebfp t\u1ee5c...";
            resetColor();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            LamMoiManHinh();
        }

    } while (luaChon != 0);

    for (VuKhi* v : danhSachVK) delete v;
    danhSachVK.clear();

    return 0;
}

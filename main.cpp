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

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor() {
    setColor(MAU_MAC_DINH);
}

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

void InThongBao(const string& s) {
    setColor(MAU_XANH_LA);
    cout << s << '\n';
    resetColor();
}

void InCanhBao(const string& s) {
    setColor(MAU_VANG);
    cout << s << '\n';
    resetColor();
}

void InLoi(const string& s) {
    setColor(MAU_DO);
    cout << s << '\n';
    resetColor();
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

        cout << "Nhap ten kiem: ";
        getline(in >> ws, ten);
        cout << "Nhap sat thuong co ban: ";
        in >> stcb;
        cout << "Nhap toc do ra don: ";
        in >> tdrd;
        cout << "Nhap do ben: ";
        in >> db;

        k.setTenVuKhi(ten);
        k.setSatThuongCoBan(stcb);
        k.setTocDoRaDon(tdrd);
        k.setDoBen(db);
        return in;
    }

    friend ostream& operator<<(ostream& out, Kiem k) {
        setColor(MAU_CYAN); out << "  +---------------------------------------+\n  | ";
        resetColor(); out << left << setw(18) << "Loai vu khi:" << setw(20) << "Kiem";
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(18) << "Ten vu khi:" << setw(20) << k.getTenVuKhi();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(18) << "ST co ban:" << fixed << setprecision(2) << setw(20) << k.getSatThuongCoBan();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(18) << "Toc do ra don:" << fixed << setprecision(2) << setw(20) << k.getTocDoRaDon();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(18) << "Do ben:" << setw(20) << k.doBen;
        setColor(MAU_CYAN); out << "|\n  +---------------------------------------+";
        resetColor();
        return out;
    }

    // 4. virtual method
    void TanCong() override {
        setColor(MAU_XANH_LA);
        cout << "  [Kiem] Thuc hien mot chuoi chem lien hoan.\n";
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
    int soLuongDanToiDa;    // Dung tich bang (khong doi)
    int soLuongDanTrongOng; // Dan hien tai trong bang (trang thai)
    float tocDoThayBang;    // Giay de nap 1 bang day

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
        soLuongDanTrongOng = soLuongDanToiDa; // bat dau voi bang day
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

        cout << "Nhap ten sung: ";
        getline(in >> ws, ten);
        cout << "Nhap sat thuong co ban (1 vien): ";
        in >> stcb;
        cout << "Nhap toc do ra don (giay/vien): ";
        in >> tdrd;
        cout << "Nhap dung tich bang dan (so vien toi da): ";
        in >> slToiDa;
        cout << "Nhap toc do thay bang (giay): ";
        in >> tdthay;

        s.setTenVuKhi(ten);
        s.setSatThuongCoBan(stcb);
        s.setTocDoRaDon(tdrd);
        s.setSoLuongDanToiDa(slToiDa);
        s.soLuongDanTrongOng = slToiDa; // nap day khi tao moi
        s.setTocDoThayBang(tdthay);
        return in;
    }

    friend ostream& operator<<(ostream& out, Sung s) {
        string danHienThi = to_string(s.soLuongDanTrongOng) + "/" + to_string(s.soLuongDanToiDa);
        setColor(MAU_CYAN); out << "  +---------------------------------------+\n  | ";
        resetColor(); out << left << setw(18) << "Loai vu khi:" << setw(20) << "Sung";
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(18) << "Ten vu khi:" << setw(20) << s.getTenVuKhi();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(18) << "ST co ban:" << fixed << setprecision(2) << setw(20) << s.getSatThuongCoBan();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(18) << "Toc do ra don:" << fixed << setprecision(2) << setw(20) << s.getTocDoRaDon();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(18) << "Dan trong bang:" << setw(20) << danHienThi;
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(18) << "Toc do thay bang:" << fixed << setprecision(2) << setw(20) << s.tocDoThayBang;
        setColor(MAU_CYAN); out << "|\n  +---------------------------------------+";
        resetColor();
        return out;
    }

    //4. virtual method
    void TanCong() override {
        setColor(MAU_VANG);
        cout << "  [Sung] Xa dan lien tuc vao muc tieu.\n";
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

        cout << "Nhap ten phep thuat: ";
        getline(in >> ws, ten);
        cout << "Nhap sat thuong co ban: ";
        in >> stcb;
        cout << "Nhap toc do ra don: ";
        in >> tdrd;
        cout << "Nhap loai phep: ";
        getline(in >> ws, loai);
        cout << "Nhap nang luong tieu hao moi lan: ";
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
        resetColor(); out << left << setw(18) << "Loai vu khi:" << setw(20) << "Phep Thuat";
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(18) << "Ten vu khi:" << setw(20) << p.getTenVuKhi();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(18) << "ST co ban:" << fixed << setprecision(2) << setw(20) << p.getSatThuongCoBan();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(18) << "Toc do ra don:" << fixed << setprecision(2) << setw(20) << p.getTocDoRaDon();
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(18) << "Loai phep:" << setw(20) << p.loaiPhep;
        setColor(MAU_CYAN); out << "|\n  | ";
        resetColor(); out << setw(18) << "NL tieu hao:" << setw(20) << p.nangLuongTieuHao;
        setColor(MAU_CYAN); out << "|\n  +---------------------------------------+";
        resetColor();
        return out;
    }

    // 4. virtual method
    void TanCong() override {
        setColor(MAU_TIM);
        cout << "  [Phep Thuat] Tung ra cac don ma thuat uy luc.\n";
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

void XoaBoDemNhap() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void HienThiDanhSachVK(const vector<VuKhi*>& ds) {
    if (ds.empty()) {
        InCanhBao("Danh sach vu khi dang rong.");
        return;
    }

    TieuDe("DANH SACH CAC LOAI VU KHI TRONG KHO", MAU_XANH_LA);

    setColor(MAU_DO);
    cout << "+====+============+====================+===========+===============+\n";
    cout << "|"; resetColor(); cout << left << setw(4) << "STT";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(12) << " Loai Vu Khi";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(20) << " Ten Vu Khi";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(11) << " ST Co Ban";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(15) << " Toc Do Ra Don";
    setColor(MAU_DO); cout << "|\n";
    cout << "+====+============+====================+===========+===============+\n";
    
    for (size_t i = 0; i < ds.size(); ++i) {
        setColor(MAU_DO); cout << "| "; resetColor(); cout << left << setw(3) << i + 1;
        
        if (ds[i] == nullptr) {
            setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(11) << "NULL";
            setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(19) << "Khong ton tai";
            setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(10) << "";
            setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(14) << "";
            setColor(MAU_DO); cout << "|\n";
            continue;
        }

        string loaiVK = "Khong Ro";
        if (dynamic_cast<const Kiem*>(ds[i])) loaiVK = "Kiem";
        else if (dynamic_cast<const Sung*>(ds[i])) loaiVK = "Sung";
        else if (dynamic_cast<const PhepThuat*>(ds[i])) loaiVK = "Phep Thuat";

        setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(11) << loaiVK;
        setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(19) << ds[i]->getTenVuKhi();
        setColor(MAU_DO); cout << "| "; resetColor(); cout << fixed << setprecision(2) << setw(10) << ds[i]->getSatThuongCoBan();
        setColor(MAU_DO); cout << "| "; resetColor(); cout << fixed << setprecision(2) << setw(14) << ds[i]->getTocDoRaDon();
        setColor(MAU_DO); cout << "|\n";
    }
    cout << "+====+============+====================+===========+===============+\n";
    resetColor();
}

void XemChiTietVuKhi(const vector<VuKhi*>& ds) {
    if (ds.empty()) {
        InCanhBao("Danh sach vu khi dang rong.");
        return;
    }

    HienThiDanhSachVK(ds);

    int chon = -1;
    while (true) {
        setColor(MAU_VANG);
        cout << "\nNhap STT vu khi de xem chi tiet (0 de quay lai): ";
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
                InLoi("Vu khi khong ton tai.");
                continue;
            }
            setColor(MAU_VANG);
            cout << " >> [Chi tiet Vu khi " << chon << "] <<\n";
            resetColor();
            if (const Kiem* k = dynamic_cast<const Kiem*>(ds[chon - 1])) {
                cout << *k << '\n';
            } else if (const Sung* s = dynamic_cast<const Sung*>(ds[chon - 1])) {
                cout << *s << '\n';
            } else if (const PhepThuat* p = dynamic_cast<const PhepThuat*>(ds[chon - 1])) {
                cout << *p << '\n';
            }
        } else {
            InLoi("STT khong hop le.");
        }
    }
}

/**
 * @brief Tạo vũ khí mới dựa trên lựa chọn của người dùng.
 */
VuKhi* TaoVuKhiTheoLuaChon() {
    int chon;

    setColor(MAU_XANH_DUONG);
    cout << "Chon loai vu khi:\n";
    cout << "1. Kiem\n";
    cout << "2. Sung\n";
    cout << "3. PhepThuat\n";
    resetColor();

    setColor(MAU_VANG);
    cout << "Nhap lua chon: ";
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
            InLoi("Lua chon khong hop le. Khong tao vu khi.");
            break;
    }

    return moi;
}

/**
 * @brief Thêm vũ khí mới vào kho.
 * @return Con trỏ vũ khí vừa được thêm vào kho.
 */
VuKhi* ThemVuKhi(vector<VuKhi*>& ds) {
    TieuDe("THEM VU KHI", MAU_VANG);
    VuKhi* vk = TaoVuKhiTheoLuaChon();

    if (vk == nullptr) {
        InLoi("Them vu khi that bai.");
        return nullptr;
    }

    ds.push_back(vk);
    InThongBao("Da them vu khi thanh cong.");
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
    cout << "Format: LOAI|tenVuKhi|satThuongCoBan|tocDoRaDon|thuocTinhRieng1|thuocTinhRieng2\n"; ;
    cout << "Nhap duong dan file txt: " ;
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

                    // soLuongDanTrongOng tu dong = soLuongDanToiDa (bang day khi tao)
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
                    InLoi("Loai vu khi khong hop le: " + loaiVuKhi);
                    continue;
                }
                InThongBao("Da them vu khi thanh cong.");
            }
            catch (...) {
                InLoi("Khong the nhap vu khi nay.");
                continue;
            }
        }
        InThongBao("Hoan tat them vu khi tu file.");
    }
    else {
        cout << duongDanFile << endl;
        InLoi("Duong dan khong ton tai.");
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
        InCanhBao("Danh sach vu khi rong.");
        return nullptr;
    }

    HienThiDanhSachVK(ds);

    int idx;
    setColor(MAU_VANG);
    cout << "Chon vu khi cho nhan vat (1-" << ds.size() << "): ";
    resetColor();
    cin >> idx;

    if (!cin || idx < 1 || idx > static_cast<int>(ds.size())) {
        XoaBoDemNhap();
        InLoi("Chi so vu khi khong hop le.");
        return nullptr;
    }

    if (ds[idx - 1] == nullptr) {
        InLoi("Vu khi khong ton tai.");
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
    cout << "Nhap ten nhan vat: ";
    getline(in >> ws, ten);
    cout << "Nhap mau: ";
    in >> mau;
    cout << "Nhap nang luong: ";
    in >> nangLuong;

    nv.setTenNhanVat(ten);
    nv.setMau(mau);
    nv.setNangLuong(nangLuong);
    nv.setVuKhi(nullptr);
    return in;
    }
    
    friend ostream& operator<<(ostream& out, NhanVat nv) {
        setColor(MAU_XANH_LA); out << "+=========================================+\n| ";
        resetColor(); out << left << setw(18) << "Ten nhan vat:" << setw(20) << nv.tenNhanVat;
        setColor(MAU_XANH_LA); out << "|\n| ";
        resetColor(); out << setw(18) << "Mau:" << fixed << setprecision(2) << setw(20) << nv.mau;
        setColor(MAU_XANH_LA); out << "|\n| ";
        resetColor(); out << setw(18) << "Nang luong:" << setw(20) << nv.nangLuong;
        setColor(MAU_XANH_LA); out << "|\n| ";
        resetColor(); out << setw(18) << "Trang thai:" << setw(20) << ((nv.mau > 0) ? "Con song" : "Da bi ha guc");
        setColor(MAU_XANH_LA); out << "|\n| ";
        resetColor(); out << setw(18) << "Vu khi:";
        
        if (nv.vk == nullptr) {
            out << setw(20) << "Khong co";
            setColor(MAU_XANH_LA); out << "|\n+=========================================+\n";
            resetColor();
            return out;
        } else {
            out << setw(20) << "";
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
            InLoi("  [!] " + tenNhanVat + " chua co vu khi de tan cong.");
            return;
        }
        if (mau <= 0) {
            InLoi("  [!] " + tenNhanVat + " da bi ha guc nen khong the tan cong.");
            return;
        }
        if (b.mau <= 0) {
            InLoi("  [!] " + b.tenNhanVat + " da bi ha guc.");
            return;
        }
        if (t <= 0) {
            InLoi("  [!] Thoi gian tan cong phai > 0.");
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
        cout << " gay ra ";
        setColor(MAU_DO);
        cout << fixed << setprecision(2) << satThuong;
        setColor(MAU_TRANG_SANG);
        cout << " sat thuong len ";
        setColor(MAU_XANH_DUONG);
        cout << b.tenNhanVat << "!\n\n";
        resetColor();
    }
};


// ========================= CAC HAM MENU =========================
void LamMoiManHinh() {
    system("cls");
}

void HienThiDanhSach(const vector<NhanVat>& ds) {
    if (ds.empty()) {
        InCanhBao("Danh sach nhan vat dang rong.");
        return;
    }

    TieuDe("DANH SACH NHAN VAT", MAU_XANH_LA);

    setColor(MAU_DO);
    cout << "+====+====================+========+========+====================+\n";
    cout << "|"; resetColor(); cout << left << setw(4) << "STT";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(20) << " Ten Nhan Vat";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(8) << " Mau";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(8) << " N.Luong";
    setColor(MAU_DO); cout << "|"; resetColor(); cout << setw(20) << " Vu Khi (Ten)";
    setColor(MAU_DO); cout << "|\n";
    cout << "+====+====================+========+========+====================+\n";
    
    for (size_t i = 0; i < ds.size(); ++i) {
        setColor(MAU_DO); cout << "| "; resetColor(); cout << left << setw(3) << i + 1;
        setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(19) << ds[i].getTenNhanVat();
        setColor(MAU_DO); cout << "| "; resetColor(); cout << fixed << setprecision(2) << setw(7) << ds[i].getMau();
        setColor(MAU_DO); cout << "| "; resetColor(); cout << setw(7) << ds[i].getNangLuong();
        setColor(MAU_DO); cout << "| "; resetColor(); 
        
        string tenVK = "Khong co";
        if (ds[i].getVuKhi() != nullptr) {
            tenVK = ds[i].getVuKhi()->getTenVuKhi();
        }
        cout << setw(19) << tenVK;
        setColor(MAU_DO); cout << "|\n";
    }
    cout << "+====+====================+========+========+====================+\n";
    resetColor();
}

void XemChiTietNhanVat(const vector<NhanVat>& ds) {
    if (ds.empty()) {
        InCanhBao("Danh sach nhan vat dang rong.");
        return;
    }

    HienThiDanhSach(ds);

    int chon = -1;
    while (true) {
        setColor(MAU_VANG);
        cout << "\nNhap STT nhan vat de xem chi tiet (0 de quay lai): ";
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
            cout << " >> [Chi tiet Nhan vat " << chon << "] <<\n";
            resetColor();
            cout << ds[chon - 1] << "\n";
        } else {
            InLoi("STT khong hop le.");
        }
    }
}

void TaoDuLieuMau(vector<NhanVat>& ds, vector<VuKhi*>& dsVK) {
    dsVK.push_back(new Kiem(12, "Excalibur", 18.5f, 1.0f));
    dsVK.push_back(new Sung(30, 2.5f, "M4A1", 7.5f, 0.2f));
    dsVK.push_back(new PhepThuat("Hoa cau", 15, "Truong lua", 25.0f, 1.5f));

    ds.push_back(NhanVat("Arthur", 250.0f, 80, SaoChepVuKhi(dsVK[0])));
    ds.push_back(NhanVat("Rambo", 220.0f, 60, SaoChepVuKhi(dsVK[1])));
    ds.push_back(NhanVat("Merlin", 180.0f, 120, SaoChepVuKhi(dsVK[2])));

    InThongBao("Da tao 3 nhan vat mau va 3 vu khi mau trong kho.");
}

void ThemNhanVat(vector<NhanVat>& ds) {
    TieuDe("THEM NHAN VAT", MAU_VANG);
    NhanVat nv;
    cin >> nv;
    ds.push_back(nv);
    InThongBao("Da them nhan vat thanh cong.");
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
        InCanhBao("Chua co nhan vat nao.");
        return;
    }

    HienThiDanhSach(ds);

    int idx, opt;
    VuKhi* moi;
    setColor(MAU_VANG);
    cout << "Chon chi so nhan vat can trang bi (1-" << ds.size() << "): ";
    resetColor();
    cin >> idx;

    if (idx < 1 || idx > static_cast<int>(ds.size())) {
        InLoi("Chi so khong hop le.");
        return;
    }

    cout << "1. Trang bi vu khi co san\n"
         << "2. Trang bi vu khi moi\n";
    
    cout << "Nhap lua chon: ";
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
            InLoi("Chi so khong hop le.");
            return;
    }

    if (moi == nullptr) {
        InLoi("Khong the trang bi vu khi.");
        return;
    }

    ds[idx - 1].TrangBi(moi);
}

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

void HienThiHaiNhanVatSongSong(const NhanVat& nv1, const NhanVat& nv2) {
    stringstream ss1, ss2;
    ss1 << nv1;
    ss2 << nv2;
    
    vector<string> lines1 = splitLines(ss1.str());
    vector<string> lines2 = splitLines(ss2.str());
    
    size_t maxLines = max(lines1.size(), lines2.size());
    
    setColor(MAU_VANG);
    cout << " >> [Nhan vat 1]" << string(31, ' ') << " >> [Nhan vat 2]\n";
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

void TanCong(vector<NhanVat>& ds) {
    if (ds.size() < 2) {
        InCanhBao("Can it nhat 2 nhan vat de mo phong tan cong.");
        return;
    }

    HienThiDanhSach(ds);

    int a, b;

    setColor(MAU_VANG);
    cout << "Chon nhan vat thu nhat (1-" << ds.size() << "): ";
    resetColor();
    cin >> a;

    setColor(MAU_VANG);
    cout << "Chon nhan vat thu hai (1-" << ds.size() << "): ";
    resetColor();
    cin >> b;

    if (!cin || a < 1 || a > static_cast<int>(ds.size()) ||
        b < 1 || b > static_cast<int>(ds.size()) || a == b) {
        XoaBoDemNhap();
        InLoi("Lua chon khong hop le.");
        return;
    }

    int luaChonTiepTuc = 1;

    while (luaChonTiepTuc == 1) {
        int t;

        setColor(MAU_VANG);
        cout << "Nhap thoi gian tan cong t: ";
        resetColor();
        cin >> t;

        if (!cin || t <= 0) {
            XoaBoDemNhap();
            InLoi("Thoi gian tan cong phai la so nguyen > 0.");
            continue;
        }

        TieuDe("KET QUA TAN CONG", MAU_DO);
        
        int turn = rand() % 2;
        if (turn == 0) {
            InThongBao(" -> " + ds[a - 1].getTenNhanVat() + " gianh duoc quyen tan cong truoc!");
            ds[a - 1].TanCongMucTieu(ds[b - 1], t);
            if (ds[b - 1].getMau() > 0) {
                ds[b - 1].TanCongMucTieu(ds[a - 1], t);
            }
        } else {
            InThongBao(" -> " + ds[b - 1].getTenNhanVat() + " gianh duoc quyen tan cong truoc!");
            ds[b - 1].TanCongMucTieu(ds[a - 1], t);
            if (ds[a - 1].getMau() > 0) {
                ds[a - 1].TanCongMucTieu(ds[b - 1], t);
            }
        }

        TieuDe("TRANG THAI SAU LUOT TAN CONG", MAU_XANH_LA);

        HienThiHaiNhanVatSongSong(ds[a - 1], ds[b - 1]);

        if (ds[a - 1].getMau() <= 0 && ds[b - 1].getMau() <= 0) {
            InThongBao("Ca hai nhan vat da bi ha guc. Ket thuc tran dau.");
            break;
        }
        if (ds[a - 1].getMau() <= 0) {
            InThongBao(ds[a - 1].getTenNhanVat() + " da bi ha guc. Ket thuc tran dau.");
            break;
        }
        if (ds[b - 1].getMau() <= 0) {
            InThongBao(ds[b - 1].getTenNhanVat() + " da bi ha guc. Ket thuc tran dau.");
            break;
        }

        setColor(MAU_VANG);
        cout << "1. Tan cong tiep\n0. Ket thuc tan cong\nLua chon: ";
        resetColor();
        cin >> luaChonTiepTuc;

        if (!cin) {
            XoaBoDemNhap();
            luaChonTiepTuc = 0;
        }
    }
}

void InMenu() {
    TieuDe("CHUONG TRINH QUAN LY NHAN VAT - VU KHI", MAU_TIM);

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
         << setw(6) << "0." << "Thoat\n";
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
            InLoi("Vui long nhap so hop le.");
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
                InThongBao("Tam biet!");
                break;
            default:
                InLoi("Lua chon khong hop le.");
        }

        if (luaChon != 0) {
            system("pause > nul");
            LamMoiManHinh();
        }

    } while (luaChon != 0);

    for (VuKhi* v : danhSachVK) delete v;
    danhSachVK.clear();

    return 0;
}

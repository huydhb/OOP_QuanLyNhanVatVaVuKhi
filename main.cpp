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

using namespace std;
void XoaBoDemNhap();
VuKhi* SaoChepVuKhi(const VuKhi* src);
// ========================= MAU CONSOLE =========================
enum MauChu {
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
    cout << s << '\n';
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
class VuKhi {
private:
    string tenVuKhi;
    float satThuongCoBan;
    float tocDoRaDon;

public:
    string getTenVuKhi() const;
    float getSatThuongCoBan() const;
    float getTocDoRaDon() const;

    void setTenVuKhi(string _TenVuKhi);
    void setSatThuongCoBan(float _SatThuongCoBan);
    void setTocDoRaDon(float _TocDoRaDon);

    VuKhi();
    VuKhi(string, float, float);
    VuKhi(const VuKhi&);
    virtual ~VuKhi();

    virtual void TanCong() = 0;
    virtual float SatThuong(int t) = 0;
};

string VuKhi::getTenVuKhi() const {
    return tenVuKhi;
}

float VuKhi::getSatThuongCoBan() const {
    return satThuongCoBan;
}

float VuKhi::getTocDoRaDon() const {
    return tocDoRaDon;
}

void VuKhi::setTenVuKhi(string _TenVuKhi) {
    tenVuKhi = _TenVuKhi;
}

void VuKhi::setSatThuongCoBan(float _SatThuongCoBan) {
    satThuongCoBan = (_SatThuongCoBan >= 0) ? _SatThuongCoBan : 0;
}

void VuKhi::setTocDoRaDon(float _TocDoRaDon) {
    tocDoRaDon = (_TocDoRaDon > 0) ? _TocDoRaDon : 1;
}

VuKhi::VuKhi() : tenVuKhi(""), satThuongCoBan(0), tocDoRaDon(1) {}

VuKhi::VuKhi(string tenVuKhi, float satThuongCoBan, float tocDoRaDon) {
    setTenVuKhi(tenVuKhi);
    setSatThuongCoBan(satThuongCoBan);
    setTocDoRaDon(tocDoRaDon);
}

VuKhi::VuKhi(const VuKhi& other) {
    tenVuKhi = other.tenVuKhi;
    satThuongCoBan = other.satThuongCoBan;
    tocDoRaDon = other.tocDoRaDon;
}

VuKhi::~VuKhi() {}

// ========================= LOP KIEM =========================
class Kiem : public VuKhi {
private:
    int doBen;

public:
    int getDoBen() const;
    void setDoBen(int _DoBen);

    Kiem();
    Kiem(int, string, float, float);
    Kiem(const Kiem&);

    friend istream& operator>>(istream& in, Kiem& k);
    friend ostream& operator<<(ostream& out, const Kiem& k);

    void TanCong() override;
    float SatThuong(int t) override;
};

int Kiem::getDoBen() const {
    return doBen;
}

void Kiem::setDoBen(int _DoBen) {
    doBen = (_DoBen >= 0) ? _DoBen : 0;
}

Kiem::Kiem() : VuKhi(), doBen(0) {}

Kiem::Kiem(int doBen, string tenVuKhi, float satThuongCoBan, float tocDoRaDon)
    : VuKhi(tenVuKhi, satThuongCoBan, tocDoRaDon) {
    setDoBen(doBen);
}

Kiem::Kiem(const Kiem& other) : VuKhi(other), doBen(other.doBen) {}

istream& operator>>(istream& in, Kiem& k) {
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

ostream& operator<<(ostream& out, const Kiem& k) {
    out << left
        << setw(18) << "Loai vu khi:" << "Kiem\n"
        << setw(18) << "Ten vu khi:" << k.getTenVuKhi() << '\n'
        << setw(18) << "ST co ban:" << fixed << setprecision(2) << k.getSatThuongCoBan() << '\n'
        << setw(18) << "Toc do ra don:" << fixed << setprecision(2) << k.getTocDoRaDon() << '\n'
        << setw(18) << "Do ben:" << k.doBen;
    return out;
}

void Kiem::TanCong() {
    cout << "[Kiem] Thuc hien mot chuoi chem bang kiem.\n";
}

float Kiem::SatThuong(int t) {
    if (getTocDoRaDon() <= 0 || t <= 0 || doBen <= 0) return 0;

    int soLanChemTheoThoiGian = static_cast<int>(floor(t / getTocDoRaDon()));
    int soLanChem = min(doBen, soLanChemTheoThoiGian);
    float satThuong = soLanChem * getSatThuongCoBan();
    doBen -= soLanChem;
    return satThuong;
}

// ========================= LOP SUNG =========================
class Sung : public VuKhi {
private:
    int soLuongDanTrongOng;
    float tocDoThayBang;

public:
    int getSoLuongDanTrongOng() const;
    float getTocDoThayBang() const;
    void setSoLuongDanTrongOng(int _SoLuongDanTrongOng);
    void setTocDoThayBang(float _TocDoThayBang);

    Sung();
    Sung(int, float, string, float, float);
    Sung(const Sung&);

    friend istream& operator>>(istream& in, Sung& s);
    friend ostream& operator<<(ostream& out, const Sung& s);

    void TanCong() override;
    float SatThuong(int t) override;
};

int Sung::getSoLuongDanTrongOng() const {
    return soLuongDanTrongOng;
}

float Sung::getTocDoThayBang() const {
    return tocDoThayBang;
}

void Sung::setSoLuongDanTrongOng(int _SoLuongDanTrongOng) {
    soLuongDanTrongOng = (_SoLuongDanTrongOng >= 0) ? _SoLuongDanTrongOng : 0;
}

void Sung::setTocDoThayBang(float _TocDoThayBang) {
    tocDoThayBang = (_TocDoThayBang >= 0) ? _TocDoThayBang : 0;
}

Sung::Sung() : VuKhi(), soLuongDanTrongOng(0), tocDoThayBang(0) {}

Sung::Sung(int soLuongDanTrongOng, float tocDoThayBang, string tenVuKhi, float satThuongCoBan, float tocDoRaDon)
    : VuKhi(tenVuKhi, satThuongCoBan, tocDoRaDon) {
    setSoLuongDanTrongOng(soLuongDanTrongOng);
    setTocDoThayBang(tocDoThayBang);
}

Sung::Sung(const Sung& other)
    : VuKhi(other), soLuongDanTrongOng(other.soLuongDanTrongOng), tocDoThayBang(other.tocDoThayBang) {}

istream& operator>>(istream& in, Sung& s) {
    string ten;
    float stcb, tdrd, tdthay;
    int slDan;

    cout << "Nhap ten sung: ";
    getline(in >> ws, ten);
    cout << "Nhap sat thuong co ban: ";
    in >> stcb;
    cout << "Nhap toc do ra don: ";
    in >> tdrd;
    cout << "Nhap so luong dan trong ong: ";
    in >> slDan;
    cout << "Nhap toc do thay bang: ";
    in >> tdthay;

    s.setTenVuKhi(ten);
    s.setSatThuongCoBan(stcb);
    s.setTocDoRaDon(tdrd);
    s.setSoLuongDanTrongOng(slDan);
    s.setTocDoThayBang(tdthay);
    return in;
}

ostream& operator<<(ostream& out, const Sung& s) {
    out << left
        << setw(22) << "Loai vu khi:" << "Sung\n"
        << setw(22) << "Ten vu khi:" << s.getTenVuKhi() << '\n'
        << setw(22) << "ST co ban:" << fixed << setprecision(2) << s.getSatThuongCoBan() << '\n'
        << setw(22) << "Toc do ra don:" << fixed << setprecision(2) << s.getTocDoRaDon() << '\n'
        << setw(22) << "Dan trong ong:" << s.soLuongDanTrongOng << '\n'
        << setw(22) << "Toc do thay bang:" << fixed << setprecision(2) << s.tocDoThayBang;
    return out;
}

void Sung::TanCong() {
    cout << "[Sung] Nha dan vao muc tieu.\n";
}

float Sung::SatThuong(int t) {
    if (getTocDoRaDon() <= 0 || t <= 0 || soLuongDanTrongOng <= 0) return 0;

    float thoiGianBanHet1Bang = soLuongDanTrongOng * getTocDoRaDon();
    float chuKy = thoiGianBanHet1Bang + tocDoThayBang;
    if (chuKy <= 0) return 0;

    int soChuKy = static_cast<int>(floor(t / chuKy));
    float thoiGianDu = t - soChuKy * chuKy;
    int soVienBanThem = min(soLuongDanTrongOng,
                            static_cast<int>(floor(thoiGianDu / getTocDoRaDon())));
    int tongDan = soChuKy * soLuongDanTrongOng + soVienBanThem;
    return tongDan * getSatThuongCoBan();
}

// ========================= LOP PHEPTHUAT =========================
class PhepThuat : public VuKhi {
private:
    string loaiPhep;
    int nangLuongTieuHao;

public:
    string getLoaiPhep() const;
    int getNangLuongTieuHao() const;
    void setLoaiPhep(string _LoaiPhep);
    void setNangLuongTieuHao(int _NangLuongTieuHao);

    PhepThuat();
    PhepThuat(string, int, string, float, float);
    PhepThuat(const PhepThuat&);
    ~PhepThuat();

    friend istream& operator>>(istream& in, PhepThuat& p);
    friend ostream& operator<<(ostream& out, const PhepThuat& p);

    void TanCong() override;
    float SatThuong(int t) override;
};

string PhepThuat::getLoaiPhep() const {
    return loaiPhep;
}

int PhepThuat::getNangLuongTieuHao() const {
    return nangLuongTieuHao;
}

void PhepThuat::setLoaiPhep(string _LoaiPhep) {
    loaiPhep = _LoaiPhep;
}

void PhepThuat::setNangLuongTieuHao(int _NangLuongTieuHao) {
    nangLuongTieuHao = (_NangLuongTieuHao >= 0) ? _NangLuongTieuHao : 0;
}

PhepThuat::PhepThuat() : VuKhi(), loaiPhep(""), nangLuongTieuHao(0) {}

PhepThuat::PhepThuat(string loaiPhep, int nangLuongTieuHao, string tenVuKhi, float satThuongCoBan, float tocDoRaDon)
    : VuKhi(tenVuKhi, satThuongCoBan, tocDoRaDon) {
    setLoaiPhep(loaiPhep);
    setNangLuongTieuHao(nangLuongTieuHao);
}

PhepThuat::PhepThuat(const PhepThuat& other)
    : VuKhi(other), loaiPhep(other.loaiPhep), nangLuongTieuHao(other.nangLuongTieuHao) {}

PhepThuat::~PhepThuat() {}

istream& operator>>(istream& in, PhepThuat& p) {
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

ostream& operator<<(ostream& out, const PhepThuat& p) {
    out << left
        << setw(24) << "Loai vu khi:" << "PhepThuat\n"
        << setw(24) << "Ten vu khi:" << p.getTenVuKhi() << '\n'
        << setw(24) << "ST co ban:" << fixed << setprecision(2) << p.getSatThuongCoBan() << '\n'
        << setw(24) << "Toc do ra don:" << fixed << setprecision(2) << p.getTocDoRaDon() << '\n'
        << setw(24) << "Loai phep:" << p.loaiPhep << '\n'
        << setw(24) << "NL tieu hao:" << p.nangLuongTieuHao;
    return out;
}

void PhepThuat::TanCong() {
    cout << "[PhepThuat] Tung ra mot loat phep thuat.\n";
}

float PhepThuat::SatThuong(int t) {
    if (getTocDoRaDon() <= 0 || t <= 0) return 0;

    int soLanRaPhepTheoThoiGian = static_cast<int>(floor(t / getTocDoRaDon()));
    return soLanRaPhepTheoThoiGian * getSatThuongCoBan();
}

// ========================= CAC HAM KHOI TAO VA HIEN THI VA TRANG BI VU KHI =========================
void HienThiDanhSachVK(const vector<VuKhi*>& ds) {
    if (ds.empty()) {
        InCanhBao("Danh sach vu khi dang rong.");
        return;
    }

    TieuDe("DANH SACH CAC LOAI VU KHI TRONG KHO", MAU_XANH_LA);

    for (size_t i = 0; i < ds.size(); ++i) {
        setColor(MAU_TRANG_SANG);
        cout << "[Vu Khi " << i + 1 << "]\n";
        resetColor();

        if (ds[i] == nullptr) {
            cout << "Vu khi khong ton tai.\n";
        }
        else if (const Kiem* k = dynamic_cast<const Kiem*>(ds[i])) {
            cout << *k << '\n';
        }
        else if (const Sung* s = dynamic_cast<const Sung*>(ds[i])) {
            cout << *s << '\n';
        }
        else if (const PhepThuat* p = dynamic_cast<const PhepThuat*>(ds[i])) {
            cout << *p << '\n';
        }

        setColor(MAU_XANH_DUONG);
        cout << "------------------------------------------------------------\n";
        resetColor();
    }
}

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

VuKhi* ThemVuKhi(vector<VuKhi*>& ds) {
    TieuDe("THEM VU KHI", MAU_VANG);
    VuKhi* vk = TaoVuKhiTheoLuaChon();

    if (vk == nullptr) {
        InLoi("Them vu khi that bai.");
        return nullptr;
    }

    ds.push_back(vk);
    InThongBao("Da them vu khi thanh cong.");
    return vk; // tra ve con tro trong kho
}

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
                    string soLuongDanTrongOngSTR, tocDoThayBangSTR;
                    int soLuongDanTrongOng;
                    float tocDoThayBang;
                    getline(ss, soLuongDanTrongOngSTR, '|');
                    getline(ss, tocDoThayBangSTR, '|');
                    soLuongDanTrongOng = stoi(soLuongDanTrongOngSTR);
                    tocDoThayBang = stof(tocDoThayBangSTR);

                    Sung* vk = new Sung(soLuongDanTrongOng, tocDoThayBang, tenVuKhi, satThuongCoBan, tocDoRaDon);
                    VuKhi* moi = vk;
                    ds.push_back(moi);
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
class NhanVat {
private:
    string tenNhanVat;
    float mau;
    int nangLuong;
    VuKhi* vk;

public:
    string getTenNhanVat() const;
    float getMau() const;
    int getNangLuong() const;
    VuKhi* getVuKhi() const;

    void setTenNhanVat(string _tenNhanVat);
    void setMau(float _mau);
    void setNangLuong(int _nangLuong);
    void setVuKhi(VuKhi* _vk);

    NhanVat();
    NhanVat(string, float, int, VuKhi*);
    NhanVat(const NhanVat&);
    ~NhanVat();

    friend istream& operator>>(istream& in, NhanVat& nv);
    friend ostream& operator<<(ostream& out, const NhanVat& nv);

    void TrangBi(VuKhi* v);
    void NhanSatThuong(float st);
    void TanCongMucTieu(NhanVat& b, int t);
};

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

string NhanVat::getTenNhanVat() const {
    return tenNhanVat;
}

float NhanVat::getMau() const {
    return mau;
}

int NhanVat::getNangLuong() const {
    return nangLuong;
}

VuKhi* NhanVat::getVuKhi() const {
    return vk;
}

void NhanVat::setTenNhanVat(string _tenNhanVat) {
    tenNhanVat = _tenNhanVat;
}

void NhanVat::setMau(float _mau) {
    mau = (_mau >= 0) ? _mau : 0;
}

void NhanVat::setNangLuong(int _nangLuong) {
    nangLuong = (_nangLuong >= 0) ? _nangLuong : 0;
}

void NhanVat::setVuKhi(VuKhi* _vk) {
    if (vk != _vk) {
        delete vk;
        vk = _vk;
    }
}

NhanVat::NhanVat() : tenNhanVat(""), mau(0), nangLuong(0), vk(nullptr) {}

NhanVat::NhanVat(string tenNhanVat, float mau, int nangLuong, VuKhi* vk)
    : tenNhanVat(tenNhanVat), mau((mau >= 0) ? mau : 0), nangLuong((nangLuong >= 0) ? nangLuong : 0), vk(vk) {}

NhanVat::NhanVat(const NhanVat& other)
    : tenNhanVat(other.tenNhanVat), mau(other.mau), nangLuong(other.nangLuong), vk(SaoChepVuKhi(other.vk)) {}

NhanVat::~NhanVat() {
    delete vk;
    vk = nullptr;
}

istream& operator>>(istream& in, NhanVat& nv) {
    string ten;
    float mau;
    int nangLuong;
    int luaChon;

    cout << "Nhap ten nhan vat: ";
    getline(in >> ws, ten);
    cout << "Nhap mau: ";
    in >> mau;
    cout << "Nhap nang luong: ";
    in >> nangLuong;

    nv.setTenNhanVat(ten);
    nv.setMau(mau);
    nv.setNangLuong(nangLuong);
    return in;
}

ostream& operator<<(ostream& out, const NhanVat& nv) {
    out << left
        << setw(18) << "Ten nhan vat:" << nv.tenNhanVat << '\n'
        << setw(18) << "Mau:" << fixed << setprecision(2) << nv.mau << '\n'
        << setw(18) << "Nang luong:" << nv.nangLuong << '\n'
        << setw(18) << "Trang thai:" << ((nv.mau > 0) ? "Con song" : "Da bi ha guc") << '\n';

    out << setw(18) << "Vu khi:";
    if (nv.vk == nullptr) {
        out << "Khong co\n";
        return out;
    }

    out << '\n';
    if (const Kiem* k = dynamic_cast<const Kiem*>(nv.vk)) {
        out << *k << '\n';
    } else if (const Sung* s = dynamic_cast<const Sung*>(nv.vk)) {
        out << *s << '\n';
    } else if (const PhepThuat* p = dynamic_cast<const PhepThuat*>(nv.vk)) {
        out << *p << '\n';
    }
    return out;
}

void NhanVat::TrangBi(VuKhi* v) {
    setVuKhi(v);
}

void NhanVat::NhanSatThuong(float st) {
    if (st < 0) st = 0;
    mau -= st;
    if (mau < 0) {
        mau = 0;
    }
}

void NhanVat::TanCongMucTieu(NhanVat& b, int t) {
    if (vk == nullptr) {
        cout << tenNhanVat << " chua co vu khi de tan cong.\n";
        return;
    }
    if (mau <= 0) {
        cout << tenNhanVat << " da bi ha guc nen khong the tan cong.\n";
        return;
    }
    if (b.mau <= 0) {
        cout << b.tenNhanVat << " da bi ha guc.\n";
        return;
    }
    if (t <= 0) {
        cout << "Thoi gian tan cong phai > 0.\n";
        return;
    }

    float satThuong = 0;

    // Xu ly rieng cho PhepThuat vi cong thuc UML can nang luong cua NhanVat
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

    cout << tenNhanVat << " gay ra " << fixed << setprecision(2) << satThuong
         << " sat thuong len " << b.tenNhanVat << ".\n";
}

// ========================= CAC HAM MENU =========================
void LamMoiManHinh() {
    system("cls");
}

void XoaBoDemNhap() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void HienThiDanhSach(const vector<NhanVat>& ds) {
    if (ds.empty()) {
        InCanhBao("Danh sach nhan vat dang rong.");
        return;
    }

    TieuDe("DANH SACH NHAN VAT", MAU_XANH_LA);

    for (size_t i = 0; i < ds.size(); ++i) {
        setColor(MAU_TRANG_SANG);
        cout << "[Nhan vat " << i + 1 << "]\n";
        resetColor();

        cout << ds[i] << '\n';

        setColor(MAU_XANH_DUONG);
        cout << "------------------------------------------------------------\n";
        resetColor();
    }
}

void TaoDuLieuMau(vector<NhanVat>& ds, vector<VuKhi*>& dsVK) {
    // Tao vu khi mau trong kho
    dsVK.push_back(new Kiem(12, "Excalibur", 18.5f, 1.0f));
    dsVK.push_back(new Sung(30, 2.5f, "M4A1", 7.5f, 0.2f));
    dsVK.push_back(new PhepThuat("Hoa cau", 15, "Truong lua", 25.0f, 1.5f));

    // Nhan vat dung BAN SAO cua vu khi trong kho
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
    
    cin >> opt;
    switch (opt) {
        case 1:
            moi = ChonVuKhiTuDanhSach(dsVK); // ban sao
            break;
        case 2: {
            VuKhi* vkKho = ThemVuKhi(dsVK);  // them vao kho
            moi = SaoChepVuKhi(vkKho);       // nhan vat giu ban sao
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

void TanCong(vector<NhanVat>& ds) {
    if (ds.size() < 2) {
        InCanhBao("Can it nhat 2 nhan vat de mo phong tan cong.");
        return;
    }

    HienThiDanhSach(ds);

    int a, b, t;

    setColor(MAU_VANG);
    cout << "Chon nhan vat tan cong (1-" << ds.size() << "): ";
    resetColor();
    cin >> a;

    setColor(MAU_VANG);
    cout << "Chon muc tieu (1-" << ds.size() << "): ";
    resetColor();
    cin >> b;

    setColor(MAU_VANG);
    cout << "Nhap thoi gian tan cong t: ";
    resetColor();
    cin >> t;

    if (a < 1 || a > static_cast<int>(ds.size()) ||
        b < 1 || b > static_cast<int>(ds.size()) || a == b) {
        InLoi("Lua chon khong hop le.");
        return;
    }

    TieuDe("KET QUA TAN CONG", MAU_DO);
    ds[a - 1].TanCongMucTieu(ds[b - 1], t);
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
                HienThiDanhSach(danhSach);
                break;
            case 6:
                HienThiDanhSachVK(danhSachVK);
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

    return 0;
}

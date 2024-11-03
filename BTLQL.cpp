#include <bits/stdc++.h>
using namespace std;
class Cay {
    string id;
    string tenCay;
    int tuoiCay;
    float chieuCao; // don vi: m
    string tinhTrang;
public:
    Cay(string e = " ", string a = "",  int c = 0, float d = 0, string f = "")
        : id(e), tenCay(a), tuoiCay(c), chieuCao(d), tinhTrang(f) {}
    friend istream& operator>>(istream& is, Cay& ele) {
        cout << "Nhap id: "; is >> ele.id;
        cout << "Nhap ten cay: "; is >> ws; getline(is, ele.tenCay);
        cout << "Nhap tuoi cay: "; is >> ele.tuoiCay;
        cout << "Nhap chieu cao (m): "; is >> ele.chieuCao;
        cout << "Nhap tinh trang cay: "; is >> ws; getline(is, ele.tinhTrang);
        return is;
    }
    friend ostream& operator<<(ostream& os, const Cay& ele) {
        os << "ID: " << ele.id << ", Ten cay: " << ele.tenCay 
           << ", Tuoi cay: " << ele.tuoiCay << ", Chieu cao: " << fixed << setprecision(2) << ele.chieuCao
           << " m, Tinh trang: " << ele.tinhTrang;
        return os;
    }
    void capNhatCay(const string& tenCayMoi, int tuoiCayMoi, float chieuCaoMoi, const string& tinhTrangMoi) {
        tenCay = tenCayMoi;
        tuoiCay = tuoiCayMoi;
        chieuCao = chieuCaoMoi;
        tinhTrang = tinhTrangMoi;
    }
    //So sanh tuoi cay
    bool operator>(const Cay& a)  {
        return tuoiCay > a.tuoiCay;
    }
    string getId() const { return id; }
    float getChieuCao() const { return chieuCao; }
    string getTenCay() const { return tenCay; }
    int getTuoiCay() const { return tuoiCay; }
    string getTinhTrang() const { return tinhTrang; }
};
class DanhSachCay {
    list<Cay> danhSach;
	public:
    	void themCay(const Cay& c) { danhSach.push_back(c); }
    	void xoaCay(const string& tenCay) {
        	danhSach.remove_if([&tenCay](const Cay& c) { return c.getTenCay() == tenCay; });
    	}
    	bool capNhatCayCoId(const string& id, const string& tenCayMoi, int tuoiCayMoi, float chieuCaoMoi, const string& tinhTrangMoi) {
        	for (auto& cay : danhSach) {
           	 if (cay.getId() == id) {
                	cay.capNhatCay(tenCayMoi, tuoiCayMoi, chieuCaoMoi, tinhTrangMoi);
                	return true;
            	}
        	}
        	return false;
    	}
    	void xuatDanhSach() const {
        	for (const auto& c : danhSach) cout << c << endl;
    	}
    	void xuatDanhSach(const list<Cay>& ds) const {
        	for (const auto& c : ds) {
            	cout << c << endl;
        	}
    	}
    	void sapXep(const string& tieuChi) {
        	if (tieuChi == "tuoi") {
            	danhSach.sort([](const Cay& a, const Cay& b) { return a.getTuoiCay() < b.getTuoiCay(); });
        	} else if (tieuChi == "chieuCao") {
            	danhSach.sort([](const Cay& a, const Cay& b) { return a.getChieuCao() < b.getChieuCao(); });
        	} else {
            	cout << "Tieu chi sap xep khong hop le! Vui long chon: 'tuoi', 'chieuCao', hoac 'soCay'.\n";
        	}	
    	}
    	Cay timCayMin(const string& tieuChi) const {
        	if (danhSach.empty()) return Cay(); // Handle empty list
        	auto it = danhSach.begin();
        	if (tieuChi == "tuoi") {
            	it = min_element(danhSach.begin(), danhSach.end(), [](const Cay& a, const Cay& b) { return a.getTuoiCay() < b.getTuoiCay(); });
        	} else if (tieuChi == "chieuCao") {
            	it = min_element(danhSach.begin(), danhSach.end(), [](const Cay& a, const Cay& b) { return a.getChieuCao() < b.getChieuCao(); });
        	} 
        	return (it != danhSach.end()) ? *it : Cay();
    	}
    	Cay timCayMax(const string& tieuChi) const {
        	if (danhSach.empty()) throw invalid_argument("Danh sach rong.");
        	if (tieuChi == "tuoi") {
            	return *max_element(danhSach.begin(), danhSach.end(), [](const Cay& a, const Cay& b) { return a.getTuoiCay() < b.getTuoiCay(); });
        	} else if (tieuChi == "chieuCao") {
            	return *max_element(danhSach.begin(), danhSach.end(), [](const Cay& a, const Cay& b) { return a.getChieuCao() < b.getChieuCao(); });
        	} else {
            	throw invalid_argument("Tieu chi khong hop le. Vui long chon: 'tuoi', 'chieuCao', hoac 'soCay'.");
        	}
    	}
    	Cay timCayTheoId(const string& id) const {
        	for (const auto& cay : danhSach) {
            	if (cay.getId() == id) {
                	return cay;
            	}
        	}
        	cout << "Khong tim thay cay co id: " << id;
    	}
    	void locCayTheoTieuChi() {
        	list<Cay> ketQua = danhSach;
        	string luaChon;
        	while (ketQua.size() > 1) {
            	cout << "\nDanh sach hien tai:\n";
            	xuatDanhSach(ketQua);
            	cout << "\nBan muon loc theo tieu chi nao?\n";
            	cout << "1. Ten cay\n2. Tuoi\n3. Chieu cao\n4. Tinh trang\n5. Dung loc\n";
            	cout << "Nhap lua chon: ";
            	cin >> luaChon;
            	if (luaChon == "1") {
                	string tenCay;
                	cout << "Nhap ten cay: ";
                	cin >> ws; getline(cin, tenCay);
                	ketQua.remove_if([&tenCay](const Cay& c) { return c.getTenCay() != tenCay; });
           		} else if (luaChon == "2") {
                	int tuoi;
                	cout << "Nhap tuoi cay: ";
                	cin >> tuoi;
                	ketQua.remove_if([&tuoi](const Cay& c) { return c.getTuoiCay() != tuoi; });
            	} else if (luaChon == "3") {
                	float chieuCao;
                	cout << "Nhap chieu cao cay (m): ";
                	cin >> chieuCao;
                	ketQua.remove_if([&chieuCao](const Cay& c) { return abs(c.getChieuCao() - chieuCao) > 0.01; }); // Using an epsilon for floating point comparison
            	} else if (luaChon == "4") {
                	string tinhTrang;
                	cout << "Nhap tinh trang cay: ";
                	cin >> ws; getline(cin, tinhTrang);
                	ketQua.remove_if([&tinhTrang](const Cay& c) { return c.getTinhTrang() != tinhTrang; });
            	} else if (luaChon == "5") {
                	break;
            	} else {
                	cout << "Lua chon khong hop le, vui long thu lai!\n";
            	}
            	if (ketQua.empty()) {
                	cout << "Khong co cay nao thoa man cac tieu chi vua nhap.\n";
                	return;
        		}
        	}	
        	cout << "\nKet qua loc:\n";
        	xuatDanhSach(ketQua);
    	}
};
class App {
    DanhSachCay danhSachCay;
public:
    void run() {
        int luaChon;
        while (1) {
            cout << "\n=== CHUONG TRINH QUAN LY CAY UTC ===\n";
            cout << "Chuong trinh gom:\n1. Them cay\n2. Xoa cay\n3. Cap nhat cay\n4. Xuat danh sach cay\n"
           	<< "5. Sap xep danh sach cay\n6. Tim cay\n0. Thoat\n";
            cout << "Nhap lua chon: ";
            cin >> luaChon;
            switch (luaChon) {
                case 1: {
                    Cay cay;
                    cin >> cay;
                    danhSachCay.themCay(cay);
                    break;
                }
                case 2: {
                    string tenCay;
                    cout << "Nhap ten cay can xoa: ";
                    cin >> ws;
                    getline(cin, tenCay);
                    danhSachCay.xoaCay(tenCay);
                    break;
                }
                case 3: {
                    string id, tenCayMoi, tinhTrangMoi;
                    int soCayMoi, tuoiCayMoi;
                    float chieuCaoMoi;
                    cout << "Nhap id cay can cap nhat: ";
                    cin >> id;
                    cout << "Nhap ten cay moi: ";
                    cin >> ws;
                    getline(cin, tenCayMoi);
                    cout << "Nhap tuoi cay moi: ";
                    cin >> tuoiCayMoi;
                    cout << "Nhap chieu cao moi (m): ";
                    cin >> chieuCaoMoi;
                    cout << "Nhap tinh trang moi: ";
                    cin >> ws;
                    getline(cin, tinhTrangMoi);
                    if (danhSachCay.capNhatCayCoId(id, tenCayMoi,  tuoiCayMoi, chieuCaoMoi, tinhTrangMoi)) {
                        cout << "Cap nhat thanh cong!\n";
                    } else {
                        cout << "Khong tim thay cay voi id: " << id << endl;
                    }
                    break;
                }
                case 4:
                    danhSachCay.xuatDanhSach();
                    break;
                case 5: {
                    string tieuChi;
                    cout << "Nhap tieu chi sap xep (tuoi, chieuCao): ";
                    cin >> tieuChi;
                    danhSachCay.sapXep(tieuChi);
                    cout << "Da sap xep tang dan theo tieu chi!\n";
                    break;
                }
                case 6: {
                    int subChoice;
                    cout << "Ban muon tim cay theo:\n1. Id\n2. Max\n3. Min\n4. Tieu chi\n0. Thoat\n";
                    cout << "Nhap lua chon: ";
                    cin >> subChoice;
                    switch (subChoice) {
                        case 1: {
                            string id;
                            cout << "Nhap id cay: ";
                            cin >> id;
                            Cay foundCay = danhSachCay.timCayTheoId(id);
                            cout << "Cay tim thay: " << foundCay << endl;
                            break;
                        }
                        case 2: {
                            string tieuChi;
                            cout << "Nhap tieu chi tim cay max (tuoi, chieuCao): ";
                            cin >> tieuChi;
                            try {
                                Cay maxCay = danhSachCay.timCayMax(tieuChi);
                                cout << "Cay max: " << maxCay << endl;
                            } catch (const invalid_argument& e) {
                                cout << e.what() << endl;
                            }
                            break;
                        }
                        case 3: {
                            string tieuChi;
                            cout << "Nhap tieu chi tim cay min (tuoi, chieuCao): ";
                            cin >> tieuChi;
                            try {
                                Cay minCay = danhSachCay.timCayMin(tieuChi);
                                cout << "Cay min: " << minCay << endl;
                            } catch (const invalid_argument& e) {
                                cout << e.what() << endl;
                            }
                            break;
                        }
                        case 4:
                            danhSachCay.locCayTheoTieuChi();
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Lua chon khong hop le trong tim cay, vui long thu lai!\n";
                    }
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Lua chon khong hop le, vui long thu lai!\n";
            }
        }
    }
};
main() {
    App app;
    app.run();
}


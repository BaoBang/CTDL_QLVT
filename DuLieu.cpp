#include "GiaoDien.cpp"

#define MAX_LIST 100
#define MAX_VAT_TU 100


using namespace std;
// vat tu
struct VatTu{
	string MAVT;
	string TENVT;
	string DVT;
	int SOLUONGTON;
};
struct DanhSachVatTu{
	int N;
	VatTu NODE[MAX_LIST];
};

//chi tiet hoa don
struct CT_HoaDon{
	string MAVT;
	int SOLUONG;
	int DONGIA;
	int VAT;
};

struct NodeCTHoaDon{
	CT_HoaDon CTHOADON;
	NodeCTHoaDon *NEXT;
};

typedef NodeCTHoaDon * DSCTHOADONPTR;

// hoa don
struct HoaDon{
	string SOHD;
	Date NGAYLAP = layGioHeThong();
	char LOAI = 'N';
	DSCTHOADONPTR DSCTHOADON = NULL;
};

struct NodeHoaDon{
	HoaDon HOADON;
	NodeHoaDon *NEXT;
};

typedef struct NodeHoaDon* HOADONPTR;

//Nhan vien
struct NhanVien{
	string MANV="";
	string HO="";
	string TEN="";
	bool PHAI= true;
	HOADONPTR DS_HOADON = NULL;
};

// cay nhan vien
struct NodeNhanVienTree{
	NhanVien NHANVIEN;
	NodeNhanVienTree* LEFT;
	NodeNhanVienTree* RIGHT;
};

typedef struct NodeNhanVienTree* NHANVIENTREE;

/////Stack la danh sach DSLK don
// moi node thong la mot cay nhan vien
struct NodeNhanVienDSLK{
	NHANVIENTREE NODE;
	NodeNhanVienDSLK * NEXT;
};

typedef struct NodeNhanVienDSLK* Stack;

// CAC HAM CHUC NANG CUA VAT TU

// Kiem Tra Danh Sach Rong : empty = true
bool kiemTraRong(DanhSachVatTu dsVatTu) ;
// Kiem Tra Danh Sach day: full=true
bool kiemTraDay(DanhSachVatTu dsVatTu) ;
// Tim kiem Vat Tu trong Danh Sach theo MaVT
int timKiemVatTu(DanhSachVatTu dsVatTu, string maVT);
// Tim vi tri thich hop de them vao Danh Sach voi thu tu tang dan theo MaVT 
int timViTriThichHop(DanhSachVatTu dsVatTu, string maVT);
// Them Vat Tu vao vi tri Thu index. Thanh cong: true
bool themVatTuVaoViTri_index(DanhSachVatTu &dsVatTu, VatTu vatTu, int index);
// Them Vat Tu co Sap Xep theo thu tu tang dan MaVT
bool themSapXepVatTu(DanhSachVatTu &dsVatTu, VatTu vatTu);
// Xoa Vat Tu theo vi tri thu index. Xoa thanh cong: true
bool xoaVatTuTheoViTri(DanhSachVatTu &dsVatTu, int index);
// Luu Danh sach Vat tu vao file VatTu.txt
void luuDanhSachVatTuVaoFile(DanhSachVatTu &dsVatTu);

// Nap Danh Sach Vat Tu tu file "VatTu.txt" vao bo nho
void napDanhSachVatTuTuFile(DanhSachVatTu &dsVatTu);

// Tra ve tong so trang trong Bang Danh sach Vat tu
int tongSoTrangVatTu(DanhSachVatTu &dsVatTu);

// CAC HAM CHUC NANG CUA NHAN VIEN
bool push(Stack &sp, NHANVIENTREE p);
bool pop(Stack &sp, NHANVIENTREE &p);

bool kiemTraRong(HOADONPTR first);
// insert_first
bool themVaoDauDanhSach(HOADONPTR &first, HoaDon hd );
// insert_last
bool themVaoCuoiDanhSach(HOADONPTR &first, HoaDon hd );
// insert_after
bool themVaoSauMotNode(HOADONPTR &first, HOADONPTR p, HoaDon hd);
//	delete_first
bool xoaNodeDauDanhSach(HOADONPTR &first);
// delete_after
bool xoaSauNode(HOADONPTR &first, HOADONPTR p);
// delete_info
bool xoaNode_info(HOADONPTR &first, HoaDon hd);
void duyetDanhSach(HOADONPTR first);
int demSoHoaDon(HOADONPTR dsHoaDon);
HOADONPTR timKiemHoaDon(HOADONPTR dsHoaDon, string soHoaDon);
int timKiemViTriHoaDon(HOADONPTR dsHoaDon, string soHoaDon);
HOADONPTR timKiemHoaDonThuN(HOADONPTR dsHoaDon, int viTri);

// CAC HAM CHUC NANG CUA HOA DON
bool kiemTraRong(HOADONPTR first);
// insert_first
bool themVaoDauDanhSach(HOADONPTR &first, HoaDon hd );
// insert_last
bool themVaoCuoiDanhSach(HOADONPTR &first, HoaDon hd );
// insert_after
bool themVaoSauMotNode(HOADONPTR &first, HOADONPTR p, HoaDon hd);
// isert_order
bool themSapXep(HOADONPTR &first, HoaDon hoaDon);
//	delete_first
bool xoaNodeDauDanhSach(HOADONPTR &first);
// delete_after
bool xoaSauNode(HOADONPTR &first, HOADONPTR p);
// delete_info
bool xoaNode_info(HOADONPTR &first, HoaDon hd);
void duyetDanhSach(HOADONPTR first);
int demSoHoaDon(HOADONPTR dsHoaDon);
HOADONPTR timKiemHoaDon(HOADONPTR dsHoaDon, string soHoaDon);
int timKiemViTriHoaDon(HOADONPTR dsHoaDon, string soHoaDon);
HOADONPTR timKiemHoaDonThuN(HOADONPTR dsHoaDon, int viTri);
void formHoaDon(NhanVien &nv, HoaDon hoaDon, string chucNang);
void xuatHoaDonLenForm(HoaDon hoaDon, string ngayStr, string thangStr, string namStr);
// CAC HAM CHUC NANG CUA CHI TIET HOA DON
bool kiemTraRong(DSCTHOADONPTR first);
// insert_first
bool themVaoDauDanhSach(DSCTHOADONPTR &first, CT_HoaDon ctHoaDon);
//insert last
bool themVaoCuoiDanhSach(DSCTHOADONPTR &first, CT_HoaDon ctHoaDon );
// insert_order
bool themSapXep(DSCTHOADONPTR &first, CT_HoaDon ctHaDon);
// insert_after
bool themVaoSauMotNode(DSCTHOADONPTR &first, DSCTHOADONPTR p, CT_HoaDon ctHoaDon);
//	delete_first
bool xoaNodeDauDanhSach(DSCTHOADONPTR &first);
void xoaToanBoDanhSach(DSCTHOADONPTR &first);
// delete_after
bool xoaSauNode(DSCTHOADONPTR &first, DSCTHOADONPTR p);
// delete_info
bool xoaNode_info(DSCTHOADONPTR &first, CT_HoaDon ctHoaDon);
void duyetDanhSach(DSCTHOADONPTR first);
int demSoCTHoaDon(DSCTHOADONPTR first);
DSCTHOADONPTR timKiemTrongCTHoaDon(DSCTHOADONPTR first, string maVatTu);
DSCTHOADONPTR timKiemCTHoaDonThuN(DSCTHOADONPTR first, int n);
void chuyenDanhSachChiTietThanhMangHaiChieu(DSCTHOADONPTR dsCTHoaDon, string ds[][SO_COT_BANG_CT_HOA_DON]);



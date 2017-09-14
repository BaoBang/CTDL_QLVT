#include <mylib.h>
#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <sstream>

// ma phim
#define KEY_BACKSPACE 8
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_TAB 9
#define KEY_ESC 27

#define KEY_DOWN 80+256
#define KEY_UP 72+256
#define KEY_LEFT 75+256
#define KEY_RIGHT 77+256
#define KEY_PAGEUP 73
#define KEY_PAGEDOWN 81


#define KEY_DELETE 83+256
#define KEY_INSERT 82+256
#define KEY_F2 60+256
#define KEY_F5 63+256
#define KEY_F9 67+256
// color
#define BG_HEADER 4
#define BLACK 0
#define GRAY 8
#define BLUE 1
#define BG_BODY 7
#define RED 4
#define YELLOW 14
#define TEXT_COLOR 8
#define WHITE 15
#define GREEEN 10
//vi tri dat form
#define TOADOX 5
#define TOADOY 2
#define HEIGHT_HEADER 3
#define WIDTH_MENU_BAR 20
#define SCREEN_WIDTH 150
#define SCREEN_HEIGTH 36
#define HEIGHT_FOOTER 3
#define WIDTH_BODY SCREEN_WIDTH-WIDTH_MENU_BAR
#define HEIGHT_BODY SCREEN_HEIGTH-HEIGHT_HEADER-HEIGHT_FOOTER

//vi tri dat form input
#define TOADOY_FORM 12
#define WIDTH_TEXT 30
#define WIDTH_LABEL 15
#define TOADOX_LABLE  TOADOX+WIDTH_MENU_BAR+(SCREEN_WIDTH-WIDTH_MENU_BAR-WIDTH_TEXT-WIDTH_LABEL)/2
#define TOADOX_TEXT  TOADOX_LABLE + WIDTH_LABEL

#define WIDTH_MESSAGE 50

#define TABLE_COLUMN_WIDTH 20

//~~~~~~~~~~~~~~~~~~Nhan vien ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define TOADOX_CB_NAM TOADOX_TEXT 
#define TOADOX_CB_NU TOADOX_TEXT+15
#define SO_DONG_MOT_TRANG 10

#define SIZE_FORM_NHAN_VIEN 4
#define SIZE_MENU_NHAN_VIEN 3
//~~~~~~~~~~~~~~~~~Hoa don~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`

#define SIZE_FORM_HOA_DON 3
#define SO_COT_BANG_HOA_DON 5
#define SO_HANG_BANG_HOA_DON 10

#define WIDTH_INPUT_NGAY 17

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chi tiet hoa don~~~~~~~~~~~~~~~~~~~~~~~~`

#define SO_COT_BANG_CT_HOA_DON 4
#define SO_COT_BANG_XUAT_CT_HOA_DON 5
#define SO_CT_HOA_DON_MOT_TRANG 5
#define SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG 10
#define TOADOY_KHUNG_CT_HOA_DON 20
#define TOADOY_KHUNG_XUAT_CT_HOA_DON 10
#define MAX_LINE 250

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~VAt tu~~~~~~~~~~~~~~~~~~~~~~~

// Kich Thuoc Mang
#define MAX_LIST 100
#define MAX_TEXT_INPUT 40
#define MAX_SO_LUONG 1000000

#define TEXT_WHITE 15
#define TEXT_ERROR 12

#define HEIGHT_ITEM_MENU_BAR 3
#define WIDTH_INPUT_TEXT 42

#define SIZE_MENU 5
#define SIZE_THUOC_TINH_VT 4
#define SIZE_BANG_DANH_SACH_VT 5

#define SL_VAT_TU_TRONG_TRANG 10

// Thong ke vat tu
#define SO_COT_BANG_THONG_KE_VAT_TU 5

#define FILE_VAT_TU "vattu.txt"
using namespace std;

struct Date{
	int NGAY;
	int THANG;
	int NAM;
};

int keyPressed(){
	int a = getch();
	if(a == 0 || a== 224){
		a = 256 + getch();
	}
	return a;
}

void veHinhChuNhat(int toaDoX, int toaDoY, int chieuDai, int chieuRong, int color){
	SetBGColor(color);
	for(int i = 0; i < chieuRong; i++){
		gotoxy(toaDoX, toaDoY + i);
		for(int j = 0; j < chieuDai; j++){
			cout <<" ";
		}
	}
	SetBGColor(BLACK);	
}

// nhap vao chuoi s, chi nhan gia tri a-z A-Z 0-9 
int nhapChuoiKiTuVaSoKhongKhoangTrang(string &s, int toaDoX, int toaDoY, int maxLengthText, int mauNen, int mauChu){
	SetBGColor(mauNen);
	SetColor(mauChu);
	int chieuDaiChuoi = s.length();
	int c;
	gotoxy(toaDoX, toaDoY);
	cout << s;
	do{
		c=keyPressed();
		if((c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0'&& c <= '9') && chieuDaiChuoi < maxLengthText){
			gotoxy(toaDoX + chieuDaiChuoi, toaDoY);
			cout << char(c);
			chieuDaiChuoi++;
			s += char(c);
		}else if(c == KEY_BACKSPACE && chieuDaiChuoi != 0) {
			
			gotoxy(toaDoX + --chieuDaiChuoi, toaDoY);
			cout << " ";
			s.erase(chieuDaiChuoi);
			gotoxy(toaDoX + chieuDaiChuoi, toaDoY);
		}
		
		
	}while(c != KEY_ENTER && c != KEY_UP && c != KEY_DOWN && c != KEY_LEFT && c != KEY_RIGHT &&c != KEY_TAB && c!= KEY_INSERT && c!= KEY_ESC && c != KEY_F5 && c!= KEY_F2) ;
	return c;
}


// nhap vao chuoi s, chi nhan gia tri a-z A-Z 0-9 va sapce
int nhapChuoiKiTuVaSo(string &s, int toaDoX, int toaDoY, int maxLengthText, int mauNen, int mauChu){
	SetBGColor(mauNen);
	SetColor(mauChu);
	int chieuDaiChuoi = s.length();
	int c;
	gotoxy(toaDoX, toaDoY);
	cout << s;
	do{
		c=keyPressed();
		if((c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0'&& c <= '9' || c== KEY_SPACE) && chieuDaiChuoi < maxLengthText){
			gotoxy(toaDoX + chieuDaiChuoi, toaDoY);
			cout << char(c);
			chieuDaiChuoi++;
			s += char(c);
		}else if(c == KEY_BACKSPACE && chieuDaiChuoi != 0) {
			
			gotoxy(toaDoX + --chieuDaiChuoi, toaDoY);
			cout << " ";
			s.erase(chieuDaiChuoi);
			gotoxy(toaDoX + chieuDaiChuoi, toaDoY);
		}
		
		
	}while(c != KEY_ENTER && c != KEY_UP && c != KEY_DOWN && c != KEY_LEFT && c != KEY_RIGHT &&c != KEY_TAB && c!= KEY_INSERT && c!= KEY_ESC && c != KEY_F5 && c!= KEY_F2) ;
	return c;
}

// nhap vao s chuoi ki tu, chi nhan cac ki tu a-z A-Z va spcace
int nhapChuoiKiTu(string &s, int toaDoX, int toaDoY, int maxLengthText, int mauNen, int mauChu){
	SetBGColor(mauNen);
	SetColor(mauChu);
	int chieuDaiChuoi = s.length();
	int c;
	gotoxy(toaDoX, toaDoY);
	cout << s;
	do{
		c=keyPressed();
		if((c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'|| c == KEY_SPACE)&& chieuDaiChuoi < maxLengthText){
			gotoxy(toaDoX + chieuDaiChuoi, toaDoY);
			cout << char(c);
			chieuDaiChuoi++;
			s += char(c);
		}else if(c == KEY_BACKSPACE && chieuDaiChuoi != 0) {
			
			gotoxy(toaDoX + --chieuDaiChuoi, toaDoY);
			cout << " ";
			s.erase(chieuDaiChuoi);
			gotoxy(toaDoX + chieuDaiChuoi, toaDoY);
		}
		
		
	}while(c != KEY_ENTER && c != KEY_UP && c != KEY_DOWN && c != KEY_LEFT && c != KEY_RIGHT && c != KEY_TAB && c!= KEY_INSERT && c!= KEY_ESC && c != KEY_F5 && c!= KEY_F2);
	return c;
}
// nhap s chuoi ki tu so
int nhapChuoiKiTuSo(string &s, int toaDoX, int toaDoY, int maxLengthText, int mauNen, int mauChu){
	SetBGColor(mauNen);
	SetColor(mauChu);
	int chieuDaiChuoi = s.length();
	int c;
	gotoxy(toaDoX, toaDoY);
	cout << s;
	do{
		c=keyPressed();
		if(c >= '0'&& c <= '9' && chieuDaiChuoi < maxLengthText){
			gotoxy(toaDoX + chieuDaiChuoi, toaDoY);
			cout << char(c);
			chieuDaiChuoi++;
			s += char(c);
		}else if(c == KEY_BACKSPACE && chieuDaiChuoi != 0) {
			
			gotoxy(toaDoX + --chieuDaiChuoi, toaDoY);
			cout << " ";
			s.erase(chieuDaiChuoi);
			gotoxy(toaDoX + chieuDaiChuoi, toaDoY);
		}
		
		
	}while(c != KEY_ENTER && c != KEY_UP && c != KEY_DOWN && c != KEY_LEFT && c != KEY_RIGHT && c != KEY_TAB && c!= KEY_INSERT && c!= KEY_ESC && c != KEY_F5 && c!= KEY_F2);
	return c;
}

void thongBao(string message, int toaDoX, int toaDoY, int chieuDai, int chieuRong){
	veHinhChuNhat(toaDoX, toaDoY, chieuDai, chieuRong, BG_HEADER);
	gotoxy(toaDoX + (chieuDai - message.length())/2, toaDoY + chieuRong / 2);
	SetBGColor(BG_HEADER);
	SetColor(WHITE);
	cout << message;
	getch();
}

void formTimKiem(string tieuDe, int toaDoX, int toaDoY, int chieuDai, int chieuRong){
	veHinhChuNhat(toaDoX, toaDoY, chieuDai, chieuRong, BG_HEADER);
	gotoxy(toaDoX + (chieuDai - tieuDe.length())/2, toaDoY + 1);
	SetBGColor(BG_HEADER);
	SetColor(WHITE);
	cout << tieuDe;
	gotoxy(toaDoX + (chieuDai - WIDTH_TEXT)/2, toaDoY + 3);
	SetBGColor(BLACK);
	SetColor(WHITE);
	for(int i = 0; i < WIDTH_TEXT; i++) cout << " ";
}

void veKhungDanhSach(int soCot, int soHang, int toaDoX, int toaDoY){
	for (int i = 0; i <= soHang * 2; i++){
		gotoxy(toaDoX, toaDoY + i);
		if (i % 2 == 0)
		for (int j = 0; j <= soCot * TABLE_COLUMN_WIDTH + soCot; j++)
		if (i == 0 && j == 0)cout << char(218);
		else if (i == 0 && j == soCot * TABLE_COLUMN_WIDTH + soCot) cout << char(191);
		else if (j == 0 && i == soHang * 2) cout << char(192);
		else if (i == soHang * 2 && j == soCot * TABLE_COLUMN_WIDTH + soCot)cout << char(217);
		else if (j == 0) cout << char(195);
		else if (j == soCot * TABLE_COLUMN_WIDTH + soCot) cout << char(180);
		else if (i == 0 && j % (TABLE_COLUMN_WIDTH + 1) == 0) cout << char(194);
		else if (i == soHang * 2 && j % (TABLE_COLUMN_WIDTH + 1) == 0) cout << char(193);
		else if (j % (TABLE_COLUMN_WIDTH + 1) == 0) cout << char(197);
		else cout << char(196);
		else
		for (int j = 0; j <= soCot * TABLE_COLUMN_WIDTH + soCot; j++)
		if (j % (TABLE_COLUMN_WIDTH + 1) == 0)
			cout << (char)179;
		else
			cout << " ";
	}
}

void veKhungChiTietHoaDon(int soCot, int soHang, int toaDoX, int toaDoY){
	// 218- 196--194--196-- 191
	//179	      179       179
	//	
	//195   196  197   196	180
	//
	//179		179			179
	//192--196- 193----196  217
	for (int i = 0; i <= soHang * 2; i++){
		gotoxy(toaDoX, toaDoY + i);
		if (i % 2 == 0)
		for (int j = 0; j <= soCot * TABLE_COLUMN_WIDTH + soCot; j++)
		if (i == 0 && j == 0)cout << char(218);
		else if (i == 0 && j == soCot * TABLE_COLUMN_WIDTH + soCot) cout << char(191);
		else if (j == 0 && i == soHang * 2) cout << char(192);
		else if (i == soHang * 2 && j == soCot * TABLE_COLUMN_WIDTH + soCot)cout << char(217);
		else if (j == 0) cout << char(195);
		else if (j == soCot * TABLE_COLUMN_WIDTH + soCot) cout << char(180);
		else if (i == 0 && j % (TABLE_COLUMN_WIDTH + 1) == 0) cout << char(194);
		else if ((i == soHang * 2 && j % (TABLE_COLUMN_WIDTH + 1) == 0 && j > TABLE_COLUMN_WIDTH + 1) || (i == soHang * 2 - 4 && j == TABLE_COLUMN_WIDTH + 1)) cout << char(193);
		else if (j % (TABLE_COLUMN_WIDTH + 1) == 0 && ( i < soHang * 2 - 3 || j != TABLE_COLUMN_WIDTH + 1)  ) cout << char(197);
	
		else cout << char(196);
		else
		for (int j = 0; j <= soCot * TABLE_COLUMN_WIDTH + soCot; j++)
		if (j % (TABLE_COLUMN_WIDTH + 1) == 0 && (j != TABLE_COLUMN_WIDTH + 1 || i < soHang * 2 -3))
			cout << (char)179;
		else
			cout << " ";
	}
}

Date layGioHeThong(){
	time_t t = time(0);
	struct tm * now = localtime( & t );
	Date ngayHeThong;
	ngayHeThong.NGAY = now->tm_mday;
	ngayHeThong.THANG = now->tm_mon + 1;
	ngayHeThong.NAM = now->tm_year + 1900;
	
	return ngayHeThong;
}

string chuyenSoThanhChuoi(int number){
    string s = "";
	while (number!=0){
		s=char((number%10)+48) + s;
		number=number/10;
	}
	if (s.length() < 2) s = '0' + s;
	return s;
}

string chuyenNgayThanhChuoi(Date date){
	string s = "";
	string temp = "";
	temp = chuyenSoThanhChuoi(date.NGAY);
	s += temp + "/";
	temp = chuyenSoThanhChuoi(date.THANG);
	s += temp + "/";
	temp = chuyenSoThanhChuoi(date.NAM);
	s += temp;
	return s;
}



int hopThoaiLuaChon(string message, int toaDoX, int toaDoY, int chieuDai, int chieuRong){
	veHinhChuNhat(toaDoX, toaDoY, chieuDai, chieuRong, BG_HEADER);
	gotoxy(toaDoX + (chieuDai - message.length())/2, toaDoY + chieuRong / 2 - 1);
	SetBGColor(BG_HEADER);
	SetColor(WHITE);
	cout << message;
	gotoxy(toaDoX + chieuDai / 4 - 2, toaDoY + chieuRong / 2 + 1);
	cout << "CO";
	gotoxy(toaDoX +(chieuDai / 4) * 3-chieuDai / 8, toaDoY + chieuRong / 2 + 1);
	cout << "KHONG";
	int c;
	int res = 0;
	do{
		if(res == 0){
			veHinhChuNhat(toaDoX + chieuDai / 4 - 2, toaDoY + chieuRong / 2 + 1, 7, 1, BG_HEADER);
			gotoxy(toaDoX + chieuDai / 4, toaDoY + chieuRong / 2 + 1);
			SetBGColor(BG_HEADER);
			SetColor(WHITE);
			cout << "CO";
			
			veHinhChuNhat(toaDoX +(chieuDai / 4) * 3-chieuDai / 8 - 1, toaDoY + chieuRong / 2 + 1, 7, 1, BG_BODY);
			gotoxy(toaDoX +(chieuDai / 4) * 3-chieuDai / 8, toaDoY + chieuRong / 2 + 1);
			SetBGColor(BG_BODY);
			SetColor(BG_HEADER);
			cout << "KHONG";
		}else{
			veHinhChuNhat(toaDoX +(chieuDai / 4) * 3-chieuDai / 8 - 1, toaDoY + chieuRong / 2 + 1, 7, 1, BG_HEADER);
			gotoxy(toaDoX +(chieuDai / 4) * 3-chieuDai / 8, toaDoY + chieuRong / 2 + 1);
			SetBGColor(BG_HEADER);
			SetColor(WHITE);
			cout << "KHONG";
			
			veHinhChuNhat(toaDoX + chieuDai / 4- 2, toaDoY + chieuRong / 2 + 1, 7, 1, BG_BODY);
			gotoxy(toaDoX + chieuDai / 4, toaDoY + chieuRong / 2 + 1);
			SetBGColor(BG_BODY);
			SetColor(BG_HEADER);
			cout << "CO";
			
		}
		c = keyPressed();
		if(c == KEY_LEFT) res = 1;
		if(c == KEY_RIGHT) res = 0;
	}while(c != KEY_ENTER && c != KEY_ESC);
	if(c == KEY_ESC) return 0;
	return res;
}

//chuoi nhap vao khong la chuoi cac ki tu ' '
int kiemTraChuoiNhapVao(string s){
	for(int i = 0; i < s.length(); i++){
		if(s[i] !=' ') return 1;
	}
	return 0;
}

string dinhDangChuoiNhapVao(string s){
	string str = "";
	string temp = "";
	for(int i = 0; i < s.length(); i++){
		if(s[i] != ' ' && s[i] != KEY_TAB){
			temp += s[i];
		}else{
			if(temp.length() > 0){
				str += temp + " ";
				temp = "";
			}
		}
	}
	if(temp.length() > 0) str += temp + " ";
	str.erase(str.length()-1);
	return str;
}

int kiemTraNgayGiua2Ngay(Date ngayBatDau, Date ngayKetThuc, Date ngayKiemTra){
	// neu nam khong thuoc tu nam cua ngay bat dau den ban cua nay ket thuc
	if(ngayKiemTra.NAM < ngayBatDau.NAM || ngayKiemTra.NAM > ngayKetThuc.NAM) return 0;
	//neu nam cua ngay can kiem tra bang nam cua ngay bat dau
	//thi kiem tra thang cua 2 ngay nhap vao
	// neu thang ngay kiem tra < thang cua ngay bat dau thi return 0
	// neu thang cua ngay kiem tra bang thagn cua ngay bat dau
	// thi kiem tra ngay tuong tu nhu kiem tra thang
	if(ngayKiemTra.NAM == ngayBatDau.NAM){
		if(ngayKiemTra.THANG < ngayBatDau.THANG) return 0;
		if(ngayKiemTra.THANG == ngayBatDau.THANG && ngayKiemTra.NGAY < ngayBatDau.NGAY) return 0;		
	}
	
	if(ngayKiemTra.NAM == ngayKetThuc.NAM){
		if(ngayKiemTra.THANG > ngayKetThuc.THANG) return 0;
		if(ngayKiemTra.THANG == ngayBatDau.THANG && ngayKiemTra.NGAY > ngayKetThuc.NGAY) return 0;
	}
		return 1;
}

// .~~~~~~~~~~~~~~~~~TAM~~~~~~~~~~~~~~~~~~
// TAM: ve input nhap ngay thang nam
void veInputNhapNgay(int toaDoX, int toaDoY){
	// 218 --- 196 --- 191
	// 179 ----------- 179
	// 192 --- 196 --- 217
	SetColor(RED);
	SetBGColor(BG_BODY);
	
	gotoxy(toaDoX, toaDoY);
	cout << char (218);
	for (int i = 1; i < WIDTH_INPUT_NGAY; i++) cout << char (196);
	cout << char (191);
	
	gotoxy(toaDoX, toaDoY + 1);
	cout << char (179);
	gotoxy(toaDoX + WIDTH_INPUT_NGAY, toaDoY + 1);
	cout << char (179);
	
	gotoxy(toaDoX, toaDoY + 2);
	cout << char (192);
	for (int i = 1; i < WIDTH_INPUT_NGAY; i++) cout << char (196);
	cout << char (217);
	
	gotoxy(toaDoX + 5, toaDoY + 1);
	cout << "/";
	
	gotoxy(toaDoX + 10, toaDoY + 1);
	cout << "/";
}

// TAM: Ve Input Text
void veInputText(int toaDoX, int toaDoY){
	// 218 --- 196 --- 191
	// 179 ----------- 179
	// 192 --- 196 --- 217
	SetColor(RED);
	SetBGColor(BG_BODY);
	
	gotoxy(toaDoX, toaDoY);
	cout << char (218);
	for (int i = 1; i < WIDTH_INPUT_TEXT; i++) cout << char (196);
	cout << char (191);
	
	gotoxy(toaDoX, toaDoY + 1);
	cout << char (179);
	gotoxy(toaDoX + WIDTH_INPUT_TEXT, toaDoY + 1);
	cout << char (179);
	
	gotoxy(toaDoX, toaDoY + 2);
	cout << char (192);
	for (int i = 1; i < WIDTH_INPUT_TEXT; i++) cout << char (196);
	cout << char (217);
}


// TAM: kiem Tra ngay thang nam hop le: Hop le: 1, Ko Hop Le: 0
int kiemTraThoiGianNhapHopLe(int ngay, int thang, int nam, int &vtKoHopLe){
	// vtKoHopLe: ngay->0, thang->1, nam->2
	
	Date tgHienTai;
	tgHienTai = layGioHeThong();
	
	if (nam > tgHienTai.NAM) {
		vtKoHopLe = 2;
		return 0;
	} else if (thang <= 0 || thang > 12 || (nam == tgHienTai.NAM && thang > tgHienTai.THANG)) {
		vtKoHopLe = 1;
		return 0;
	} else if (nam == tgHienTai.NAM && thang == tgHienTai.THANG && ngay > tgHienTai.NGAY) {
		vtKoHopLe = 0;
		return 0;
	}
	
	switch(thang){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if(ngay <=0 || ngay > 31) {
				vtKoHopLe = 0;
				return 0;
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if(ngay <= 0 || ngay > 30) {
				vtKoHopLe = 0;
				return 0;
			}
			break;
		case 2:
			if((nam % 4 == 0 && (ngay <= 0 || ngay > 29)) || (nam % 4 != 0 && (ngay <= 0 || ngay > 28))) {
				vtKoHopLe = 0;
				return 0;
			}
			break;	
	}
	
	return 1;
}
// TAM: So sanh 2 Date A va B voi nhau A>B: 1, A=B: 0, A<B: -1
int soSanhThoiGian(Date thoiGianA, Date thoiGianB){
	if (thoiGianA.NAM > thoiGianB.NAM) return 1;
	else if (thoiGianA.NAM < thoiGianB.NAM) return -1;
	else {
		if (thoiGianA.THANG > thoiGianB.THANG) return 1;
		else if (thoiGianA.THANG < thoiGianB.THANG) return -1;
		else {
			if (thoiGianA.NGAY > thoiGianB.NGAY) return 1;
			else if (thoiGianA.NGAY < thoiGianB.NGAY) return -1;
			else return 0;
		}
	}
}  


// TAM: Ve Bang Danh Sach Vat Tu
void veBangDanhSach(int toaDoX, int toaDoY, int soCot, int soDong, int kichThuocO){
	SetColor(GRAY);
	SetBGColor(BG_BODY);

	// Tao bang
	// 218 --- 196 --- 194 --- 196 --- 191
	// 179             179             179
	// 195 --- 196 --- 197 --- 196 --- 180
	// 179             179             179
	// 192 --- 196 --- 193 --- 196 --- 217
	
	for (int i = 0; i < soDong * 2 + 1; i++){
		gotoxy(toaDoX, toaDoY + i);
		for (int j = 0; j < soCot * 2 + 1; j++) {
			// Dong dau
			if (i == 0){
				if (j == 0) cout << char (218);
				else if (j == soCot * 2) cout << char (191);
			 	else if (j % 2 == 0) cout << char (194);
				else for (int k = 0; k < kichThuocO; k++) cout << char (196);
			}	
				
			// Dong cuoi
			else if (i == soDong * 2){
				if (j == 0) cout << char (192);
				else if (j == soCot * 2) cout << char (217);
				else if (j % 2 == 0) cout << char (193);
				else for (int k = 0; k < kichThuocO; k++) cout << char (196);
			}
			
			// Dong Giua
			else {
				if (i % 2 == 0) {
					if (j == 0) cout << char (195);
					else if (j == soCot * 2) cout << char (180);
					else if (j == 0 || j == soCot * 2) cout << char (179);
					else if (j % 2 == 0) cout << char (197);
					else for (int k = 0; k < kichThuocO; k++) cout << char (196);
				}
				else if (j % 2 == 0) cout << char (179);
				else for (int k = 0; k < kichThuocO; k++) cout << " ";
			}
				
		}	
	}
}

// Kiem tra chuoi s khong co ' ' khong? khong : 0, co ' ': 1
bool kiemTraChuoiCoKhoangTrang(string s){
	for(int i = 0; i < s.length(); i++){
		if(s[i] == ' ') return true;
	}
	return false;
}

// Kiem tra chuoi toan ky tu ' ' khong?
bool kiemTraChuoiLaKhoangTrang(string s){
	int dem = 0;
	for(int i = 0; i < s.length(); i++){
		if(s[i] !=' ') dem++;
	}
	
	return dem == s.length() ? true: false;
}






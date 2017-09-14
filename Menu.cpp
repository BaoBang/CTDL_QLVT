#include "NhanVien.cpp"

//#define SIZE_MENU 4
string dsChucNang[]={"Vat tu","Nhan vien", "Thong ke hoa don", "Danh Sach ban chay", "Thoat"};

void veGiaoDienChinh(string title){

	// header
	veHinhChuNhat(TOADOX, TOADOY, SCREEN_WIDTH, 3, BG_HEADER);
	gotoxy( (TOADOX + SCREEN_WIDTH + WIDTH_MENU_BAR- title.length())/ 2, TOADOY + 1);
	SetColor(WHITE);
	SetBGColor(BG_HEADER);
	cout << title;
	//content
	veHinhChuNhat(TOADOX, TOADOY + 3, SCREEN_WIDTH, SCREEN_HEIGTH - 3, BG_BODY);
	//left-colum
	veHinhChuNhat(TOADOX, TOADOY + 3, WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_HEADER);
	
	// menu
	int Y_item = 7;
	SetColor(BG_BODY);
	SetBGColor(BG_HEADER);
	for(int j = 0; j < SIZE_MENU; j++){
		gotoxy(TOADOX + (WIDTH_MENU_BAR - dsChucNang[j].length())/ 2 , TOADOY + Y_item + j  * 6 );
				cout << dsChucNang[j];
		for(int i = 0; i < WIDTH_MENU_BAR; i++){
			gotoxy(TOADOX + i, TOADOY + Y_item - 1 + j  * 6 );
			cout << char(196);
		
			gotoxy(TOADOX + i, TOADOY + Y_item + 1 + j  * 6);	
			cout << char(196);
		}
	}	
}
// duyet tien tu (NLR) de khong lam thay doi vi tri cac node khi load lai file
void luuDanhSach(NHANVIENTREE root){
	ofstream file("quanlivattu.txt");	
	
	Stack sp = NULL;
	NHANVIENTREE p = root;
	HOADONPTR dsHoaDon;
	DSCTHOADONPTR dsCTHoaDon;
		while(p != NULL){
			
			file << "+" << endl;
			file << p->NHANVIEN.MANV << endl;
			file << p->NHANVIEN.HO << endl;
			file << p->NHANVIEN.TEN << endl;
			file << p->NHANVIEN.PHAI << endl;
			dsHoaDon = p->NHANVIEN.DS_HOADON;
			while(dsHoaDon != NULL){
				file << "-" << endl;
				file << dsHoaDon->HOADON.SOHD << endl;
				file << dsHoaDon->HOADON.NGAYLAP.NGAY << endl;
				file << dsHoaDon->HOADON.NGAYLAP.THANG << endl;
				file << dsHoaDon->HOADON.NGAYLAP.NAM << endl;
				file << dsHoaDon->HOADON.LOAI << endl;
				dsCTHoaDon = dsHoaDon->HOADON.DSCTHOADON;
				while(dsCTHoaDon != NULL){
					file << "*" << endl;
					
					file << dsCTHoaDon->CTHOADON.MAVT << endl;
					file << dsCTHoaDon->CTHOADON.SOLUONG << endl;
					file << dsCTHoaDon->CTHOADON.DONGIA << endl;
					file << dsCTHoaDon->CTHOADON.VAT << endl;
					
					dsCTHoaDon = dsCTHoaDon->NEXT;
				}
				dsHoaDon = dsHoaDon->NEXT;
			}
			if(p->RIGHT != NULL)
				push(sp, p->RIGHT);// them cay ben phai vao stack
			if(p->LEFT != NULL)
				p = p->LEFT;// roi di chuyen den cay con ben trai
			else if(sp == NULL) 
				break;
			else pop(sp, p);		
		}
	
	file << "=";
	file.close();

	return;
}


void napDanhSach(NHANVIENTREE &root){
	ifstream file("quanlivattu.txt");
	if(!file){
		cout << "Khong tim thay quanlivattu.txt" << endl;
		exit(1);
	}
	
	NhanVien nv;
	HoaDon hd;
	CT_HoaDon cthd;
	string s;
	getline(file, s);
	if(s == "=") return;
	int dem = 0;
	while(!file.eof()){
	
	LoadNhanVien:
		getline(file, nv.MANV);
	
		getline(file, nv.HO);
		getline(file , nv.TEN);
		getline(file, s);
		stringstream(s) >> nv.PHAI;
		nv.DS_HOADON = NULL;
		getline(file, s);
		if(s == "+"){
			themVaoCay(root, nv);
			goto LoadNhanVien;
		}
		if(s == "="){
			themVaoCay(root, nv);
			return;
		}
	LoadHoaDon:
		getline(file, hd.SOHD);
		getline(file ,s);
		stringstream(s) >> hd.NGAYLAP.NGAY;
		getline(file ,s);
		stringstream(s) >> hd.NGAYLAP.THANG;
		getline(file, s);
		stringstream(s) >> hd.NGAYLAP.NAM;
		hd.DSCTHOADON = NULL;
		getline(file, s);
		hd.LOAI = s[0];
		getline(file , s);
		if (s == "-")
		{
			themVaoCuoiDanhSach(nv.DS_HOADON, hd);
			goto LoadHoaDon;
		}
			if (s == "+")
		{	
			themVaoCuoiDanhSach(nv.DS_HOADON, hd);
			themVaoCay(root, nv);
			goto LoadNhanVien;
		}
		if (s == "=")
		{
			themVaoCuoiDanhSach(nv.DS_HOADON, hd);
			themVaoCay(root, nv);
			return;
		}
	
		LoadCTHoaDon:
		getline(file, cthd.MAVT);
		getline(file, s);
		stringstream(s) >> cthd.SOLUONG;
		getline(file, s);
		stringstream(s) >> cthd.DONGIA;
		getline(file, s);
		stringstream(s) >> cthd.VAT;
		getline(file, s);
		themVaoCuoiDanhSach(hd.DSCTHOADON, cthd);
		if (s == "*")goto LoadCTHoaDon;

		if (s == "-"){
			themVaoCuoiDanhSach(nv.DS_HOADON, hd);
			goto LoadHoaDon;
		}
		if (s == "=")
		{
			themVaoCuoiDanhSach(nv.DS_HOADON, hd);
			themVaoCay(root, nv);
			return;
		}
		if (s == "+")
		{
			themVaoCuoiDanhSach(nv.DS_HOADON, hd);
			themVaoCay(root, nv);
			goto LoadNhanVien;
		}
	}
	file.close();

	return;
}

void menuChucNang(NHANVIENTREE &root,DanhSachVatTu &dsVatTu ,string title){
	veGiaoDienChinh(title);
	int c;
	int viTriSauKhiThem;
	NhanVien nv;
	int luaChon  = 0;
	int Y_item = 7;
	while (true){
		gotoxy(TOADOX, TOADOY + Y_item - 1 + luaChon  * 6 );
		veHinhChuNhat(TOADOX,TOADOY + Y_item - 1 + luaChon  * 6, WIDTH_MENU_BAR, 3, BG_BODY);
		gotoxy(TOADOX + (WIDTH_MENU_BAR - dsChucNang[luaChon].length())/2, TOADOY + Y_item + luaChon  * 6 );
		SetColor(BG_HEADER);
		SetBGColor(BG_BODY);
		cout << dsChucNang[luaChon];
		c = keyPressed();
		if(c == KEY_DOWN){
				veHinhChuNhat(TOADOX,TOADOY + Y_item - 1 + luaChon  * 6, WIDTH_MENU_BAR, 3, BG_HEADER);
				SetColor(BG_BODY);
				SetBGColor(BG_HEADER);
				gotoxy(TOADOX + (WIDTH_MENU_BAR - dsChucNang[luaChon].length())/ 2 , TOADOY + Y_item + luaChon  * 6 );
				cout << dsChucNang[luaChon];
			for(int i = 0; i < WIDTH_MENU_BAR; i++){
				gotoxy(TOADOX + i, TOADOY + Y_item - 1 + luaChon  * 6 );
				cout << char(196);
				gotoxy(TOADOX + i, TOADOY + Y_item + 1 + luaChon  * 6);	
				cout << char(196);
			}
			if(luaChon < SIZE_MENU - 1)luaChon++;
		}
		
		if(c == KEY_UP){
				veHinhChuNhat(TOADOX,TOADOY + Y_item - 1 + luaChon  * 6, WIDTH_MENU_BAR, 3, BG_HEADER);
				SetColor(BG_BODY);
				SetBGColor(BG_HEADER);
				gotoxy(TOADOX + (WIDTH_MENU_BAR - dsChucNang[luaChon].length())/ 2 , TOADOY + Y_item + luaChon  * 6 );
				cout << dsChucNang[luaChon];
			for(int i = 0; i < WIDTH_MENU_BAR; i++){
				gotoxy(TOADOX + i, TOADOY + Y_item - 1 + luaChon  * 6 );
				cout << char(196);
				gotoxy(TOADOX + i, TOADOY + Y_item + 1 + luaChon  * 6);	
				cout << char(196);
			}
			if(luaChon > 0)luaChon--;
		}
		if(c == KEY_ENTER){	
			switch(luaChon){
				case 0:
					// VAT TU
					giaoDienVatTu(dsVatTu);
					veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
					break;
				case 1:
					// NHAN VIEN
					formNhanVien(root, dsVatTu);
					veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
					break;
				case 2:
					// THONG KE DANH SACH HOA DON
					giaoDienThongKeHoaDon(root);
					veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
					break;
				case 3:
					// THONG KE TOP VAT TU XUAT CAO NHAT
					giaoDienThongKeVatTuCoLuongXuatCaoNhat(root, dsVatTu);
					veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
					break;
				case 4:
					luuDanhSach(root);
					luuDanhSachVatTuVaoFile(dsVatTu);
					SetBGColor(BLACK);
					SetColor(GRAY);
					system("cls");
					exit(1);
				
			}
		}
		
	}

}


int main(){
	NHANVIENTREE root = NULL;
	DanhSachVatTu dsVatTu;
	dsVatTu.N = 0;
	napDanhSachVatTuTuFile(dsVatTu);
	napDanhSach(root);

	menuChucNang(root, dsVatTu,"QUAN LY VAT TU");

}

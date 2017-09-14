#include "DuLieu.cpp"


string menu[SIZE_MENU] = {"VAT TU", "NHAN VIEN", "HOA DON"};
string thuocTinhVatTu[SIZE_THUOC_TINH_VT] = {"Ma Vat Tu", "Ten Vat Tu", "Don Vi Tinh", "So Luong Ton"};
string tenCotBangVatTu[SIZE_BANG_DANH_SACH_VT] = {"STT", "MA VAT TU", "TEN VAT TU", "DON VI TINH", "SO LUONG TON"};


// Kiem Tra Danh Sach Rong : empty = true
bool kiemTraRong(DanhSachVatTu dsVatTu){
	if (dsVatTu.N == 0) return true;
	return false;
}

// Kiem Tra Danh Sach day: full=true
bool kiemTraDay(DanhSachVatTu dsVatTu) {
	if (dsVatTu.N == MAX_VAT_TU) return true;
	return false;
}

// Tim kiem Vat Tu trong Danh Sach theo MaVT
int timKiemVatTu(DanhSachVatTu dsVatTu, string maVT) {
	for (int i = 0; i < dsVatTu.N; i++)
		if (dsVatTu.NODE[i].MAVT == maVT)
			return i;	// tra ve index cua Vat Tu
	return -1;	// neu ko co thi tra ve -1
}

// Tim vi tri thich hop de them vao Danh Sach voi thu tu tang dan theo MaVT 
int timViTriThichHop(DanhSachVatTu dsVatTu, string maVT) {
	for (int i = 0; i< dsVatTu.N; i++){
		// Neu ma so trung thi return -1
		if (dsVatTu.NODE[i].MAVT == maVT) return -1;
		// return vi tri thich hop	
		if (dsVatTu.NODE[i].MAVT > maVT) return i;
	}	
	return dsVatTu.N;
}

// Them Vat Tu vao vi tri Thu x. Thanh cong: true
bool themVatTuVaoViTriX(DanhSachVatTu &dsVatTu, VatTu vatTu, int x) {
	if (x < 0 || x > dsVatTu.N || kiemTraDay(dsVatTu)) return false;
	
	for (int i = dsVatTu.N; i > x; i--)
		dsVatTu.NODE[i] = dsVatTu.NODE[i - 1];
		
	dsVatTu.NODE[x] = vatTu;
	dsVatTu.N++;
	
	return true;
}

// Them Vat Tu co Sap Xep theo thu tu tang dan MaVT
bool themVatTuSapXepTheoMa(DanhSachVatTu &dsVatTu, VatTu vatTu) {
	int viTriThem = timViTriThichHop(dsVatTu, vatTu.MAVT);
	bool kq = themVatTuVaoViTriX(dsVatTu, vatTu, viTriThem);
	return kq;
}

// Xoa Vat Tu theo vi tri theo viTriXoa. Xoa thanh cong: true
bool xoaVatTuTheoViTri(DanhSachVatTu &dsVatTu, int viTriXoa) {
	if (viTriXoa < 0 || viTriXoa > dsVatTu.N || kiemTraRong(dsVatTu)) return false;
	
	for (int i = viTriXoa;  i < dsVatTu.N; i++ )
		dsVatTu.NODE[i] = dsVatTu.NODE[i + 1];
	
	dsVatTu.N--;
	
	return true;	
}

// Luu Danh sach Vat tu vao file VatTu.txt
void luuDanhSachVatTuVaoFile(DanhSachVatTu &dsVatTu){
	ofstream fileOut(FILE_VAT_TU);
	if(!fileOut) return;
	
	for (int i = 0; i < dsVatTu.N; i++){
		if (i > 0) fileOut << endl;
		fileOut << dsVatTu.NODE[i].MAVT << endl;
		fileOut << dsVatTu.NODE[i].TENVT << endl;
		fileOut << dsVatTu.NODE[i].DVT << endl;
		fileOut << dsVatTu.NODE[i].SOLUONGTON;
	}
	
	fileOut.close();
}

// Nap Danh Sach Vat Tu tu file "VatTu.txt" vao bo nho
void napDanhSachVatTuTuFile(DanhSachVatTu &dsVatTu){
	ifstream fileIn(FILE_VAT_TU);
	if (!fileIn){
		dsVatTu.N = 0;
		return;
	}	
	
	VatTu vt;
	string str;
	
	while(!fileIn.eof()){
		getline(fileIn, str);
		if (str != ""){
			vt.MAVT = str;
			getline(fileIn, vt.TENVT);
			getline(fileIn, vt.DVT);
			
			getline(fileIn, str);
			stringstream(str) >> vt.SOLUONGTON;
			
			themVatTuSapXepTheoMa(dsVatTu, vt);
		}
	}
	
	fileIn.close();
}



/*~~~~~~~~~~~~~~~~~~~~~~ TAM: THEM MOI VAT TU ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// Ve giao dien Them moi vat tu
void veGiaoDienThemMoiVatTu(){
	SetColor(RED);
	SetBGColor(BG_BODY);
	
	// Xoa noi dung trong body
	for (int i = 0; i < HEIGHT_BODY; i ++)
		for (int j = 0; j < WIDTH_BODY; j++){
			gotoxy(TOADOX+WIDTH_MENU_BAR + j, TOADOY + HEIGHT_HEADER + i);
			cout << " ";
		}
		
	// Tieu De
	string tieuDe = "THEM MOI VAT TU";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - tieuDe.length()) / 2, TOADOY + HEIGHT_HEADER + 1 );
	cout << tieuDe;
	
	// Nhap thong tin vat tu
	int toaDoXNhan = TOADOX + WIDTH_MENU_BAR + 30;
	int toaDoYNhan = TOADOY + HEIGHT_HEADER + 5;
	int toaDoXInputText = toaDoXNhan + 15;
	int toaDoYInputText = toaDoYNhan - 1;
	
	for (int i = 0; i < SIZE_THUOC_TINH_VT; i++) {
		gotoxy(toaDoXNhan, toaDoYNhan + 3 * i);
		cout << thuocTinhVatTu[i];
		veInputText(toaDoXInputText, toaDoYInputText + 3 * i);
	}
	
	// Ve Footer
	gotoxy(TOADOX + WIDTH_MENU_BAR, TOADOY + HEIGHT_HEADER + HEIGHT_BODY);
	for (int i = 0; i < SCREEN_WIDTH-WIDTH_MENU_BAR; i++)
		cout << char(196);
	for (int i = 0; i < HEIGHT_FOOTER - 1; i++){
		gotoxy(TOADOX + WIDTH_MENU_BAR, TOADOY + HEIGHT_HEADER + HEIGHT_BODY + i + 1);
		for (int j = 0; j < WIDTH_BODY; j++){
			cout << " ";
		}
	}
	string strHuongDan = "ESC: Tro ve \t F5: Luu";
	gotoxy(TOADOX + WIDTH_MENU_BAR+(SCREEN_WIDTH-WIDTH_MENU_BAR-strHuongDan.length())/2, SCREEN_HEIGTH );
	cout << strHuongDan;
}

// Them moi Vat Tu: tra ve vi tri duoc them vao danh sach
int themMoiVatTu(DanhSachVatTu &dsVatTu){
	// Giao dien them moi vat tu
	veGiaoDienThemMoiVatTu();
	
	VatTu vt;
	int c;
	int viTriNhapLieu = 0;
	string soLuongStr = "";
	string maVT = "";
	string errors [SIZE_THUOC_TINH_VT] = {"", "", "", ""};
	
	
	int toaDoXNhan = TOADOX + WIDTH_MENU_BAR + 30;
	int toaDoYNhan = TOADOY + HEIGHT_HEADER + 5;
	int toaDoXInputText = toaDoXNhan + 16;
	int toaDoYInputText = toaDoYNhan ;
	
	do {
		switch (viTriNhapLieu){
			// Nhap MAVT
			case 0:
				c = nhapChuoiKiTuVaSo(maVT, toaDoXInputText , toaDoYInputText + viTriNhapLieu * 3, WIDTH_INPUT_TEXT - 2, BG_BODY, BLACK);
				
				// Xoa thong bao nhap loi!!!
				gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
				
				// Kiem tra MAVT: Rong & co ky tu khoang trang ko?
				if (maVT.length() <= 0) {
					// Noi dung thong bao
					errors[viTriNhapLieu] = "Muc nay khong duoc de trong!";
					
					// Thong bao Loi!!!
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
					//Kiem tra MAVT co trung ko?
				}else if (timKiemVatTu(dsVatTu, maVT) > -1){
					// Noi dung thong bao
					errors[viTriNhapLieu] = "Ma " + vt.MAVT + " da ton tai!";
					
					// Thong bao Loi!!!
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
					// Kiem tra MAVT co ' ' ko ?
				} else if (kiemTraChuoiCoKhoangTrang(maVT)){
					// Noi dung thong bao
					errors[viTriNhapLieu] = "Ma VT khong duoc co ky tu khoang trang!";
					
					// Thong bao Loi!!!
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
				} else {
					vt.MAVT = maVT;
					maVT = "";
					errors[viTriNhapLieu] = "";
				}
				
				break;
				
			// Nhap TENVT
			case 1:	
				c = nhapChuoiKiTuVaSo(vt.TENVT, toaDoXInputText , toaDoYInputText + viTriNhapLieu * 3,WIDTH_INPUT_TEXT - 2, BG_BODY, BLACK);
				
				// Xoa thong bao nhap loi!!!
				gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
					
					// Kiem tra rong
				if (vt.TENVT.length() <= 0) {	
					// Noi dung thong bao
					errors[viTriNhapLieu] = "Muc nay khong duoc de trong!";
					
					// Thong bao Loi!!!
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];

				} else errors[viTriNhapLieu] = "";
					
				break;
				
			// Nhap DVT
			case 2:	
				c = nhapChuoiKiTuVaSo(vt.DVT, toaDoXInputText , toaDoYInputText + viTriNhapLieu * 3,WIDTH_INPUT_TEXT - 2, BG_BODY, BLACK);
				
				// Xoa thong bao nhap loi!!!
				gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
					
				if (vt.DVT.length() <= 0) {
					// Noi dung thong bao
					errors[viTriNhapLieu] = "Muc nay khong duoc de trong!";
					
					// Thong bao Loi!!!
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];

				} else errors[viTriNhapLieu] = "";
				
				break;
			
			// Nhap SOLUONGTON
			case 3:	
				c = nhapChuoiKiTuSo(soLuongStr, toaDoXInputText , toaDoYInputText + viTriNhapLieu * 3,WIDTH_INPUT_TEXT - 2, BG_BODY, BLACK);
				
				// Xoa thong bao nhap loi!!!
				gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
					
				if (soLuongStr.length() <= 0) {
					// Noi dung thong bao
					errors[viTriNhapLieu] = "Muc nay khong duoc de trong!";
					
					// Thong bao Loi!!!
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
				} else errors[viTriNhapLieu] = "";
				
				break;
		}
		
		if (c == KEY_DOWN && viTriNhapLieu < SIZE_THUOC_TINH_VT - 1) viTriNhapLieu++;
		
		if (c == KEY_UP && viTriNhapLieu > 0) viTriNhapLieu--;
		
		if(c == KEY_F5){
			if (vt.MAVT.length() > 0 && vt.TENVT.length() > 0 && vt.DVT.length() > 0 && soLuongStr.length() > 0) {
				stringstream(soLuongStr) >> vt.SOLUONGTON;
				themVatTuSapXepTheoMa(dsVatTu, vt);
				
				luuDanhSachVatTuVaoFile(dsVatTu);
				
				string noiDungThongBao = "Them thanh cong: " + vt.MAVT + " - " + vt.TENVT;
				thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);
			
				return timKiemVatTu(dsVatTu, vt.MAVT);
			}	
		}
		
	} while (c != KEY_ESC);
	
	return -1;
}


/*~~~~~~~~~~~~~~~~~~~~~~ TAM: CAP NHAT VAT TU ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// Ve Giao dien cap nhat Vat tu
void veGiaoDienCapNhatThongTinVatTu(){
	SetColor(RED);
	SetBGColor(BG_BODY);
	
	// Xoa noi dung trong body
	for (int i = 0; i < HEIGHT_BODY; i ++)
		for (int j = 0; j < WIDTH_BODY; j++){
			gotoxy(TOADOX+WIDTH_MENU_BAR + j, TOADOY + HEIGHT_HEADER + i);
			cout << " ";
		}
		
	// Tieu De
	string tieuDe = "CAP NHAT THONG TIN VAT TU";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - tieuDe.length()) / 2, TOADOY + HEIGHT_HEADER + 1 );
	cout << tieuDe;
	
	// Nhap thong tin vat tu
	int toaDoXNhan = TOADOX + WIDTH_MENU_BAR + 30;
	int toaDoYNhan = TOADOY + HEIGHT_HEADER + 5;
	int toaDoXInputText = toaDoXNhan + 15;
	int toaDoYInputText = toaDoYNhan - 1;
	
	for (int i = 0; i < SIZE_THUOC_TINH_VT; i++) {
		gotoxy(toaDoXNhan, toaDoYNhan + 3 * i);
		cout << thuocTinhVatTu[i];
		veInputText(toaDoXInputText, toaDoYInputText + 3 * i);
	}
	
	// Ve Footer
	gotoxy(TOADOX + WIDTH_MENU_BAR, TOADOY + HEIGHT_HEADER + HEIGHT_BODY);
	for (int i = 0; i < SCREEN_WIDTH-WIDTH_MENU_BAR; i++)
		cout << char(196);
	for (int i = 0; i < HEIGHT_FOOTER - 1; i++){
		gotoxy(TOADOX + WIDTH_MENU_BAR, TOADOY + HEIGHT_HEADER + HEIGHT_BODY + i + 1);
		for (int j = 0; j < WIDTH_BODY; j++){
			cout << " ";
		}
	}
	string strHuongDan = "ESC: Tro ve \t F5: Luu";
	gotoxy(TOADOX + WIDTH_MENU_BAR+(SCREEN_WIDTH-WIDTH_MENU_BAR-strHuongDan.length())/2, SCREEN_HEIGTH );
	cout << strHuongDan;
}

// Cap nhat vat tu
void capNhatThongTinVatTu(DanhSachVatTu &dsVatTu, VatTu vt){
	// Ve giao dien
	veGiaoDienCapNhatThongTinVatTu();
	
	int c;
	int viTriNhapLieu = 1;
	int toaDoXNhan = TOADOX + WIDTH_MENU_BAR + 30;
	int toaDoYNhan = TOADOY + HEIGHT_HEADER + 5;
	int toaDoXInputText = toaDoXNhan + 16;
	int toaDoYInputText = toaDoYNhan ;
	
	// In thong tin vat tu vao input
	// Khong cho cap nhat
	SetColor(RED);
	gotoxy(toaDoXInputText, toaDoYInputText + 0 * 3);
	cout << vt.MAVT;
	gotoxy(toaDoXInputText, toaDoYInputText + 3 * 3);
	cout << vt.SOLUONGTON;
	
	// cho phep cap nhat
	SetColor(BLACK);
	gotoxy(toaDoXInputText, toaDoYInputText + 1 * 3);
	cout << vt.TENVT;
	gotoxy(toaDoXInputText, toaDoYInputText + 2 * 3);
	cout << vt.DVT;
	
	string errors[2] = {"", ""};
	
	do {
		switch(viTriNhapLieu){
			// Cap nhat TENVT
			case 1:	
				c = nhapChuoiKiTuVaSo(vt.TENVT, toaDoXInputText , toaDoYInputText + viTriNhapLieu * 3,WIDTH_INPUT_TEXT, BG_BODY, BLACK);
				
				// Xoa thong bao nhap loi!!!
				gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
				for (int i = 0; i < errors[0].length(); i++) cout << " ";
				
				if (vt.TENVT.length() <= 0) {				
					// Noi dung thong bao
					errors[0] = "Muc nay khong duoc de trong!";
					
					// Thong bao Loi!!!
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[0];
					
				} else errors[0] = "";
				
				break;
			
			// Cap nhat DVT
			case 2:	
				c = nhapChuoiKiTuVaSo(vt.DVT, toaDoXInputText , toaDoYInputText + viTriNhapLieu * 3,WIDTH_INPUT_TEXT, BG_BODY, BLACK);

				// Xoa thong bao nhap loi!!!
				gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
				for (int i = 0; i < errors[1].length(); i++) cout << " ";
				
				if (vt.DVT.length() <= 0) {
					// Noi dung thong bao
					errors[1] = "Muc nay khong duoc de trong!";
					
					// Thong bao Loi!!!
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInputText + WIDTH_INPUT_TEXT + 1, toaDoYInputText + viTriNhapLieu * 3);
					cout << errors[1];
					
				} else errors[1] = "";
				
				break;
		}
		
		if (c == KEY_DOWN) viTriNhapLieu = 2;
		
		if (c == KEY_UP) viTriNhapLieu = 1;
		
		if(c == KEY_F5){
			int viTri = timKiemVatTu(dsVatTu, vt.MAVT);
			if (viTri > -1 && vt.TENVT.length() > 0 && vt.DVT.length() > 0){
				
			 	dsVatTu.NODE[viTri] = vt;
				
				luuDanhSachVatTuVaoFile(dsVatTu);
				
				// Thong bao
				string noiDungThongBao = "Cap nhat thanh cong: " + vt.MAVT + " - " + vt.TENVT;
				thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);
				break;
			}
		}
	} while (c != KEY_ESC);
}



/*~~~~~~~~~~~~~~~~~~~~~~ TAM: XOA VAT TU ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// Xoa Vat tu (true: xoa | false: huy)
bool xoaVatTu(DanhSachVatTu &dsVatTu, string maVT) {
	int vtVatTuXoa = timKiemVatTu(dsVatTu, maVT);
	if (vtVatTuXoa > -1){
		VatTu vt = dsVatTu.NODE[vtVatTuXoa];
		string noiDungThongBao = "Ban co muon xoa " + vt.MAVT + " - " + vt.TENVT + " khong?";
		
		int xacNhanXoa = hopThoaiLuaChon(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5)/2, noiDungThongBao.length() + 10, 5 );
		if(xacNhanXoa == 1){
			xoaVatTuTheoViTri(dsVatTu, vtVatTuXoa);
			luuDanhSachVatTuVaoFile(dsVatTu);
			
			// Thong bao
			noiDungThongBao = "Da xoa Vat tu: " + vt.MAVT + " - " + vt.TENVT;
			thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);
			
			return true;
		}
	}
	return false;
}



/*~~~~~~~~~~~~~~~~~~~~~~ TAM: DANH SACH VAT TU ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// Ve giao dien danh sach vat tu
void veGiaoDienDanhSachVatTu(int tongTrang, int trang, int toaDoX, int toaDoY, int soCot, int soDong, int kichThuocO, string chucNang){
	SetColor(RED);
	SetBGColor(BG_BODY);
	
	// Xoa noi dung trong body
	for (int i = 0; i < HEIGHT_BODY; i ++)
		for (int j = 0; j < WIDTH_BODY; j++){
			gotoxy(TOADOX+WIDTH_MENU_BAR + j, TOADOY + HEIGHT_HEADER + i);
			cout << " ";
		}
	
	// Tieu De
	string tieuDe = "DANH SACH VAT TU";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - tieuDe.length()) / 2, TOADOY + HEIGHT_HEADER + 1 );
	cout << tieuDe;
	
	//Ve Bang Danh sach VAT TU
	veBangDanhSach(toaDoX, toaDoY, soCot, soDong, kichThuocO);
	
	// Ghi Nhan cho Bang Danh Sach
	SetColor(RED);
	SetBGColor(BG_BODY);
	int toaDoXNhan;
	for (int i = 0; i < SIZE_BANG_DANH_SACH_VT; i++){
		toaDoXNhan = toaDoX + i * (kichThuocO + 1) + 1 + (kichThuocO - tenCotBangVatTu[i].length()) / 2;
		gotoxy(toaDoXNhan, toaDoY + 1);
		cout << tenCotBangVatTu[i];
	}
	
	// Ve Footer
	gotoxy(TOADOX + WIDTH_MENU_BAR, TOADOY + HEIGHT_HEADER + HEIGHT_BODY);
	SetColor(RED);
	SetBGColor(BG_BODY);
	for (int i = 0; i < SCREEN_WIDTH-WIDTH_MENU_BAR; i++)
		cout << char(196);
	for (int i = 0; i < HEIGHT_FOOTER - 1; i++){
		gotoxy(TOADOX + WIDTH_MENU_BAR, TOADOY + HEIGHT_HEADER + HEIGHT_BODY + i + 1);
		for (int j = 0; j < WIDTH_BODY; j++){
			cout << " ";
		}
	}
	
	gotoxy(TOADOX + WIDTH_MENU_BAR+(SCREEN_WIDTH-WIDTH_MENU_BAR-chucNang.length())/2, SCREEN_HEIGTH );
	cout << chucNang;
}

// Xoa du lieu trong bang danh sach vat tu
void xoaDuLieuTrongBangDanhSachVatTu(int toaDoX, int toaDoY, int soCot, int soDong, int kichThuocO){
	SetColor(GRAY);
	SetBGColor(BG_BODY);

	int toaDoXCuaConTro;
	int toaDoYCuaConTro;
	int dong = 0;
	
	for (int i = 0; i < SL_VAT_TU_TRONG_TRANG; i++){
		
		toaDoYCuaConTro = toaDoY + 3 + 2 * dong;
		dong++;
		
		// IN STT
		toaDoXCuaConTro = toaDoX + 0 * (kichThuocO + 1) + 1;
		gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
		for (int k = 0; k < kichThuocO; k++) cout << " ";
		
		// IN MAVT
		toaDoXCuaConTro = toaDoX + 1 * (kichThuocO + 1) + 1;
		gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
		for (int k = 0; k < kichThuocO; k++) cout << " ";
		
		// IN TENVT
		toaDoXCuaConTro = toaDoX + 2 * (kichThuocO + 1) + 1;
		gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
		for (int k = 0; k < kichThuocO; k++) cout << " ";
		
		// IN DVT
		toaDoXCuaConTro = toaDoX + 3 * (kichThuocO + 1) + 1;
		gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
		for (int k = 0; k < kichThuocO; k++) cout << " ";
		
		// IN SOLUONGTON
		toaDoXCuaConTro = toaDoX + 4 * (kichThuocO + 1) + 1;
		gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
		for (int k = 0; k < kichThuocO; k++) cout << " ";
	
	}
}

// Nap du lieu vao bang danh sach vat tu
void napDuLieuVaoBangDanhSachVatTu(DanhSachVatTu &dsVatTu, int tongTrang, int trang, int toaDoX, int toaDoY, int soCot, int soDong, int kichThuocO){
	// Xoa du lieu trong bang
	xoaDuLieuTrongBangDanhSachVatTu(toaDoX, toaDoY, soCot, soDong, kichThuocO);
	
	// Ghi du lieu moi vao bang
	SetColor(BLACK);	
	int toaDoXCuaConTro;
	int toaDoYCuaConTro;	
	int vtDau = (trang - 1) * SL_VAT_TU_TRONG_TRANG;	
	int tam = 0;
	string str;
	
	for (int i = vtDau; i < trang * SL_VAT_TU_TRONG_TRANG && i < dsVatTu.N; i++){
		
		toaDoYCuaConTro = toaDoY + 3 + 2 * tam;
		tam++;
		
		// IN STT
		str = chuyenSoThanhChuoi(i + 1);
		toaDoXCuaConTro = toaDoX + 0 * (kichThuocO + 1) + 1 + (kichThuocO - str.length()) / 2;
		gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
		cout << str;
		
		// IN MAVT
		toaDoXCuaConTro = toaDoX + 1 * (kichThuocO + 1) + 1 + (kichThuocO - dsVatTu.NODE[i].MAVT.length()) / 2;
		gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
		cout << dsVatTu.NODE[i].MAVT;
		
		// IN TENVT
		toaDoXCuaConTro = toaDoX + 2 * (kichThuocO + 1) + 1 + (kichThuocO - dsVatTu.NODE[i].TENVT.length()) / 2;
		gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
		cout << dsVatTu.NODE[i].TENVT;
		
		// IN DVT
		toaDoXCuaConTro = toaDoX + 3 * (kichThuocO + 1) + 1 + (kichThuocO - dsVatTu.NODE[i].DVT.length()) / 2;
		gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
		cout << dsVatTu.NODE[i].DVT;
		
		// IN SOLUONGTON
		str = chuyenSoThanhChuoi(dsVatTu.NODE[i].SOLUONGTON);
		toaDoXCuaConTro = toaDoX + 4 * (kichThuocO + 1) + 1 + (kichThuocO - str.length()) / 2;
		gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
		cout << dsVatTu.NODE[i].SOLUONGTON;
	
	}
	
	// phan trang
	SetColor(RED);
	SetBGColor(BG_BODY);
	string strTrang = "Trang: " + chuyenSoThanhChuoi(trang) + "/" + chuyenSoThanhChuoi(tongTrang);	
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - strTrang.length()) / 2, TOADOY + HEIGHT_HEADER + HEIGHT_BODY - 3);
	cout << strTrang;
}

// Tra ve tong so trang trong Bang Danh sach Vat tu
int tongSoTrangVatTu(DanhSachVatTu &dsVatTu){
	return dsVatTu.N / SL_VAT_TU_TRONG_TRANG + (dsVatTu.N % SL_VAT_TU_TRONG_TRANG == 0 ? 0 : 1);
}

// Giao dien Vat Tu
void giaoDienVatTu(DanhSachVatTu &dsVatTu){	
	if (kiemTraRong(dsVatTu)){
		// Thong bao Danh sach vat tu rong
		string noiDungThongBao = "Danh sach VAT TU rong!";
		thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);	
	} else {
		int trang = 1;
		int tongTrang = tongSoTrangVatTu(dsVatTu);
		int vtLuaChon = 1;
		int c;
		string s;
		
		int soCot = SIZE_BANG_DANH_SACH_VT;
		int soDong = SL_VAT_TU_TRONG_TRANG + 1; // +1 dong cho nhan de
		int kichThuocO = 22;
		int toaDoX = TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - soCot * kichThuocO - soCot - 1) / 2;
		int toaDoY = TOADOY + HEIGHT_HEADER + 3;
		string strHuongDan = "ESC: Thoat \t INSERT: Them \t DELETE: Xoa \t F2: Cap nhat \t <-Trang truoc \t Trang sau->";
		// Ve form danh sach
		veGiaoDienDanhSachVatTu(tongTrang, trang, toaDoX, toaDoY, soCot, soDong, kichThuocO, strHuongDan);
		// Nap du lieu vao ban
		napDuLieuVaoBangDanhSachVatTu(dsVatTu, tongTrang, trang, toaDoX, toaDoY, soCot, soDong, kichThuocO);	
		// Ve con tro
		SetColor(RED);
		gotoxy(toaDoX - 3, toaDoY + 3);
		cout << "->";
		
		do {
			c = keyPressed();
			
			// CHUYEN VI TRI CON TRO
			if (c == KEY_UP){
				if (vtLuaChon > 1){
					// Xoa con tro
					SetColor(RED);
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "  ";
					// Gan vi tri moi cho con tro
					vtLuaChon--;
					// Ve con tro
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "->";
				}
			} else if (c == KEY_DOWN){
				if (vtLuaChon < SL_VAT_TU_TRONG_TRANG && (vtLuaChon + (trang - 1) * SL_VAT_TU_TRONG_TRANG) < dsVatTu.N ) 
				{
					// Xoa con tro
					SetColor(RED);
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "  ";
					// Gan vi tri moi cho con tro
					vtLuaChon++;
					// Ve con tro
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "->";
				}
			
			// CHUYEN TRANG
			} else if(c == KEY_LEFT) {
				if (trang > 1){
					trang--;	

					// Nap du lieu vao ban
					napDuLieuVaoBangDanhSachVatTu(dsVatTu, tongTrang, trang, toaDoX, toaDoY, soCot, soDong, kichThuocO);	
					
					// Xoa con tro
					SetColor(RED);
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "  ";
					// Gan vi tri moi cho con tro
					vtLuaChon = 1;	
					// Ve con tro
					SetColor(RED);
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "->";
				} 
			} else if(c == KEY_RIGHT){
				if (trang < tongTrang){
					trang++;
						
					// Nap du lieu vao ban
					napDuLieuVaoBangDanhSachVatTu(dsVatTu, tongTrang, trang, toaDoX, toaDoY, soCot, soDong, kichThuocO);	
					
					// Xoa con tro
					SetColor(RED);
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "  ";
					// Gan vi tri moi cho con tro
					vtLuaChon = 1;	
					// Ve con tro
					SetColor(RED);
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "->";
				} 
			
			// THEM MOI VAT TU
			} else if (c == KEY_INSERT){
				int viTriVT = themMoiVatTu(dsVatTu);	// Tra ve vi tri Vat tu them moi (= -1 : huy)
				if (viTriVT > -1){
					tongTrang = tongSoTrangVatTu(dsVatTu);
					trang = ((viTriVT + 1) / SL_VAT_TU_TRONG_TRANG) + ((viTriVT + 1)%SL_VAT_TU_TRONG_TRANG == 0 ? 0 : 1);
					vtLuaChon = (viTriVT + 1)%SL_VAT_TU_TRONG_TRANG;
				}
						
				// ve form danh sach
				veGiaoDienDanhSachVatTu(tongTrang, trang, toaDoX, toaDoY, soCot, soDong, kichThuocO, strHuongDan);
			
				// Nap du lieu vao ban
				napDuLieuVaoBangDanhSachVatTu(dsVatTu, tongTrang, trang, toaDoX, toaDoY, soCot, soDong, kichThuocO);	
						
				// Ve con tro
				SetColor(RED);
				gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
				cout << "->";
					
						
			// CAP NHAT THONG TIN VAT TU
			} else if (c == KEY_F2){
				int vtVatTu = (trang - 1) * SL_VAT_TU_TRONG_TRANG + vtLuaChon - 1;
				capNhatThongTinVatTu(dsVatTu, dsVatTu.NODE[vtVatTu]);
												
				// ve form danh sach
				veGiaoDienDanhSachVatTu(tongTrang, trang, toaDoX, toaDoY, soCot, soDong, kichThuocO, strHuongDan);
				// Nap du lieu vao ban
				napDuLieuVaoBangDanhSachVatTu(dsVatTu, tongTrang, trang, toaDoX, toaDoY, soCot, soDong, kichThuocO);	
	
				// Ve con tro
				SetColor(RED);
				gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
				cout << "->";
						
			// XOA VAT TU	
			} else if (c == KEY_DELETE) {
				int vtVatTuXoa = (trang - 1) * SL_VAT_TU_TRONG_TRANG + vtLuaChon - 1;
				bool kqXoa = xoaVatTu(dsVatTu, dsVatTu.NODE[vtVatTuXoa].MAVT);
				if (kqXoa) {
					tongTrang = tongSoTrangVatTu(dsVatTu);		
					if (trang > 1 && vtLuaChon == 1){
						trang--;
						vtLuaChon = SL_VAT_TU_TRONG_TRANG;
					} else if (vtLuaChon > 1) vtLuaChon--;
				}
				
				// ve form danh sach
				veGiaoDienDanhSachVatTu(tongTrang, trang, toaDoX, toaDoY, soCot, soDong, kichThuocO, strHuongDan);
				// Nap du lieu vao ban
				napDuLieuVaoBangDanhSachVatTu(dsVatTu, tongTrang, trang, toaDoX, toaDoY, soCot, soDong, kichThuocO);	
					
				// Xoa con tro
				SetColor(RED);
				gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
				cout << "  ";
				// Gan vi tri moi cho con tro
				vtLuaChon = 1;	
				// Ve con tro
				SetColor(RED);
				gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
				cout << "->";
	
			} 
	
		} while (c != KEY_ESC);
	} 
}


// Tra ve mang chua danh sach so luong xuat cua vat tu trong 2 khoang thoi gian
int* thongKeVatTuTheoSoLuongXuat(NHANVIENTREE root, DanhSachVatTu &dsVatTu, Date ngayBD, Date ngayKT) {
	Stack sp = NULL;
	NHANVIENTREE p = root;
	HOADONPTR dsHoaDon;
	DSCTHOADONPTR dsCTHoaDon;
	int *soLuongVatTu = new int[dsVatTu.N]{0};
	int viTriVatTu;
	
	// Duyet DS NHANVIEN -> DSHOADON
	do {
		while(p != NULL){
			push(sp, p);
			p = p->LEFT;
		}
		
		if(sp != NULL){
			pop(sp, p);
			if(p->NHANVIEN.DS_HOADON != NULL){
				dsHoaDon = p->NHANVIEN.DS_HOADON;
				// Duyet DSHOADON -> DSCTHOADON
				while(dsHoaDon != NULL){
					// if :: LOAI == Xuat && DSCTHOADON != NULL && ngayBD < NGAYLAP, ngayKT > NGAYLAP
					if (dsHoaDon->HOADON.LOAI == 'X' && dsHoaDon->HOADON.DSCTHOADON != NULL && kiemTraNgayGiua2Ngay(ngayBD, ngayKT, dsHoaDon->HOADON.NGAYLAP) == 1){
						dsCTHoaDon = dsHoaDon->HOADON.DSCTHOADON ;
						// Duyet DSCTHOADON -> DSVATTU
						while(dsCTHoaDon != NULL){
							viTriVatTu = timKiemVatTu(dsVatTu, dsCTHoaDon->CTHOADON.MAVT);
							soLuongVatTu[viTriVatTu] += dsCTHoaDon->CTHOADON.SOLUONG;
							
							dsCTHoaDon = dsCTHoaDon->NEXT;
						}
					}
					
					dsHoaDon = dsHoaDon->NEXT;
				}
			}
			
			p = p->RIGHT;
		} else break;
		
	} while (true);
	
	return soLuongVatTu;		
}



void xemDanhSachVatTu(DanhSachVatTu &dsVatTu){	
	if (kiemTraRong(dsVatTu)){
		// Thong bao Danh sach vat tu rong
		string noiDungThongBao = "Danh sach VAT TU rong!";
		thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);	
	} else {
		int trang = 1;
		int tongTrang = tongSoTrangVatTu(dsVatTu);
		int vtLuaChon = 1;
		int c;
		string s;
		
		int soCot = SIZE_BANG_DANH_SACH_VT;
		int soDong = SL_VAT_TU_TRONG_TRANG + 1; // +1 dong cho nhan de
		int kichThuocO = 22;
		int toaDoX = TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - soCot * kichThuocO - soCot - 1) / 2;
		int toaDoY = TOADOY + HEIGHT_HEADER + 3;
		string strHuongDan = "ESC: Thoat \t <-Trang truoc \t Trang sau->";
		// Ve form danh sach
		veGiaoDienDanhSachVatTu(tongTrang, trang, toaDoX, toaDoY, soCot, soDong, kichThuocO, strHuongDan);
		// Nap du lieu vao ban
		napDuLieuVaoBangDanhSachVatTu(dsVatTu, tongTrang, trang, toaDoX, toaDoY, soCot, soDong, kichThuocO);	
		// Ve con tro
		SetColor(RED);
		gotoxy(toaDoX - 3, toaDoY + 3);
		cout << "->";
	
		do {
			c = keyPressed();
			
			// CHUYEN VI TRI CON TRO
			if (c == KEY_UP){
				if (vtLuaChon > 1){
					// Xoa con tro
					SetColor(RED);
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "  ";
					// Gan vi tri moi cho con tro
					vtLuaChon--;
					// Ve con tro
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "->";
				}
			} else if (c == KEY_DOWN){
				if (vtLuaChon < SL_VAT_TU_TRONG_TRANG && (vtLuaChon + (trang - 1) * SL_VAT_TU_TRONG_TRANG) < dsVatTu.N ) 
				{
					// Xoa con tro
					SetColor(RED);
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "  ";
					// Gan vi tri moi cho con tro
					vtLuaChon++;
					// Ve con tro
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "->";
				}
			
			// CHUYEN TRANG
			} else if(c == KEY_LEFT) {
				if (trang > 1){
					trang--;	

					// Nap du lieu vao ban
					napDuLieuVaoBangDanhSachVatTu(dsVatTu, tongTrang, trang, toaDoX, toaDoY, soCot, soDong, kichThuocO);	
					
					// Xoa con tro
					SetColor(RED);
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "  ";
					// Gan vi tri moi cho con tro
					vtLuaChon = 1;	
					// Ve con tro
					SetColor(RED);
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "->";
				} 
			} else if(c == KEY_RIGHT){
				if (trang < tongTrang){
					trang++;
						
					// Nap du lieu vao ban
					napDuLieuVaoBangDanhSachVatTu(dsVatTu, tongTrang, trang, toaDoX, toaDoY, soCot, soDong, kichThuocO);	
					
					// Xoa con tro
					SetColor(RED);
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "  ";
					// Gan vi tri moi cho con tro
					vtLuaChon = 1;	
					// Ve con tro
					SetColor(RED);
					gotoxy(toaDoX - 3, toaDoY + 3 + (vtLuaChon - 1) * 2);
					cout << "->";
				} 
			
			}
		} while (c != KEY_ESC);
	
	}
}


#include "CT_HoaDon.cpp"


string lable[SIZE_FORM_HOA_DON] = {"So Hoa Don", "Ngay Lap", "Loai"};
string tenCotHoaDon[SO_COT_BANG_HOA_DON] = {"SO HD", "NGAY LAP", "LOAI HD", "HO TEN NV", "TRI GIA HD"};
string tenCotHoaDon2[SO_COT_BANG_HOA_DON] = {"STT", "SO HD", "NGAY NHAP", "LOAI", "TRI GIA HD"};
string tenCotThongKeVatTu[SO_COT_BANG_THONG_KE_VAT_TU] = {"STT", "MA VT", "TEN VT", "SO LUONG TON", "SO LUONG XUAT"};

bool kiemTraRong(HOADONPTR first){
	if(first == NULL) return true;
	return false;
}
// insert_first
bool themVaoDauDanhSach(HOADONPTR &first, HoaDon hd ){
	HOADONPTR p = new NodeHoaDon;
	if(p == NULL) return false;
	p->HOADON = hd;
	p->NEXT = first;
	first = p;
	return true;
}
// insert_last
bool themVaoCuoiDanhSach(HOADONPTR &first, HoaDon hd ){
	HOADONPTR p = new NodeHoaDon;
	if(p == NULL) return false;
	p->HOADON = hd;
	p->NEXT = NULL;
	
	// neu danh sach rong thi them vao dau
	if(first == NULL){
		first = p;
	}else{
		HOADONPTR q;
		// danh sasch khac rong
		// tim q la node cuoi cung cua danh sach
		for(q = first; q->NEXT != NULL; q=q->NEXT);
		q->NEXT = p;
	}
	return true;
}
// insert_after
bool themVaoSauMotNode(HOADONPTR &first, HOADONPTR p, HoaDon hd){
	if(p == NULL){
		cout << "Khong the them vao" << endl;
		return false;
	}else{
		HOADONPTR q = new NodeHoaDon;
		q->HOADON = hd;
		// q->next tro den Node sau Node can them vao
		q->NEXT = p->NEXT;
		// p->next tro den Node can them vao
		p->NEXT = q;
	}
	
	return true;
}

// insert_order
bool themSapXep(HOADONPTR &first, HoaDon hoaDon){
	HOADONPTR p = new NodeHoaDon;
	if(p == NULL) return false;
	p->HOADON = hoaDon;
	p->NEXT = NULL;
	
	// neu danh sach rong thi them vao dau
	if(first == NULL){
		first = p;
		return true;
	}
	HOADONPTR nodeHienTai = first;
	HOADONPTR nodeTruoc = NULL;
	// danh sasch khac rong
	// tim q la node cuoi cung cua danh sach
	while(nodeHienTai != NULL && nodeHienTai->HOADON.SOHD < hoaDon.SOHD){
		nodeTruoc = nodeHienTai;
		nodeHienTai = nodeHienTai->NEXT;
	}
	// neu la vi tri SOHD can them vao < SOHD cua hoa don dau tien trong danh sach
	if(nodeTruoc == NULL){
		themVaoDauDanhSach(first, hoaDon);
	}
	// Vi tri them se la cuoi danh sach hoac la vi tri sau truoc nodeHienTai
	// tuc la sau nodeTruoc
	else{
		themVaoSauMotNode(first, nodeTruoc, hoaDon);
	}
	
	return true;
}

//	delete_first
bool xoaNodeDauDanhSach(HOADONPTR &first){
	if(kiemTraRong(first)){
		cout << "danh sach rong, khong the xoa" << endl;
		return false;
	}
	// p la node can xoa
	HOADONPTR p = first;
	// di chuyen con tro first den node thu 2
	first = p->NEXT;
	delete p;
	return true;
}
// delete_after
bool xoaSauNode(HOADONPTR &first, HOADONPTR p){
	if(p == NULL || p->NEXT == NULL){
		cout << "Khong the xoa " << endl;
		return false;
	}
	// q la Node can xoa
	HOADONPTR q = p->NEXT;
	// bo lien ket giua p va q
	p->NEXT = q->NEXT;
	delete q;
	return true;
	
}
// delete_info
bool xoaNode_info(HOADONPTR &first, HoaDon hd){
	HOADONPTR p = first;
	if(p == NULL){
		cout << "Khong the xoa hoa don" << hd.SOHD << endl; 
		return false;
	}
	// neu node can xoa la node dau tien
	if(p->HOADON.SOHD == hd.SOHD){
		return	xoaNodeDauDanhSach(first);
		
	}
	p = first;
	// tim node p la node truoc node can xoa
	for(p; p->NEXT != NULL && p->NEXT->HOADON.SOHD != hd.SOHD; p = p->NEXT);
	// neu p->NEXT != NULL thi tim thay node can xoa
	if(p->NEXT != NULL){
		return	xoaSauNode(first, p);
	}
	else return false;
}

void duyetDanhSach(HOADONPTR first){
	
	if(first == NULL){
		cout << "Danh sach hoa don rong" << endl;
		return;
	}
	HOADONPTR p = first;
	while(p != NULL){
		cout << p->HOADON.SOHD << "\t" << p->HOADON.LOAI << "\t" << p->HOADON.NGAYLAP.NGAY << "/" << p->HOADON.NGAYLAP.NGAY << "/" << p->HOADON.NGAYLAP.NAM << endl;
		p = p->NEXT;
	}
	
}

int demSoHoaDon(HOADONPTR dsHoaDon){
	HOADONPTR p = dsHoaDon;
	int dem = 0;
	while(p != NULL){
	
		dem++;
		p = p->NEXT;
	}
	return dem;
}

HOADONPTR timKiemHoaDon(HOADONPTR dsHoaDon, string soHoaDon){
	HOADONPTR p = dsHoaDon;
	if(dsHoaDon == NULL) return NULL;
	while(p!= NULL){
		if(p->HOADON.SOHD == soHoaDon){
			break;
		}
		p = p->NEXT;
	}
	return p;
}

int timKiemViTriHoaDon(HOADONPTR dsHoaDon, string soHoaDon){
	HOADONPTR p = dsHoaDon;
	int dem = 0;
	if(dsHoaDon == NULL) return -1;
	while(p!= NULL){
		if(p->HOADON.SOHD == soHoaDon){
			return dem;
		}
		dem++;
		p = p->NEXT;
	}

	return dem;
}

HOADONPTR timKiemHoaDonThuN(HOADONPTR dsHoaDon, int viTri){
	HOADONPTR p = dsHoaDon;
	if(dsHoaDon == NULL) return NULL;
	int dem = 0;
	while(p!= NULL){
		if(dem == viTri){
			break;
		}
		dem++;
		p = p->NEXT;
	}
	return p;
}

void formHoaDon(NhanVien &nv, HoaDon hoaDon, string chucNang){
	veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, 15, BG_BODY);
	SetBGColor(BG_BODY);
	SetColor(BLACK);
	gotoxy(90, 8);
	cout << "NHAP HOA DON";
	gotoxy(30, 10);
	cout << "Nhan vien: " << nv.HO << " " << nv.TEN;
	// form nhap lieu
	//So hoa don
	SetBGColor(BG_BODY);
	SetColor(BLACK);
	gotoxy(TOADOX_LABLE, TOADOY_FORM + 0 * 2);
	cout << lable[0];
	veHinhChuNhat(TOADOX_TEXT, TOADOY_FORM + 0 * 2, 30, 1, BLACK);
	// ngay nhap
	SetBGColor(BG_BODY);
	SetColor(BLACK);
	gotoxy(TOADOX_LABLE, TOADOY_FORM + 1 * 2);
	cout << lable[1];
	veHinhChuNhat(TOADOX_TEXT, TOADOY_FORM + 1 * 2, 8, 1, BLACK);
	SetBGColor(BG_BODY);
	SetColor(BLACK);
	cout << " / ";
	veHinhChuNhat(TOADOX_TEXT +11, TOADOY_FORM + 1 * 2, 8, 1, BLACK); 
	SetBGColor(BG_BODY);
	SetColor(BLACK);
	cout << " / ";
	veHinhChuNhat(TOADOX_TEXT + 22, TOADOY_FORM + 1 * 2, 8, 1, BLACK);
	// loai
	SetBGColor(BG_BODY);
	SetColor(BLACK);
	gotoxy(TOADOX_LABLE, TOADOY_FORM + 2 * 2);
	cout << lable[2];
	veHinhChuNhat(TOADOX_TEXT, TOADOY_FORM + 2 * 2, 3, 1, BLACK);
	SetBGColor(BG_BODY);
	cout << " Nhap";
	veHinhChuNhat(TOADOX_TEXT + 15, TOADOY_FORM + 2 * 2, 3, 1, BLACK);
	SetBGColor(BG_BODY);
	cout << " Xuat";

	
	// footer
	//string s = "ESC: Thoat   Insert: Them vao danh sach   F5: Nhap danh sach vat tu   F12: Danh sach vat tu";
	gotoxy(TOADOX + WIDTH_MENU_BAR, SCREEN_HEIGTH -1);
	for(int i = 0; i < SCREEN_WIDTH - WIDTH_MENU_BAR; i++){
		SetBGColor(BG_BODY);
		SetColor(BG_HEADER);
		cout << char(196);
	}
	gotoxy(TOADOX + WIDTH_MENU_BAR+(SCREEN_WIDTH-WIDTH_MENU_BAR-chucNang.length())/2, SCREEN_HEIGTH );
	cout << chucNang;
	



}

void xuatHoaDonLenForm(HoaDon hoaDon, string ngayStr, string thangStr, string namStr){
	SetBGColor(BLACK);
	SetColor(TEXT_COLOR);
	
	gotoxy(TOADOX_TEXT, TOADOY_FORM + 0 * 2 );
	cout << hoaDon.SOHD;
	
	gotoxy(TOADOX_TEXT + 0 * 11, TOADOY_FORM + 1 * 2 );
	cout << ngayStr;
	
	gotoxy(TOADOX_TEXT + 1 * 11, TOADOY_FORM + 1 * 2 );
	cout << thangStr;
	
	gotoxy(TOADOX_TEXT + 2 * 11, TOADOY_FORM + 1 * 2 );
	cout << namStr;
	
	if(hoaDon.LOAI == 'N'){
		gotoxy(TOADOX_TEXT + 15, TOADOY_FORM + 2 * 2);
		cout << "   ";
		gotoxy(TOADOX_TEXT, TOADOY_FORM + 2 * 2);
		cout << " X ";
	}else{
		gotoxy(TOADOX_TEXT, TOADOY_FORM + 2 * 2);
		cout << "   ";
		gotoxy(TOADOX_TEXT + 15, TOADOY_FORM + 2 * 2);
		cout << " X ";
	}
}

void khungHoaDon(NhanVien nv,int soCot,int soHang,int  toaDoKhungX,int toaDoKhungY){
	veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
	SetBGColor(BG_BODY);
	SetColor(BG_HEADER);
	string tenBang = "BANG THONG TIN HOA DON DA LAP";
	gotoxy(TOADOX + WIDTH_MENU_BAR+(SCREEN_WIDTH - WIDTH_MENU_BAR - tenBang.length())/ 2, TOADOY + 5);
	cout << tenBang;
	SetBGColor(BG_BODY);
	SetColor(BLACK);
	gotoxy(30, 9);
	cout << "Nhan vien: " << nv.HO << " " << nv.TEN;
	SetBGColor(BG_BODY);
	SetColor(TEXT_COLOR);
	veKhungDanhSach(soCot, soHang, toaDoKhungX, toaDoKhungY );	
	//footer	
	SetBGColor(BG_BODY);
	SetColor(BG_HEADER);
	string s = "ESC: Thoat    DELETE: Xoa    F5: Sua    F2: Chi tiet    INSERT: Them hoa don    F9: Tim kiem    <-Trang truoc    Trang sau->";
	gotoxy(TOADOX + WIDTH_MENU_BAR, SCREEN_HEIGTH -1);
	for(int i = 0; i < SCREEN_WIDTH - WIDTH_MENU_BAR; i++){
		SetBGColor(BG_BODY);
		SetColor(BG_HEADER);
		cout << char(196);
	}
	gotoxy(TOADOX + WIDTH_MENU_BAR+(SCREEN_WIDTH-WIDTH_MENU_BAR-s.length())/2, SCREEN_HEIGTH );
	cout << s;
	//table column names
	for(int i = 0; i < soCot; i ++){
			gotoxy(toaDoKhungX + i * (TABLE_COLUMN_WIDTH + 1)+ (TABLE_COLUMN_WIDTH - tenCotHoaDon2[i].length())/2, toaDoKhungY + 1);
			cout << tenCotHoaDon2[i];
	}

}

void in1TrangDanhSachHoaDon(HOADONPTR first, int trang, int tongTrang, int toaDoKhungX, int toaDoKhungY){
	int viTri = (trang - 1) * SO_HANG_BANG_HOA_DON;
	HOADONPTR p = first;
	int dem = 0;
	while(p != NULL && dem < viTri){
		p = p->NEXT;
		dem++;
	}
	for(int i = 0; i < SO_HANG_BANG_HOA_DON; i++){
		veHinhChuNhat(toaDoKhungX + 0 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2+ 3,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 1 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i* 2+ 3,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 2 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2+ 3,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 3 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2+ 3,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 4 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2+ 3,TABLE_COLUMN_WIDTH, 1, BG_BODY);
	}
	SetBGColor(BG_BODY);
	SetColor(BLACK);
	string s;
	while(p != NULL && viTri < trang * SO_HANG_BANG_HOA_DON){
		
		gotoxy(toaDoKhungX + 0 * (TABLE_COLUMN_WIDTH + 1)+ (TABLE_COLUMN_WIDTH - 3)/2,  toaDoKhungY + (viTri % SO_HANG_BANG_HOA_DON) * 2+ 3);				
		cout << viTri + 1;
		gotoxy(toaDoKhungX + 1 * (TABLE_COLUMN_WIDTH + 1)+ (TABLE_COLUMN_WIDTH - p->HOADON.SOHD.length())/2,  toaDoKhungY + (viTri % SO_HANG_BANG_HOA_DON) * 2+ 3);				
		cout << p->HOADON.SOHD;
		s = chuyenNgayThanhChuoi(p->HOADON.NGAYLAP);
		gotoxy(toaDoKhungX + 2 * (TABLE_COLUMN_WIDTH + 1)+ (TABLE_COLUMN_WIDTH - s.length())/2,  toaDoKhungY + (viTri % SO_HANG_BANG_HOA_DON) * 2+ 3);				
		cout << s;
		gotoxy(toaDoKhungX + 3 * (TABLE_COLUMN_WIDTH + 1)+ (TABLE_COLUMN_WIDTH - 4)/2,  toaDoKhungY + (viTri % SO_HANG_BANG_HOA_DON) * 2+ 3);				
		if(p->HOADON.LOAI == 'X')	cout << "Xuat";
		else cout << "Nhap";
		gotoxy(toaDoKhungX + 4 * (TABLE_COLUMN_WIDTH + 1)+ (TABLE_COLUMN_WIDTH - s.length())/2,  toaDoKhungY + (viTri % SO_HANG_BANG_HOA_DON) * 2+ 3);				
		cout << tinhTienMotHoaDon(p->HOADON.DSCTHOADON);
		viTri++;
		p = p->NEXT;
	}
}

int nhapHoaDon(DanhSachVatTu &dsVatTu, NhanVien &nv, int &viTriHoaDonSauKhiThem){
	int c;
	int viTri = 0;
	int temp = 0;
	// viTri con tro hien tai cua bang CT hoa don
	int viTriCot = 0;
	int viTriDong = 0;
	HoaDon hoaDon;
	bool ketQua = false;
	veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
	string chucNang = "ESC: Thoat   Insert: Them vao danh sach   F5: Nhap danh sach vat tu   F2: Danh sach vat tu";
	formHoaDon(nv, hoaDon, chucNang);
	string  ngayStr = "", thangStr = "", namStr = "";
	ngayStr = chuyenSoThanhChuoi(hoaDon.NGAYLAP.NGAY);
	thangStr = chuyenSoThanhChuoi(hoaDon.NGAYLAP.THANG);
	namStr = chuyenSoThanhChuoi(hoaDon.NGAYLAP.NAM);
	//string dsCTHoaDon[MAX_LINE + 1][SO_COT_BANG_CT_HOA_DON] = {""};
	// khoi tao mang con tro 
	string **dsCTHoaDon = new string *[MAX_LINE];
	for(int i = 0; i < MAX_LINE; i++)
		dsCTHoaDon[i] = new string [SO_COT_BANG_CT_HOA_DON];
	for(int i = 0; i < MAX_LINE; i++)
		for(int j = 0; j < SO_COT_BANG_CT_HOA_DON; j++)
			dsCTHoaDon[i][j] = "";
	//
	chuyenDanhSachChiTietThanhMangHaiChieu(hoaDon.DSCTHOADON, dsCTHoaDon);
	xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);
	do{
		
		if(viTri == 0){
			c = nhapChuoiKiTuVaSoKhongKhoangTrang(hoaDon.SOHD, TOADOX_TEXT, TOADOY_FORM + viTri * 2, WIDTH_TEXT, BLACK, TEXT_COLOR);
		}else if(viTri == 1){
			do{
				
				if(temp == 0){
					c = nhapChuoiKiTuSo(ngayStr,TOADOX_TEXT + temp * 11, TOADOY_FORM + viTri * 2 ,2 , BLACK, TEXT_COLOR);
					stringstream(ngayStr) >> hoaDon.NGAYLAP.NGAY;
				}else if(temp == 1){
					c = nhapChuoiKiTuSo(thangStr,TOADOX_TEXT + temp * 11, TOADOY_FORM + viTri * 2 ,2 , BLACK, TEXT_COLOR);
					stringstream(thangStr) >> hoaDon.NGAYLAP.THANG;
				}else{
					c = nhapChuoiKiTuSo(namStr,TOADOX_TEXT + temp * 11, TOADOY_FORM + viTri * 2 ,4 , BLACK, TEXT_COLOR);
					stringstream(namStr) >> hoaDon.NGAYLAP.NAM;
				}
				if(c == KEY_RIGHT){
					if(temp < 2) temp++;
				}
					if(c == KEY_LEFT){
					if(temp > 0) temp--;
				}
		
			}while(c != KEY_UP && c != KEY_DOWN && c != KEY_ESC && c != KEY_INSERT && c != KEY_F5 && c != KEY_TAB && c!= KEY_F2);
		}else {
		
				do{
					if(hoaDon.LOAI == 'N'){
						gotoxy(TOADOX_TEXT + 15, TOADOY_FORM + 2 * 2);
						cout << "   ";
						gotoxy(TOADOX_TEXT, TOADOY_FORM + 2 * 2);
						cout << " X ";
					}else{
						gotoxy(TOADOX_TEXT, TOADOY_FORM + 2 * 2);
						cout << "   ";
						gotoxy(TOADOX_TEXT + 15, TOADOY_FORM + 2 * 2);
						cout << " X ";
						
				}
				c = keyPressed();
				if(c == KEY_RIGHT) hoaDon.LOAI = 'X';
				if(c== KEY_LEFT) hoaDon.LOAI = 'N';
				
				
			}while(c != KEY_UP && c != KEY_DOWN && c != KEY_ESC && c != KEY_INSERT && c != KEY_F5 && c!= KEY_F2);
			
		}
		
		if((c == KEY_DOWN || c == KEY_ENTER || c == KEY_TAB) && viTri < 2){
			viTri++;
			if(viTri == 1) temp =0;
		} 
	
		if(c == KEY_UP && viTri > 0){
			viTri--;
			if(viTri == 1) temp = 0;
		}
	
		if(c == KEY_INSERT){
			if(hoaDon.SOHD != ""){
				if(!kiemTraChuoiNhapVao(hoaDon.SOHD)){
					viTri = 0;
					thongBao("Ma nhan vien bao gom nhung ki tu a-z A-Z 0-9", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
					formHoaDon(nv, hoaDon, chucNang);
					xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);

				}else if(!kiemTraChuoiNhapVao(ngayStr)){
					viTri = 1;
					temp = 0;
					thongBao("Ngay bao gom nhung ki tu 0-9", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
					formHoaDon(nv, hoaDon, chucNang);
					xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);

				}else if(!kiemTraChuoiNhapVao(thangStr)){
					viTri = 1;
					temp = 1;
					thongBao("Thang bao gom nhung ki tu 0-9", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
					formHoaDon(nv, hoaDon, chucNang);
					xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);

					
				}else if(!kiemTraChuoiNhapVao(namStr)){
					viTri = 1;
					temp = 2;
					thongBao("Nam bao gom nhung ki tu 0-9", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
					formHoaDon(nv, hoaDon, chucNang);
					xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);

				}else{
					hoaDon.SOHD = dinhDangChuoiNhapVao(hoaDon.SOHD);
					ketQua = kiemTraThoiGianNhapHopLe(hoaDon.NGAYLAP.NGAY, hoaDon.NGAYLAP.THANG, hoaDon.NGAYLAP.NAM, temp);
				if(ketQua == 0){
						thongBao("Ngay Nhap Vao Khong Hop Le", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
						viTri = 1;
						formHoaDon(nv, hoaDon, chucNang);
						xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);
				}else{
					HOADONPTR p = timKiemHoaDon(nv.DS_HOADON, hoaDon.SOHD);
					if(p == NULL){
						ketQua = themSapXep(nv.DS_HOADON, hoaDon);
							if(ketQua == true){
								viTriHoaDonSauKhiThem = timKiemViTriHoaDon(nv.DS_HOADON, hoaDon.SOHD);
								thongBao("Them Hoa Don Cong", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
								break;
							}else{
								thongBao("Them Hoa Don That Bai", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
							formHoaDon(nv, hoaDon, chucNang);
								xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);
						}
					}else{
						viTri = 0;
						thongBao("Hoa Don Da Ton Tai", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
						formHoaDon(nv, hoaDon, chucNang);
						xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);
					}
				}
					
					
				}
				
			} else{
				viTri = 0;
				thongBao("Vui Long Nhap Vao So Hoa Don", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
			formHoaDon(nv, hoaDon, chucNang);
				xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);
			} 
		}	
	
		if(c == KEY_F5){
			if(hoaDon.SOHD != ""){
				do{
					c = nhapChiTietHoaDon(dsVatTu, nv , hoaDon, dsCTHoaDon, viTriDong, viTriCot);
					formHoaDon(nv, hoaDon, chucNang);
					xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);
					
				}while(c != KEY_ESC && c != KEY_INSERT);
				if(c == KEY_INSERT){
						if(hoaDon.SOHD != ""){
							
//							stringstream(ngayStr) >> hoaDon.NGAYLAP.NGAY;
//							stringstream(thangStr) >> hoaDon.NGAYLAP.THANG;
//							stringstream(namStr) >>hoaDon.NGAYLAP.NAM;
							HOADONPTR p = timKiemHoaDon(nv.DS_HOADON, hoaDon.SOHD);
							if(p == NULL){
								ketQua = themSapXep(nv.DS_HOADON, hoaDon);
									if(ketQua == true){
										thongBao("Them Hoa Don Cong", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
										break;
									}else{
										thongBao("Them Hoa Don That Bai", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
									formHoaDon(nv, hoaDon, chucNang);
										xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);
								}
							}else{
								thongBao("Hoa Don Da Ton Tai", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
							formHoaDon(nv, hoaDon, chucNang);
								xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);
							}	
						} else{
							thongBao("Vui Long Nhap Vao So Hoa Don", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
						formHoaDon(nv, hoaDon, chucNang);
							xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);
						} 
				}
				if(c == KEY_ESC) c = 1;
				
			}else{
					thongBao("Nhap Vao So Hoa Don", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
					formHoaDon(nv, hoaDon, chucNang);
					xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);
			}
		}
		
		if(c == KEY_F2){
			xemDanhSachVatTu(dsVatTu);
			string chucNang = "ESC: Thoat   Insert: Them vao danh sach   F5: Nhap danh sach vat tu   F2: Danh sach vat tu";
			veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, 30, BG_BODY);
			formHoaDon(nv, hoaDon, chucNang);
			xuatHoaDonLenForm(hoaDon, chuyenSoThanhChuoi(hoaDon.NGAYLAP.NGAY), chuyenSoThanhChuoi(hoaDon.NGAYLAP.THANG), chuyenSoThanhChuoi(hoaDon.NGAYLAP.NAM));
			
		}
		
	}while(c != KEY_ESC );
		
	// giai phong mang

	for(int i = 0; i < MAX_LINE; i++)
		delete[] dsCTHoaDon[i];
	delete[] dsCTHoaDon;
	//
	if(c == KEY_ESC) return -1;
	return c;
}

int capNhatHoaDon(DanhSachVatTu &dsVatTu, NhanVien &nv, HoaDon &hoaDon,int &viTriHoaDonSauKhiThem){
	int c;
	int viTri = 1;
	int temp = 0;
	// viTri con tro hien tai cua bang CT hoa don
	int viTriCot = 0;
	int viTriDong = 0;
	bool ketQua = false;
	veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
	string chucNang = "ESC: Thoat   Insert: Cap Nhat   F5: Nhap danh sach vat tu   F2: Danh sach vat tu";
	formHoaDon(nv, hoaDon, chucNang);
	string ngayStr = "", thangStr = "", namStr = "";

	ngayStr = chuyenSoThanhChuoi(hoaDon.NGAYLAP.NGAY);
	thangStr = chuyenSoThanhChuoi(hoaDon.NGAYLAP.THANG);
	namStr = chuyenSoThanhChuoi(hoaDon.NGAYLAP.NAM);
	
	//string dsCTHoaDon[MAX_LINE + 1][SO_COT_BANG_CT_HOA_DON] = {""};
	// khoi tao mang con tro 
	string **dsCTHoaDon = new string *[MAX_LINE];
	for(int i = 0; i < MAX_LINE; i++)
		dsCTHoaDon[i] = new string [SO_COT_BANG_CT_HOA_DON];
	for(int i = 0; i < MAX_LINE; i++)
		for(int j = 0; j < SO_COT_BANG_CT_HOA_DON; j++)
			dsCTHoaDon[i][j] = "";
	//
	chuyenDanhSachChiTietThanhMangHaiChieu(hoaDon.DSCTHOADON, dsCTHoaDon);
	xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);
	do{
		
		if(viTri == 1){
			do{
				
				if(temp == 0){
					c = nhapChuoiKiTuSo(ngayStr,TOADOX_TEXT + temp * 11, TOADOY_FORM + viTri * 2 ,2, BLACK, TEXT_COLOR );
				}else if(temp == 1){
					c = nhapChuoiKiTuSo(thangStr,TOADOX_TEXT + temp * 11, TOADOY_FORM + viTri * 2 ,2, BLACK, TEXT_COLOR );
				}else{
					c = nhapChuoiKiTuSo(namStr,TOADOX_TEXT + temp * 11, TOADOY_FORM + viTri * 2 ,4, BLACK, TEXT_COLOR );
				}
				if(c == KEY_RIGHT){
					if(temp < 2) temp++;
				}
					if(c == KEY_LEFT){
					if(temp > 0) temp--;
				}
		
			}while(c != KEY_UP && c != KEY_DOWN && c != KEY_ESC && c != KEY_INSERT && c != KEY_F5 && c != KEY_TAB && c != KEY_F2);
		}else {
		
				do{
					if(hoaDon.LOAI == 'N'){
						gotoxy(TOADOX_TEXT + 15, TOADOY_FORM + 2 * 2);
						cout << "   ";
						gotoxy(TOADOX_TEXT, TOADOY_FORM + 2 * 2);
						cout << " X ";
					}else{
						gotoxy(TOADOX_TEXT, TOADOY_FORM + 2 * 2);
						cout << "   ";
						gotoxy(TOADOX_TEXT + 15, TOADOY_FORM + 2 * 2);
						cout << " X ";
						
				}
				c = keyPressed();
				if(c == KEY_RIGHT) hoaDon.LOAI = 'X';
				if(c== KEY_LEFT) hoaDon.LOAI = 'N';
				
				
			}while(c != KEY_UP && c != KEY_DOWN && c != KEY_ESC && c != KEY_INSERT && c != KEY_F5 && c != KEY_F2);
			
		}
		
		if((c == KEY_DOWN || c == KEY_ENTER || c == KEY_TAB) && viTri < 2){
			viTri++;
			if(viTri == 1) temp =0;
		} 
	
		if(c == KEY_UP && viTri > 1){
			viTri--;
			if(viTri == 1) temp = 0;
		}
	
		if(c == KEY_INSERT){
					
				if(!kiemTraChuoiNhapVao(ngayStr)){
					viTri = 1;
					temp = 0;
					thongBao("Ngay bao gom nhung ki tu 0-9", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
				formHoaDon(nv, hoaDon, chucNang);
					xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);

				}else if(!kiemTraChuoiNhapVao(thangStr)){
					viTri = 1;
					temp = 1;
					thongBao("Thang bao gom nhung ki tu 0-9", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
				formHoaDon(nv, hoaDon, chucNang);
					xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);

					
				}else if(!kiemTraChuoiNhapVao(namStr)){
					viTri = 1;
					temp = 2;
					thongBao("Nam bao gom nhung ki tu 0-9", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
				formHoaDon(nv, hoaDon, chucNang);
					xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);

				}else{
						stringstream(ngayStr) >> hoaDon.NGAYLAP.NGAY;
						stringstream(thangStr) >> hoaDon.NGAYLAP.THANG;
						stringstream(namStr) >> hoaDon.NGAYLAP.NAM;
					ketQua = kiemTraThoiGianNhapHopLe(hoaDon.NGAYLAP.NGAY, hoaDon.NGAYLAP.THANG, hoaDon.NGAYLAP.NAM, temp);
					if(ketQua == 0){
							thongBao("Ngay Nhap Vao Khong Hop Le", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
							viTri = 1;
						formHoaDon(nv, hoaDon, chucNang);
							xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);
					}else{				
					
						viTriHoaDonSauKhiThem = timKiemViTriHoaDon(nv.DS_HOADON, hoaDon.SOHD);
						thongBao("Cap nhat Hoa Don Cong", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
						break;			
					}
				}
					
		}	
	
		if(c == KEY_F5){
		
				do{
					c = nhapChiTietHoaDon(dsVatTu, nv , hoaDon, dsCTHoaDon, viTriDong, viTriCot);
				formHoaDon(nv, hoaDon, chucNang);
					xuatHoaDonLenForm(hoaDon, ngayStr, thangStr, namStr);
					
				}while(c != KEY_ESC && c != KEY_INSERT);
				if(c == KEY_INSERT){
							stringstream(ngayStr) >> hoaDon.NGAYLAP.NGAY;
							stringstream(thangStr) >> hoaDon.NGAYLAP.THANG;
							stringstream(namStr) >>hoaDon.NGAYLAP.NAM;	
							thongBao("Cap nhat Hoa Don Cong", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
							break;						
				}
				if(c == KEY_ESC) c = 1;
		}
		if(c == KEY_F2){
			xemDanhSachVatTu(dsVatTu);
			string chucNang = "ESC: Thoat   Insert: Them vao danh sach   F5: Nhap danh sach vat tu   F2: Danh sach vat tu";
			veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, 30, BG_BODY);
			formHoaDon(nv, hoaDon, chucNang);
			xuatHoaDonLenForm(hoaDon, chuyenSoThanhChuoi(hoaDon.NGAYLAP.NGAY), chuyenSoThanhChuoi(hoaDon.NGAYLAP.THANG), chuyenSoThanhChuoi(hoaDon.NGAYLAP.NAM));
			
		}
		
	}while(c != KEY_ESC );
	// giai phong mang

	for(int i = 0; i < MAX_LINE; i++)
		delete[] dsCTHoaDon[i];
	delete[] dsCTHoaDon;
	//	
	if(c == KEY_ESC) return -1;
	return c;
}

int timKiemHoaDon(HOADONPTR dsHoaDon, string &maHoaDon, int toaDoX, int toaDoY, int chieuDai, int chieuRong){
	formTimKiem("Nhap vao ma hoa don",toaDoX, toaDoY, chieuDai, chieuRong);

	int c;
	do{
		c = nhapChuoiKiTuVaSoKhongKhoangTrang(maHoaDon, toaDoX + (chieuDai - WIDTH_TEXT)/2 ,toaDoY + 3, WIDTH_TEXT, BLACK, WHITE);
	}while(c != KEY_ENTER && c != KEY_ESC);
	// thoat khong tim kiem
	if(c == KEY_ESC) 
		return -2;
	int viTriHoaDon = timKiemViTriHoaDon(dsHoaDon, maHoaDon);
	return  viTriHoaDon;
	
}

int danhSachHoaDonDaLapCuaNhanVien(DanhSachVatTu &dsVatTu, NhanVien &nv){
	int toaDoKhungX = TOADOX + WIDTH_MENU_BAR + (SCREEN_WIDTH - WIDTH_MENU_BAR - (SO_COT_BANG_HOA_DON * TABLE_COLUMN_WIDTH + SO_COT_BANG_HOA_DON + 1))/2;
	int toaDoKhungY = TOADOY + 3 + (SCREEN_HEIGTH - 3 - SO_HANG_BANG_HOA_DON * 2)/ 2;
	khungHoaDon(nv, SO_COT_BANG_HOA_DON, SO_HANG_BANG_HOA_DON + 1, toaDoKhungX, toaDoKhungY);
	int soHoaDon = demSoHoaDon(nv.DS_HOADON);
	int trang = 1, tongTrang, viTri = 0;
	tongTrang = soHoaDon / SO_HANG_BANG_HOA_DON;
	if(soHoaDon % SO_HANG_BANG_HOA_DON != 0) tongTrang++;
	if(soHoaDon ==0) trang = tongTrang = 1;
	int c, ketQua;
	int viTriHoaDonSauKhiThem;
	do{
		in1TrangDanhSachHoaDon(nv.DS_HOADON, trang, tongTrang, toaDoKhungX, toaDoKhungY);
		gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
		gotoxy(TOADOX + WIDTH_MENU_BAR + (SCREEN_WIDTH - WIDTH_MENU_BAR) / 2 - 5, TOADOY + SCREEN_HEIGTH -4);
		SetBGColor(BG_BODY);
		cout << "\t\t\t\t\t";
		SetColor(BG_HEADER);
		gotoxy(TOADOX + WIDTH_MENU_BAR + (SCREEN_WIDTH - WIDTH_MENU_BAR) / 2 - 5, TOADOY + SCREEN_HEIGTH -4);
		cout << "Trang "  << trang << "/" << tongTrang;
		do{
			gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
			cout << "->";
			c = keyPressed();
			if(c == KEY_DOWN){
				//neu la dong cuoi cung
				//chua la trang cuoi
				//so hon lon hon 0
				if(viTri == SO_HANG_BANG_HOA_DON - 1 && trang < tongTrang && soHoaDon > 0){
					trang++;
					//
					gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
					cout << "  ";
					viTri = 0;
					break;
				}
				//neu chua la dong cuoi
				//chua la nhan vien cuoi
				//va so nhan vien lon hon 0
				if(viTri < SO_HANG_BANG_HOA_DON - 1 && (viTri + ((trang - 1) * SO_HANG_BANG_HOA_DON) )< soHoaDon - 1 && soHoaDon > 0){
					//
					gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
					cout << "  ";
					viTri++;
				}	
			}
			if(c == KEY_UP){
				// neu la vi tri dau tien
				// khong phai la trang dau
				// so hoa don lon hon 0
				if(viTri == 0 && trang > 1 && soHoaDon > 0){
					trang--;
					//
					gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
					cout << "  ";	
					viTri = SO_HANG_BANG_HOA_DON - 1;
					break;
				}
					// neu chua la vi tri dau tien  va so nhan vien lon hon khong 0
				if(viTri > 0 && soHoaDon > 0){
					//
					gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
					cout << "  ";
					viTri--;
				}
			}
			
				if(c == KEY_INSERT){
				do{
					
					veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
					c = nhapHoaDon(dsVatTu, nv, viTriHoaDonSauKhiThem);
					if(c != -1){
						soHoaDon = demSoHoaDon(nv.DS_HOADON);
						// tinh lai tong trang
						tongTrang =  soHoaDon / SO_HANG_BANG_HOA_DON;
						if(soHoaDon % SO_HANG_BANG_HOA_DON != 0) tongTrang++;
						// tim trang ma nhan vien moi duoc them vao
						trang = viTriHoaDonSauKhiThem / SO_HANG_BANG_HOA_DON;
					//	if(viTriHoaDonSauKhiThem % SO_HANG_BANG_HOA_DON != 0)
						 trang++;
					//	if(viTriHoaDonSauKhiThem == 0) trang = 1;
						
						gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
						cout << "  ";
						// tim vi tri trong trang cua nhan vien
						//
						viTri = viTriHoaDonSauKhiThem % SO_HANG_BANG_HOA_DON; 
					
					}
					
				}while(c != -1);
				
				khungHoaDon(nv, SO_COT_BANG_HOA_DON, SO_HANG_BANG_HOA_DON + 1, toaDoKhungX, toaDoKhungY);
				break;
			}
			if(c == KEY_F5){
				HOADONPTR p = timKiemHoaDonThuN(nv.DS_HOADON, (trang- 1) * SO_HANG_BANG_HOA_DON + viTri);
				if(p != NULL){
					if(p->HOADON.DSCTHOADON != NULL){
						thongBao("Hoa don da co chi tiet hoa don khong the sua.", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
						khungHoaDon(nv, SO_COT_BANG_HOA_DON, SO_HANG_BANG_HOA_DON + 1, toaDoKhungX, toaDoKhungY);
						break;
					}else{
						
							HoaDon hd = p->HOADON;
							ketQua = capNhatHoaDon(dsVatTu, nv, p->HOADON, viTriHoaDonSauKhiThem);
							if(ketQua == -1) p->HOADON = hd;
							SetBGColor(BG_BODY);
							SetColor(BG_HEADER);
							khungHoaDon(nv, SO_COT_BANG_HOA_DON, SO_HANG_BANG_HOA_DON + 1, toaDoKhungX, toaDoKhungY);
							break;
						
					}
				}
			}
			if(c == KEY_DELETE){
					HOADONPTR p = timKiemHoaDonThuN(nv.DS_HOADON, (trang- 1) * SO_HANG_BANG_HOA_DON + viTri);		
					if(p != NULL){
						if(p->HOADON.DSCTHOADON != NULL){
						thongBao("Khong the xoa hoa don da co chi tiet", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
//						khungHoaDon(nv, SO_COT_BANG_HOA_DON, SO_HANG_BANG_HOA_DON + 1, toaDoKhungX, toaDoKhungY);
//						break;
					}else{
						ketQua = hopThoaiLuaChon("BAN CO MUON XOA HOA DON "+ p->HOADON.SOHD + " KHONG?", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, 50,5 );
						if(ketQua == 1){
							xoaNode_info(nv.DS_HOADON, p->HOADON);
							thongBao("Xoa thanh cong", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
							SetBGColor(BG_BODY);
							SetColor(BG_HEADER);
							soHoaDon--;if(soHoaDon  < 0) soHoaDon = 0; //demSoNhanVien(root);
							tongTrang =  soHoaDon / SO_HANG_BANG_HOA_DON;
							if(soHoaDon % SO_HANG_BANG_HOA_DON != 0) tongTrang++;	
							// neu la vi tri dau tien
							// chua phai la trang dau tien				
							if(viTri == 0 && trang > 1){
							 	trang--;
								//
								gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
								cout << "  "; 
								viTri = SO_HANG_BANG_HOA_DON - 1;
							}
							//con tro dang dung o vi tri co STT lon hon soHoaDon				
							if((trang - 1) * SO_HANG_BANG_HOA_DON + viTri >= soHoaDon && soHoaDon > 0){
								//
								gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
								cout << "  ";
								viTri = soHoaDon % SO_HANG_BANG_HOA_DON - 1;
							} 
							if(soHoaDon == 0) trang = tongTrang = 1;
//							khungHoaDon(nv, SO_COT_BANG_HOA_DON, SO_HANG_BANG_HOA_DON + 1, toaDoKhungX, toaDoKhungY);		
						}							
					}
					khungHoaDon(nv, SO_COT_BANG_HOA_DON, SO_HANG_BANG_HOA_DON + 1, toaDoKhungX, toaDoKhungY);
					break;
					}
			}
			
			if(c == KEY_F2){
				HOADONPTR p = timKiemHoaDonThuN(nv.DS_HOADON, (trang- 1) * SO_HANG_BANG_HOA_DON + viTri);
				if(p != NULL){
				
					xuatChiTietHoaDon(nv, p->HOADON);
					khungHoaDon(nv, SO_COT_BANG_HOA_DON, SO_HANG_BANG_HOA_DON + 1, toaDoKhungX, toaDoKhungY);
				}
						
				break;
				
			}
			
			if(c == KEY_F9){
				string maHoaDon = "";
				int viTriHoaDon = timKiemHoaDon(nv.DS_HOADON, maHoaDon, TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
				while(viTriHoaDon != -2){
					if(viTriHoaDon == -1){
						thongBao("Ma hoa don khong ton tai", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
						viTriHoaDon = timKiemHoaDon(nv.DS_HOADON, maHoaDon,TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
					}else{
						trang = viTriHoaDon / SO_HANG_BANG_HOA_DON;
//						if(viTriNhanVien % SO_DONG_MOT_TRANG != 0)
						 trang++;
//						if(viTriNhanVien == 0) trang = 1;
						gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
						cout << "  ";
						viTri = viTriHoaDon % SO_HANG_BANG_HOA_DON; 
						break;
					}
				}
				khungHoaDon(nv, SO_COT_BANG_HOA_DON, SO_HANG_BANG_HOA_DON + 1, toaDoKhungX, toaDoKhungY);
				break;
			}
			
		}while(c!= KEY_ESC && c!= KEY_LEFT && c != KEY_RIGHT && c != KEY_F2);
		if(c == KEY_RIGHT){
		
			if(trang < tongTrang ) trang++;
			if(trang == tongTrang && (trang - 1) * SO_HANG_BANG_HOA_DON + viTri >= soHoaDon){
				gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
				cout << "  ";
				if(soHoaDon > 0)
				viTri = (soHoaDon - 1) % SO_HANG_BANG_HOA_DON;
				else viTri = 0;
			}	
			
		}
		if(c == KEY_LEFT){
			
			if(trang > 1 ) trang--;	
		}
		
	}while(c != KEY_ESC);
	if(c == KEY_ESC) return -1;
	return c;
}


/*~~~~~~~~~~~~~~~~~~~~~~ TAM: THONG KE HOA DON ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// Ve Bang Danh sach thong ke hoa don
void veBangThongKeHoaDon(int toaDoX, int toaDoY, int soCot, int soDong, int kichThuocO){
	// Tao Bang Danh sach
	veBangDanhSach(toaDoX, toaDoY, soCot, soDong, kichThuocO);
	
	// Ghi ten cot cho bang danh sach
	SetColor(RED);
	SetBGColor(BG_BODY);
	int toaDoXNhan;
	for (int i = 0; i < SO_COT_BANG_HOA_DON; i++){
		toaDoXNhan = toaDoX + i * (kichThuocO + 1) + 1 + (kichThuocO - tenCotHoaDon[i].length()) / 2;
		gotoxy(toaDoXNhan, toaDoY + 1);
		cout << tenCotHoaDon[i];
	}
}

// Ve giao dien thong ke hoa don theo ngay
void veGiaoDienThongKeHoaDon(int toaDoX, int toaDoY, int soCot, int soDong, int kichThuocO){
	SetColor(RED);
	SetBGColor(BG_BODY);
	
	string s;
	
	// Tieu De
	s = "BANG THONG KE DANH SACH HOA DON";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 1 );
	cout << s;
	
	//NHAP THOI GIAN
	// Nhap ngay BAt Dau
	SetColor(BLACK);
	gotoxy(toaDoX + 25, toaDoY - 2);// 64
	cout << "Tu Ngay: ";
	veInputNhapNgay(toaDoX + 34, toaDoY - 3); // 73
	// Nhap ngay Ket thuc
	SetColor(BLACK);
	gotoxy(toaDoX + 55, toaDoY - 2); // 92
	cout << "Den Ngay";
	veInputNhapNgay(toaDoX + 66, toaDoY - 3); //98
	
	// Tao bang Danh sach thong ke
	veBangThongKeHoaDon(toaDoX, toaDoY, soCot, soDong, kichThuocO);
	
	// Ve Footer
	SetColor(RED);
	gotoxy(TOADOX + WIDTH_MENU_BAR, TOADOY + HEIGHT_HEADER + HEIGHT_BODY);
	for (int i = 0; i < SCREEN_WIDTH-WIDTH_MENU_BAR; i++)
		cout << char(196);
	for (int i = 0; i < HEIGHT_FOOTER - 1; i++){
		gotoxy(TOADOX + WIDTH_MENU_BAR, TOADOY + HEIGHT_HEADER + HEIGHT_BODY + i + 1);
		for (int j = 0; j < WIDTH_BODY; j++){
			cout << " ";
		}
	}
	s = "ESC: Thoat \t F2: Nhap ngay \t ENTER: Thong ke \t\t <-Trang truoc \t Trang sau->";
	gotoxy(TOADOX + WIDTH_MENU_BAR+(SCREEN_WIDTH-WIDTH_MENU_BAR-s.length())/2, SCREEN_HEIGTH );
	cout << s;

}

// Xoa du lieu trong bang thong ke hoa don
void xoaDuLieuTrongBangDanhSachThongKeHoaDon(int toaDoX, int toaDoY, int soCot, int soDong, int kichThuocO){
	SetBGColor(BG_BODY);
	
	int toaDoXCuaConTro;
	int toaDoYCuaConTro;
	int tam = 0;
	int i, j, k;
	
	for (i = 0 ; i < soDong; i++){
		toaDoYCuaConTro = toaDoY + 3 + 2 * tam;	
		tam++;
		for (j = 0; j < soCot; j++) {
			toaDoXCuaConTro = toaDoX + j * (kichThuocO + 1) + 1;
			gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
			for (k = 0; k < kichThuocO; k++) cout << " ";
		}	
	}

}

// Tinh tri gia hoa don
int triGiaCuaHoaDon(DSCTHOADONPTR first){
	float tongTien = 0.0;	
	DSCTHOADONPTR p = first;
	while(p != NULL){
		tongTien += (((float)p->CTHOADON.DONGIA * p->CTHOADON.SOLUONG) * (1 + (float)p->CTHOADON.VAT / 100));
		p = p->NEXT;
	}
	return (int) tongTien;
}

// Tong so hoa don trong 2 khoang thoi gian
int tongSoHoaDonTrongKhoangThoiGian(NHANVIENTREE root, Date ngayBD, Date ngayKT){
	int soHoaDon = 0;
	
	// Duyet danh sach nhan vien kiem tra co hoa don ko?
	Stack sp = NULL;
	NHANVIENTREE p = root;
	HOADONPTR hd = NULL;
	
	int kiemTra;
	Date ngayLapHD;
	
	do{
		while(p != NULL){
			push(sp, p);
			p = p->LEFT;
		}
		
		if(sp != NULL){
			pop(sp, p);				
			hd = p->NHANVIEN.DS_HOADON;
			
			// Kiem tra nv co danh sach hoa don ko ?
			if (hd != NULL){
				// Dem so hoa don trong DS_HOADON cua NV do	
				while(hd != NULL){
					ngayLapHD = hd->HOADON.NGAYLAP;
					// Kiem tra: ngayBD <= ngayLapHD <= ngayKT
					if (kiemTraNgayGiua2Ngay(ngayBD, ngayKT, ngayLapHD) == 1) 
						soHoaDon++;
					
					hd = hd->NEXT;
				}
			}
			
			p = p->RIGHT;
		} else break;
		
	} while (true);
	
	return soHoaDon;
}

// Nap danh sach hoa don trong khoang thoi gian ngayBD->ngayKT cua tat ca nhan vien
string** napDanhSachHoaDon(NHANVIENTREE root, Date ngayBD, Date ngayKT, int tongSoHoaDon){
	int i, c;
	
	// Khoi tao du lieu ban dau
	string **dsHoaDon = new string *[tongSoHoaDon];
	for(i = 0; i < tongSoHoaDon; i++) dsHoaDon[i] = new string[SO_COT_BANG_HOA_DON]{""};

	// Duyet Danh sach NV de lay danh sach HoaDon trong khoang thoi gian
	Stack sp = NULL;
	NHANVIENTREE p = root;
	HOADONPTR hd;
	NhanVien nv;
	
	int kiemTra;
	i = 0;
	Date ngayLapHD;
	
	do{
		while(p != NULL){
			push(sp, p);
			p = p->LEFT;
		}
		
		if(sp != NULL){
			pop(sp, p);			
			
			nv = p->NHANVIEN;
			hd = nv.DS_HOADON;
			
			// Kiem tra nv co danh sach hoa don ko ?
			if (hd != NULL){
				
				// Dem so hoa don trong DS_HOADON cua NV do	
				while(hd != NULL){
					ngayLapHD = hd->HOADON.NGAYLAP;
					//soSanhThoiGian(Date A, Date B) :: So sanh 2 Date A va B voi nhau A>B: 1, A=B: 0, A<B: -1
					// if:: ngayBD <= ngayLapHD && ngayLapHD <= ngayKT soHoaDon++
					if ( !(soSanhThoiGian(ngayBD, ngayLapHD) == 1) && !(soSanhThoiGian(ngayLapHD, ngayKT) == 1) ) {
						// HOP LE	{"SO HD", "NGAY LAP", "LOAI HD", "HO TEN NV", "TRI GIA HD"}
						dsHoaDon[i][0] = hd->HOADON.SOHD;						// SO HD
						dsHoaDon[i][1] = chuyenNgayThanhChuoi(ngayLapHD);		// NGAY LAP
						
						if (hd->HOADON.LOAI == 'X') dsHoaDon[i][2] = "Xuat";	// LOAI HD
						else dsHoaDon[i][2] = "Nhap";		
						
						dsHoaDon[i][3] = nv.HO + " " + nv.TEN;					// HO TEN NV
						dsHoaDon[i][4] = chuyenSoThanhChuoi(triGiaCuaHoaDon(hd->HOADON.DSCTHOADON)); // TRI GIA HD
						
						i++;
					}
					hd = hd->NEXT;
				}
			}	
			p = p->RIGHT;
		} else break;	
		
	} while (true);
	
	return dsHoaDon;
}

// Thong ke hoa don theo ngay
void giaoDienThongKeHoaDon(NHANVIENTREE root){
	int soCot = SO_COT_BANG_HOA_DON;
	int soDong = SO_HANG_BANG_HOA_DON + 1; // +1 dong cho nhan de
	int kichThuocO = 22;
	int toaDoX = TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - soCot * kichThuocO - soCot - 1) / 2;
	int toaDoY = TOADOY + HEIGHT_HEADER + 5;
	
	Date ngayBD, ngayKT;	
	string ngBD, thBD, namBD, ngKT, thKT, namKT;
	string noiDungThongBao = "";
	int kiemTraNgayBD, kiemTraNgayKT, kiemTraNgayHopLe;
	int viTriNhapThoiGian = 0;
	int vtNhapKhongHopLe = 0;

	int c;
	int i, j, tam;
	
	int trang = 0;
	int tongTrang = 0;
	int tongSoHoaDon = 0;
	string **dsHoaDon;
	string strTrang;
	
	int toaDoXCuaConTro;
	int toaDoYCuaConTro;
	
	// ve giao dien thong ke
	veGiaoDienThongKeHoaDon(toaDoX, toaDoY, soCot, soDong, kichThuocO);
	
	// NHAP THOI GIAN
	do {
		switch (viTriNhapThoiGian){
			// Thoi gian BD
			case 0:
				c = nhapChuoiKiTuSo(ngBD,toaDoX + 36, toaDoY - 2, 2, BG_BODY, BLACK);
				break;
			case 1:
				c = nhapChuoiKiTuSo(thBD,toaDoX + 41, toaDoY - 2, 2, BG_BODY, BLACK);
				break;
			case 2:
				c = nhapChuoiKiTuSo(namBD,toaDoX + 46, toaDoY - 2, 4, BG_BODY, BLACK);
				break;
						
			// Thoi gian KT
			case 3:
				c = nhapChuoiKiTuSo(ngKT,toaDoX + 68, toaDoY - 2, 2, BG_BODY, BLACK);
				break;
			case 4:
				c = nhapChuoiKiTuSo(thKT,toaDoX + 73, toaDoY - 2, 2, BG_BODY, BLACK);
				break;
			case 5:
				c = nhapChuoiKiTuSo(namKT,toaDoX + 78, toaDoY - 2, 4, BG_BODY, BLACK);
				break;
		}
				
		if (c == KEY_RIGHT && viTriNhapThoiGian < 5) viTriNhapThoiGian++;
		if (c == KEY_LEFT && viTriNhapThoiGian > 0) viTriNhapThoiGian--;
		if (c == KEY_ENTER){
			if (ngBD == "" || thBD == "" || namBD == "" || ngKT == "" || thKT == "" || namKT == ""){	
				if (ngBD == "") viTriNhapThoiGian = 0;
				else if (thBD == "") viTriNhapThoiGian = 1;
				else if (namBD == "") viTriNhapThoiGian = 2;
				else if (ngKT == "") viTriNhapThoiGian = 3;
				else if (thKT == "") viTriNhapThoiGian = 4;
				else if (namKT == "") viTriNhapThoiGian = 5;
			
				//Thong bao: Ngay nhap khong hop le!
				noiDungThongBao = "Thoi Gian Nhap Khong Hop Le!";
				thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);
			
			} else {

				// gan ngay thang nam vao : ngayBD, ngayKT
				stringstream(ngBD) >> ngayBD.NGAY;
				stringstream(thBD) >> ngayBD.THANG;
				stringstream(namBD) >> ngayBD.NAM;
							
				stringstream(ngKT) >> ngayKT.NGAY;
				stringstream(thKT) >> ngayKT.THANG;
				stringstream(namKT) >> ngayKT.NAM;
						
				//Kiem tra thoi gian nhap hop ly ko: ngayBD, ngayKT
				kiemTraNgayBD = kiemTraThoiGianNhapHopLe(ngayBD.NGAY, ngayBD.THANG, ngayBD.NAM, vtNhapKhongHopLe);
				kiemTraNgayKT = kiemTraThoiGianNhapHopLe(ngayKT.NGAY, ngayKT.THANG, ngayKT.NAM, vtNhapKhongHopLe);
											
				if(kiemTraNgayBD == 0){
					//Chuyen con tro toi vi tri thoi gian nhap sai
					viTriNhapThoiGian = vtNhapKhongHopLe;
							
					//Thong bao: Ngay nhap khong hop le!
					noiDungThongBao = "Thoi Gian Bat Dau Khong Hop Le!";
					thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);
	
				} else if (kiemTraNgayKT == 0){
					//Chuyen con tro toi vi tri thoi gian nhap sai
					viTriNhapThoiGian = vtNhapKhongHopLe + 3;
							
					//Thong bao: Ngay nhap khong hop le!
					noiDungThongBao = "Thoi Gian Ket Thuc Khong Hop Le!";
					thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);
							
				} else{
					// so sanh 2 ngay co hop ly ko
					kiemTraNgayHopLe = soSanhThoiGian(ngayKT, ngayBD);
					if (kiemTraNgayHopLe == -1){
						//Chuyen con tro toi vi tri thoi gian nhap sai
						viTriNhapThoiGian = 2;
								
						//Thong bao: Ngay nhap khong hop le!
						noiDungThongBao = "Thoi Gian Bat Dau Khong Duoc Lon Hon Thoi Gian Ket Thuc!";
						thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);
	
					} else {
						// THOI GIAN HOP LE
						noiDungThongBao = "";
						viTriNhapThoiGian = 0; 
						
						tongSoHoaDon = tongSoHoaDonTrongKhoangThoiGian(root, ngayBD, ngayKT);
						if (tongSoHoaDon <= 0){
							// Thong bao Danh sach HOA DON rong
							string noiDungThongBao = "Danh sach HOA DON rong!";
							thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);	
						} else {
							// Nap du lieu duyet duoc vao mang tam
							dsHoaDon = napDanhSachHoaDon(root, ngayBD, ngayKT, tongSoHoaDon);
									
							tongTrang = tongSoHoaDon / SO_HANG_BANG_HOA_DON + (tongSoHoaDon%SO_HANG_BANG_HOA_DON == 0 ? 0:1);
							if (tongTrang > 0) trang = 1;
	
							do {
								// IN DU LIEU
										
								SetColor(BLACK);
								SetBGColor(BG_BODY);
								tam = 0;
								for (i = (trang - 1) * SO_HANG_BANG_HOA_DON ; i < trang * SO_HANG_BANG_HOA_DON && i < tongSoHoaDon; i++){
									toaDoYCuaConTro = toaDoY + 3 + 2 * tam;	
									tam++;
									for (j = 0; j < soCot; j++) {
										toaDoXCuaConTro = toaDoX + j * (kichThuocO + 1) + 1 + (kichThuocO - dsHoaDon[i][j].length()) / 2;		
										gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
										cout << dsHoaDon[i][j];				
									}
								}
										
								// Phan Trang
								SetColor(RED);
								strTrang = "Tong so HD: " + chuyenSoThanhChuoi(tongSoHoaDon) + " | Trang: " + chuyenSoThanhChuoi(trang) + "/" + chuyenSoThanhChuoi(tongTrang);
								gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - strTrang.length()) / 2, TOADOY + HEIGHT_HEADER + HEIGHT_BODY - 2);
								cout << strTrang;
										
								c = keyPressed();
									
											
								if (c == KEY_LEFT && trang > 1) {
									// Xoa du lieu trong bang thong ke
									xoaDuLieuTrongBangDanhSachThongKeHoaDon(toaDoX, toaDoY, soCot, soDong, kichThuocO);
									trang--;
								}
								if (c == KEY_RIGHT && trang < tongTrang) {
									// Xoa du lieu trong bang thong ke
									xoaDuLieuTrongBangDanhSachThongKeHoaDon(toaDoX, toaDoY, soCot, soDong, kichThuocO);
									trang++;
								}
										
							} while (c != KEY_ESC && c != KEY_F2);				
						}
						
						ngayBD.NGAY = 0;
						ngayBD.THANG = 0;
						ngayBD.NAM = 0;
									
						ngayKT.NGAY = 0;
						ngayKT.THANG = 0;
						ngayKT.NAM = 0;
					}
				}						
			}
			// Tao bang --------> xoa thong bao
			veBangThongKeHoaDon(toaDoX, toaDoY, soCot, soDong, kichThuocO);
		}
	} while (c != KEY_ESC);
}


/*~~~~~~~~~~~~~~~~~~~~~~ TAM: THONG KE 10 VAT TU CO SO LUONG XUAT CAO NHAT ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// Ve bang thong ke vat tu
void veBangThongKeVatTu(int toaDoX, int toaDoY, int soCot, int soDong, int kichThuocO){
	// Tao Bang Danh sach
	veBangDanhSach(toaDoX, toaDoY, soCot, soDong, kichThuocO);
	
	// Ghi Nhan cho Bang Danh Sach
	SetColor(RED);
	SetBGColor(BG_BODY);
	int toaDoXNhan;
	for (int i = 0; i < SO_COT_BANG_THONG_KE_VAT_TU; i++){
		toaDoXNhan = toaDoX + i * (kichThuocO + 1) + 1 + (kichThuocO - tenCotThongKeVatTu[i].length()) / 2;
		gotoxy(toaDoXNhan, toaDoY + 1);
		cout << tenCotThongKeVatTu[i];
	}
}

// Ve giao dien thong ke vat tu
void veGiaoDienThongKeVatTuCoLuongXuatCaoNhat(int toaDoX, int toaDoY, int soCot, int soDong, int kichThuocO){
	SetColor(RED);
	SetBGColor(BG_BODY);
	
	string s;
	
	// Tieu De
	s = "BANG THONG KE 10 VAT TU CO SO LUONG XUAT CAO NHAT";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 1 );
	cout << s;
	
	//NHAP THOI GIAN
	// Nhap ngay BAt Dau
	SetColor(BLACK);
	gotoxy(toaDoX + 25, toaDoY - 2);// 64
	cout << "Tu Ngay: ";
	veInputNhapNgay(toaDoX + 34, toaDoY - 3); // 73
	// Nhap ngay Ket thuc
	SetColor(BLACK);
	gotoxy(toaDoX + 55, toaDoY - 2); // 92
	cout << "Den Ngay";
	veInputNhapNgay(toaDoX + 66, toaDoY - 3); //98
	
	// Tao bang Danh sach thong ke
	veBangThongKeVatTu(toaDoX, toaDoY, soCot, soDong, kichThuocO);
	
	// Ve Footer
	SetColor(RED);
	gotoxy(TOADOX + WIDTH_MENU_BAR, TOADOY + HEIGHT_HEADER + HEIGHT_BODY);
	for (int i = 0; i < SCREEN_WIDTH-WIDTH_MENU_BAR; i++)
		cout << char(196);
	for (int i = 0; i < HEIGHT_FOOTER - 1; i++){
		gotoxy(TOADOX + WIDTH_MENU_BAR, TOADOY + HEIGHT_HEADER + HEIGHT_BODY + i + 1);
		for (int j = 0; j < WIDTH_BODY; j++){
			cout << " ";
		}
	}
	s = "ESC: Thoat \t F2: Nhap ngay \t ENTER: Thong ke";
	gotoxy(TOADOX + WIDTH_MENU_BAR+(SCREEN_WIDTH-WIDTH_MENU_BAR-s.length())/2, SCREEN_HEIGTH );
	cout << s;

}

// Tra ve mang chua vi tri vat tu duoc sap xep theo so luong xuat giam dan
int* danhSachViTriVatTuCoSoLuongXuatCaoNhat(DanhSachVatTu &dsVatTu, int *thongKeVatTu){
	int *viTri = new int[dsVatTu.N]; // Danh sach vi tri vat tu dc sap xep theo so luong xuat
	int i, j;
	int tam;
	
	for (i = 0; i < dsVatTu.N; i++) viTri[i] = i;
	
	for (i = 0; i < dsVatTu.N - 1; i++)
		for (j = i + 1; j < dsVatTu.N; j++)
			if (thongKeVatTu[viTri[j]] > thongKeVatTu[viTri[i]]){
				tam = viTri[i];
				viTri[i] = viTri[j];
				viTri[j] = tam;	
			}
	
	return viTri;
}

// Thong ke 10 Vat tu co so luong xuat cao nhat trong 2 khoang thoi gian
void giaoDienThongKeVatTuCoLuongXuatCaoNhat(NHANVIENTREE root, DanhSachVatTu &dsVatTu){
	if (kiemTraRong(dsVatTu)){
		// Thong bao Danh sach vat tu rong
		string noiDungThongBao = "Danh sach VAT TU rong!";
		thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);	
	} else {
		int soCot = SO_COT_BANG_THONG_KE_VAT_TU;
		int soDong = SL_VAT_TU_TRONG_TRANG + 1; // +1 dong cho nhan de
		int kichThuocO = 22;
		int toaDoX = TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - soCot * kichThuocO - soCot - 1) / 2;
		int toaDoY = TOADOY + HEIGHT_HEADER + 5;
			
		// Ve giao dien
		veGiaoDienThongKeVatTuCoLuongXuatCaoNhat(toaDoX, toaDoY, soCot, soDong, kichThuocO);
		
		Date ngayBD, ngayKT;	
		string ngBD, thBD, namBD, ngKT, thKT, namKT;
		string noiDungThongBao = "";
		int kiemTraNgayBD, kiemTraNgayKT, kiemTraNgayHopLe;
		int viTriNhapThoiGian = 0;
		int vtNhapKhongHopLe = 0;
	
		int c;
		int i;
		int tam = 0;
		string str;
		int *dsThongKeVatTu; // Danh sach so luong Xuat cua vat tu
		int *dsViTriVatTu; // Danh sach vi tri vat tu co so luong xuat sap xep giam dan
		
		int toaDoXCuaConTro;
		int toaDoYCuaConTro;
		
		c = KEY_F2;
		do {
			
			switch (viTriNhapThoiGian){
				// Thoi gian BD
				case 0:
					c = nhapChuoiKiTuSo(ngBD,toaDoX + 36, toaDoY - 2, 2, BG_BODY, BLACK);
					break;
				case 1:
					c = nhapChuoiKiTuSo(thBD,toaDoX + 41, toaDoY - 2, 2, BG_BODY, BLACK);
					break;
				case 2:
					c = nhapChuoiKiTuSo(namBD,toaDoX + 46, toaDoY - 2, 4, BG_BODY, BLACK);
					break;
				// THOI gian KT
				case 3:
					c = nhapChuoiKiTuSo(ngKT,toaDoX + 68, toaDoY - 2, 2, BG_BODY, BLACK);
					break;
				case 4:
					c = nhapChuoiKiTuSo(thKT,toaDoX + 73, toaDoY - 2, 2, BG_BODY, BLACK);
					break;
				case 5:
					c = nhapChuoiKiTuSo(namKT,toaDoX + 78, toaDoY - 2, 4, BG_BODY, BLACK);
					break;
			}
					
			if (c == KEY_RIGHT && viTriNhapThoiGian < 5) viTriNhapThoiGian++;
			if (c == KEY_LEFT && viTriNhapThoiGian > 0) viTriNhapThoiGian--;
			if (c == KEY_ENTER){	
				if (ngBD == "" || thBD == "" || namBD == "" || ngKT == "" || thKT == "" || namKT == ""){	
					if (ngBD == "") viTriNhapThoiGian = 0;
					else if (thBD == "") viTriNhapThoiGian = 1;
					else if (namBD == "") viTriNhapThoiGian = 2;
					else if (ngKT == "") viTriNhapThoiGian = 3;
					else if (thKT == "") viTriNhapThoiGian = 4;
					else if (namKT == "") viTriNhapThoiGian = 5;
				
					//Thong bao: Ngay nhap khong hop le!
					noiDungThongBao = "Thoi Gian Nhap Khong Hop Le!";
					thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);
				
				} else {
	
					// gan ngay thang nam vao : ngayBD, ngayKT
					stringstream(ngBD) >> ngayBD.NGAY;
					stringstream(thBD) >> ngayBD.THANG;
					stringstream(namBD) >> ngayBD.NAM;
								
					stringstream(ngKT) >> ngayKT.NGAY;
					stringstream(thKT) >> ngayKT.THANG;
					stringstream(namKT) >> ngayKT.NAM;
							
					//Kiem tra thoi gian nhap hop ly ko: ngayBD, ngayKT
					kiemTraNgayBD = kiemTraThoiGianNhapHopLe(ngayBD.NGAY, ngayBD.THANG, ngayBD.NAM, vtNhapKhongHopLe);
					kiemTraNgayKT = kiemTraThoiGianNhapHopLe(ngayKT.NGAY, ngayKT.THANG, ngayKT.NAM, vtNhapKhongHopLe);
												
					if(kiemTraNgayBD == 0){
						//Chuyen con tro toi vi tri thoi gian nhap sai
						viTriNhapThoiGian = vtNhapKhongHopLe;
								
						//Thong bao: Ngay nhap khong hop le!
						noiDungThongBao = "Thoi Gian Bat Dau Khong Hop Le!";
						thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);
		
					} else if (kiemTraNgayKT == 0){
						//Chuyen con tro toi vi tri thoi gian nhap sai
						viTriNhapThoiGian = vtNhapKhongHopLe + 3;
								
						//Thong bao: Ngay nhap khong hop le!
						noiDungThongBao = "Thoi Gian Ket Thuc Khong Hop Le!";
						thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);
								
					} else{
						// so sanh 2 ngay co hop ly ko
						kiemTraNgayHopLe = soSanhThoiGian(ngayKT, ngayBD);
						if (kiemTraNgayHopLe == -1){
							//Chuyen con tro toi vi tri thoi gian nhap sai
							viTriNhapThoiGian = 2;
									
							//Thong bao: Ngay nhap khong hop le!
							noiDungThongBao = "Thoi Gian Bat Dau Khong Duoc Lon Hon Thoi Gian Ket Thuc!";
							thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);
						} else {		
						
							// THOI GIAN HOP LE
							noiDungThongBao = "";
							viTriNhapThoiGian = 0; 
							
							// thong ke So luong Vat tu XUAT 
							dsThongKeVatTu = thongKeVatTuTheoSoLuongXuat(root, dsVatTu, ngayBD, ngayKT);
							// Danh sach vi tri vat tu sap xet theo so luong XUAT giam dan
							dsViTriVatTu = danhSachViTriVatTuCoSoLuongXuatCaoNhat(dsVatTu, dsThongKeVatTu);
							
							
							// Kiem tra danh sach thong ke vat tu trong khoang thoi gian co so luong xuat ko ?
							if (dsThongKeVatTu[dsViTriVatTu[0]] == 0){
								// Thong bao Danh sach so luong vat tu xuat trong khoang thoi gian
								string noiDungThongBao = "Khong co VAT TU xuat!";
								thongBao(noiDungThongBao, TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - noiDungThongBao.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, noiDungThongBao.length() + 10, 5);	
							} else {
								// In du lieu ra Bang
								SetColor(BLACK);
								SetBGColor(BG_BODY);
								for (i = 0; i < 10; i++){
									// Neu so luong xuat cua vat tu > 0 thi moi in ra man hinh
									if (dsThongKeVatTu[dsViTriVatTu[i]] > 0){
										toaDoYCuaConTro = toaDoY + 3 + 2 * tam;
										tam++;
												
										// IN STT
										str = chuyenSoThanhChuoi(i + 1);
										toaDoXCuaConTro = toaDoX + 0 * (kichThuocO + 1) + 1 + (kichThuocO - str.length()) / 2;
										gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
										cout << str;
												
										// IN MAVT
										toaDoXCuaConTro = toaDoX + 1 * (kichThuocO + 1) + 1 + (kichThuocO - dsVatTu.NODE[dsViTriVatTu[i]].MAVT.length()) / 2;
										gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
										cout << dsVatTu.NODE[dsViTriVatTu[i]].MAVT;
												
										// IN TENVT
										toaDoXCuaConTro = toaDoX + 2 * (kichThuocO + 1) + 1 + (kichThuocO - dsVatTu.NODE[dsViTriVatTu[i]].TENVT.length()) / 2;
										gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
										cout << dsVatTu.NODE[dsViTriVatTu[i]].TENVT;
												
										// IN SO LUONG TON
										str = chuyenSoThanhChuoi(dsVatTu.NODE[dsViTriVatTu[i]].SOLUONGTON);
										toaDoXCuaConTro = toaDoX + 3 * (kichThuocO + 1) + 1 + (kichThuocO - str.length()) / 2;
										gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
										cout << dsVatTu.NODE[dsViTriVatTu[i]].SOLUONGTON;
											
										// IN SOLUONG XUAT
										str = chuyenSoThanhChuoi(dsThongKeVatTu[dsViTriVatTu[i]]);
										toaDoXCuaConTro = toaDoX + 4 * (kichThuocO + 1) + 1 + (kichThuocO - str.length()) / 2;
										gotoxy(toaDoXCuaConTro, toaDoYCuaConTro);
										cout << str;
									}
								}
								
								do {
									c = keyPressed();
									if (c == KEY_ESC) return;
									if (c == KEY_F2){
										tam =0;
										break;
									}
								} while (true);
								
							}
						}	
					}	
				}
				
				ngayBD.NGAY = 0;
				ngayBD.THANG = 0;
				ngayBD.NAM = 0;
											
				ngayKT.NGAY = 0;
				ngayKT.THANG = 0;
				ngayKT.NAM = 0;
				
				// Tao bang Danh sach thong ke -----> Xoa box thong bao
				veBangThongKeVatTu(toaDoX, toaDoY, soCot, soDong, kichThuocO);
			}	
			
		} while (c != KEY_ESC);
	}
}



#include "VatTu.cpp"



string tenCotBangCTHoaDon[] = {"Ma Vat Tu", "So Luong" , "Don Gia", "VAT"};
string tenCotBangCTHoaDon2[] = {"STT", "Ma Vat Tu", "So Luong" , "Don Gia", "VAT"};
bool kiemTraRong(DSCTHOADONPTR first){
	if(first == NULL) return true;
	return false;
}

// insert_first
bool themVaoDauDanhSach(DSCTHOADONPTR &first, CT_HoaDon ctHoaDon){
	DSCTHOADONPTR p = new NodeCTHoaDon;
	if(p == NULL) return false;
	p->CTHOADON = ctHoaDon;
	p->NEXT = first;
	first = p;
	return true;
}

//insert last
bool themVaoCuoiDanhSach(DSCTHOADONPTR &first, CT_HoaDon ctHoaDon ){
	DSCTHOADONPTR p = new NodeCTHoaDon;
	if(p == NULL) return false;
	p->CTHOADON = ctHoaDon;
	p->NEXT = NULL;
	
	// neu danh sach rong thi them vao dau
	if(first == NULL){
		first = p;
	}else{
		DSCTHOADONPTR q;
		// danh sasch khac rong
		// tim q la node cuoi cung cua danh sach
		for(q = first; q->NEXT != NULL; q=q->NEXT);
		q->NEXT = p;
	}
	
}

// insert_after
bool themVaoSauMotNode(DSCTHOADONPTR &first, DSCTHOADONPTR p, CT_HoaDon ctHoaDon){
	if(p == NULL){
		cout << "Khong the them vao" << endl;
		return false;
	}else{
		DSCTHOADONPTR q = new NodeCTHoaDon;
			q->CTHOADON = ctHoaDon;
		// q->next tro den Node sau Node can them vao
		q->NEXT = p->NEXT;
		// p->next tro den Node can them vao
		p->NEXT = q;
	}
	
	return true;
}

// insert_oreder
bool themSapXep(DSCTHOADONPTR &first, CT_HoaDon ctHoaDon){
	
	DSCTHOADONPTR p = new NodeCTHoaDon;
	if(p == NULL) return false;
	p->CTHOADON = ctHoaDon;
	p->NEXT = NULL;
	
	// neu danh sach rong thi them vao dau
	if(first == NULL){
		first = p;
		return true;
	}
	DSCTHOADONPTR nodeHienTai = first;
	DSCTHOADONPTR nodeTruoc = NULL;
	// danh sasch khac rong
	// tim q la node cuoi cung cua danh sach
	while(nodeHienTai != NULL && nodeHienTai->CTHOADON.MAVT < ctHoaDon.MAVT){
		nodeTruoc = nodeHienTai;
		nodeHienTai = nodeHienTai->NEXT;
	}
	// neu la vi tri SOHD can them vao < SOHD cua hoa don dau tien trong danh sach
	if(nodeTruoc == NULL){
		themVaoDauDanhSach(first, ctHoaDon);
	}
	// Vi tri them se la cuoi danh sach hoac la vi tri sau truoc nodeHienTai
	// tuc la sau nodeTruoc
	else{
		themVaoSauMotNode(first, nodeTruoc, ctHoaDon);
	}
	
	return true;
}
//	delete_first
bool xoaNodeDauDanhSach(DSCTHOADONPTR &first){
	if(kiemTraRong(first)){
		cout << "danh sach rong, khong the xoa" << endl;
		return false;
	}
	// p la node can xoa
	DSCTHOADONPTR p = first;
	// di chuyen con tro first den node thu 2
	first = p->NEXT;
	delete p;
	return true;
}

void xoaToanBoDanhSach(DSCTHOADONPTR &first){
	while(first != NULL) xoaNodeDauDanhSach(first);
}

// delete_after
bool xoaSauNode(DSCTHOADONPTR &first, DSCTHOADONPTR p){
	if(p == NULL || p->NEXT == NULL){
		cout << "Khong the xoa " << endl;
		return false;
	}
	// q la Node can xoa
	DSCTHOADONPTR q = p->NEXT;
	// bo lien ket giua p va q
	p->NEXT = q->NEXT;
	delete q;
	return true;
	
}

// delete_info
bool xoaNode_info(DSCTHOADONPTR &first, CT_HoaDon ctHoaDon){
	DSCTHOADONPTR p = first;
	if(first == NULL){
		cout << "Khong the xoa hoa don" << ctHoaDon.MAVT << endl; 
		return false;
	}
	// neu node can xoa la node dau tien
	if(p->CTHOADON.MAVT == ctHoaDon.MAVT){
		xoaNodeDauDanhSach(first);
	}
	// tim node p la node truoc node can xoa
	for(p; p->NEXT != NULL && p->NEXT->CTHOADON.MAVT != ctHoaDon.MAVT; p = p->NEXT);
	if(p->NEXT != NULL){
		xoaSauNode(first, p);
	}
	return true;
}

void duyetDanhSach(DSCTHOADONPTR first){
	
	if(first == NULL){
		cout << "Danh sach hoa don rong" << endl;
		return;
	}
	DSCTHOADONPTR p = first;
	while(p != NULL){
		cout << p->CTHOADON.MAVT << "\t" << p->CTHOADON.SOLUONG << "\t" << p->CTHOADON.DONGIA << "\t" << p->CTHOADON.VAT << endl;
		p = p->NEXT;
	}
	
}

int demSoCTHoaDon(DSCTHOADONPTR first){
	DSCTHOADONPTR p = first;
	int dem = 0;
	while(p != NULL){
		dem++;
		p = p->NEXT;
	}
	return dem;
}

//int timKiemViTriCTHoaDon(DSCTHOADONPTR first, string maVatTu){
//	DSCTHOADONPTR p = first;
//	if(p == NULL) return -1;
//	int dem = 0;
//	while(p != NULL){
//		if( p->CTHOADON.MAVT == maVatTu)
//			return dem;
//		dem++;
//		p = p->NEXT;
//	}
//	return -1;
//}

//DSCTHOADONPTR timKiemTrongCTHoaDon(DSCTHOADONPTR first, string maVatTu){
//	DSCTHOADONPTR p = first;
//	while(p != NULL && p->CTHOADON.MAVT != maVatTu){
//		p = p->NEXT;
//	}
//	return p;
//}

//DSCTHOADONPTR timKiemCTHoaDonThuN(DSCTHOADONPTR first, int n){
//	int dem  = 0;
//	DSCTHOADONPTR p = first;
//	while(p != NULL && dem != n){
//		dem++;
//		p = p->NEXT;
//	}
//	return p;
//}

void chuyenDanhSachChiTietThanhMangHaiChieu(DSCTHOADONPTR dsCTHoaDon, string **ds){
	DSCTHOADONPTR p = dsCTHoaDon;
	int i = 0;
	int j;
	while(p != NULL){
		j = 0;
		ds[i][j++] = p->CTHOADON.MAVT;
		ds[i][j++] = chuyenSoThanhChuoi(p->CTHOADON.SOLUONG);
		ds[i][j++] = chuyenSoThanhChuoi(p->CTHOADON.DONGIA);
		ds[i][j++] = chuyenSoThanhChuoi(p->CTHOADON.VAT);
		i++;
		p = p->NEXT;
	}
}

void formNhapChiTietHoaDon(){
	veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 15, SCREEN_WIDTH - WIDTH_MENU_BAR, 14, BG_BODY);
	int toaDoXKhung = TOADOX + WIDTH_MENU_BAR + (SCREEN_WIDTH - WIDTH_MENU_BAR - SO_COT_BANG_CT_HOA_DON * TABLE_COLUMN_WIDTH - SO_COT_BANG_CT_HOA_DON - 1)/2;
	SetBGColor(BG_BODY);
	SetColor(BG_HEADER);
	string s = "BANG CHI TIET HOA DON";
	gotoxy(toaDoXKhung + (SO_COT_BANG_CT_HOA_DON * TABLE_COLUMN_WIDTH + SO_CT_HOA_DON_MOT_TRANG + 1 - s.length()) / 2,TOADOY_KHUNG_CT_HOA_DON - 1);
	cout << s; 
	SetBGColor(BG_BODY);
	SetColor(TEXT_COLOR);
	veKhungDanhSach(SO_COT_BANG_CT_HOA_DON, SO_CT_HOA_DON_MOT_TRANG + 1, toaDoXKhung ,TOADOY_KHUNG_CT_HOA_DON);
	SetBGColor(BG_BODY);
	SetColor(BG_HEADER);
	for(int i = 0; i < SO_COT_BANG_CT_HOA_DON; i ++){
			gotoxy(toaDoXKhung + i  * (TABLE_COLUMN_WIDTH) + i + 1 + (TABLE_COLUMN_WIDTH - tenCotBangCTHoaDon[i].length())/2, TOADOY_KHUNG_CT_HOA_DON + 1);
			cout << tenCotBangCTHoaDon[i];
	}

}

void formXuatChiTietHoaDon(NhanVien nv, HoaDon hoaDon){
	veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
	int toaDoXKhung = TOADOX + WIDTH_MENU_BAR + (SCREEN_WIDTH - WIDTH_MENU_BAR - SO_COT_BANG_XUAT_CT_HOA_DON * TABLE_COLUMN_WIDTH - SO_COT_BANG_XUAT_CT_HOA_DON - 1)/2;
	SetBGColor(BG_BODY);
	SetColor(BG_HEADER);
	string s = "BANG CHI TIET HOA DON";
	gotoxy(toaDoXKhung + (SO_COT_BANG_XUAT_CT_HOA_DON * TABLE_COLUMN_WIDTH + SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG + 1 - s.length()) / 2,TOADOY_KHUNG_XUAT_CT_HOA_DON - 5);
	cout << s;
	
	gotoxy(toaDoXKhung,TOADOY_KHUNG_XUAT_CT_HOA_DON - 4);
	cout << "Nhan vien:" << nv.HO << " " << nv.TEN;
	gotoxy(toaDoXKhung,TOADOY_KHUNG_XUAT_CT_HOA_DON - 3);
	cout << "So HD:    " << hoaDon.SOHD;
	gotoxy(toaDoXKhung,TOADOY_KHUNG_XUAT_CT_HOA_DON - 2);
	cout << "Loai HD:  ";
	if(hoaDon.LOAI == 'X') cout << "Xuat";
	else cout << "Nhap";
	gotoxy(toaDoXKhung,TOADOY_KHUNG_XUAT_CT_HOA_DON - 1); 
	cout << "Ngay lap: " << chuyenNgayThanhChuoi(hoaDon.NGAYLAP);


	SetBGColor(BG_BODY);
	SetColor(TEXT_COLOR);
	veKhungChiTietHoaDon(SO_COT_BANG_XUAT_CT_HOA_DON, SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG, toaDoXKhung ,TOADOY_KHUNG_XUAT_CT_HOA_DON);
	SetBGColor(BG_BODY);
	SetColor(BG_HEADER);
	for(int i = 0; i < SO_COT_BANG_XUAT_CT_HOA_DON ; i ++){
			gotoxy(toaDoXKhung + i  * (TABLE_COLUMN_WIDTH) + i + 1 + (TABLE_COLUMN_WIDTH - tenCotBangCTHoaDon2[i].length())/2, TOADOY_KHUNG_XUAT_CT_HOA_DON + 1);
			cout << tenCotBangCTHoaDon2[i];
	}
	gotoxy(toaDoXKhung+ 1, TOADOY_KHUNG_XUAT_CT_HOA_DON + SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG * 2 - 3);
	cout << "Tong cong";
	gotoxy(toaDoXKhung+ 1, TOADOY_KHUNG_XUAT_CT_HOA_DON + SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG * 2 - 1);
	cout << "Thanh tien";
	//footer
	gotoxy(TOADOX + WIDTH_MENU_BAR, SCREEN_HEIGTH -1);
	for(int i = 0; i < SCREEN_WIDTH - WIDTH_MENU_BAR; i++){
		SetBGColor(BG_BODY);
		SetColor(BG_HEADER);
		cout << char(196);
	}
	string chucNang = "ESC: Thoat     <-: Trang Truoc     ->: Trang Sau";
	gotoxy(TOADOX + WIDTH_MENU_BAR+(SCREEN_WIDTH-WIDTH_MENU_BAR-chucNang.length())/2, SCREEN_HEIGTH );
	cout << chucNang;
}

void In1TrangCTHoaDon(string **dsCTHoaDon ,int trang, int toaDoKhungX, int toaDoKhungY){	
	for(int i = 0; i < SO_CT_HOA_DON_MOT_TRANG; i++){
		veHinhChuNhat(toaDoKhungX + 0 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 1 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i* 2,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 2 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 3 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 4 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2,TABLE_COLUMN_WIDTH, 1, BG_BODY);
	}
	int i = (trang - 1) * SO_CT_HOA_DON_MOT_TRANG;
	SetBGColor(BG_BODY);
	SetColor(BLACK);
	while( i < trang * SO_CT_HOA_DON_MOT_TRANG){
			gotoxy(toaDoKhungX + 0 * (TABLE_COLUMN_WIDTH + 1) + 1,  toaDoKhungY + (i % SO_CT_HOA_DON_MOT_TRANG) * 2);
			cout << dsCTHoaDon[i][0];
			gotoxy(toaDoKhungX + 1 * (TABLE_COLUMN_WIDTH + 1) + 1,  toaDoKhungY + (i % SO_CT_HOA_DON_MOT_TRANG) * 2);
			cout << dsCTHoaDon[i][1];
			gotoxy(toaDoKhungX + 2 * (TABLE_COLUMN_WIDTH + 1) + 1,  toaDoKhungY + (i % SO_CT_HOA_DON_MOT_TRANG) * 2);
			cout << dsCTHoaDon[i][2];
			gotoxy(toaDoKhungX + 3 * (TABLE_COLUMN_WIDTH + 1) + 1,  toaDoKhungY + (i % SO_CT_HOA_DON_MOT_TRANG) * 2);
			cout << dsCTHoaDon[i][3];		
		i++;
	
	}
}

int kiemTraHopLeCTHoaDonNhapVao(DanhSachVatTu dsVatTu,string **dsCTHoaDon, int soCTHoaDon, int &viTriCot, int &viTriDong, int &trang, int toaDoKhungX, int toaDoKhungY){
		//kiem tra tinh hop le cua chi tiet hoa don nhap vao
		int res;int soLuong, donGia, VAT;
			for(int i = soCTHoaDon; i < MAX_LINE; i++){
				if(dsCTHoaDon[i][0] == "" && dsCTHoaDon[i][1] == "" && dsCTHoaDon[i][2] == "" && dsCTHoaDon[i][3] == ""){
					// neu hang khong nhap thi bo qua
					
				}else if(dsCTHoaDon[i][0] != "" && dsCTHoaDon[i][1] != "" && dsCTHoaDon[i][2] != "" && dsCTHoaDon[i][3] != ""){
						res = timKiemVatTu(dsVatTu,dsCTHoaDon[i][0]);
						if(res == -1){
							viTriCot = 0;
							trang = i / SO_CT_HOA_DON_MOT_TRANG;
							//if(i % SO_CT_HOA_DON_MOT_TRANG != 0) 
							trang++;
							viTriDong = i % SO_CT_HOA_DON_MOT_TRANG;
							thongBao("Vat tu khong ton tai", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
							formNhapChiTietHoaDon();
							return 0;
						}
						
					
						stringstream(dsCTHoaDon[i][1]) >> soLuong;
						stringstream(dsCTHoaDon[i][2]) >> donGia;
						stringstream(dsCTHoaDon[i][3]) >> VAT;
						if(soLuong == 0){
								trang = i / SO_CT_HOA_DON_MOT_TRANG;
							//	if(i % SO_CT_HOA_DON_MOT_TRANG != 0)
								 trang++;
								viTriDong = i % SO_CT_HOA_DON_MOT_TRANG;
								viTriCot = 1;
								thongBao("So Luong Vat Tu Phai > 0", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
								formNhapChiTietHoaDon();
								return 0;
						}
						if(donGia == 0){
								trang = i / SO_CT_HOA_DON_MOT_TRANG;
							//	if(i % SO_CT_HOA_DON_MOT_TRANG != 0) 
								trang++;
								viTriDong = i % SO_CT_HOA_DON_MOT_TRANG;
								viTriCot = 2;
								thongBao("Don Gia Vat Tu Phai > 0", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
								formNhapChiTietHoaDon();
								return 0;
						}
						if(VAT == 0){
								trang = i / SO_CT_HOA_DON_MOT_TRANG;
							//	if(i % SO_CT_HOA_DON_MOT_TRANG != 0) 
								trang++;
								viTriDong = i % SO_CT_HOA_DON_MOT_TRANG;
								viTriCot = 3;
								thongBao(" VAT Phai > 0", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
								formNhapChiTietHoaDon();
								return 0;
						}
				}else{
			
						if(dsCTHoaDon[i][0] == ""){
							viTriCot = 0;
						} else if(dsCTHoaDon[i][1] == ""){
							viTriCot = 1;
						}else if(dsCTHoaDon[i][2] == ""){
							viTriCot = 2;
						}else if(dsCTHoaDon[i][3] == ""){
							viTriCot = 3;
						}
						trang = i / SO_CT_HOA_DON_MOT_TRANG;
						//if(i % SO_CT_HOA_DON_MOT_TRANG != 0)
						 trang++;
						viTriDong = i % SO_CT_HOA_DON_MOT_TRANG;
						thongBao("Du Lieu Nhap Thieu", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
						formNhapChiTietHoaDon();
					//	In1TrangCTHoaDon(dsCTHoaDon, trang, toaDoKhungX, toaDoKhungY);
						return 0;
			
				}
				
			}
			return 1;
}

int kiemTraHopLeSoLuongVatTuNhapVao(DanhSachVatTu dsVatTu,string **dsCTHoaDon,int soCTHoaDon, int &viTriCot, int &viTriDong, int &trang){
	int soLuong;
	int viTriVatTu;
	
	int *mangSoLuong  = new int[dsVatTu.N];
	for(int i = 0; i < dsVatTu.N; i++)
		mangSoLuong[i] = dsVatTu.NODE[i].SOLUONGTON;
	
	for(int i = soCTHoaDon; i < MAX_LINE; i++){
		stringstream(dsCTHoaDon[i][1]) >> soLuong;
		viTriVatTu = timKiemVatTu(dsVatTu, dsCTHoaDon[i][0]);
		if(viTriVatTu == -1) return 1;
	
		if(soLuong > mangSoLuong[viTriVatTu]){
			trang = i / SO_CT_HOA_DON_MOT_TRANG;
			//if(i % SO_CT_HOA_DON_MOT_TRANG != 0) 
			trang++;
			viTriDong = i % SO_CT_HOA_DON_MOT_TRANG;
			viTriCot = 1;
			thongBao("Kho Chi Con " + chuyenSoThanhChuoi(dsVatTu.NODE[viTriVatTu].SOLUONGTON) + " " + dsVatTu.NODE[viTriVatTu].MAVT, TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
			formNhapChiTietHoaDon();
			return 0;
		}else{
			mangSoLuong[viTriVatTu] -= soLuong;
		}	
	}
	return 1;
}

// neu 2 vat tu co cung don gia va VAT thi nhap lam 1
void congDonCTHoaDonTrungNhau(string **dsCTHoaDon ){
	int soLuong1, soLuong2;
	for(int i = 0; i < MAX_LINE; i++){
		
		if(dsCTHoaDon[i][0] != ""){
			for(int j = i + 1; j < MAX_LINE; j++){
				if(dsCTHoaDon[j][0] == dsCTHoaDon[i][0] && dsCTHoaDon[j][2] == dsCTHoaDon[i][2] && dsCTHoaDon[j][3] == dsCTHoaDon[i][3]){
					stringstream(dsCTHoaDon[i][1]) >> soLuong1;
					stringstream(dsCTHoaDon[j][1]) >> soLuong2;
					soLuong1 += soLuong2;
					dsCTHoaDon[i][1] = chuyenSoThanhChuoi(soLuong1);
					dsCTHoaDon[j][0] = "";
					dsCTHoaDon[j][1] = "";
					dsCTHoaDon[j][2] = "";
					dsCTHoaDon[j][3] = "";
				}
			}
		}
	}
}

int nhapChiTietHoaDon(DanhSachVatTu &dsVatTu, NhanVien &nhanVien ,HoaDon &hoaDon, string **dsCTHoaDon, int &viTriDong, int &viTriCot){
	formNhapChiTietHoaDon();

	// 
	int viTriVatTu;
	int res, res2;
	CT_HoaDon ctHoaDon;
	

	// tinh toan trang, tongTrang, viTriDong, viTriCot
	int c;
	int trang = 1;
	int soCTHoaDon = demSoCTHoaDon(hoaDon.DSCTHOADON);
	
	int tongTrang = MAX_LINE / SO_CT_HOA_DON_MOT_TRANG;
	if(soCTHoaDon == 0){
		trang = 1;
	}else{		
		viTriDong = soCTHoaDon % SO_CT_HOA_DON_MOT_TRANG;
		trang = soCTHoaDon / SO_CT_HOA_DON_MOT_TRANG;
		trang++;
	}

	int toaDoXKhung = TOADOX + WIDTH_MENU_BAR + (SCREEN_WIDTH - WIDTH_MENU_BAR - SO_COT_BANG_CT_HOA_DON * TABLE_COLUMN_WIDTH - SO_COT_BANG_CT_HOA_DON - 1)/2;
	int toaDoYKhung = TOADOY_KHUNG_CT_HOA_DON + 3;
	
	do{
		In1TrangCTHoaDon(dsCTHoaDon, trang, toaDoXKhung, toaDoYKhung);
		gotoxy(toaDoXKhung + 40, toaDoYKhung + (SO_CT_HOA_DON_MOT_TRANG) * 2+ 1);
		cout << "\t\t\t\t\t";
		gotoxy(toaDoXKhung + 40, toaDoYKhung + (SO_CT_HOA_DON_MOT_TRANG) * 2+ 1);
		cout << "Trang " << trang << "/" << tongTrang;
		// khong the nhap nhung CT hoa don da duoc luc (viTriCot == -1)
		if(viTriCot != -1 ){
			if(viTriCot == 0){
				c = nhapChuoiKiTuVaSoKhongKhoangTrang(dsCTHoaDon[(trang - 1) * SO_CT_HOA_DON_MOT_TRANG + viTriDong][viTriCot],toaDoXKhung+ viTriCot + 1+ viTriCot * TABLE_COLUMN_WIDTH ,toaDoYKhung + viTriDong * 2,WIDTH_TEXT, BG_BODY, BLACK);
			}else{
			
				c = nhapChuoiKiTuSo(dsCTHoaDon[(trang - 1) * SO_CT_HOA_DON_MOT_TRANG + viTriDong][viTriCot],toaDoXKhung+ viTriCot + 1+ viTriCot * TABLE_COLUMN_WIDTH ,toaDoYKhung + viTriDong * 2,WIDTH_TEXT, BG_BODY, BLACK);
			} 	
		
		}else{
			gotoxy(toaDoXKhung - 1,toaDoYKhung + viTriDong * 2);
			c =keyPressed();
		}

		if((c == KEY_TAB || c == KEY_RIGHT) && viTriCot < SO_COT_BANG_CT_HOA_DON - 1){
			viTriCot++;
		}	
		
		if(c == KEY_LEFT && viTriCot > 0){
			viTriCot--;
		}
		
		if(c == KEY_ENTER || c == KEY_DOWN){
			viTriCot = 0;
			if(viTriDong < SO_CT_HOA_DON_MOT_TRANG - 1){
				viTriDong++;
			}else{
				viTriDong = 0;
				if(trang <tongTrang )trang++;
			}
			if((trang - 1) * SO_CT_HOA_DON_MOT_TRANG + viTriDong < soCTHoaDon){
				viTriCot = -1;
			}					
		}
		
		if(c == KEY_UP){
			viTriDong--;
			if(viTriDong < 0){
				if(trang > 1){
					trang--;
					viTriDong = SO_CT_HOA_DON_MOT_TRANG - 1;
				}else{
					viTriDong = 0;
				}	
			}
			if((trang - 1) * SO_CT_HOA_DON_MOT_TRANG + viTriDong < soCTHoaDon){
				viTriCot = -1;
			}	
		}
		
		if(c == KEY_INSERT){
			
			res = kiemTraHopLeCTHoaDonNhapVao(dsVatTu, dsCTHoaDon, soCTHoaDon, viTriCot, viTriDong, trang, toaDoXKhung, toaDoYKhung);
			if(res != 1){
				string chucNang = "ESC: Thoat   Insert: Them vao danh sach   F5: Nhap danh sach vat tu   F2: Danh sach vat tu";
				formHoaDon(nhanVien, hoaDon, chucNang);
				xuatHoaDonLenForm(hoaDon, chuyenSoThanhChuoi(hoaDon.NGAYLAP.NGAY), chuyenSoThanhChuoi(hoaDon.NGAYLAP.THANG), chuyenSoThanhChuoi(hoaDon.NGAYLAP.NAM));
				formNhapChiTietHoaDon();
				In1TrangCTHoaDon(dsCTHoaDon, trang, toaDoXKhung, toaDoYKhung);
				continue;
				
			}
			if(hoaDon.LOAI == 'X'){
				res2 =kiemTraHopLeSoLuongVatTuNhapVao(dsVatTu, dsCTHoaDon, soCTHoaDon, viTriCot, viTriDong, trang);
				if(res2 != 1){
					string chucNang = "ESC: Thoat   Insert: Them vao danh sach   F5: Nhap danh sach vat tu   F2: Danh sach vat tu";
					formHoaDon(nhanVien, hoaDon, chucNang);
					xuatHoaDonLenForm(hoaDon, chuyenSoThanhChuoi(hoaDon.NGAYLAP.NGAY), chuyenSoThanhChuoi(hoaDon.NGAYLAP.THANG), chuyenSoThanhChuoi(hoaDon.NGAYLAP.NAM));
					formNhapChiTietHoaDon();
					In1TrangCTHoaDon(dsCTHoaDon, trang, toaDoXKhung, toaDoYKhung);
					continue;
					
				}
			}
		
			// them chi tiet hoa don vao ds
		
			if(res == 1){
				congDonCTHoaDonTrungNhau(dsCTHoaDon);
				for(int i = soCTHoaDon; i < MAX_LINE; i++){
					if(dsCTHoaDon[i][0] != ""){
						ctHoaDon.MAVT = dsCTHoaDon[i][0];
						stringstream(dsCTHoaDon[i][1]) >> ctHoaDon.SOLUONG;
						stringstream(dsCTHoaDon[i][2]) >> ctHoaDon.DONGIA;
						stringstream(dsCTHoaDon[i][3]) >> ctHoaDon.VAT;
						themSapXep(hoaDon.DSCTHOADON, ctHoaDon);
						if(hoaDon.LOAI =='X'){
							viTriVatTu =	timKiemVatTu(dsVatTu, ctHoaDon.MAVT);
							dsVatTu.NODE[viTriVatTu].SOLUONGTON -= ctHoaDon.SOLUONG;
							
						}else{
							viTriVatTu =	timKiemVatTu(dsVatTu, ctHoaDon.MAVT);
							dsVatTu.NODE[viTriVatTu].SOLUONGTON += ctHoaDon.SOLUONG;
						}
					}
				}
					break;
			}
				string chucNang = "ESC: Thoat   Insert: Them vao danh sach   F5: Nhap danh sach vat tu   F2: Danh sach vat tu";
				formHoaDon(nhanVien, hoaDon, chucNang);
				xuatHoaDonLenForm(hoaDon, chuyenSoThanhChuoi(hoaDon.NGAYLAP.NGAY), chuyenSoThanhChuoi(hoaDon.NGAYLAP.THANG), chuyenSoThanhChuoi(hoaDon.NGAYLAP.NAM));
				formNhapChiTietHoaDon();
				In1TrangCTHoaDon(dsCTHoaDon, trang, toaDoXKhung, toaDoYKhung);
		}
			if(c == KEY_F2){
			xemDanhSachVatTu(dsVatTu);
			string chucNang = "ESC: Thoat   Insert: Them vao danh sach   F5: Nhap danh sach vat tu   F2: Danh sach vat tu";
			formHoaDon(nhanVien, hoaDon, chucNang);
			xuatHoaDonLenForm(hoaDon, chuyenSoThanhChuoi(hoaDon.NGAYLAP.NGAY), chuyenSoThanhChuoi(hoaDon.NGAYLAP.THANG), chuyenSoThanhChuoi(hoaDon.NGAYLAP.NAM));
			formNhapChiTietHoaDon();
			In1TrangCTHoaDon(dsCTHoaDon, trang, toaDoXKhung, toaDoYKhung);
		}
		
	}while(c != KEY_ESC);
	return c;
}

void inChiTiet(DSCTHOADONPTR first, int trang, int toaDoKhungX, int toaDoKhungY){
	
	DSCTHOADONPTR p = first;
	int viTri = (trang - 1) * (SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG -3);
	int dem = 0;
	// tim vi tri bat dau cua trang
	while(p != NULL && dem < viTri){	
		dem++;
		p = p->NEXT;
	}
	//Xoa du lieu trang truoc do
	for(int i = 0; i < SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG - 3; i++){
		veHinhChuNhat(toaDoKhungX + 0 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 1 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i* 2,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 2 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 3 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 4 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2,TABLE_COLUMN_WIDTH, 1, BG_BODY);
	}
	// in chi tiet vat tu
	SetBGColor(BG_BODY);
	SetColor(BLACK);
	while(p != NULL && viTri < (trang * (SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG -3))){
		
			gotoxy(toaDoKhungX + 0 * (TABLE_COLUMN_WIDTH + 1) + 1,  toaDoKhungY + (viTri% (SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG -3)) * 2);
			cout << viTri + 1;
			gotoxy(toaDoKhungX + 1 * (TABLE_COLUMN_WIDTH + 1) + 1,  toaDoKhungY + (viTri % (SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG -3)) * 2);
			cout << p->CTHOADON.MAVT;
			gotoxy(toaDoKhungX + 2 * (TABLE_COLUMN_WIDTH + 1) + 1,  toaDoKhungY + (viTri % (SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG -3)) * 2);
			cout <<p->CTHOADON.SOLUONG;
			gotoxy(toaDoKhungX + 3 * (TABLE_COLUMN_WIDTH + 1) + 1,  toaDoKhungY + (viTri % (SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG -3)) * 2);
			cout << p->CTHOADON.DONGIA;
			gotoxy(toaDoKhungX + 4 * (TABLE_COLUMN_WIDTH + 1) + 1,  toaDoKhungY + (viTri % (SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG -3)) * 2);
			cout << p->CTHOADON.VAT;
		viTri++;
		p = p->NEXT;
	}
	

}

long long tinhTienMotHoaDon(DSCTHOADONPTR first){
	long long tongTien = 0;
	long long tongThue = 0;
	DSCTHOADONPTR p = first;
	while(p != NULL){
		tongTien += (long long)p->CTHOADON.DONGIA * p->CTHOADON.SOLUONG;
		tongThue += (long long)p->CTHOADON.DONGIA * p->CTHOADON.SOLUONG * p->CTHOADON.VAT / 100;
		p = p->NEXT;
	}
	return tongThue + tongTien;
}

void tinhTienMotHoaDon(DSCTHOADONPTR first,int &tongSoLuong, long long &tongTien, long long &tongThue){
	tongSoLuong = 0;
	tongTien = 0;
	tongThue = 0;
	DSCTHOADONPTR p = first;
	while(p != NULL){
		tongSoLuong += p->CTHOADON.SOLUONG;
		tongTien += (long long)p->CTHOADON.DONGIA * p->CTHOADON.SOLUONG;
		tongThue += (long long) p->CTHOADON.DONGIA * p->CTHOADON.SOLUONG * p->CTHOADON.VAT / 100;
		p = p->NEXT;
	}
}

void xuatChiTietHoaDon(NhanVien &nv, HoaDon &hoaDon){
	formXuatChiTietHoaDon(nv, hoaDon);

	// tinh toan trang, tongTrang, viTriDong, viTriCot
	int soHang = SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG - 3;
	int c;
	int trang = 1;
	int soCTHoaDon = demSoCTHoaDon(hoaDon.DSCTHOADON);
	
	int tongTrang = soCTHoaDon / soHang;
	if(soCTHoaDon % soHang != 0) tongTrang++;
	if(soCTHoaDon == 0) trang = tongTrang = 1;

	int toaDoXKhung = TOADOX + WIDTH_MENU_BAR + (SCREEN_WIDTH - WIDTH_MENU_BAR - SO_COT_BANG_XUAT_CT_HOA_DON * TABLE_COLUMN_WIDTH - SO_COT_BANG_XUAT_CT_HOA_DON - 1)/2;
	int toaDoYKhung = TOADOY_KHUNG_XUAT_CT_HOA_DON;
	long long tongTien = 0, tongThue = 0;
	int tongSoLuong = 0; 
	tinhTienMotHoaDon(hoaDon.DSCTHOADON, tongSoLuong, tongTien, tongThue);
	gotoxy(toaDoXKhung + 2 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoYKhung + (SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG - 1) * 2 -1);
	cout << tongSoLuong;
	gotoxy(toaDoXKhung + 3 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoYKhung + (SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG - 1) * 2 -1);
	cout << tongTien;
	gotoxy(toaDoXKhung + 4 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoYKhung + (SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG - 1) * 2- 1) ;
	cout << tongThue;
	gotoxy(toaDoXKhung + 1 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoYKhung + SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG * 2- 1) ;
	cout << tongTien + tongThue;
	do{
		SetBGColor(BG_BODY);
		SetColor(BG_HEADER);
		gotoxy(toaDoXKhung + 50, TOADOY_KHUNG_XUAT_CT_HOA_DON + SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG * 2 + 2);
		cout << "\t\t\t\t\t\t";
		gotoxy(toaDoXKhung + 50, TOADOY_KHUNG_XUAT_CT_HOA_DON + SO_HANG_XUAT_CT_HOA_DON_MOT_TRANG * 2 + 2);
		cout << "Trang " << trang  << "/" <<tongTrang;
		inChiTiet(hoaDon.DSCTHOADON, trang, toaDoXKhung, toaDoYKhung + 3);
		c =keyPressed();
		if(c == KEY_RIGHT && trang < tongTrang) trang++;
		if(c == KEY_LEFT && trang > 1) trang--;
	
	}while(c != KEY_ESC);
}



#include "HoaDon.cpp"

string lableNhanVien[SIZE_FORM_NHAN_VIEN]={"Ma nhan vien", "Ho", "Ten", "Phai"};
string menuChucNangNhanVien[SIZE_MENU_NHAN_VIEN] = {"Them", "Cap Nhat", "In Danh Sach"};
string tenCotBangNhanVien[] = {"STT", "Ma nhan vien", "Ho", "Ten", "Phai"};

// them mot cay con vao stack
bool push(Stack &sp, NHANVIENTREE p){
	if(p == NULL)
	return false;
	// Khoi tao mot node Stack de chua cay nhan vien con
	Stack q = new NodeNhanVienDSLK;
	q->NODE = p;
	//them vao dau danh sach lien kiet don stack
	q->NEXT = sp;
	sp = q;
	return true;
}
// lay mot cay con tu stacck
bool pop(Stack &sp, NHANVIENTREE &p){
	if(sp == NULL) return false;
	Stack q;
	q = sp; // nut can xoa
	
	p = sp->NODE;
	// xoa node dau cua stack
	sp = q->NEXT;
	delete q;
	return true;
}

bool kiemTraRong(NHANVIENTREE root){
	if(root == NULL) return true;
	return false;
}

bool themVaoCay(NHANVIENTREE &p, NhanVien nv){
	if(p == NULL){// nut p hien tai la nut la
		p = new NodeNhanVienTree;
		p->NHANVIEN = nv;
		p->LEFT = NULL;
		p->RIGHT = NULL;
		return true;
	}else{
		if(nv.MANV < p->NHANVIEN.MANV)
			themVaoCay(p->LEFT, nv);
		else if(nv.MANV > p->NHANVIEN.MANV)
			themVaoCay(p->RIGHT, nv);
		else return false;
	}
}
//Nut cuc trai cua cay con ben phai cua p co khoa vua lon hon khoa cua p
//de loai p cho r chi den nut cuc trai do
//sao cheo noi dung cua r vao nut ma rp dang troo den
//tao lien ket thic hop de loai bo rp ra khoi cay va xoa rp
void xoaTruongHop3(NHANVIENTREE &p, NHANVIENTREE &rp){
	if(p->LEFT != NULL)// neu p chua la  nut cuc trai
		xoaTruongHop3(p->LEFT, rp);
	
	else{	// den day r da la nut cuc trai cua cai con ben phai co  goc la rp
		rp->NHANVIEN =  p->NHANVIEN; // chep noi dung cua r sang rp de giai phong rp
		rp = p; // di chuyen rp den p, rp la node can giai phong
		p = rp->RIGHT;// p luc nay la cha cua p tro LEFT(tinh chat de quy)
	}
}

bool xoaNodeCuaCay(NHANVIENTREE &p, string maNV){
	NHANVIENTREE rp;
	if(p == NULL){
		return false;
	}
	if(maNV < p->NHANVIEN.MANV)
		xoaNodeCuaCay(p->LEFT, maNV);
	else if (maNV > p->NHANVIEN.MANV)
		xoaNodeCuaCay(p->RIGHT, maNV);
	else{ // p la nut can xoa
		rp = p;
		if(rp->RIGHT == NULL) p = rp->LEFT;// p la nut la hoac p chi co cay con ben trai
		else if(rp->LEFT == NULL) p = rp->RIGHT; // p chi co cay con ben phai
		else xoaTruongHop3(rp->RIGHT, rp);// p co ca 2 cay con
		delete rp;
		return true;
	}
}

NHANVIENTREE timKiemMotNode(NHANVIENTREE  root, NhanVien nv){
	NHANVIENTREE p;
	p = root;
	
	while( p != NULL && p->NHANVIEN.MANV != nv.MANV)
		if(nv.MANV < p->NHANVIEN.MANV)
			p = p->LEFT;
		else p = p->RIGHT;
	return p;
}


void duyetLNR(NHANVIENTREE root){
	Stack sp = NULL;
	NHANVIENTREE p = root;
	do{
		while(p != NULL){
			push(sp, p);// them cay hien tai vao stack
			p = p->LEFT;// roi di chuyen den cay con ben trai
						// lap lai cho den khi p = NULL, tuc la het cay con ben trai
		}
		
		if(sp != NULL){
			//lay cay con ben trai duoc them cuoi cung ra
			// luc nay cay con ben trai la NULL hoac da duyet qua 
			// tiep theo chuyen p den cay con ben phai roi tiep tuc quay lai buoc them cay vao stack	
			pop(sp, p);
			cout << p->NHANVIEN.MANV << "\t" << p->NHANVIEN.HO << "\t" << p->NHANVIEN.TEN << "\t" << 
					p->NHANVIEN.PHAI << endl;
			p = p->RIGHT;
		}else break;
		
	}while(true);
}
// tra ve so nhan vien
int demSoNhanVien(NHANVIENTREE root){
	Stack sp = NULL;
	int dem = 0;
	NHANVIENTREE p = root;
	do{
		while(p != NULL){
			push(sp, p);
			p = p->LEFT;
		}
		
		if(sp != NULL){
			pop(sp, p);
			dem++;
			p = p->RIGHT;
		}else break;
		
	}while(true);
	return dem;
}

// tim thu tu cua nhan vien trong danh sach
// vi tri bat dau tu 0
// khong tim thay tra ve -1
int timViTriNhanVien(NHANVIENTREE root, string maNV){
	
	Stack sp = NULL;
	int dem = 0;
	NHANVIENTREE p = root;
	do{
		while(p != NULL){
			push(sp, p);
			p = p->LEFT;
		}
		
		if(sp != NULL){
			pop(sp, p);
			//
			if(p->NHANVIEN.MANV == maNV){
				return dem;
			}
			dem++;
			p = p->RIGHT;
		}else break;
		
	}while(true);
	return -1;

}
// tim nhan vien thu N cua danh sach
NHANVIENTREE timKiemNodeThuN(NHANVIENTREE root, int N){
	Stack sp = NULL;
	int dem = 0;
	NHANVIENTREE p = root;
	do{
		while(p != NULL){
			push(sp, p);
			p = p->LEFT;
		}
		
		if(sp != NULL){
			pop(sp, p);
			if(dem == N) return p;
			dem++;
			p = p->RIGHT;
		}else break;
		
	}while(true);
	return NULL;
}
// ve form nhap du lieu cho nhanh vien
void formThemNhanVien(string tieuDe, string chucNang){
//	veHinhChuNhat(TOADOX + COL_LEFT_WIDTH, TOADOY + 3, SCREEN_WIDTH - COL_LEFT_WIDTH, SCREEN_HEIGTH - 3, BG_BODY_COLOR);
	SetBGColor(BG_BODY);
	SetColor(BLACK);
	gotoxy(TOADOX + WIDTH_MENU_BAR + (SCREEN_WIDTH - WIDTH_MENU_BAR - tieuDe.length()) / 2, 10);
	cout << tieuDe;
	// ve form nhap du lieu
	for(int i = 0; i < SIZE_FORM_NHAN_VIEN; i++){
		gotoxy(TOADOX_LABLE, TOADOY_FORM + i * 2);
		SetBGColor(BG_BODY);
		SetColor(BLACK);
		cout << lableNhanVien[i];
		if(i != 3)
			veHinhChuNhat(TOADOX_TEXT, TOADOY_FORM + i * 2, WIDTH_TEXT, 1, BLACK);
		else{
			veHinhChuNhat(TOADOX_CB_NAM, TOADOY_FORM + i * 2, 3, 1, BLACK);
			SetBGColor(BG_BODY);
			cout << " Nam";
			veHinhChuNhat(TOADOX_CB_NU, TOADOY_FORM + i * 2, 3, 1, BLACK);
			SetBGColor(BG_BODY);
			cout << " Nu";
		}
	}
	
	// footer
//	string s = "ESC: Thoat\tInsert: Them vao danh sach";
	gotoxy(TOADOX + WIDTH_MENU_BAR, SCREEN_HEIGTH -1);
	for(int i = 0; i < SCREEN_WIDTH - WIDTH_MENU_BAR; i++){
		SetBGColor(BG_BODY);
		SetColor(BG_HEADER);
		cout << char(196);
	}
	gotoxy(TOADOX + WIDTH_MENU_BAR+(SCREEN_WIDTH-WIDTH_MENU_BAR-chucNang.length())/2, SCREEN_HEIGTH );
	cout << chucNang;
}


// cap nhat thong tin cua nhan vien
int capNhapNhanVien(NhanVien &nv){
	int c;	
	// index = 1 nhap HO
	// index = 2 nhap TEN
	// index = 3 nhap gioi tinh
	int index = 1;
	bool ketQua = false;
	veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
	string tieuDe = "CAP NHAT NHAN VIEN";
	string chucNang = "ESC: Thoat\tInsert: Cap nhat danh sach";
	formThemNhanVien(tieuDe, chucNang);
	SetBGColor(BLACK);
	SetColor(TEXT_COLOR);
	
	// xuat thong tin nhan vien len form
	gotoxy(TOADOX_TEXT, TOADOY_FORM + 0 * 2);
	cout << nv.MANV;
	
	gotoxy(TOADOX_TEXT, TOADOY_FORM + 1 * 2);
	cout << nv.HO;
	
	gotoxy(TOADOX_TEXT, TOADOY_FORM + 2 * 2);
	cout << nv.TEN;
	
	if(nv.PHAI== true){
		gotoxy(TOADOX_CB_NU + 1, TOADOY_FORM + 3 * 2);
		cout << " ";
		gotoxy(TOADOX_CB_NAM + 1, TOADOY_FORM + 3 * 2);
		cout << "X";
	}else{
		gotoxy(TOADOX_CB_NAM + 1, TOADOY_FORM + 3 * 2);
		cout << " ";
		gotoxy(TOADOX_CB_NU + 1, TOADOY_FORM + 3 * 2);
		cout << "X";
	}
	//
	do{
		// index == 1 con tro dang o vi tri nhap HO
		 if(index == 1){
			c = nhapChuoiKiTu(nv.HO, TOADOX_TEXT, TOADOY_FORM + index * 2, WIDTH_TEXT, BLACK, TEXT_COLOR);
		// index == 2 con tro dang o vi tri nhap TEN
		}else if(index == 2){
			c = nhapChuoiKiTu(nv.TEN, TOADOX_TEXT, TOADOY_FORM + index * 2, WIDTH_TEXT, BLACK, TEXT_COLOR);
		}else{
			do{
				// danh dau X vao o gioi tinh Nam
				if(nv.PHAI== true){
					gotoxy(TOADOX_CB_NU + 1, TOADOY_FORM + 3 * 2);
					cout << " ";
					gotoxy(TOADOX_CB_NAM + 1, TOADOY_FORM + 3 * 2);
					cout << "X";
				// danh dau X vao o gioi tinh Nu
				}else{
					gotoxy(TOADOX_CB_NAM + 1, TOADOY_FORM + 3 * 2);
					cout << " ";
					gotoxy(TOADOX_CB_NU + 1, TOADOY_FORM + 3 * 2);
					cout << "X";
					
				}
				c = keyPressed();
				// bam phim ->
				if(c == KEY_RIGHT) nv.PHAI = false;
				// bam phim <-
				if(c== KEY_LEFT) nv.PHAI = true;
				
				
			}while(c != KEY_UP && c != KEY_DOWN && c != KEY_ESC && c != KEY_INSERT);
		}
		if((c == KEY_DOWN || c == KEY_ENTER || c == KEY_TAB) && index < 3) index++;
		
		if(c == KEY_UP && index > 1) index--;
		
		if(c == KEY_INSERT){
			 if(nv.MANV !="" && nv.HO != "" && nv.TEN != ""){
					if(!kiemTraChuoiNhapVao(nv.MANV)){
			 		index = 0;
			 		thongBao("Ma nhan vien bao gom nhung ki tu a-z A-Z 0-9", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
				 }else if(!kiemTraChuoiNhapVao(nv.HO)){
				 	index = 1;
				 	thongBao("Ho vien bao gom nhung ki tu a-z A-Z 0-9", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
				 }else if(!kiemTraChuoiNhapVao(nv.TEN)){
				 	index = 2;
				 	thongBao("Ten nhan vien bao gom nhung ki tu a-z A-Z 0-9", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
				 }else{
				 		nv.MANV = dinhDangChuoiNhapVao(nv.MANV);
				 		nv.HO = dinhDangChuoiNhapVao(nv.HO);
				 		nv.TEN = dinhDangChuoiNhapVao(nv.TEN);
						thongBao("Cap nhat Nhan Vien Thanh Cong", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
						veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
						return 1;	 		
				}
			
			 	
			 } else{
					thongBao("Vui Long Khong De Trong Thong Tin", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
			 } 
		     
		        veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
			  	formThemNhanVien(tieuDe, chucNang);
				if(nv.PHAI== true){
					gotoxy(TOADOX_CB_NU + 1, TOADOY_FORM + 3 * 2);
					cout << " ";
					gotoxy(TOADOX_CB_NAM + 1, TOADOY_FORM + 3 * 2);
					cout << "X";
					
				}else{
					gotoxy(TOADOX_CB_NAM + 1, TOADOY_FORM + 3 * 2);
					cout << " ";
					gotoxy(TOADOX_CB_NU + 1, TOADOY_FORM + 3 * 2);
					cout << "X";
				}
				SetColor(TEXT_COLOR);
				SetBGColor(BLACK);
				gotoxy (TOADOX_TEXT, TOADOY_FORM + 4);
				cout << nv.TEN;
				gotoxy (TOADOX_TEXT, TOADOY_FORM + 2);
				cout << nv.HO; 
				gotoxy (TOADOX_TEXT, TOADOY_FORM );
				cout << nv.MANV;  
		}	
	}while(c != KEY_ESC);
	
//	cout << nv.MANV << "\t" << nv.HO << "\t" << nv.TEN << "\t" <<  nv.PHAI << endl;
	if(c == KEY_ESC)
		return -1;
}
// nhap thong tin cua mot nhan vien
int nhapNhanVien(NHANVIENTREE &root, int &viTriNhanVienVuaNhap){
	int c;
	// index = 0 nhap MANV
	// index = 1 nhap HO
	// index = 2 nhap TEN
	// index = 3 nhap gioi tinh
	int index = 0;
	bool ketQua = false;
	NHANVIENTREE p = NULL;
	NhanVien nv;
	string tieuDe = "NHAP NHAN VIEN";
	string chucNang = "ESC: Thoat\tInsert: Them vao danh sach";
	formThemNhanVien(tieuDe, chucNang);
	SetColor(TEXT_COLOR);
	SetBGColor(BLACK);
	if(nv.PHAI== true){
		gotoxy(TOADOX_CB_NU + 1, TOADOY_FORM + 3 * 2);
		cout << " ";
		gotoxy(TOADOX_CB_NAM + 1, TOADOY_FORM + 3 * 2);
		cout << "X";
	}else{
		gotoxy(TOADOX_CB_NU + 1, TOADOY_FORM + 3 * 2);
		cout << "X";
		gotoxy(TOADOX_CB_NAM + 1, TOADOY_FORM + 3 * 2);
		cout << " ";
	}

	do{
		if(index == 0){
			c = nhapChuoiKiTuVaSoKhongKhoangTrang(nv.MANV, TOADOX_TEXT, TOADOY_FORM + index * 2, WIDTH_TEXT, BLACK, TEXT_COLOR);
		}else if(index == 1){
			c = nhapChuoiKiTu(nv.HO, TOADOX_TEXT, TOADOY_FORM + index * 2, WIDTH_TEXT, BLACK, TEXT_COLOR);
		}else if(index == 2){
			c = nhapChuoiKiTu(nv.TEN, TOADOX_TEXT, TOADOY_FORM + index * 2, WIDTH_TEXT, BLACK, TEXT_COLOR);
		}else{
			do{
				if(nv.PHAI== true){
					SetColor(TEXT_COLOR);
					SetBGColor(BLACK);
					gotoxy(TOADOX_CB_NU + 1, TOADOY_FORM + 3 * 2);
					cout << " ";
					gotoxy(TOADOX_CB_NAM + 1, TOADOY_FORM + 3 * 2);
					cout << "X";
				}else{
					SetColor(TEXT_COLOR);
					SetBGColor(BLACK);
					gotoxy(TOADOX_CB_NAM + 1, TOADOY_FORM + 3 * 2);
					cout << " ";
					gotoxy(TOADOX_CB_NU + 1, TOADOY_FORM + 3 * 2);
					cout << "X";
				
				}
				c = keyPressed();
				if(c == KEY_RIGHT) nv.PHAI = false;
				if(c== KEY_LEFT) nv.PHAI = true;
				
				
			}while(c != KEY_UP && c != KEY_DOWN && c != KEY_ESC && c != KEY_INSERT);
		}
		if((c == KEY_DOWN || c == KEY_ENTER || c == KEY_TAB) && index < 3) index++;
		
		if(c == KEY_UP && index > 0) index--;
		
		if(c == KEY_INSERT){
			 if(nv.MANV !="" && nv.HO != "" && nv.TEN != ""){
			 	
			 	if(!kiemTraChuoiNhapVao(nv.MANV)){
			 		index = 0;
			 		thongBao("Ma nhan vien bao gom nhung ki tu a-z A-Z 0-9", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
				 }else if(!kiemTraChuoiNhapVao(nv.HO)){
				 	index = 1;
				 	thongBao("Ho vien bao gom nhung ki tu a-z A-Z 0-9", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
				 }else if(!kiemTraChuoiNhapVao(nv.TEN)){
				 	index = 2;
				 	thongBao("Ten nhan vien bao gom nhung ki tu a-z A-Z 0-9", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
				 }else{
				 		nv.MANV = dinhDangChuoiNhapVao(nv.MANV);
				 		nv.HO = dinhDangChuoiNhapVao(nv.HO);
				 		nv.TEN = dinhDangChuoiNhapVao(nv.TEN);
					 	p = timKiemMotNode(root, nv);
			 	if(p == NULL){
				 	ketQua = themVaoCay(root, nv);
			 		if(ketQua == true){
						thongBao("Them Nhan Vien Thanh Cong", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
						viTriNhanVienVuaNhap = timViTriNhanVien(root, nv.MANV);
						veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
						break;
					}else{
					thongBao("Them Nhan Vien That Bai", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
					}
				}else{
					
					thongBao("Nhan Vien Da Ton Tai", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
				}
				 }
			 	
			 	
			 } else{
					thongBao("Vui Long Khong De Trong Thong Tin", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
			 } 
		      /////////////
		        veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
			  	formThemNhanVien(tieuDe, chucNang);
				if(nv.PHAI== true){
					SetColor(TEXT_COLOR);
					SetBGColor(BLACK);
					gotoxy(TOADOX_CB_NU + 1, TOADOY_FORM + 3 * 2);
					cout << " ";
					gotoxy(TOADOX_CB_NAM + 1, TOADOY_FORM + 3 * 2);
					cout << "X";
					
				}else{
					SetColor(TEXT_COLOR);
					SetBGColor(BLACK);
					gotoxy(TOADOX_CB_NAM + 1, TOADOY_FORM + 3 * 2);
					cout << " ";
					gotoxy(TOADOX_CB_NU + 1, TOADOY_FORM + 3 * 2);
					cout << "X";
				}
				SetColor(TEXT_COLOR);
				SetBGColor(BLACK);
				gotoxy (TOADOX_TEXT, TOADOY_FORM + 4);
				cout << nv.TEN;
				gotoxy (TOADOX_TEXT, TOADOY_FORM + 2);
				cout << nv.HO; 
				gotoxy (TOADOX_TEXT, TOADOY_FORM );
				cout << nv.MANV;  
		}	
	}while(c != KEY_ESC);
	if(c == KEY_ESC)
		return -1;
}
//In mot trang danh sach nhan vien 
void in1TrangNhanVien(NHANVIENTREE root, int trang, int tongTrang, int toaDoKhungX, int toaDoKhungY){
	Stack sp = NULL;
	int dem = 0;
	NHANVIENTREE p = root;
	for(int i = 0; i < SO_DONG_MOT_TRANG; i++){
		veHinhChuNhat(toaDoKhungX + 0 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2+ 3,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 1 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i* 2+ 3,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 2 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2+ 3,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 3 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2+ 3,TABLE_COLUMN_WIDTH, 1, BG_BODY);
		veHinhChuNhat(toaDoKhungX + 4 * (TABLE_COLUMN_WIDTH + 1) + 1, toaDoKhungY + i * 2+ 3,TABLE_COLUMN_WIDTH, 1, BG_BODY);
	}
	do{
		while(p != NULL){
			push(sp, p);
			p = p->LEFT;
		}
		
		if(sp != NULL){
			pop(sp, p);
			if(dem >= (trang - 1) * SO_DONG_MOT_TRANG && dem < trang   * SO_DONG_MOT_TRANG){
					gotoxy(toaDoKhungX + 0 * (TABLE_COLUMN_WIDTH + 1)+ (TABLE_COLUMN_WIDTH - 3)/2,  toaDoKhungY + (dem % SO_DONG_MOT_TRANG) * 2+ 3);
					SetBGColor(BG_BODY);
					SetColor(BLACK);	
					cout << dem + 1;
					
					gotoxy(toaDoKhungX + 1 * (TABLE_COLUMN_WIDTH + 1)+ (TABLE_COLUMN_WIDTH - p->NHANVIEN.MANV.length())/2, toaDoKhungY+ (dem % SO_DONG_MOT_TRANG) * 2 + 3);
					SetBGColor(BG_BODY);
					SetColor(BLACK);
					cout << p->NHANVIEN.MANV;
					
					gotoxy(toaDoKhungX + 2 * (TABLE_COLUMN_WIDTH + 1)+ (TABLE_COLUMN_WIDTH - p->NHANVIEN.HO.length())/2, toaDoKhungY+ (dem % SO_DONG_MOT_TRANG) * 2+ 3);
					SetBGColor(BG_BODY);
					SetColor(BLACK);
					cout << p->NHANVIEN.HO;
					
					gotoxy(toaDoKhungX + 3 * (TABLE_COLUMN_WIDTH + 1)+ (TABLE_COLUMN_WIDTH - p->NHANVIEN.TEN.length())/2, toaDoKhungY + (dem % SO_DONG_MOT_TRANG) * 2+ 3);
					SetBGColor(BG_BODY);
					SetColor(BLACK);
					cout << p->NHANVIEN.TEN;
					
					gotoxy(toaDoKhungX + 4 * (TABLE_COLUMN_WIDTH + 1)+ (TABLE_COLUMN_WIDTH - 3)/2,  toaDoKhungY + (dem % SO_DONG_MOT_TRANG) * 2+ 3);
					SetBGColor(BG_BODY);
					SetColor(BLACK);
					if(p->NHANVIEN.PHAI == true) cout << "Nam";
					else cout << "Nu";
			}
				
			dem++;
			p = p->RIGHT;
		}else break;
		
	}while(true);

}

// Khung in danh sach nhanh vien
void khungNhanVien(int soCot,int soHang,int  toaDoKhungX,int toaDoKhungY){
	veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
	SetBGColor(BG_BODY);
	SetColor(BG_HEADER);
	string tenBang = "BANG THONG TIN NHAN VIEN";
	gotoxy(TOADOX + WIDTH_MENU_BAR+(SCREEN_WIDTH - WIDTH_MENU_BAR - tenBang.length())/ 2, TOADOY + 5);
	cout << tenBang;
	SetBGColor(BG_BODY);
	SetColor(TEXT_COLOR);
	veKhungDanhSach(soCot, soHang, toaDoKhungX, toaDoKhungY );	
	//footer	
	SetBGColor(BG_BODY);
	SetColor(BG_HEADER);
	string s = "ESC: Thoat    INSERT: Them    DELETE: Xoa    F5: Sua    F2: Danh sach hoa don    F9: Tim kiem    <-Trang truoc    Trang sau->";
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
			gotoxy(toaDoKhungX + i * (TABLE_COLUMN_WIDTH + 1)+ (TABLE_COLUMN_WIDTH - tenCotBangNhanVien[i].length())/2, toaDoKhungY + 1);
			cout << tenCotBangNhanVien[i];
	}

}

int timKiemNhanVien(NHANVIENTREE root, string &maNhanVien, int toaDoX, int toaDoY, int chieuDai, int chieuRong){
	formTimKiem("Nhap vao ma nhan vien",toaDoX, toaDoY, chieuDai, chieuRong);

	int c;
	do{
		c = nhapChuoiKiTuVaSoKhongKhoangTrang(maNhanVien, toaDoX + (chieuDai - WIDTH_TEXT)/2 ,toaDoY + 3, WIDTH_TEXT, BLACK, WHITE);
	}while(c != KEY_ENTER && c != KEY_ESC);
	// thoat khong tim kiem
	if(c == KEY_ESC) 
		return -2;
	int viTriNhanVien = timViTriNhanVien(root, maNhanVien);
	return  viTriNhanVien;
	
}

void formNhanVien(NHANVIENTREE &root, DanhSachVatTu &dsVatTu){
	int ketQua;
	int c;
	int soNhanVien = demSoNhanVien(root);
	int tongTrang =  soNhanVien / SO_DONG_MOT_TRANG;
	if(soNhanVien % SO_DONG_MOT_TRANG != 0) tongTrang++;
	if(tongTrang == 0) tongTrang = 1;
	int viTri = 0;
	int trang  = 1;
	NHANVIENTREE p;
	int soCot = 5;
	int viTriNhanVienSauKhiThem = 0;
	int soHang = SO_DONG_MOT_TRANG + 1;
	int toaDoKhungX = TOADOX + WIDTH_MENU_BAR + (SCREEN_WIDTH - WIDTH_MENU_BAR - (soCot * TABLE_COLUMN_WIDTH + soCot + 1))/2;
	int toaDoKhungY = TOADOY + 3 + (SCREEN_HEIGTH - 3 - soHang * 2)/ 2;
	khungNhanVien(soCot, soHang, toaDoKhungX, toaDoKhungY );
	do{
		
		p = root;
		in1TrangNhanVien(p, trang, tongTrang, toaDoKhungX, toaDoKhungY);
		gotoxy(TOADOX + WIDTH_MENU_BAR + (SCREEN_WIDTH - WIDTH_MENU_BAR) / 2, TOADOY + SCREEN_HEIGTH -5);
		SetBGColor(BG_BODY);
		cout << "\t\t\t\t\t\t";
		SetColor(BG_HEADER);
		gotoxy(TOADOX + WIDTH_MENU_BAR + (SCREEN_WIDTH - WIDTH_MENU_BAR) / 2, TOADOY + SCREEN_HEIGTH -5);
		cout << "Trang "  << trang << "/" << tongTrang;
	
	
		
		do{
			gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
			cout << "->";
			c = keyPressed();
			// di chuyen con tro di xuong
			if(c == KEY_DOWN){
				//neu la dong cuoi cung
				//chua la trang cuoi
				//so nhan vien lon hon 0
				if(viTri == SO_DONG_MOT_TRANG - 1 && trang < tongTrang && soNhanVien > 0){
					trang++;
					//
					gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
					cout << "  ";
					viTri = 0;
					break;
				}
				//neu chua la dong cuoi
				//chua la nhan vien cuoi
				//va nhan vien lon hon 0
				if(viTri < SO_DONG_MOT_TRANG - 1 && (viTri + ((trang - 1) * SO_DONG_MOT_TRANG) )< soNhanVien - 1 && soNhanVien > 0){
					//
					gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
					cout << "  ";
					viTri++;
				}	
			}
			// di chuyen con tro di len
			if(c == KEY_UP){
				// neu la vi tri dau tien
				// khong phai la trang dau
				// so nhan vien lon hon 0
				if(viTri == 0 && trang > 1 && soNhanVien > 0){
					trang--;
					//
					gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
					cout << "  ";	
					viTri = SO_DONG_MOT_TRANG - 1;
					break;
				}
				// neu chua la vi tri dau tien  va so nhan vien lon hon khong 0
				if(viTri > 0 && soNhanVien > 0){
					//
					gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
					cout << "  ";
					viTri--;
				}
			}
			// them moi nhan vien
			if(c == KEY_INSERT){
				do{
					
					veHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BG_BODY);
					c = nhapNhanVien(root, viTriNhanVienSauKhiThem);
					if(c != -1){
						soNhanVien = demSoNhanVien(root);
						// tinh lai tong trang
						tongTrang =  soNhanVien / SO_DONG_MOT_TRANG;
						if(soNhanVien % SO_DONG_MOT_TRANG != 0) tongTrang++;
						// tim trang ma nhan vien moi duoc them vao
						trang = viTriNhanVienSauKhiThem / SO_DONG_MOT_TRANG;
						//if(viTriNhanVienSauKhiThem % SO_DONG_MOT_TRANG != 0)
						 trang++;
						//if(viTriNhanVienSauKhiThem == 0) trang = 1;
						
						gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
						cout << "  ";
						// tim vi tri trong trang cua nhan vien
						//
						viTri = viTriNhanVienSauKhiThem % SO_DONG_MOT_TRANG; 
					
					}
					
				}while(c != -1);
				
				khungNhanVien(soCot, soHang, toaDoKhungX, toaDoKhungY );
				break;
			}
			// cap nhat thong tin cua nhan vien
			if(c == KEY_F5){
				NHANVIENTREE p = timKiemNodeThuN(root, (trang - 1) * SO_DONG_MOT_TRANG+viTri);
				if(p != NULL){
					NhanVien nv = p->NHANVIEN;
					ketQua = capNhapNhanVien(p->NHANVIEN);
					if(ketQua == -1) p->NHANVIEN = nv;
					SetBGColor(BG_BODY);
					SetColor(BG_HEADER);
					khungNhanVien(soCot, soHang, toaDoKhungX, toaDoKhungY );
					break;
				}
			}
			// xoa nhan vien
			if(c == KEY_DELETE){
				NHANVIENTREE p = timKiemNodeThuN(root, (trang - 1) * SO_DONG_MOT_TRANG+viTri);
				if(p != NULL){
					if(p->NHANVIEN.DS_HOADON != NULL){
						thongBao("Nhan vien da lap hoa don", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
						SetBGColor(BG_BODY);
						SetColor(BG_HEADER);
						khungNhanVien(soCot, soHang, toaDoKhungX, toaDoKhungY );
						break;
					}else{
						ketQua = hopThoaiLuaChon("BAN CO MUON XOA NHAN VIEN "+ p->NHANVIEN.MANV + " KHONG?", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, 50,5 );
						if(ketQua == 1){
							
							xoaNodeCuaCay(root, p->NHANVIEN.MANV);
							
							thongBao("Xoa thanh cong", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
							SetBGColor(BG_BODY);
							SetColor(BG_HEADER);
							soNhanVien--;if(soNhanVien  < 0) soNhanVien = 0; //demSoNhanVien(root);
							tongTrang =  soNhanVien / SO_DONG_MOT_TRANG;
							if(soNhanVien % SO_DONG_MOT_TRANG != 0) tongTrang++;
		
							// neu la vi tri dau tien
							// chua phai la trang dau tien				
							if(viTri == 0 && trang > 1){
							 	trang--;
								//
								gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
								cout << "  "; 
								viTri = SO_DONG_MOT_TRANG - 1;
							}
							
							//				
							if((trang - 1) * SO_DONG_MOT_TRANG + viTri >= soNhanVien && soNhanVien > 0){
								//
								gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
								cout << "  ";
								viTri = soNhanVien % SO_DONG_MOT_TRANG - 1;
							} 
							if(soNhanVien == 0) trang = tongTrang = 1;
							khungNhanVien(soCot, soHang, toaDoKhungX, toaDoKhungY );
							
						
						}else{
							khungNhanVien(soCot, soHang, toaDoKhungX, toaDoKhungY );
						}
							break;
					}
				}
			}
			// xem danh sach hoa don da lap cua nhan vien
			if(c == KEY_F2){
				NHANVIENTREE p = timKiemNodeThuN(root, (trang - 1) * SO_DONG_MOT_TRANG + viTri);
				danhSachHoaDonDaLapCuaNhanVien(dsVatTu, p->NHANVIEN);
				khungNhanVien(soCot, soHang, toaDoKhungX, toaDoKhungY );			
				break;
				
			}
			// tim kiem nhan vien
			if(c == KEY_F9){
				string maNV = "";
				int viTriNhanVien = timKiemNhanVien(root, maNV, TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
				while(viTriNhanVien != -2){
					if(viTriNhanVien == -1){
						thongBao("Ma nhan vien khong ton tai", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
						viTriNhanVien = timKiemNhanVien(root, maNV,TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5);
					}else{
						trang = viTriNhanVien / SO_DONG_MOT_TRANG;
//						if(viTriNhanVien % SO_DONG_MOT_TRANG != 0)
						 trang++;
//						if(viTriNhanVien == 0) trang = 1;
						gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
						cout << "  ";
						viTri = viTriNhanVien % SO_DONG_MOT_TRANG; 
						break;
					}
				}
				khungNhanVien(soCot, soHang, toaDoKhungX, toaDoKhungY );
				break;
				
			}
			
		}while(c != KEY_ESC && c!= KEY_RIGHT && c != KEY_LEFT);
		
	
		if(c == KEY_RIGHT){
		
			if(trang < tongTrang ) trang++;
			if(trang == tongTrang && (trang - 1) * SO_DONG_MOT_TRANG + viTri >= soNhanVien){
				gotoxy(toaDoKhungX -3, toaDoKhungY + 2+ viTri * 2 + 1);
				cout << "  ";
				if(soNhanVien > 0)
				viTri = (soNhanVien - 1) % SO_DONG_MOT_TRANG;
				else viTri = 0;
			}	
			
		}
		if(c == KEY_LEFT){
			
			if(trang > 1 ) trang--;	
		}
		
	
	
	}while(c!= KEY_ESC);
	

}


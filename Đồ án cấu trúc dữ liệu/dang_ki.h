#pragma once
#include "sinh_vien.h"

// ========================================================= DK LỚP TÍN CHỈ =========================================== //
void Duyet_Cay_Tim_NienKhoa_HocKi(tree p, string nien_khoa, int hocki, node_Lop_tin_chi* ds[], int &n)  // duyet de cho sinh vien dang ki lop tin chi
{
	if (p == NULL) // duyệt hết cây, đến trị trí cuối cùng thì thoát
	{
		return; // Thoát
	}
	if (p->data.nien_khoa == nien_khoa && p->data.hoc_ki == hocki)
	{
		ds[n] = p;
		n++;
	}

	Duyet_Cay_Tim_NienKhoa_HocKi(p->pleft, nien_khoa, hocki, ds, n);
	Duyet_Cay_Tim_NienKhoa_HocKi(p->pright, nien_khoa, hocki, ds, n);
}


//=================================== Giao diện đăng kí lớp tín chỉ =====================================//
string getTenMonHoc(ds_mh dsmon_hoc, string maMH)
{
	for (int i = 0; i < dsmon_hoc.sl; i++)
	{
		if (maMH == dsmon_hoc.ds[i]->ma_mh)
		{
			return dsmon_hoc.ds[i]->ten_mh;
		}
	}
}

void CheckMonHocDaDK(node_Lop_tin_chi* a[], string maSV, int n, string maMH, bool &kt) //check sinh viên đó đã đăng kí môn này hay chưa
{
	if (a == NULL)
	{
		kt = true;
	}

	for (int i = 0; i < n; i++)
	{
		if (a[i]->data.ma_mh == maMH)
		{
			for (dang_ki* k = a[i]->data.ds_dk.phead; k != NULL; k = k->pnext)
			{
				if (k->ma_sv == maSV)
				{
					kt = false; // sinh viên đã đăng kí môn học này
				}
			}
		}
	}
}

bool CheckLopSVDaDK(tree t, string maSV, int maLopTC) // kiểm tra xem lớp tín chỉ đó sinh viên đã đăng kí hay chưa
{
	if (t == NULL)
	{
		return true;
	}

	if (t->data.malop_tc == maLopTC)
	{
		for (dang_ki* k = t->data.ds_dk.phead; k != NULL; k = k->pnext)
		{
			if (k->ma_sv == maSV)
			{
				return false;  // có return false
			}
		}
	}

	if (maLopTC < t->data.malop_tc)
		CheckLopSVDaDK(t->pleft, maSV, maLopTC);

	if (maLopTC >t->data.malop_tc)
		CheckLopSVDaDK(t->pright, maSV, maLopTC);
}

// ============================= || Xuất thông tin các môn mà sinh viên đó đã đăng kí rồi  ||======================== //


//===== Phần giao diện =========//
void GiaoDienInLop_da_dang_ki(int toadoX, int toadoY, int n)
{
	//Logo(20, 1);

	int chieucao = 3 + 2 * n;
	int chieudai = 100 -10;
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, toadoY);
		if (i == toadoX)
			cout << (char)218;
		else if (i == chieudai + toadoX)
			cout << (char)191;
		else
			cout << (char)196;
	}
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, chieucao + toadoY);
		if (i == toadoX)
			cout << (char)192;
		else if (i == chieudai + toadoX)
			cout << (char)217;
		else
			cout << char(196);
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(toadoX, i);
		cout << (char)179;
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(chieudai + toadoX, i);
		cout << (char)179;
	}

	// gach xuong
	for (int i = toadoX + 1; i < chieudai + toadoX; i++)
	{
		if (i == toadoX + 10 || i == toadoX + 30 || i == toadoX + 70 || i == toadoX + 80 || i == toadoX + 90)
		{
			for (int j = toadoY; j < chieucao + toadoY + 1; j++)
			{
				gotoXY(i, j);
				if (j == toadoY)
					cout << char(194);
				else if (j == chieucao + toadoY)
					cout << char(193);
				else
					cout << (char)179;
			}
		}
	}

	// gach ngang
	for (int j = 3; j < chieucao; j = j + 2)
	{
		for (int i = toadoX; i <= chieudai + toadoX; i++)
		{
			gotoXY(i, toadoY + j);
			if (i == toadoX)
				cout << (char)195;
			else if (i == chieudai + toadoX)
				cout << (char)180;
			else if (i == toadoX + 10 || i == toadoX + 30 || i == toadoX + 70 || i == toadoX + 80 || i == toadoX + 90)
				cout << (char)197;
			else
				cout << (char)196;
		}
	}

	gotoXY(toadoX + 1, toadoY + 1);
	cout << CanDeuChuoi("STT", 9);
	gotoXY(toadoX + 16, toadoY + 1);
	cout << CanDeuChuoi("MaLopTC", 1);
	gotoXY(toadoX + 31, toadoY + 1);
	cout << CanDeuChuoi("MaMonHoc", 39);
	gotoXY(toadoX + 71, toadoY + 1);
	cout << CanDeuChuoi("HocKi", 9);
	gotoXY(toadoX + 81, toadoY + 1);
	cout << CanDeuChuoi("Nhom", 9);
	
}

void Xuat_Ds_Mon_Da_DK_Cua_SV_DO(node_Lop_tin_chi* ds[], int n, int toadoX, int toadoY)   // Xuất ds môn học sinh viên đó đã đăng kí (Phần thông tin)
{

	gotoXY(80, 25);
	cout << "DANH SACH MON HOC MA BAN DA DANG KI  " << endl;

	int dem = 0;
	for (int i = 0; i < n; i++) // duyet mang moi cap nhat
	{
				gotoXY(toadoX + 1-1, toadoY + 4 + (dem * 2) -10);
				cout << i + 1;
				gotoXY(toadoX + 11 +3, toadoY + 4 + (dem * 2) - 10);
				cout << ds[i]->data.malop_tc;
				gotoXY(toadoX + 31 +10, toadoY + 4 + (dem * 2) - 10);
				cout << ds[i]->data.ma_mh;
				gotoXY(toadoX + 71 - 1, toadoY + 4 + (dem * 2) - 10);
				cout << ds[i]->data.hoc_ki;
				gotoXY(toadoX + 81 - 1, toadoY + 4 + (dem * 2) - 10);
				cout << ds[i]->data.nhom;
				dem++;
	}
	GiaoDienInLop_da_dang_ki(toadoX -5, toadoY-10, n);
	
}


node_sinh_vien* getSV(ds_sv DS_SV, string maSV) // duyệt sinh viên có mã sinh viên
{
	for (node_sinh_vien* k = DS_SV.phead; k != NULL; k = k->pnext)
	{
		if (maSV == k->data.ma_sv)
		{
			return k;
		}
	}
	return NULL;
}


// ============================================== GIAO DIỆN IN DANH SÁCH CÁC LỚP  CÓ THỂ ĐĂNG KÍ=======================================//

void GiaoDienInLopDK(int toadoX, int toadoY, int n)  // giao diện kẻ bảng
{
	Logo(20, 1);

	int chieucao = 3 + 2 * n;
	int chieudai = 100;
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, toadoY);
		if (i == toadoX)
			cout << (char)218;
		else if (i == chieudai + toadoX)
			cout << (char)191;
		else
			cout << (char)196;
	}
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, chieucao + toadoY);
		if (i == toadoX)
			cout << (char)192;
		else if (i == chieudai + toadoX)
			cout << (char)217;
		else
			cout << char(196);
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(toadoX, i);
		cout << (char)179;
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(chieudai + toadoX, i);
		cout << (char)179;
	}

	// gach xuong
	for (int i = toadoX + 1; i < chieudai + toadoX; i++)
	{
		if (i == toadoX + 10 || i == toadoX + 30 || i == toadoX + 70 || i == toadoX + 80 || i == toadoX + 90)
		{
			for (int j = toadoY; j < chieucao + toadoY + 1; j++)
			{
				gotoXY(i, j);
				if (j == toadoY)
					cout << char(194);
				else if (j == chieucao + toadoY)
					cout << char(193);
				else
					cout << (char)179;
			}
		}
	}

	// gach ngang
	for (int j = 3; j < chieucao; j = j + 2)
	{
		for (int i = toadoX; i <= chieudai + toadoX; i++)
		{
			gotoXY(i, toadoY + j);
			if (i == toadoX)
				cout << (char)195;
			else if (i == chieudai + toadoX)
				cout << (char)180;
			else if (i == toadoX + 10 || i == toadoX + 30 || i == toadoX + 70 || i == toadoX + 80 || i == toadoX + 90)
				cout << (char)197;
			else
				cout << (char)196;
		}
	}

	gotoXY(toadoX + 1, toadoY + 1);
	cout << CanDeuChuoi("STT", 9);
	gotoXY(toadoX + 11+ 5, toadoY + 1);
	cout << CanDeuChuoi("Ma LopTC", 1);
	gotoXY(toadoX + 31, toadoY + 1);
	cout << CanDeuChuoi("Ma Mon Hoc", 39);
	gotoXY(toadoX + 71 , toadoY + 1);
	cout << CanDeuChuoi("Nhom", 9);
	gotoXY(toadoX + 81, toadoY + 1);
	cout << CanDeuChuoi("So luong", 9);
	gotoXY(toadoX + 91, toadoY + 1);
	cout << CanDeuChuoi("Con Lai", 9);
}



int XuatDSLTCDK(node_Lop_tin_chi* a[], node_Lop_tin_chi* b[], ds_mh dsmon_hoc, int n, int sl_da_dk, int toadoX, int toadoY, string maSV, bool &kt)  // Xuất ds lớptc có thể đăng kí
{
	Logo(20, 1);
	
	int dem = 0;
	int chose = 0;


	gotoXY(80, 10);
	cout << "DANH SACH CAC MON CO THE DANG KI" << endl;

	for (int i = 0; i < n; i++)                      //   Hiển thị thông tin
	{
		gotoXY(toadoX + 1-1, toadoY + 4 + (dem * 2) -5);
		cout << i + 1;
		gotoXY(toadoX + 11 +4, toadoY + 4 + (dem * 2) -5);
		cout << a[i]->data.malop_tc;
		gotoXY(toadoX + 31+ 10, toadoY + 4 + (dem * 2) -5);
		cout << a[i]->data.ma_mh;
		gotoXY(toadoX + 71 -2, toadoY + 4 + (dem * 2) -5);
		cout << a[i]->data.nhom;
		gotoXY(toadoX + 81 -1, toadoY + 4 + (dem * 2) -5);
		cout << a[i]->data.so_svmax;
		gotoXY(toadoX + 91 -1, toadoY + 4 + (dem * 2) -5);
		cout << a[i]->data.so_svmax - a[i]->data.ds_dk.sl;

		dem++;
	}

	GiaoDienInLopDK(toadoX -5, toadoY -5, dem);  // kẻ bảng

	gotoXY(130, 10);
	cout << "0.De thoat";

	ShowCur(1);
	gotoXY(10, 10);
	cout << "1.Them" ;

	gotoXY(10, 11);
	cout << "2.Huy";

	gotoXY(10, 12);
	cout << "Nhap lua chon: ";
	int lua_chon ;
	cin >> lua_chon;
	
	switch (lua_chon)
	{
	case 1:
	{
			  kt = true;
			  break;
	}
	case 2:
	{
			  kt = false;
			  break;
	}
	default:
		break;
	}
	gotoXY(10, 13);
	cout << "Chon Lop Bang STT:";
	cin >> chose;
	ShowCur(0);

	if (chose == 0)
	{
		return 0;
	}
	else 
	{
		if (kt == true && chose > n)
			return -1;
		else if (kt == false && chose > sl_da_dk)
			return  -1;
	}

	//
	if (kt == true)  // đăng kí
	{
		return a[chose - 1]->data.malop_tc;  // a = ds // dang lop co the dang ki
	}
	else  // hủy đăng kí
	{
		return b[chose - 1]->data.malop_tc;  // b : ds đã đăng kí
	}
}

// ======== Hàm duyệt ds sv các môn mà sinh viên đã đăng kí rồi ===;
void Duyet_tim_ds_da_dang_ki_do(node_Lop_tin_chi* ds[], node_Lop_tin_chi* b[], int n, int &sl_da_dk, string maSV )   // Xuất ds lớp mà sinh đó đã đăng kí sinh viên đó đã đăng kí (Phần thông tin)
{
	for (int i = 0; i < n; i++) // duyet mang moi cap nhat
	{
		for (dang_ki *k = ds[i]->data.ds_dk.phead; k != NULL; k = k->pnext)
		{
			if (maSV == k->ma_sv)
			{
				b[sl_da_dk] = ds[i];  // lấy con trỏ 
				sl_da_dk++;
			}
		}
		
	}
}



void DangKiLopTC(ds_sv DS_SV, ds_lop_tc &dslop_tc, ds_mh dsmon_hoc, int toadoX, int toadoY)
{
	Logo(20, 1);
	ShowCur(1);
	int hocki;
	string maSV, nien_khoa;
	node_sinh_vien* k;
	int toadoYTemp;
	do {
		toadoYTemp = toadoYMain;
		gotoXY(toadoXBox, toadoYTemp);
		cout << "Nhap Vao MaSV :";
		maSV = XuLyNhapchu();

		if (maSV == "0")
		{
			return;
		}

		k = getSV(DS_SV, maSV);  // check maSV co ton tai hay ko.
		if (k == NULL)
		{
			showNotifyMessageBox("Thong bao", "Ma sv ko ton tai!");
			system("cls");
		}
	} while (k == NULL);

	ShowCur(0);

	toadoYTemp += 2;

	gotoXY(toadoXBox + 5, toadoYTemp++);
	cout << "THONG TIN SINH VIEN";
	gotoXY(toadoXBox, toadoYTemp++);
	cout << "Ma Sinh Vien :" << maSV;
	gotoXY(toadoXBox, toadoYTemp++);
	cout << "Ho Va Ten Sinh Vien :" << k->data.ho + " " + k->data.ten;
	gotoXY(toadoXBox, toadoYTemp++);
	cout << "Phai :" << k->data.phai;
	gotoXY(toadoXBox, toadoYTemp++);
	cout << "SDT :" << k->data.sdt;
	gotoXY(toadoXBox, toadoYTemp++);
	cout << "Vui Long Kiem Tra Thong Tin !!!";
	getch();

	ShowCur(1);
	system("cls");
	toadoYTemp = toadoYMain;
	toadoYTemp = toadoYTemp + 2;
	Logo(20, 1);
	
	gotoXY(toadoXBox, toadoYTemp);
	cin.ignore();
	cout << "Nhap Vao Nien Khoa :";
	//nien_khoa = XuLyNhapchu();
	getline(cin, nien_khoa);

	if (nien_khoa == "0")
	{
		return;
	}
	gotoXY(toadoXBox, toadoYTemp+2);

	cout << "Nhap Vao Hoc Ki : ";
	cin >> hocki;
	

	gotoXY(80, 20);
	cout << "Hoc ki: 1 || 2 || 3";
	gotoXY(80, 21);
	cout << "NienKhoa > 2016";


	ShowCur(0);
	if (hocki == 0)
	{
		return;
	}

	while (true)
	{
		system("cls");
		node_Lop_tin_chi *ds[100]; // lớp có niên khóa học kì đổ vào ds[]
		node_Lop_tin_chi *b[100]; // ds lớp mà sinh viên đó [đã đăng kí]  dựa vào mảng ds[]

		int n = 0;
		int sl_da_dk = 0;

		bool kt;
		Duyet_Cay_Tim_NienKhoa_HocKi(dslop_tc.ds, nien_khoa, hocki, ds, n);   //  lấy ra dslớp có niên khóa và học kì nhập vào
		Duyet_tim_ds_da_dang_ki_do(ds, b, n, sl_da_dk, maSV);             // duyệt trong cái ds        => b

		if (n == 0)
		{
			showNotifyMessageBox("Thong bao", "Chua co lop nao de dang ki!");
			return;
		}
		Xuat_Ds_Mon_Da_DK_Cua_SV_DO(b, sl_da_dk, toadoX -5, toadoY + 20);// xuất ds môn học đã đăng kí của sinh viên đó từ b[] vói số lượng là sl_da_dk

		int maLTC = XuatDSLTCDK(ds,b, dsmon_hoc, n, sl_da_dk, toadoX -5, toadoY  , maSV, kt); // Show ra list môn học có thể đăng kí của sinh viên đó [duyệt ra all các lớp ds có niên khóa học kì]
		// Lấy mã lớp để đăng kí

		if (maLTC == 0)
		{
			return;
		}
		/*
		else if (maLTC == -1)
		{
			showNotifyMessageBox("Thong bao", "Invalib!");
			return;
		}*/

		if (kt == true)  // thực hiện đăng kí
		{
			for (int i = 0; i < n; i++)// add dk vào dsdk // duyet trong ds moi do vào dsdk
			{
				if (ds[i]->data.malop_tc == maLTC)
				{
					bool kt = true;
					// kiểm tra trong lớp này có sinh viên đó hay chưa
					CheckMonHocDaDK(ds, maSV, n, ds[i]->data.ma_mh, kt); // kiem tra sinh vien do da dang ki mon hoc do hay chua
					if (!kt)
					{
						showNotifyMessageBox("Thong bao", "Mon nay da dang ki trong ki nay!");
						return;
					}



					dang_ki* p = new dang_ki;
					p->pnext = NULL;
					p->ma_sv = maSV;
					p->diem = -1;

					if (ds[i]->data.ds_dk.phead == NULL) // them dk vao dsdk
					{
						ds[i]->data.ds_dk.phead = p;
					}
					else {												// ko phai
						dang_ki* temp = ds[i]->data.ds_dk.phead;
						while (true)
						{
							if (temp->pnext == NULL)
							{
								temp->pnext = p;
								break;
							}
							temp = temp->pnext;
						}
					}
					ds[i]->data.ds_dk.sl++;
					break;
				}
			}
			showNotifyMessageBox("Thong bao", "Da dang ki thanh cong!");
			//Xuat_Ds_Mon_Da_DK_Cua_SV_DO(ds, n, maSV, toadoX, toadoY + 20);
		}

		else // tiến hành hủy đăng kí
		{
			for (int i = 0; i < sl_da_dk; i++)
			{
				if (b[i]->data.malop_tc == maLTC)  // nếu có stt mà mã lớp bằng thì nó xóa thèn đó
				{
					dang_ki* tam = NULL;

					if (b[i]->data.ds_dk.phead->ma_sv == maSV) // xoa dau
					{
						tam = b[i]->data.ds_dk.phead;
						b[i]->data.ds_dk.phead = b[i]->data.ds_dk.phead->pnext;
						delete tam;
						break;
					}
					else
					{
						dang_ki* h = b[i]->data.ds_dk.phead;  // h chay theo k 
						for (dang_ki* k = b[i]->data.ds_dk.phead; k != NULL; k = k->pnext) // duyet het dslk neu trung
						{
							if (k->ma_sv == maSV)
							{
								h->pnext = k->pnext;
								delete k;
								break;
							}
							h = k;
						}
					}
					break;
				}
			}
		}
	}
}

// ================= IN DS SINH VIEN DA DANG KI LOP TIN CHI THEO :[ NIEN KHOA - HOC KI - NHOM - MA_MON_HOC] =====================
//string Duyet_node_dang_ki(ds_sv DS_SV, node_sinh_vien *h)
//{
//	for (node_sinh_vien *h = DS_SV.phead ; h != NULL; h = h->pnext)
//	{
//		return h->data.ma_sv ;
//	}
//}

void Duyet_Cay_Tim_NienKhoa_HocKi(tree p,  ds_dang_ki dsdang_ki, ds_sv DS_SV, string nien_khoa, int hocki, int nhom, string maMH) // duyet cay tim 4 fields
{
	Logo(20, 1);
	gotoXY(50, 9);
	cout << "THONG TIN SINH VIEN CO 4 fields LA ";
	if (p == NULL) // duyệt hết cây, đến trị trí cuối cùng thì thoát
	{
		return;
	}

	if (p->data.nien_khoa == nien_khoa && p->data.hoc_ki == hocki && p->data.ma_mh == maMH && p->data.nhom == nhom )
	{
		for (dang_ki *k = p->data.ds_dk.phead; k != NULL; k = k->pnext)
		{
				for (node_sinh_vien *h = DS_SV.phead; h != NULL; h = h->pnext)
				{
					int i = 0; 
					if (k->ma_sv == h->data.ma_sv)
					{
						cout << "Sinh vien thu " << i + 1 << " la " << endl;	

						cout << "\n\nHo :" << h->data.ho << endl;
						cout << "Ten :" << h->data.ten << endl;
						cout << "Phai :" << h->data.phai << endl;
						cout << "SDT :" << h->data.sdt << endl;
						cout << "MaLop :" << h->data.ma_lop << endl;
						cout << "MaSV :" << h->data.ma_sv << endl;
						cout << "NamNhapHoc :" << h->data.nam_nhap_hoc << endl;
						i++;
					}
				}
		} 
	}

	Duyet_Cay_Tim_NienKhoa_HocKi(p->pleft, dsdang_ki,  DS_SV, nien_khoa,  hocki,  nhom,  maMH);
	Duyet_Cay_Tim_NienKhoa_HocKi(p->pright,  dsdang_ki,  DS_SV, nien_khoa,  hocki,  nhom,  maMH);
	
}

void In_ds_theo_4Fields(ds_lop_tc ds, ds_dang_ki dsdang_ki, ds_sv DS_SV)
{
	Logo(20, 1);
	string nien_khoa;
	string maMH;
	int hocki;  
	int nhom;
	
	gotoXY(50, 9);
	cout << "NHAP THONG TIN 4 fields CAN XUAT LA";
	gotoXY(20, 10);
	cout << "Nhap nien_khoa: "; 
	nien_khoa = XuLyNhapchu();

	gotoXY(20, 11);
	cout << "Nhap Hoc Ki: ";
	hocki = XuLyNhapSo();

	gotoXY(20, 12);
	cout << "Nhap nhom: ";
	nhom = XuLyNhapSo();

	gotoXY(20, 13);
	cout << "Nhap maMH: ";
	maMH = XuLyNhapchu();

	system("cls"); // xóa màn hình nhập vào
	Duyet_Cay_Tim_NienKhoa_HocKi(ds.ds, dsdang_ki, DS_SV, nien_khoa, hocki, nhom, maMH);

	system("pause");
}


// ===================================== NHAP DIEM ========================================//

void getDSLTC(tree t, dang_ki* a[],int &n ,int HK, int nhom, string nienKhoa, string maMonHoc) // nhập 4 trường
{
	if (t == NULL)
	{
		return;
	}

	if (t->data.hoc_ki == HK && t->data.nhom == nhom && t->data.nien_khoa == nienKhoa && t->data.ma_mh == maMonHoc)
	{
		for (dang_ki* k = t->data.ds_dk.phead; k != NULL; k = k->pnext) // node sv đăng kí trong cái list đăng kí đổ vào mảng con trỏ a quản lí
		{
			a[n++] = k; // đổ node đăng kí vào mảng con trỏ a để quản lí
		}
	}
	getDSLTC( t->pleft,a,  n,  HK,  nhom, nienKhoa,  maMonHoc);
	getDSLTC(t->pright, a, n, HK, nhom, nienKhoa, maMonHoc);
	
	

}
bool XuLyNhapDiem(float& n, int toadoX, int& toadoY)
{
	int toadoXtam;
	string x = to_string(n);
	if (n == -1)
	{
		x = "";
	}
	else {
		x = x.substr(0, 4);
	}
	char c;
	while (true)
	{
		c = getch();
		if (((c >= 48 && c <= 57) || c == 46) && x.length() < 4 && whereX() < toadoX + 10)// nếu là số thì
		{
			if (x.length() == 1)
			{
				if ((x == "1" && c == 48) || c == 46)
				{
					x.insert(x.begin() + (whereX() - toadoX), c);
					if ((whereX() - toadoX) < x.length() - 1)
					{
						toadoXtam = whereX() + 1;
						gotoXY(toadoX, whereY());
						cout << "  ";
						gotoXY(toadoX, whereY());
						cout << x;
						gotoXY(toadoXtam, whereY());
					}
					else
						cout << c;
				}
			}
			else {
				x.insert(x.begin() + (whereX() - toadoX), c);
				if ((whereX() - toadoX) < x.length() - 1)
				{
					toadoXtam = whereX() + 1;
					gotoXY(toadoX, whereY());
					cout << "     ";
					gotoXY(toadoX, whereY());
					cout << x;
					gotoXY(toadoXtam, whereY());
				}
				else
					cout << c;
			}

		}
		else if (c == 8 && whereX() > toadoX)
		{
			x.erase(x.begin() + x.length() - 1);
			cout << "\b";
			cout << " ";
			cout << "\b";

		}
		else if (c == 13 && x.length() > 0)// nếu là phím enter
		{
			toadoY = toadoY + 2;
			n = atof(x.c_str());
			gotoXY(1, 1);
			cout << n;
			break;
		}
		else if (c == -32)
		{
			c = getch();
			if (c == 80)
			{
				if (x.empty())
				{
					n = 0;
				}
				else
				{
					n = atof(x.c_str());
				}
				toadoY = toadoY + 2;
				break;
			}
			else if (c == 72)
			{
				if (x.empty())
				{
					n = 0;
				}
				else
				{
					n = atof(x.c_str());
				}
				toadoY = toadoY - 2;
				break;
			}
		}
		else if (c == 27 && x.length() > 0)// nếu là phím enter
		{
			n = atof(x.c_str());
			return false;
		}
	}
	return true;
}
void GiaoDienNhapDiem(int toadoX, int toadoY, int n) // vẽ giao diện nhập điểm
{
	int chieucao = 3 + 2 * n;
	int chieudai = 100;
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, toadoY);
		if (i == toadoX)
			cout << (char)218;
		else if (i == chieudai + toadoX)
			cout << (char)191;
		else
			cout << (char)196;
	}
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, chieucao + toadoY);
		if (i == toadoX)
			cout << (char)192;
		else if (i == chieudai + toadoX)
			cout << (char)217;
		else
			cout << char(196);
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(toadoX, i);
		cout << (char)179;
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(chieudai + toadoX, i);
		cout << (char)179;
	}


	// gach xuong
	for (int i = toadoX + 1; i < chieudai + toadoX; i++)
	{
		if (i == toadoX + 10 || i == toadoX + 40 || i == toadoX + 70 || i == toadoX + 90)
		{
			for (int j = toadoY; j < chieucao + toadoY + 1; j++)
			{
				gotoXY(i, j);
				if (j == toadoY)
					cout << char(194);
				else if (j == chieucao + toadoY)
					cout << char(193);
				else
					cout << (char)179;
			}
		}
	}


	// gach ngang
	for (int j = 3; j < chieucao; j = j + 2)
	{
		for (int i = toadoX; i <= chieudai + toadoX; i++)
		{
			gotoXY(i, toadoY + j);
			if (i == toadoX)
				cout << (char)195;
			else if (i == chieudai + toadoX)
				cout << (char)180;
			else if (i == toadoX + 10 || i == toadoX + 40 || i == toadoX + 70 || i == toadoX + 90)
				cout << (char)197;
			else
				cout << (char)196;
		}
	}

	gotoXY(toadoX + 1, toadoY + 1);
	cout << CanDeuChuoi("STT", 9);
	gotoXY(toadoX + 11, toadoY + 1);
	cout << CanDeuChuoi("MSSV", 29);
	gotoXY(toadoX + 41, toadoY + 1);
	cout << CanDeuChuoi("Ho", 29);
	gotoXY(toadoX + 71, toadoY + 1);
	cout << CanDeuChuoi("Ten", 19);
	gotoXY(toadoX + 91, toadoY + 1);
	cout << CanDeuChuoi("Diem", 9);
} // 
void XuatDSDiem(ds_sv dsSV, dang_ki* a[], int n, int toadoX, int toadoY, int kt = 1)
{

	int dem = 0;
	for (int i = 0; i < n; i++)
	{
		node_sinh_vien *temp = getSV(dsSV, a[i]->ma_sv);
		gotoXY(toadoX + 1, toadoY + 4 + (dem * 2));
		cout << CanDeuChuoi(ChuyenSoSangString(i + 1), 9);
		gotoXY(toadoX + 11, toadoY + 4 + (dem * 2));
		cout << CanDeuChuoi(a[i]->ma_sv, 29);
		gotoXY(toadoX + 41, toadoY + 4 + (dem * 2));
		cout << CanDeuChuoi(temp->data.ho, 29);
		gotoXY(toadoX + 71, toadoY + 4 + (dem * 2));
		cout << CanDeuChuoi(temp->data.ten, 19);
		gotoXY(toadoX + 91, toadoY + 4 + (dem * 2));
		if (kt == 1)
		{
			if (a[i]->diem != -1)
				cout << showpoint << setprecision(3) << a[i]->diem;
		}
		else {
			if (a[i]->diem == -1)
			{
				cout << CanDeuChuoi("Chua Co", 9);
			}
			else
				cout << showpoint << setprecision(3) << a[i]->diem;;
		}
		dem++;
	}
	GiaoDienNhapDiem(toadoX, toadoY, n);
}
void RunNhapDiem(dang_ki* a[], int n, int toadoX, int toadoY)
{
	gotoXY(60, 10);
	cout << "NHAP DIEM CHO SINH VIEN";
	Logo(20, 1);
	gotoXY(80, 10);
	cout << "Nhan ESC: Ket Thuc Qua Trinh Nhap";
	int length = 0;
	ShowCur(1);
	int pointer1 = toadoY;
	while (true)
	{
		if (a[(pointer1 - toadoY) / 2]->diem == -1)
		{
			gotoXY(toadoX, pointer1);
		}
		else
			gotoXY(toadoX + 4, pointer1);
		if (!XuLyNhapDiem(a[(pointer1 - toadoY) / 2]->diem, toadoX, pointer1)) {
			return;
		}

		if (pointer1 < toadoY)
		{
			pointer1 = toadoY;
		}
		else if (pointer1 > toadoY + (2 * n) - 2)
		{
			pointer1 = toadoY + (2 * n) - 2;
		}
	}
	ShowCur(0);
}
void NhapDiem(ds_sv DS_SV, ds_lop_tc& dslop_tc, ds_mh dsmon_hoc, int toadoX, int toadoY)  // menu chính để nhập điểm
{
	Logo(20, 1);
	int HK, nhom;
	string maMonHoc;
	string nienKhoa;

	gotoXY(60, 10);
	cout << "NHAP DIEM CHO SINH VIEN";

	ShowCur(1);
	gotoXY(10,11);
	cout << "Nhap Nien Khoa: ";
	nienKhoa = XuLyNhapchu();
	if (nienKhoa == "")
	{
		ShowCur(0);
		return;
	}
	
	gotoXY(10, 12);
	cout << "Nhap Hoc Ki: ";
	HK = XuLyNhapSo();
	if (HK == -1)
	{
		ShowCur(0);
		return;
	}
	
	gotoXY(10, 13);
	cout << "Nhap Nhom: ";
	nhom = XuLyNhapSo();
	if (nhom == -1)
	{
		ShowCur(0);
		return;
	}

	gotoXY(10, 14);
	cout << "Nhap Ma Mon Hoc: ";
	maMonHoc = XuLyNhapchu();

	if (maMonHoc == "")
	{
		ShowCur(0);
		return;
	}
	ShowCur(0);

	int n = 0;
	dang_ki* a[2000];
	
	getDSLTC(dslop_tc.ds, a, n, HK, nhom, nienKhoa, maMonHoc);

	if (n == 0)
	{
		GiaoDienThongBao("Lop Tin Chi Khong Ton Tai");
		return;
	}
	system("cls");

	XuatDSDiem(DS_SV, a, n, 20, 15);
	RunNhapDiem(a, n, 20 + 91, 15 + 4);
}

// ========================Cau i : IN BANG DIEM MON HOC CUA 1 LOP TIN CHI ==================== //

void GiaoDienXuatDiem(int toadoX, int toadoY, int n) // vẽ giao diện nhập điểm
{
	int chieucao = 3 + 2 * n;
	int chieudai = 100;
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, toadoY);
		if (i == toadoX)
			cout << (char)218;
		else if (i == chieudai + toadoX)
			cout << (char)191;
		else
			cout << (char)196;
	}
	for (int i = toadoX; i <= chieudai + toadoX; i++)
	{
		gotoXY(i, chieucao + toadoY);
		if (i == toadoX)
			cout << (char)192;
		else if (i == chieudai + toadoX)
			cout << (char)217;
		else
			cout << char(196);
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(toadoX, i);
		cout << (char)179;
	}
	for (int i = toadoY + 1; i < chieucao + toadoY; i++)
	{
		gotoXY(chieudai + toadoX, i);
		cout << (char)179;
	}


	// gach xuong
	for (int i = toadoX + 1; i < chieudai + toadoX; i++)
	{
		if (i == toadoX + 10 || i == toadoX + 40 || i == toadoX + 70 || i == toadoX + 90)
		{
			for (int j = toadoY; j < chieucao + toadoY + 1; j++)
			{
				gotoXY(i, j);
				if (j == toadoY)
					cout << char(194);
				else if (j == chieucao + toadoY)
					cout << char(193);
				else
					cout << (char)179;
			}
		}
	}


	// gach ngang
	for (int j = 3; j < chieucao; j = j + 2)
	{
		for (int i = toadoX; i <= chieudai + toadoX; i++)
		{
			gotoXY(i, toadoY + j);
			if (i == toadoX)
				cout << (char)195;
			else if (i == chieudai + toadoX)
				cout << (char)180;
			else if (i == toadoX + 10 || i == toadoX + 40 || i == toadoX + 70 || i == toadoX + 90)
				cout << (char)197;
			else
				cout << (char)196;
		}
	}

	gotoXY(toadoX + 1, toadoY + 1);
	cout << CanDeuChuoi("STT", 9);
	gotoXY(toadoX + 11, toadoY + 1);
	cout << CanDeuChuoi("MSSV", 29);
	gotoXY(toadoX + 41, toadoY + 1);
	cout << CanDeuChuoi("Ho", 29);
	gotoXY(toadoX + 71, toadoY + 1);
	cout << CanDeuChuoi("Ten", 19);
	gotoXY(toadoX + 91, toadoY + 1);
	cout << CanDeuChuoi("Diem", 9);
} 

void XuatDS(ds_sv DS_SV, dang_ki* a[], int n, int toadoX, int toadoY)
{
	Logo(20, 1);
	int dem = 0;
	for (int i = 0; i < n; i++)
	{
		node_sinh_vien *temp = getSV(DS_SV, a[i]->ma_sv);  // getSV -> return ve node_sinh_vien

		gotoXY(toadoX + 1, toadoY + 4 + (dem * 2));
		cout << CanDeuChuoi(ChuyenSoSangString(i + 1), 9);
		gotoXY(toadoX + 11, toadoY + 4 + (dem * 2));
		cout << CanDeuChuoi(a[i]->ma_sv, 29);
		gotoXY(toadoX + 41, toadoY + 4 + (dem * 2));
		cout << CanDeuChuoi(temp->data.ho, 29);
		gotoXY(toadoX + 71, toadoY + 4 + (dem * 2));
		cout << CanDeuChuoi(temp->data.ten, 19);
		gotoXY(toadoX + 101, toadoY + 4 + (dem * 2));
		cout << a[i]->diem;
		/*if ( a[i]->ma_sv == temp->data.ma_sv )
		{
			gotoXY(toadoX + 91-4, toadoY + 4 + (dem * 2));
			
		}*/
		dem++;
	}

	


	GiaoDienXuatDiem(toadoX, toadoY, n);
	system("pause");
}

void In_bang_diem_cua_1_lop_tc (ds_sv DS_SV, ds_lop_tc& dslop_tc, ds_mh dsmon_hoc, int toadoX, int toadoY)  // menu chính để nhập điểm
{
	Logo(20, 1);
	int HK, nhom;
	string maMonHoc;
	string nienKhoa;

	gotoXY(60, 10);
	cout << "BANG DIEM MON HOC";

	ShowCur(1);
	gotoXY(10, 12);
	cout << "Nhap Nien Khoa: ";
	nienKhoa = XuLyNhapchu();
	if (nienKhoa == "")
	{
		ShowCur(0);
		return;
	}

	gotoXY(10, 13);
	cout << "Nhap Hoc Ki: ";
	HK = XuLyNhapSo();
	if (HK == -1)
	{
		ShowCur(0);
		return;
	}

	gotoXY(10, 14);
	cout << "Nhap Nhom: ";
	nhom = XuLyNhapSo();
	if (nhom == -1)
	{
		ShowCur(0);
		return;
	}

	gotoXY(10, 15);
	cout << "Nhap Ma Mon Hoc: ";
	maMonHoc = XuLyNhapchu();

	if (maMonHoc == "")
	{
		ShowCur(0);
		return;
	}
	ShowCur(0);

	int n = 0;
	dang_ki* a[2000];

	getDSLTC(dslop_tc.ds, a, n, HK, nhom, nienKhoa, maMonHoc);  // duyệt dslop_tc đổ vào mảng con trỏ a

	if (n == 0)
	{
		GiaoDienThongBao("Lop Tin Chi Khong Ton Tai");
		return;
	}
	system("cls");

	for (int j = 0; j < dsmon_hoc.sl; j++) // duyệt để tìm tên môn học
	{
		if (dsmon_hoc.ds[j]->ma_mh == dslop_tc.ds->data.ma_mh)
		{
			gotoXY(80, 11);
			cout << "MOC HOC: " << dsmon_hoc.ds[j]->ten_mh;
		}
		
		
	}

	gotoXY(20, 11);
	cout << "Nien khoa: " << nienKhoa;
	gotoXY(40, 11);
	cout << "Hoc Ki: " << HK;
	gotoXY(60, 11);
	cout << "Nhom: " << nhom;

	XuatDS(DS_SV, a, n, 20, 15 );
}



// ========================== Câu cuối: In thống kê bảng điểm trung bình khóa học

//void Get_ma_sv_co_2fields_malop_NamNhapHoc (ds_sv DS_SV ,string malop, int nam_nhap_hoc ,node_sinh_vien* ds[],int &sl)
//{
//	for (node_sinh_vien *k = DS_SV.phead; k != NULL; k = k->pnext)
//	{
//		if (k->data.ma_lop == malop && k->data.nam_nhap_hoc == nam_nhap_hoc)
//		{
//			ds[sl++] = k; 		
//		}
//	}	
//}
//
//void  Duyet_cay_1(tree t, ds_sv DS_SV, node_Lop_tin_chi* a[], int &soluong ) // chuyển cây sang mảng con trỏ
//{
//	if (t == NULL)
//	{
//		return;
//	}
//	
//	a[soluong++] = t; 
//
//	Duyet_cay_1(t->pleft, DS_SV,a,soluong);
//	Duyet_cay_1(t->pright, DS_SV, a, soluong);
//}
//
//void  Duyet_cay(tree t ,ds_sv DS_SV)
//{
//	
//	string malop;
//	cout << "Nhap malop: ";
//	malop = XuLyNhapchu();
//
//	int nam_nhap_hoc;
//	cout << "NamNhapHoc";
//	nam_nhap_hoc = XuLyNhapSo();
//
//	node_sinh_vien* ds[100];
//	node_Lop_tin_chi* a[100];
//	int sl = 0; // sl của ds có mã lớp & năm nhập học
//	int soluong = 0;
//	Get_ma_sv_co_2fields_malop_NamNhapHoc(DS_SV, malop, nam_nhap_hoc ,ds,sl);
//	Duyet_cay_1(t, DS_SV, a, soluong);
//
//	for (int i = 0; i < soluong; i++)
//	{
//		for (int j = 0; j < sl; j++)
//		{
//			int dem = 0;
//			int S = 0;
//			float DTB;
//			if (a[i]->data.ds_dk.phead->ma_sv == ds[j]->data.ma_sv)
//			{
//				S += a[i]->data.ds_dk.phead->diem;
//				dem++;
//			}
//			DTB = S / dem;
//			cout << DTB << endl;
//		}
//	}
//}
#pragma once
#include "lop_tc.h"



// ======================= HÀM THÊM XÓA SỬA SINH VIÊN =============================== //

// ===== SEARCH MASV =======//
int Search_masv(ds_sv DS_SV, string a)  // ham kt ma sv
{

	for (node_sinh_vien *k = DS_SV.phead; k != NULL; k = k->pnext)
	{
		if (k->data.ma_sv == a)
		{
			return true;
		}
	}
	return false;
}
// ===== THÊM SINH VIÊN ==== //

void Nhap_sinh_vien(ds_sv &DS_SV)
{
	string maLop;
	cout << "Nhap lop: ";
	getline(cin, maLop);
	if (maLop == "")
	{
		return;
	}

	while (true)
	{
		node_sinh_vien *p = new node_sinh_vien;
		cout << "\nNhap thong tin sinh vien :";
		

		do{
			cout << "\nNhap ma sv: ";
			getline(cin, p->data.ma_sv);

			if (p->data.ma_sv == "")
			{
				return;
			}

			if (Search_masv(DS_SV, p->data.ma_sv) == true)
			{
				
				cout << "\nMa sinh vien da ton tai !";
			}

		} while (Search_masv(DS_SV, p->data.ma_sv) == true);
		

		
		//p->data.ma_lop = maLop;

		cout << "Nhap ho: "; getline(cin, p->data.ho);
		cout << "Nhap ten: "; getline(cin, p->data.ten);
		cout << "Nhap phai: "; getline(cin, p->data.phai);

		cout << "Nhap nam nhap hoc: "; cin >> p->data.nam_nhap_hoc; // cin: ko nhận khoảng trắng , xuống dòng
		cin.ignore();
		cout << "Nhap sdt: "; getline(cin, p->data.sdt);

		p->pnext = NULL; // xac dinh dc then cuoi

		Them_sinh_vien(DS_SV, p);
	}

}

// ===== XUAT DS SINH VIEN ====//

void xuat_1_sv(node_sinh_vien *phead)
{
	int i = 1;
	cout << "\n======== DS SINH VIEN LA ======  " << endl;
	for (node_sinh_vien *k = phead; k != NULL; k = k->pnext)
	{
		cout << "\n------- sv " << i << " ---------" << endl;
		//-------- xuat -------
		cout << "\nMa sv: " << k->data.ma_sv << endl;
		cout << "Ma lop: " << k->data.ma_lop << endl;
		cout << "Ho Ten sv: " << k->data.ho << " " << k->data.ten << endl;
		cout << "Phai sv: " << k->data.phai << endl;
		cout << "SDT sv: " << k->data.sdt << endl;
		cout << "Nam nhap hoc sv: " << k->data.nam_nhap_hoc << endl;
		i++;
	}
}

void xuat_sv(ds_sv DS_SV) // xuat all sinh vien
{
	xuat_1_sv(DS_SV.phead);
	system("pause");
}


// ===== XÓA SINH VIÊN ==== //

void xoa_sv(ds_sv &DS_SV)
{
	Logo(20, 1);
	cin.ignore();
	string a;

	do{
		cout <<"\nNhap ma sinh vien can xoa: "; getline(cin, a);
		if ((Search_masv(DS_SV, a) == false))
		{
			cout << "\nMa sinh vien ko ton tai !";
		}
	} while ((Search_masv(DS_SV, a) == false));
	
	
	
	node_sinh_vien* tam = NULL;

	if (DS_SV.phead->data.ma_sv == a) // xoa dau
	{
		tam = DS_SV.phead;
		DS_SV.phead = DS_SV.phead->pnext;
		delete tam;
		return;
	}

	node_sinh_vien* h = DS_SV.phead;  // h chay theo k 
	for (node_sinh_vien* k = DS_SV.phead; k != NULL; k = k->pnext) // duyet het dslk neu trung
	{
		if (k->data.ma_sv == a)
		{
			h->pnext = k->pnext;
			delete k;
			return;
		}
		h = k;
	}

	cout << "Xoa thanh cong sinh vien";
	system("pause");
}

// ===== HIỆU CHỈNH SINH VIÊN ====// ok
bool Hieu_chinh_sv(ds_sv &DS_SV)
{
	string a;
	cout << "\nNhap ma so sinh vien can hieu chinh "; getline(cin, a);//can chuan hoa ma sinh vien
	for (node_sinh_vien *k = DS_SV.phead; k != NULL; k = k->pnext)
	{
		if (k->data.ma_sv == a)
		{
			cout << "\nNhap cac thong tin can hieu chinh cua sinh vien : " << a << " la " ;

			cout << "\nNhap ma lop: "; getline(cin, k->data.ma_lop);
			cout << "Nhap ho : "; getline(cin, k->data.ho);
			cout << "Nhap ten: "; getline(cin, k->data.ten);
			cout << "Nhap phai: "; getline(cin, k->data.phai);
			cout << "Nhap sdt: "; getline(cin, k->data.sdt);
			cout << "Nhap nam nhap hoc: "; cin >> k->data.nam_nhap_hoc;


			cout << "Hieu chinh sinh vien Thanh Cong!" << endl;
			return true;
		}
		else
		{
			cout << "Ma sinh vien ko ton tai!" << endl;
		}
	}
	return false;
}

// ============================== Clear list dslk vừa tạo để chứa các sinh viên của 1 lớp theo mã sinh viên ========================================================= //
void clearlist(ds_sv &plist)
{
	node_sinh_vien *p;
	while (plist.phead != NULL)
	{
		p = plist.phead;
		plist.phead = plist.phead->pnext;
		delete p;
	}
}

bool kt_ma_lop_co_ton_tai_hay_ko(ds_sv DS_SV, string a)
{
	for (node_sinh_vien* k = DS_SV.phead; k != NULL; k = k->pnext)
	{

		if (k->data.ma_lop == a)
		{
			return true;
		}
	}
	return false;
}

// ============================== In DSSV của 1 lớp (dựa vào mã lớp) theo thứ tự alphabet tăng dần của masv ========================================================= //

void Search_sv_co_malop(ds_sv DS_SV, ds_sv &ds_sv_theo_lop_moi)
{
	Logo(20, 1);
	string a;
	cin.ignore();

	do{

		cout << "Nhap ma lop can xuat DS_SV theo alph: "; getline(cin, a);
		if (kt_ma_lop_co_ton_tai_hay_ko( DS_SV, a) == false)
		{
			cout << " Malop ko ton tai !!! " ;
		}

	} while (kt_ma_lop_co_ton_tai_hay_ko(DS_SV, a) == false);
	
	for (node_sinh_vien *k = DS_SV.phead; k != NULL; k = k->pnext)
	{
		node_sinh_vien *n = new node_sinh_vien;

		// ngắt các kết nối đến con trỏ khác trong dslk DS_SV, lấy data và lấy địa chỉ khác

		n->data.ma_sv = k->data.ma_sv;
		n->data.ma_lop = k->data.ma_lop;
		n->data.ho = k->data.ho;
		n->data.ten = k->data.ten;
		n->data.sdt = k->data.sdt;
		n->data.nam_nhap_hoc = k->data.nam_nhap_hoc;
		n->data.phai = k->data.phai;

		n->pnext = NULL;

		if (n->data.ma_lop == a)
		{
			Them_sinh_vien(ds_sv_theo_lop_moi, n);
		}
	}
}
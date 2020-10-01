#pragma once
#include "load_file.h"

//========================================= HÀM THÊM MÔN HỌC =======================================================//

bool getMamh(ds_mh dsmon_hoc, string a)
{
	for (int i = 0; i < dsmon_hoc.sl; i++)
	{
		if (dsmon_hoc.ds[i]->ma_mh == a)
		{
			return false;
		}
	}
	return true;
}

void Them_mon_hoc(ds_mh &dsmon_hoc)
{
	mon_hoc *p = new mon_hoc; // cấp phát động , cho thèn p nên khi ko dùng tới phải xóa nó đi

	cout << "\n ===== NHAP THONG TIN MON HOC CAN THEM ===";
	cin.ignore();

	do{
		cout << "\nNhap ma mon hoc: "; getline(cin, p->ma_mh);
		if (p->ma_mh == "")
		{
			return;
		}
		if (getMamh(dsmon_hoc, p->ma_mh) == false)
		{
			cout << "Ma mon hoc da bi trung";
		}
		

	} while (getMamh(dsmon_hoc, p->ma_mh) == false);
	
	cout << "\nNhap ten mon hoc: "; getline(cin, p->ten_mh);
	
	cout << "Nhap so tin chi ly thuyet: "; cin >> p->so_tclt;
	cout << "Nhap so tin chi thuc hanh: "; cin >> p->so_tcth;


	dsmon_hoc.ds[dsmon_hoc.sl] = p; //  mảng có 5 phần tử thì truyển vào phần tử sau cùng , vì mảng start bằng số 0 a[0]  a[n-1]
	dsmon_hoc.sl++;
}

// ========================================= XUAT MON HOC ===========================================================//
void xuat_ds_mon_hoc(ds_mh dsmon_hoc)
{
	
	for (int i = 0; i < dsmon_hoc.sl; i++)
	{
		cout << "\t\t============= MON HOC " << i + 1 << " =============" << endl;

		cout << "Ten mon hoc: " << dsmon_hoc.ds[i]->ten_mh << endl;
		cout << "Ma mon hoc: " << dsmon_hoc.ds[i]->ma_mh << endl;
		cout << "So tin chi li thuyet: " << dsmon_hoc.ds[i]->so_tclt << endl;
		cout << "So tin chi thuc hanh: " << dsmon_hoc.ds[i]->so_tcth << endl;
	}

	
}

int kt_ma__mon_hoc(string a, ds_mh dsmon_hoc)
{
	for (int i = 0; i < dsmon_hoc.sl; i++)
	{
		//kt ma mon hoc a ton tai
		if (dsmon_hoc.ds[i]->ma_mh == a)
		{
			return i;
		}
	}
	return -1;
}

// ==================== XOA MON HOC ==========================//
void xoa_mon_hoc(ds_mh &dsmon_hoc)
{
	string a;
	cin.ignore();
	cout << "Nhap ma mon hoc can xoa: "; getline(cin, a);
	//chuan_hoa_chu(a);
	//=======================
	int vt = kt_ma__mon_hoc(a, dsmon_hoc);
	//======== xoa ========
	//dời
	if (vt < 0)
	{
		cout << "Mon hoc ko ton tai." << endl;
		system("pause");
	}
	else
	{
		for (int i = vt; i < dsmon_hoc.sl - 1; i++)
		{
			dsmon_hoc.ds[i]->ma_mh = dsmon_hoc.ds[i + 1]->ma_mh;
			dsmon_hoc.ds[i]->ten_mh = dsmon_hoc.ds[i + 1]->ten_mh;
			dsmon_hoc.ds[i]->so_tclt = dsmon_hoc.ds[i + 1]->so_tclt;
			dsmon_hoc.ds[i]->so_tcth = dsmon_hoc.ds[i + 1]->so_tcth;
		}
		//giảm sl [do xóa mon hoc nên phải giảm sl]
		dsmon_hoc.sl--;
		cout << "Da xoa mon hoc thanh cong !" << endl;
		system("pause");
	}
}

//============= HIEU CHINH MON HOC ===================//
void hieu_chinh_mon_hoc(ds_mh dsmon_hoc)
{
	string a;
	cin.ignore();

	cout << "\nNhap ma mon hoc can hieu chinh: ";
	getline(cin, a);

	//========= kiem tra ma vt =============
	int vt = kt_ma__mon_hoc(a, dsmon_hoc);
	if (vt < 0)
	{
		cout << "Ma khong ton tai!" << endl;
		system("pause");
	}
	else
	{
		//======== hieu chinh ==========

		getline(cin, dsmon_hoc.ds[vt]->ma_mh);
		cout << "\nNhap ten mon hoc: ";
		cin.ignore();
		getline(cin, dsmon_hoc.ds[vt]->ten_mh);

		cout << "\nNhap so tin chi li thuyet"; cin >> dsmon_hoc.ds[vt]->so_tclt;
		cout << "\nNhap so tin chi li thuyet"; cin >> dsmon_hoc.ds[vt]->so_tcth;


		/*chuan_hoa_chu(ds_vt.ds[vt]->ten_vt);
		chuan_hoa_chu(ds_vt.ds[vt]->don_vi_tinh);*/
		cout << "===================" << endl;
		cout << "\nDa thay doi thong tin mon hoc !" << endl;
		system("pause");
	}
}
// ==================================== IN DS MON HOC TANG DAN THEO TEN MON HOC ===========================================//
void hoan_vi_mon_hoc(mon_hoc *a, mon_hoc *b)
{
	mon_hoc *tam = new mon_hoc;

	tam->ma_mh = a->ma_mh;
	tam->ten_mh = a->ten_mh;
	tam->so_tclt = a->so_tclt;
	tam->so_tcth = a->so_tcth;

	//---------
	a->ma_mh = b->ma_mh;
	a->ten_mh = b->ten_mh;
	a->so_tclt = b->so_tclt;
	a->so_tcth = b->so_tcth;
	//------------
	b->ma_mh = tam->ma_mh;
	b->ten_mh = tam->ten_mh;
	b->so_tclt = tam->so_tclt;
	b->so_tcth = tam->so_tcth;

	delete tam;
}

void sap_xep_mon_hoc_tang_dan(ds_mh dsmon_hoc)
{

	for (int i = 0; i < dsmon_hoc.sl - 1; i++)
	{
		for (int j = i + 1; j < dsmon_hoc.sl; j++)
		{
			if (strcmp(dsmon_hoc.ds[i]->ten_mh.c_str(), dsmon_hoc.ds[j]->ten_mh.c_str())  > 0) // ham so sanh
			{
				hoan_vi_mon_hoc(dsmon_hoc.ds[i], dsmon_hoc.ds[j]);
			}
		}
	}
	xuat_ds_mon_hoc(dsmon_hoc);
	system("pause");
}



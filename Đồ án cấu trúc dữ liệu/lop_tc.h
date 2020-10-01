#pragma once
#include "mon_hoc.h"


// ============================================================= THÊM LỚP TÍN CHỈ =============================================//

//=== Dem sl lop tin chi == //

int DemSLloptc(tree t)
{
	if (t == NULL) return 0;
	else 
		return DemSLloptc(t->pright) + DemSLloptc(t->pleft) + 1;
}

bool GetMaMH(ds_mh dsmon_hoc , string maMh)  // kt mã môn học có tồn tại hay ko
{
	for (int i = 0; i < dsmon_hoc.sl; i++)
	{
		if (maMh == dsmon_hoc.ds[i]->ma_mh)
		{
			return true;
		}

	}
	return false;
}

void xuat_ds_ma_mon_hoc(ds_mh dsmon_hoc)
{
	int dem = 1;
	gotoXY(130, 11);
	cout << "DS Ma mon hoc: ";
	for (int i = 0; i < dsmon_hoc.sl; i++)
	{
		gotoXY(145, 10 + dem);
		cout  << dsmon_hoc.ds[i]->ma_mh << endl;
		dem++;
	}

}

void Nhap_lop_tin_chi(ds_lop_tc &dslop_tc, ds_mh dsmon_hoc)
{
	Logo(20, 1);
	lop_tin_chi a;

	
	
	gotoXY(80, 11); cout << " Ghi chu: 1. Nien khoa : >= 2019               ";
	gotoXY(80, 12); cout << "          2. Hoc ky    : 1, 2, 3(he)           ";
	gotoXY(80, 13); cout << "          3. MaxSV     : > 0 & <=200           ";
	gotoXY(80, 14); cout << "          4. MinSV     : > 0  & < maxsv        ";

	xuat_ds_ma_mon_hoc(dsmon_hoc);

	gotoXY(60,8);
	cout << "  THEM LOP TIN CHI ";

	do{
		gotoXY(20, 10);
		cout << "\nNhap ma mon hoc: ";
		
		a.ma_mh = XuLyNhapchu();

		if (GetMaMH(dsmon_hoc, a.ma_mh) == false)
		{
			gotoXY(25, 11);
			cout << "Ma mon hoc ko ton tai !" ;	
		}
	

	} while (GetMaMH(dsmon_hoc, a.ma_mh) == false);

	
	gotoXY(20, 11);
	cout << "\nNhap nien khoa: ";  
	a.nien_khoa= XuLyNhapchu();

	gotoXY(20, 12);
	cout << "\nNhap hoc ki: "; 
	a.hoc_ki= XuLyNhapSo();

	gotoXY(20, 13);
	cout << "\nNhap nhom: ";  
	a.nhom= XuLyNhapSo();

	gotoXY(20, 14);
	cout << "\nNhap so sv max: ";
	a.so_svmax= XuLyNhapSo();

	gotoXY(20, 15);
	cout << "\nNhap so sv min: ";  
	a.so_svmin= XuLyNhapSo();

	a.malop_tc = load_file();

	Insert_lop_tc(dslop_tc.ds, a);
}


//==================================== XÓA LỚP TÍN CHỈ ============================= ///
void  remove_case_3(tree &x , tree &y)   
{
	if (y->pleft != NULL) 
	{
		remove_case_3(x, y->pleft);
	}
	else 
	{
		x->data = y->data;
		x = y;
		y = y->pright;
	}
}

void  remove(int x, tree &t)  // x la m lop tin chi
{


	if (t == NULL)
	{
		cout << "Lop tin chi rong";
	}

	else
	{
		if (x < t->data.malop_tc)
		{
			remove(x, t->pleft);
		}
		else if (x > t->data.malop_tc)
		{
			remove(x, t->pright);
		}
			
		else    
		{	
			tree x = t;  

			t->data.ds_dk.sl > 0;
			if (t->pright == NULL)
			{
				t = t->pleft;
			}
			else if (t->pleft == NULL)
			{
				t = t->pright;
			}
			else  
			{
				tree y = t->pright;
				remove_case_3(x,y);
			}
			delete x;
		}
	}
	

}


//========================================== HÀM HIỆU CHỈNH LỚP TÍN CHỈ============================================//
tree search(tree p, int x) //LRN
{
	if (p == NULL)
	{
		return NULL;
	}
	if (p->data.malop_tc == x)
	{
		return p;
	}
	else if (x < p->data.malop_tc)
		return search(p->pleft, x);
	else
		return search(p->pright, x);
}

void Hieu_chinh_1_lop_tc(tree t, int x) // NLR
{
	if (t != NULL)
	{
		if (t->data.malop_tc == x)
		{
			cout << "\nNhap thong tin lop tin chi can thay doi" << endl;
			cin.ignore(); 
			cout << "\nNhap ma mon hoc: "; getline(cin, t->data.ma_mh);
			cout << "\nNhap nien khoa: ";  getline(cin, t->data.nien_khoa);
		
			cout << "\nNhap hoc ki: ";  cin >> t->data.hoc_ki;
		
			cout << "\nNhap nhom: ";   cin >> t->data.nhom;
			
			cout << "\nNhap so sv max: "; cin >> t->data.so_svmax;
		
			cout << "\nNhap so sv min: ";  cin >> t->data.so_svmin;
		

		}
		else if (x < t->data.malop_tc)
		{
			Hieu_chinh_1_lop_tc(t->pleft, x);
		}
		else if (x > t->data.malop_tc)
		{
			Hieu_chinh_1_lop_tc(t->pright, x);
		}
	}
}

void Hieu_chinh_lop_tin_chi(ds_lop_tc &dslop_tc)
{
	int x;
	cout << "Nhap ma lop tin chi can hieu chinh ";
	cin >> x;
	tree node_lop = search(dslop_tc.ds, x);

	// IN RA DANH SÁCH CHO NGƯỜI DÙNG XEM 
	cout << "\n======= MA LOP TIN CHI TIM THAY LA =======";
	cout << "Ma lop tin chi " << node_lop->data.malop_tc << endl;
	cout << "Ma mon hoc " << node_lop->data.ma_mh << endl;
	cout << "Nien khoa " << node_lop->data.nien_khoa << endl;
	cout << "Hoc ki " << node_lop->data.hoc_ki << endl;
	cout << "Nhom " << node_lop->data.nhom << endl;
	cout << "So sv max " << node_lop->data.so_svmax << endl;
	cout << "So sv min" << node_lop->data.so_svmin << endl;
	system("pause");

	if (node_lop == NULL)
	{
		cout << "Ko tim thay lop";
		return;
	}
	else
	{
		Hieu_chinh_1_lop_tc(dslop_tc.ds, x);

		cout << "\nDa hieu chinh thong tin lop tin chi" << endl;

		cout << "\n ========== THONG TIN LOP TIN CHI SAU KHI HIEU CHINH LA ======";

		cout << "Ma mon hoc: " << dslop_tc.ds->data.ma_mh << endl;
		cout << "Nien khoa: " << dslop_tc.ds->data.nien_khoa << endl;
		cout << "Hoc ki: " << dslop_tc.ds->data.hoc_ki << endl;
		cout << "Nhom: " << dslop_tc.ds->data.nhom << endl;
		cout << "So sv max: " << dslop_tc.ds->data.so_svmax << endl;
		cout << "So sv min: " << dslop_tc.ds->data.so_svmin << endl;

		system("pause");
	}
}

//========================================= HÀM XUẤT LỚP TÍN CHỈ ===================================================//
void Xuat_loptc(lop_tin_chi x)
{
		cout << "\n\nMa loptc:" << x.malop_tc << endl;
		cout << "Ma mon hoc:" << x.ma_mh << endl;
		cout << "Nien khoa:" << x.nien_khoa << endl;
		cout << "Hoc ki:" << x.hoc_ki << endl;
		cout << "Nhom:" << x.nhom << endl;
		cout << "So sv max:" << x.so_svmax << endl;
		cout << "So sv min:" << x.so_svmin << endl;
}

void Xuat_LNR(tree T)
{
	//Logo(20, 1);

	if (T != NULL)
	{
		Xuat_LNR(T->pleft);	
		Xuat_loptc(T->data);
		Xuat_LNR(T->pright);	
	}
	
}
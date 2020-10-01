#pragma once
#include <fstream>  // hàm đọc ghi file
#include "ctdl.h"
#include <cstdlib>
#include <ctime>


//========================================= LOAD FILE MON HOC [ Mảng con trỏ ] ============================================//
void load_file_mon_hoc(ds_mh &dsmon_hoc )
{
	ifstream filein;

	filein.open("D:\\Tai lieu cau truc du lieu\\Doc_ghi_file\\ghi_mon_hoc.txt", ios_base::in);
	if (filein.fail() == true)
	{
		cout << "Mo file that bai !";
		system("pause");
	}
		
	filein >> dsmon_hoc.sl;
	filein.ignore();

	for (int i = 0; i < dsmon_hoc.sl; i++)
	{
		mon_hoc* a = new mon_hoc;

		getline(filein, a->ma_mh, ',');

		getline(filein, a->ten_mh, ',');

		filein >> a->so_tclt;
		filein.ignore();
		
		filein >> a->so_tcth;
		filein.ignore();              

		dsmon_hoc.ds[i] = a;
	}
		
			

		
	filein.close();
}

// ======================== GHI FILE DANH SÁCH MÔN HỌC [ Mảng con trỏ ] ===============================//


void ghi_file_mon_hoc(ds_mh dsmon_hoc)
{	
	ofstream fileout;

	fileout.open("D:\\Tai lieu cau truc du lieu\\Doc_ghi_file\\ghi_mon_hoc.txt", ios_base::out);
	if (fileout.fail() == true)
	{
		cout << "Mo file that bai !";
		system("pause");
	}
	
	fileout<< dsmon_hoc.sl<< endl;
	
	for (int i = 0; i < dsmon_hoc.sl; i++)
	{
		fileout << dsmon_hoc.ds[i]->ten_mh << "," << dsmon_hoc.ds[i]->ma_mh << "," << dsmon_hoc.ds[i]->so_tclt << "," << dsmon_hoc.ds[i]->so_tcth << endl;
	}
	fileout.close();
}

// ========================================= ĐỌC FILE SINH VIÊN [ DANH SÁCH LIÊN KẾT ] ==========================================//

void Them_sinh_vien(ds_sv &DS_SV, node_sinh_vien *p) //
{
	node_sinh_vien *nodePre = DS_SV.phead;
	if (DS_SV.phead == NULL) // ds rỗng thêm đầu => dung
	{
		p->pnext = DS_SV.phead;
		DS_SV.phead = p;
		return;
	}

	string s1 = p->data.ma_lop + p->data.ma_sv;
	string s2 = nodePre->data.ma_lop + nodePre->data.ma_sv;

	if (s1 <= s2)  // thêm đầu ds
	{
		// thêm đầu
		p->pnext = DS_SV.phead;
		DS_SV.phead = p;
		return;
	}
	// neu ko phai la dau ds
	for (node_sinh_vien *k = DS_SV.phead->pnext; k != NULL; k = k->pnext) // thêm sau ds
	{
		if (p->data.ma_lop + p->data.ma_sv <= k->data.ma_lop + k->data.ma_sv)
		{
			nodePre->pnext = p;
			p->pnext = k;
			return;
		}
		nodePre = k;
	}

	// thêm cuối
	nodePre->pnext = p;
}


void load_file_dssv(ds_sv &DS_SV)
{
	ifstream filein;

	filein.open("D:\\Tai lieu cau truc du lieu\\Doc_ghi_file\\ghi_sinh_vien.txt", ios_base::in);
	if (filein.fail() == true)
	{
		cout << "Mo file that bai !";
		system("pause");
	}

	filein >> DS_SV.sl;
	filein.ignore();
	
	for (int i = 0; i < DS_SV.sl; i++)
	{
		node_sinh_vien *a = new node_sinh_vien;

		getline(filein, a->data.ma_sv, ',');
		
		getline(filein, a->data.ma_lop, ',');
		
		getline(filein, a->data.ho, ',');

		getline(filein, a->data.ten, ',');
	
		getline(filein, a->data.phai, ',');
		
		getline(filein, a->data.sdt, ',');
		
		filein >> a->data.nam_nhap_hoc;
	
		filein.ignore();

		a->pnext = NULL; //  bỏ cái con trỏ khi mình khởi tạo [node_sinh_viên]

		Them_sinh_vien(DS_SV, a);
	}
	
		
	

	filein.close();
}


// ========================================= GHI FILE SINH VIÊN [ DANH SÁCH LIÊN KẾT ] ==========================================//
int DemSinhVien(ds_sv DS_SV)
{
	int dem = 0;
	for (node_sinh_vien *k = DS_SV.phead; k != NULL; k = k->pnext)
	{
		dem++;
	}
	return dem;
}

void ghi_file_dssv(ds_sv DS_SV)
{
	// khai báo
	ofstream fileout;

	// mở file rồi ghi
	fileout.open("D:\\Tai lieu cau truc du lieu\\Doc_ghi_file\\ghi_sinh_vien.txt", ios_base::out);

	if (fileout.fail() == true)
	{
		cout << "Mo file sinh vien that bai !";
		system("pause");
	}
	
	int sl = DemSinhVien(DS_SV);
	fileout << sl << endl;

	for (node_sinh_vien *k = DS_SV.phead; k != NULL; k = k->pnext)
	{
		
		fileout << k->data.ma_sv << "," << k->data.ma_lop << "," << k->data.ho << "," << k->data.ten << "," << k->data.phai << "," << k->data.sdt << "," << k->data.nam_nhap_hoc << endl ;

	}
	fileout.close();
}

//================================================================================================================//
//===================================================== LỚP TÍN CHỈ ==============================================//

void Insert_lop_tc(tree &p, lop_tin_chi a)  // insert node
{
	if (p == NULL )    // nút p hiện tại là nút lá
	{
		p = new node_Lop_tin_chi;
		p->data = a;
		p->pleft = NULL;
		p->pright = NULL;
	}
	else if (a.malop_tc < p->data.malop_tc)
		Insert_lop_tc(p->pleft, a);
	else if (a.malop_tc > p->data.malop_tc)
		Insert_lop_tc(p->pright, a);

}

void load_file_lop_tc(ds_lop_tc &dslop_tc)
{
	ifstream filein;

	filein.open("D:\\Tai lieu cau truc du lieu\\Doc_ghi_file\\ghi_loptc.txt", ios_base::in);
	if (filein.fail() == true)
	{
		cout << "Mo file that bai !";
		system("pause");
	}
	
		filein >> dslop_tc.sl;
		filein.ignore(); 

		for (int i = 0; i < dslop_tc.sl; i++)
		{
			tree a = new node_Lop_tin_chi;

			filein >> a->data.malop_tc;

			filein.ignore();

			getline(filein, a->data.ma_mh, ',');

			getline(filein, a->data.nien_khoa, ',');

			filein >> a->data.hoc_ki;
			filein.ignore();

			filein >> a->data.nhom;
			filein.ignore();

			filein >> a->data.so_svmax;
			filein.ignore();

			filein >> a->data.so_svmin;

			filein.ignore();

			Insert_lop_tc(dslop_tc.ds, a->data);
		}

	filein.close();
}

// ============================================= GHI FILE LỚP TÍN CHỈ [ CÂY NHỊ PHÂN ] ==========================================//
int DemSlLoptc(tree t)
{
	if (t == NULL) return 0;
	else
		return DemSlLoptc(t->pright) + DemSlLoptc(t->pleft) + 1;
}

void Luuloptc(tree t, ofstream& fileout) {
	if (t!= NULL) {
		Luuloptc(t->pleft, fileout);
		Luuloptc(t->pright, fileout);

		fileout << t->data.malop_tc << "," << t->data.ma_mh << "," << t->data.nien_khoa << "," << t->data.hoc_ki << "," << t->data.nhom << "," << t->data.so_svmax << "," << t->data.so_svmin << endl;
	}
}
void ghi_file_loptc(ds_lop_tc dslop_tc)
{
	ofstream fileout;

	fileout.open("D:\\Tai lieu cau truc du lieu\\Doc_ghi_file\\ghi_loptc.txt", ios_base::out);

	if (fileout.fail() == true)
	{
		cout << "Mo file loptc that bai !";
		system("pause");
	}
	
	int sl = DemSlLoptc(dslop_tc.ds);

	fileout  << sl << endl;

	if (dslop_tc.ds!= NULL) {
		Luuloptc(dslop_tc.ds, fileout);
	}

	fileout.close();
}


// =============== // ========= //

void in_file_random()
{
	
	if (ifstream("D:\\Tai lieu cau truc du lieu\\Doc_ghi_file\\random.txt"))
	{
		//cout << "File already exists" << endl;
		return ;
	}
	
	std::ofstream fileout("D:\\Tai lieu cau truc du lieu\\Doc_ghi_file\\random.txt");
		const int n = 10000;
		int ds[n];
		for (int i = 0; i< n; i++)
		{
			ds[i] = i;

		}

		for (int j = 0; j< n/2 ; j++)
		{
			int value = rand() % (n) ;
			int tam = ds[j];  // tam = 0,1,2,3,4,5,6
			ds[j] = ds[value];
			ds[value] = tam;
		}

		int i = 0;
		int value;

		fileout << n << endl ;
		fileout << n  << endl; // index
		while (i < n)
		{
			fileout << ds[i] << ",";
			i++;
		}
		fileout.close();
}


int load_file()
{
	ifstream filein;

	filein.open("D:\\Tai lieu cau truc du lieu\\Doc_ghi_file\\random.txt", ios_base::in);
	if (filein.fail() == true)
	{
		cout << "Mo file that bai !";
		system("pause");
	}

	int n ; 
	int index;
	

	filein >> n ;
	filein.ignore();

	filein >> index;
	filein.ignore();

	int ds[10000];

	for (int i = 0; i < n; i++)
	{
		int number;
		filein >> number ;
		ds[i] = number;
		filein.ignore();
	}


	filein.close();



	// mo lai
	ofstream fileout;

	fileout.open("D:\\Tai lieu cau truc du lieu\\Doc_ghi_file\\random.txt", ios_base::out);

	if (fileout.fail() == true)
	{
		cout << "Mo file loptc that bai !";
		system("pause");
	}

	fileout << n << endl;
	fileout << (index - 1) << endl;

	for (int j = 0; j < n; j++)
	{
		fileout << ds[j] << ",";
	}

	fileout.close();

	
	return ds[index-1];

}


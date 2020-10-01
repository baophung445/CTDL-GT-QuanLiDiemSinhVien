#pragma once

#include "dang_ki.h"
// ======================================= LOP TC ======================================//
// === Nhap ===/
void Insert_lop_tc(tree &p, lop_tin_chi a);
void Nhap_lop_tin_chi(ds_lop_tc &dslop_tc);
//=== Xuat ===/
void Xuat_loptc(lop_tin_chi x);
void Xuat_LNR(tree T);
//=== Xoa ===//
void remove_case_3(tree &r);
void  remove(int x, tree &p);
// === Hieu chinh ===//
void Hieu_chinh_1_lop_tc(tree t, int x);
void Hieu_chinh_lop_tin_chi(ds_lop_tc &dslop_tc);
// === Load - Ghi file lop tin chi ===//
void load_file_lop_tc(ds_lop_tc &dslop_tc);
int DemSlLoptc(tree t);
void Luuloptc(tree dslop_tc, ofstream& fileout);
void ghi_file_loptc(ds_lop_tc dslop_tc);



// ====================================== MON HOC ======================================//
void Them_mon_hoc(ds_mh &dsmon_hoc);
void xuat_ds_mon_hoc(ds_mh dsmon_hoc);
int kt_ma__mon_hoc(string a, ds_mh dsmon_hoc);
void xoa_mon_hoc(ds_mh &dsmon_hoc);
void hieu_chinh_mon_hoc(ds_mh dsmon_hoc);
void hoan_vi_mon_hoc(mon_hoc *a, mon_hoc *b);
void sap_xep_mon_hoc_tang_dan(ds_mh dsmon_hoc);

// ====== Load file mon hoc =====//
void load_file_mon_hoc(ds_mh &dsmon_hoc);
int demSLmonHoc(ds_mh dsmon_hoc);
void ghi_file_mon_hoc(ds_mh dsmon_hoc);


// ========================================= SINH VIEN =================================//
void Them_sinh_vien(ds_sv &DS_SV, node_sinh_vien *p);
void Nhap_sinh_vien(ds_sv &DS_SV);
bool Hieu_chinh_sv(ds_sv &DS_SV);

void xuat_1_sv(node_sinh_vien *phead);
void xuat_sv(ds_sv DS_SV);
//== xoa sv == //
void xoa_sv(ds_sv &DS_SV);
//======== Search theo ma sv =========//
int Search_masv(ds_sv DS_SV, string a);
//============ Load file SV ================//
void load_file_dssv(ds_sv &DS_SV);
int DemSinhVien(ds_sv DS_SV);
void ghi_file_dssv(ds_sv DS_SV);
// ======== In dssv tang dan theo alpha =======//
void Search_sv_co_malop(ds_sv DS_SV, ds_sv &ds_sv_theo_lop_moi);
void clearlist( ds_sv &plist);        //clear list dssv;

// ====================================== DANG KI LOP TIN CHI ===========================//
void dang_ki_lop_tc(ds_lop_tc dslop_tc, ds_mh dsmon_hoc, ds_sv DS_SV);
void Duyet_Cay_Tim_NienKhoa_HocKi(tree p, string nien_khoa, int hocki, lop_tin_chi ds[], int &n);
string getTenMonHoc(ds_mh dsmon_hoc, string maMH);
void CheckMonHocDaDK(node_Lop_tin_chi* a[], string maSV, int n, string maMH, bool &kt);
bool CheckLopSVDaDK(tree t, string maSV, int maLopTC);





// ============= Menu ================== //

string strMNMain[] = {
	
	" 1.  Them Lop Tin Chi       ",
	" 2.  Xoa Lop Tin Chi        ",
	" 3.  Sua Lop Tin Chi        ",
	" 4.  In ds dadk ltc 4Fields ",
	" 5.  Them Sinh Vien         ",
	" 6.  Xoa Sinh Vien          ",
	" 7.  Chinh sua Sinh Vien    ",
	" 8.  In DS_SV theo alphabet ",
	" 9.  Them Mon Hoc           ",
	" 10. Sua Mon Hoc            ",
	" 11. Xoa Mon Hoc            ",
	" 12. In danh sach mon hoc   ",
	" 13. Dk & huy lop tin chi   ",
	" 14. Nhap diem              ",
	" 15. In bang diem mon hoc   ",
	" 16. In diem trung binh     ",
	" 17. Load file              ",
	" 18. Ghi file               ",

	" 0.  Ket thuc chuong trinh  "
};

void Menu()
{
	//textcolor(240);
	int j = 15;
	for (int i = 0; i < sizeof(strMNMain) / sizeof(*strMNMain); i++)
	{
		gotoXY(35, j++);
		cout << strMNMain[i];
	}
}
void RunMenu(ds_sv &DS_SV, ds_lop_tc &dslop_tc, ds_mh &dsmon_hoc, ds_sv &ds_sv_theo_lop_moi ,ds_dang_ki &dsdang_ki)
{
	if (kbhit())
	{
		char c = getch();
		if (c == -32)
		{
			c = getch();
			if (c == 72)
			{
				if (pointer == 15)
				{
					Menu();
					pointer = 15 - 1 + sizeof(strMNMain) / sizeof(*strMNMain);
				}
				else
				{
					Menu();
					pointer--;
				}
			}
			else if (c == 80) // mã ascii mui tên xuống
			{
				if (pointer == 15 - 1 + sizeof(strMNMain) / sizeof(*strMNMain))
				{
					Menu();
					pointer = 15;
				}
				else
				{
					Menu();
					pointer++;
				}
			}
		}
		else if (c == 13)
		{
			system("cls");
			switch (pointer)
			{
				

			case 15:
			{

					   in_file_random();

					  
					   Nhap_lop_tin_chi(dslop_tc, dsmon_hoc); 

					   Xuat_LNR(dslop_tc.ds);

					   system("pause");
					   break;
			}
			case 16:
			{		   int x;
					   cout << "Nhap ma lop tin chi can xoa";
					   cin >> x;
					   remove(x ,dslop_tc.ds);
					   Xuat_LNR(dslop_tc.ds);
					   system("pause");
					   break;
			}
			case 17:
			{
					   Hieu_chinh_lop_tin_chi(dslop_tc);
					   break;
			}

			case 18:
			{
					   In_ds_theo_4Fields(dslop_tc, dsdang_ki, DS_SV);
						   break;
			}
			case 19:
			{
					 
					   Nhap_sinh_vien(DS_SV);
					   xuat_sv(DS_SV);
					   break;
			}
			case 20:
			{
					   xoa_sv(DS_SV);
					   system("pause");
					   xuat_sv(DS_SV);
					   break;
			}

			case 21:
			{

					   if (Hieu_chinh_sv(DS_SV) == false)
					   {
						   cout << "Ma sinh vien khong ton tai." << endl;
					   }
					   system("pause");
					   break;
			}
			case 22:
			{
					   Search_sv_co_malop(DS_SV, ds_sv_theo_lop_moi);// in dssv tăng dần theo lớp
					   xuat_sv(ds_sv_theo_lop_moi);

					   clearlist(ds_sv_theo_lop_moi);

					   break;
			}

			case 23:
			{
					  

					   Them_mon_hoc(dsmon_hoc);
					   xuat_ds_mon_hoc(dsmon_hoc);

					   system("pause");
					   break;
			}
			case 24:
			{
					   hieu_chinh_mon_hoc(dsmon_hoc);
					   xuat_ds_mon_hoc(dsmon_hoc);
					   break;
			}
			case 25:
			{
					   xoa_mon_hoc(dsmon_hoc);
					   break;
			}

			case 26:
			{
					   
					   sap_xep_mon_hoc_tang_dan(dsmon_hoc);
					   break;
			}
			case 27:
			{
					  // dang_ki_lop_tc( dslop_tc, dsmon_hoc, DS_SV);
					   DangKiLopTC(DS_SV, dslop_tc, dsmon_hoc,55, 17);
					   system("pause");
					   break;
			}

			case 28:
			{
					   NhapDiem(DS_SV, dslop_tc, dsmon_hoc, 50, 50);
					   break;
			}

			case 29:
			{
					   In_bang_diem_cua_1_lop_tc(DS_SV, dslop_tc, dsmon_hoc, 60, 60);
					  
					  
					   break;
			}
			case 30:
			{
					  // Duyet_cay(dslop_tc.ds, DS_SV);
					   break;
			}
			case 31:
			{
					   load_file_lop_tc(dslop_tc);
					   load_file_mon_hoc(dsmon_hoc);
					   load_file_dssv(DS_SV);
					   cout << "Load file thanh cong !!! ";
					   system("pause");
					   break;

			}
			case 32:
			{
					   ghi_file_loptc(dslop_tc);
					   ghi_file_dssv(DS_SV);
					   ghi_file_mon_hoc(dsmon_hoc);
					   
					   cout << "Ghi file file thanh cong !!!";
					   system("pause");
					   break;
					   

			}
			case 33:
			{
					   exit(0);
			}
			}

			system("cls");
			GiaoDienMain();
			Menu();

		}
	}
	ShowCur(0);
	// to mau 
	textcolor(180);
	gotoXY(35, pointer);
	cout << strMNMain[pointer - 15];
	textcolor(7);
}
	int main()
	{
		srand(time(NULL));
		ds_sv DS_SV;
		ds_lop_tc dslop_tc;
		ds_mh dsmon_hoc;
		ds_sv ds_sv_theo_lop_moi;
		ds_dang_ki dsdang_ki;
		//mon_hoc a;

		
		resizeConsole(1500, 900);
		Menu();
		GiaoDienMain();
		while (true)
		{

			RunMenu(DS_SV, dslop_tc, dsmon_hoc, ds_sv_theo_lop_moi, dsdang_ki);
		}

		return 0;
	}






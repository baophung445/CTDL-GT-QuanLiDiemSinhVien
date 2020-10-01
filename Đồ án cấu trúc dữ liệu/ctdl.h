#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include "mylib.h"
#include <string.h>

using namespace std;
#pragma warning(disable:4996)
int pointer = 15;

#define MAXMON 300
#define MAXLOP 100

int toadoXBox = 15;
int toadoYBox = 9;
int toadoYMain = 10;




//========================= DS MON HOC =================//
struct mon_hoc
{
	string ma_mh;
	string ten_mh;
	float so_tclt;
	float so_tcth;
};

struct ds_mh
{
	mon_hoc *ds[MAXMON];  
	int sl = 0;
};

// ========================= DS SINH VIEN ======================///
struct sinh_vien
{
	// data
	string ma_sv;
	string ma_lop;
	string ho;
	string ten;
	string phai;
	string sdt;
	int nam_nhap_hoc;
};

struct node_sinh_vien
{
	sinh_vien data; //data
	node_sinh_vien *pnext; // chứa con trỏ , nên bản thân nó cũng là con trỏ
};

struct ds_sv
{
	node_sinh_vien *phead = NULL;//dau ds
	int sl ;
};

//=========================== DS DANG KI ========================//
struct dang_ki
{
	//data
	string ma_sv;
	float diem;

	// pointer
	dang_ki *pnext;
};


struct ds_dang_ki
{
	dang_ki *phead = NULL;
	int sl = 0;
};

//==================== DS LOP TIN CHI ========================//
struct lop_tin_chi
{
	int malop_tc;
	string ma_mh;
	string nien_khoa; 
	int hoc_ki;
	int nhom;
	int so_svmax ;
	int so_svmin;
	//int soluong; //lấy svmax - số lượng hiện tại (soluong++) để xem còn ko mà cho đăng kí
	// con tro tro den dsdk
	ds_dang_ki ds_dk;
};

struct node_Lop_tin_chi
{
	//data
	lop_tin_chi data;
	// pointer
	node_Lop_tin_chi *pleft;
	node_Lop_tin_chi *pright;
};
typedef struct node_Lop_tin_chi* tree;

struct ds_lop_tc
{
	tree ds = NULL;
	int sl = 0;
};


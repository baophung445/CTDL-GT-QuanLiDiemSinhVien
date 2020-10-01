#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>

using namespace std;

// Hàm thay d?i kích c? c?a khung cmd v?i tham s? truy?n vào là chi?u cao, chi?u r?ng.
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

// Hàm d?ch chuy?n con tr? d?n t?a d? x, y.
void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Hàm xóa màn hình.
void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

// Hàm backgroud
void BackGroundColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
// Hàm t? vi?t
void ToMau(int x, int y, char *a, int color) // x, y là t?a d? con tr? c?n nh?y d?n d? vi?t, a là chu?i c?n truy?n vào, color là màu truy?n vào.
{
	gotoXY(x, y);
	textcolor(color);
	cout << a;
	textcolor(7);
}



//============================== Cac ham ho tro ============================ //
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
int whereX()
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.X;
}
int whereY()
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.Y;
}
// Hàm xử lí nhập chữ
string XuLyNhapchu()
{
	string input;
	ShowCur(1);
	gotoXY(whereX(), whereY());
	while (true)
	{
		char c = _getch(); 
		if ((c >= 48 && c <= 57) || c == '-'||c =='_' || (c >= 65 && c <= 90) ) 
		{
			input.insert(input.begin() + input.length(), c);
			cout << c;
		}
		else if (c >= 97 && c <= 122)
		{
			input.insert(input.begin() + input.length(), c);
			cout << c;
		}
		else if (c == 8 && input.length() > 0)
		{
			input.erase(input.begin() + input.length() - 1);
			cout << "\b";
			cout << " ";
			cout << "\b";
		}
		else if (c == 27)
		{
			input.clear();
			ShowCur(0);
			return input;
		}
		else if (c == 13 && input.length() > 0)// nếu là phím enter
		{
			ShowCur(0);
			return input;
		}
	}
}
// Hàm xử lí nhập số
int XuLyNhapSo()
{
	int n;
	ShowCur(1);
	gotoXY(whereX(), whereY());
	string x = "";
	char c;
	while (true)
	{
		c = _getch();
		if ((c >= 48 && c <= 57))// nếu là số thì
		{
			x.insert(x.begin() + x.length(), c);
			cout << c;
		}
		else if (c == 8 && x.length()>0) // space
		{
			x.erase(x.begin() + x.length() - 1);
			cout << "\b";
			cout << " ";
			cout << "\b";
		}
		else if (c == 27)
		{
			ShowCur(0);
			return -1;
		}
		else if (c == 13 && x.length() > 0)// nếu là phím enter
		{
			n = atoi(x.c_str());
			ShowCur(0);
			return n;
		}
	}
}



//========== Hàm menu ================//
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void VeHCN(int toadoX, int toadoY, int chieudai, int chieucao, int mauSet)
{
	SetColor(mauSet);
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
	SetColor(7);
}
void ToMauHCN(int toadoX, int toadoY, int chieudai, int chieucao, int mauText)
{
	textcolor(mauText);
	for (int i = toadoY + 1; i < toadoY + chieucao; i++)
	{
		for (int j = toadoX + 1; j < chieudai + toadoX; j++)
		{
			gotoXY(j, i);
			cout << " ";
		}
	}
	textcolor(7);
}
string CanDeuChuoi(string str, int ChieuRong)
{
	if (str.empty())
	{
		return str;
	}
	else if (str.length() > ChieuRong)
	{
		return str;
	}
	return string((ChieuRong - str.length()) / 2, ' ') + str;
}
void Logo(int toadoX, int toadoY)
{
	string str;
	ifstream FileIn;
	FileIn.open("input.txt", ios::in);
	int h = toadoY;
	SetColor(6);
	while (true)
	{
		getline(FileIn, str);
		gotoXY(toadoX, h++);
		cout << str << endl;
		if (FileIn.eof())
		{
			break;
		}
	}
	textcolor(8);
	FileIn.close();
}
void GiaoDienMain() // giao diện logo
{
	ShowCur(0);
	
	Logo(20, 5);
}
void GiaoDienThongBao(string x)
{
	ToMauHCN(60, 10, 35, 10, 20);
	textcolor(3);
	gotoXY(60, 10);
	//gotoXY(whereX(), whereY());
	cout << CanDeuChuoi(x, 40);
	_getch();
	textcolor(7);
}

int showNotifyMessageBox(char* title, char* message, int typeIcon = MB_ICONINFORMATION)
{
	//hi?n MessageBox
	int msgboxID = MessageBoxA(
		GetConsoleWindow(),
		message,
		title,
		typeIcon | MB_OK
		);
	return msgboxID;
}


// ===== Hien thong bao ====== //
//int showMessageBox(char* title, char* message, int typeIcon)
//{
//	//hi?n MessageBox
//	int msgboxID = MessageBoxA(
//		GetConsoleWindow(),
//		message,
//		title,
//		typeIcon | MB_OKCANCEL
//		);
//	return msgboxID;
//}

char Chuyen1SoSangKiTu(int n)
{
	switch (n)
	{
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	case 0:
		return '0';
	}
}
string ChuyenSoSangString(int n)
{
	string str;
	int a;
	if (n == 0)
	{
		str = "0";
	}
	while (n > 0)
	{
		a = n % 10;
		Chuyen1SoSangKiTu(a);
		str.insert(str.begin() + 0, Chuyen1SoSangKiTu(a));
		n = n / 10;
	}
	return str;
}
// Vẽ giao diện
void SetBGColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void Normal() {
	SetColor(0);
	SetBGColor(255);
}


void drawRectangleInput(int x, int y, int width, int height, int color) {
	SetColor(color);
	for (int i = 1; i <= width; i++) {
		gotoXY(x + i, y);
		if (i == 1) {
			cout << char(201);
		}
		else {
			if (i == width) {
				cout << char(187);
			}
			else
				cout << char(205);
		}
	}

	for (int i = 1; i <= height; i++) {

		for (int j = 1; j <= width; j++) {
			gotoXY(x + j, y + i);

			if (j == 1 || j == width) {
				cout << char(186);
			}
			else {
				cout << " ";
			}
		}
	}
	for (int i = 1; i <= width; i++) {
		gotoXY(x + i, y + height);
		if (i == 1) {
			cout << char(200);
		}
		else {
			if (i == width) {
				cout << char(188);
			}
			else
				cout << char(205);
		}
	}
	Normal();
	
}

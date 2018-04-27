#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct SINHVIEN
{
	wchar_t* MSSV;
	wchar_t* HovaTen;
	wchar_t* Khoa;
	int KhoaTuyen;
	wchar_t* NgaySinh;
	wchar_t* Email;
	wchar_t* HinhAnhCaNhan;
	wchar_t* MoTaBanThan;
	wchar_t** SoThich;
};

wchar_t* Get_line(FILE* f)
{
	wchar_t* a = (wchar_t*)malloc(sizeof(wchar_t)* 2);
	int i = 0;
	int size = 2;
	while (*(a + i - 1) != '\n' && *(a + i - 1) != '\0')
	{
		a = (wchar_t*)realloc(a, sizeof(wchar_t)* size);
		fgetws(a + i, 2, f);
		i++;
		size++;
	}
	return a;
}

void Tok(SINHVIEN& a, wchar_t* str)
{
	const wchar_t c[2] = L",";
	wchar_t* token = wcstok(str, c);
	a.MSSV = token;
	token = wcstok(NULL, c);
	a.HovaTen = token;
	token = wcstok(NULL, c);
	a.Khoa = token;
	token = wcstok(NULL, c);
	int l = wcslen(token);
	char* b = (char*)malloc(l);
	l = wcstombs(b, token, sizeof(b));
	a.KhoaTuyen = atoi(b);
	token = wcstok(NULL, c);
	a.NgaySinh = token;
	token = wcstok(NULL, c);
	a.Email= token;
	token = wcstok(NULL, c);
	a.HinhAnhCaNhan = token;
	token = wcstok(NULL, L"\n");
	if (*token == L'"') token = wcstok(token, L"\"");
	else token = wcstok(token, c);
	a.MoTaBanThan = token;
	int i = 0;
	int size = 3;
	a.SoThich = (wchar_t* *)malloc(sizeof(wchar_t*)*size);
	size++;
	token = wcstok(NULL, L"\n");
	while (token != NULL)
	{
		if (*token == L'"') token = wcstok(token, L"\"");
		else if ((*token == L',' && *(token + 1) == L'"')) token = wcstok(token+1, L"\"");
		else token = wcstok(token, c);
		a.SoThich = (wchar_t* *)realloc(a.SoThich, sizeof(wchar_t*)*size);
		*(a.SoThich + i) = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(token)+1));
		*(a.SoThich + i) = token;
		i++;
		size++;
		token = wcstok(NULL, L"\n");
	}
	*(a.SoThich + i) = NULL;
}

wchar_t* DocFileHtml(FILE* f, int& i)
{
	wchar_t* a = (wchar_t*)malloc(sizeof(wchar_t)* 2);
	i = 0;
	int size = 2;
	while (!feof(f))
	{
		a = (wchar_t*)realloc(a, sizeof(wchar_t)* size);
		fgetws(a + i, 2, f);
		i++;
		size++;
	}
	int lg = (size - 1)*(sizeof(wchar_t));
	return a;
}

void DeleteSubStr(wchar_t* &Str, int& StartPos, int i)
{
	int l = wcslen(Str);
	while (*(Str + StartPos) != '<'&&*(Str + StartPos) != '"')	StartPos++;
	int j;
	for (j = i; j < l; j++)
	{
		*(Str + j) = *(Str + j + StartPos - i);
	}
	*(Str + j) = L'\0';
}

void Delete(SINHVIEN a, int& l, wchar_t*& b, FILE* f)
{
	b = DocFileHtml(f, l);
	wchar_t* c = wcsstr(b, L"<title>");
	int i = 15;
	DeleteSubStr(c, i, 15);
	c = wcsstr(b, L"Personal_FullName");
	i = 19;
	DeleteSubStr(c, i, 19);
	c = wcsstr(b, L"Personal_Department");
	i = 21;
	DeleteSubStr(c, i, 21);
	c = wcsstr(b, L"Personal_Phone");
	i = 16;
	DeleteSubStr(c, i, 16);
	c = wcsstr(b, L"Personal_HinhcanhanKhung");
	i = 43;
	DeleteSubStr(c, i, 43);
	c = wcsstr(b, L"TextInList");
	i = 64;
	DeleteSubStr(c, i, 64);
	i = 82;
	DeleteSubStr(c, i, 82);
	i = 116;
	DeleteSubStr(c, i, 116);
	i = 146;
	DeleteSubStr(c, i, 146);
	c = wcsstr(b, L"Email");
	i = 7;
	DeleteSubStr(c, i, 7);
	c = wcsstr(b, L"\"InfoGroup\">S");
	i = 148;
	DeleteSubStr(c, i, 148);
	i = 166;
	DeleteSubStr(c, i, 166);
	int j;
	for (j = 144; j < wcslen(c); j++)
	{
		*(c + j) = *(c + j + 27);
	}
	*(c + j) = L'\0';
	c = wcsstr(b, L"Description");
	i = 13;
	DeleteSubStr(c, i, 13);
	c = wcsstr(b, L"MSSV");
	i = 0;
	DeleteSubStr(c, i, 0);
	l = wcslen(b);
}

wchar_t* StrCopy(wchar_t* a, wchar_t* b)
{
	int i;
	int l = wcslen(b);
	for (i = 0; i < l; i++)
	{
		*(a + i) = *(b + i);
	}
	*(a + i) = '\0';
	return a;
}

void InsertSubStr(wchar_t*& Str, wchar_t* SubStr, int i)
{
	int l = wcslen(SubStr);
	int lg = wcslen(Str);
	wchar_t* temp = (wchar_t*)malloc((lg + 1)*sizeof(wchar_t));
	StrCopy(temp, Str + i);
	StrCopy(Str + i, SubStr);
	StrCopy(Str + i + l, temp);
}

int Kt(wchar_t**s)
{
	int i = 0;
	while (*(s + i) != NULL)i++;
	return i;
}

void Insert(SINHVIEN a, int& l, wchar_t*& b, FILE* f)
{
	wchar_t* c = wcsstr(b, L"<title>");
	int lg = wcslen(a.HovaTen);
	InsertSubStr(c, a.HovaTen, 15);
	c = wcsstr(b, L"Personal_FullName");
	InsertSubStr(c, a.HovaTen, 19);
	InsertSubStr(c, L" - ", 19 + lg);
	InsertSubStr(c, a.MSSV, 22 + lg);
	c = wcsstr(b, L"Personal_Department");
	InsertSubStr(c, L"KHOA ", 21);
	InsertSubStr(c, a.Khoa, 26);
	c = wcsstr(b, L"Personal_Phone");
	InsertSubStr(c, a.Email, 16);
	c = wcsstr(b, L"Personal_HinhcanhanKhung");
	InsertSubStr(c, L"Images/", 43);
	InsertSubStr(c, a.HinhAnhCaNhan, 50);
	c = wcsstr(b, L"TextInList");
	InsertSubStr(c, a.HovaTen, 64);
	InsertSubStr(c, L"MSSV: ", 82 + lg);
	InsertSubStr(c, a.MSSV, 88 + lg);
	InsertSubStr(c, a.Khoa, 122 + lg + wcslen(a.MSSV));
	InsertSubStr(c, a.NgaySinh, 152 + lg + wcslen(a.MSSV) + wcslen(a.Khoa));
	c = wcsstr(b, L"Email");
	InsertSubStr(c, a.Email, 7);
	c = wcsstr(b, L"\"InfoGroup\">S");
	int i = 111;
	int iST = Kt(a.SoThich);
	if (iST == 0) InsertSubStr(c, L"<li>N/A</li>", 111);
	else for (int j = 0; j < iST; j++)
	{
		InsertSubStr(c, L"<li>", i);
		InsertSubStr(c, *(a.SoThich + j), i + 4);
		InsertSubStr(c, L"</li>", i + 4 + wcslen(*(a.SoThich + j)));
		i = i + wcslen(*(a.SoThich + j)) + 9;
	}
	c = wcsstr(b, L"Description");
	InsertSubStr(c, a.MoTaBanThan, 13);
	c = wcsstr(b, L"TH2012/03");
	InsertSubStr(c, L"1712891", 19);
	InsertSubStr(c, L" - ", 26);
	InsertSubStr(c, L"Tran Thuy Tuyen", 29);
}

void main()
{
	SINHVIEN* sv;
	wchar_t* a;
	wchar_t b[15];
	wchar_t* c;
	int i, n;
	char s[10];
	printf("> Nhap ten file csv: ");
	gets(s);
	printf("> Nhap so luong profile page can phat sinh\n");
	printf("(Theo thu tu trong file csv): ");
	scanf("%d", &n);
	while (n > 10 || n < 1)
	{
		printf("LUU Y: Chuong trinh hien tai chi ho tro\n");
		printf("Toi da 10 pages - Toi thieu 1 page\n");
		printf("Xin moi nhap lai\n");
		scanf("%d", &n);
	}
	sv = (SINHVIEN*)malloc(sizeof(SINHVIEN)*n);
	FILE* f = fopen(s, "r");
	if (f != NULL)
	{
		fseek(f, 3, SEEK_SET);
		for (int j = 0; j < n; j++)
		{
		a = Get_line(f);
		Tok(*(sv+j), a);
		}
		fclose(f);
	}
	for (int j = 0; j < n; j++)
	{
		f = fopen("1212123.htm", "r");
		if (f != NULL)
		{
			Delete(*(sv + j), i, a, f);
			Insert(*(sv + j), i, a, f);
			fclose(f);
			StrCopy(b, sv[j].MSSV);
			c = wcscat(b, L".htm");
			f = _wfopen(b, L"w");
			if (f != NULL)
			{
				fputws(a, f);
				fclose(f);
			}
		}
	}
}

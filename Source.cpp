#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct SINHVIEN
{
	wchar_t* MSSV;
	wchar_t* HovaTen;
	wchar_t* Khoa;
	int KhoaTuyen;
	wchar_t* NgaySinh;
	wchar_t* HinhAnhCaNhan;
	wchar_t* MoTaBanThan;
	wchar_t** SoThich;
};

wchar_t* Get_line(FILE* f)
{
	wchar_t* a = (wchar_t*)malloc(sizeof(wchar_t)* 2);
	int i = 0;
	int size = 2;
	if (f != NULL)
	{
		fseek(f, 3, SEEK_SET);
		while (*(a + i-1) != '\n')
		{
			a = (wchar_t*)realloc(a, sizeof(wchar_t)* size);
			fgetws(a + i, 2, f);
			i++;
			size++;
		}
		return a;
	}
}

void Tok(SINHVIEN& a,wchar_t* str)
{
	const wchar_t c[2] = L",";
	wchar_t* token = wcstok(str,c);
	a.MSSV = token;
}

void main()
{
	SINHVIEN sv;
	FILE* f = fopen("Test.csv", "r");
	wchar_t* a = Get_line(f);
	wprintf(L"%s", a);
	Tok(sv, a);
	wprintf(L"%s", sv);
	free(a);
	fclose(f);
}
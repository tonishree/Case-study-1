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

void Tok(SINHVIEN& a,wchar_t* str)
{
	const wchar_t c[2] = L",";
	wchar_t* token = wcstok(str,c);
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
		else token = wcstok(token, c);
		a.SoThich = (wchar_t* *)realloc(a.SoThich, sizeof(wchar_t*)*size);
		*(a.SoThich + i) = (wchar_t*)malloc(sizeof(wchar_t)*wcslen(token));
		*(a.SoThich + i) = token;
		i++;
		size++;
		token = wcstok(NULL, L"\n");
	}
}

void Replace(SINHVIEN a)
{
	
}

void Find(SINHVIEN a,wchar_t* b)
{

}

wchar_t* DocFileHtml(FILE* f)
{
	wchar_t* a = (wchar_t*)malloc(sizeof(wchar_t)*2);
	int i = 0;
	int size = 2;
	while (!feof(f))
	{
		a = (wchar_t*)realloc(a, sizeof(wchar_t)* size);
		fgetws(a + i, 2, f);
		i++;
		size++;
	}
	return a;
}

void GhiTapTin(SINHVIEN a) // Thu in ra file.txt
{
	FILE* f = fopen("Test.txt", "w");
	if (f != NULL)
	{
		fputws(a.MSSV, f);
		fprintf(f, "\n");
		fputws(a.HovaTen, f);
		fprintf(f, "\n");
		fputws(a.Khoa, f);
		fprintf(f, "\n");
		fprintf(f, "%d", a.KhoaTuyen);
		fprintf(f, "\n");
		fputws(a.NgaySinh, f);
		fprintf(f, "\n");
		fputws(a.HinhAnhCaNhan, f);
		fprintf(f, "\n");
		fputws(a.MoTaBanThan, f);
		fprintf(f, "\n");
//		fputws(*(a.SoThich + 1), f);
//		fprintf(f, "\n");
		fputws(*(a.SoThich), f);
		fclose(f);
	}
}

void main()
{
	//SINHVIEN sv;
	wchar_t* a;
	/*FILE* f = fopen("Test.csv", "r");
	if (f != NULL)
	{
		fseek(f, 3, SEEK_SET);
		while (!feof(f))
		{
			a = Get_line(f);
			wprintf(L"%s", a);
			Tok(sv, a);
			GhiTapTin(sv);
		}
		fclose(f);
	}*/
	/*wprintf(L"%s", a);
	Tok(sv, a);
	wprintf(L"%s\n", sv.MSSV);
	printf("%d\n", sv.KhoaTuyen);
	wprintf(L"%s\n", *(sv.SoThich + 1));
	GhiTapTin(sv);
	free(a);
	fclose(f);*/
	FILE* f = fopen("1212123.htm", "r");
	if (f != NULL)
	{
		a = DocFileHtml(f);
		fclose(f);
		wchar_t* c = wcsstr(a, L"Ngu");
		c = wcstok(c, L"<");
		
		f = fopen("1212123a.txt", "w");
		if (f != NULL)
		{
			fputws(a, f);
			fclose(f);
		}
		free(a);
	}
}

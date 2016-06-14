#include <stdio.h>
#include <string.h>
#include "define.h"

char open[] = "{\0";
char close[] = "}\0";

RtfInsert header[] =
{
	open,
	"\\rtf1\\ansi\\deff0\0",/*1_header*/
	open,
	"\\fonttbl\0",/*2_setfont*/
	"{\\f0\\froman Tms Rmn;}\0",/*tms*/
	"{\\f1\\fdecor Symbol;}\0",/*symb*/
	"{\\f2\\fswiss Helv;}\0",/*hel*/
	close,
	open,
	"\\colortbl;\0",/*3_setcolor*/
	"\\red0\\green0\\blue0;\0",/*redefinition black*/
	"\\red0\\green0\\blue255;\0",/*redefinition blue*/
	"\\red0\\green255\\blue255;\0",/*redefinition cyan*/
	"\\red0\\green255\\blue0;\0",/*redefinition lime*/
	"\\red255\\green0\\blue255;\0",/*redefinition magenta*/
	"\\red255\\green0\\blue0;\0",/*redefinition red*/
	"\\red255\\green255\\blue0;\0",/*redefinition yellow*/
	"\\red255\\green255\\blue255;\0",/*redefinition white*/
	close,
	open,
	"\\stylesheet\0",/*4_set stylesheet*/
	"{\\fs20 \\snext0 Normal;}\0",/*fontsize*/
	close,
	"\\widoctrl\\ftnbj \\sectd\\linex0\\endnhere\0",
	"\0"/*The end of array*/
};
RtfInsert footer[] =
{
	close,
	"\0"/*The End of array*/
};
//допоміжна довжина структури
int Length(RtfInsert* insert)
{
	int i = 0;
	while (insert[i].setcol!="\0")// Account of lenth of rtfinsert 
		++i;
	return ++i;
}//допоміжна
 //допоміжна, отримання імя файлу
char* RtfFileName(char**& argv)
{
	char* filename = nullptr;
	const int len_rtf_ext = 4;//довжина розширення файлу
	int len_txtname = strlen(argv[1]);//argv[1]->filename.cpp\0
	int count = 0;
	for (int i = (len_txtname -1); i > 0; --i)
	{
		if (argv[1][i] == '.')
		{
			filename = new char[i + len_rtf_ext]{ '\0' };
			strncpy(filename, argv[1], i);
			break;
		}
		if(i == 1)
		{
			filename = new char[(len_txtname - 1) + len_rtf_ext]{ '\0' };
			strcpy(filename, argv[1]);
			break;
		}
	}
	strcat(filename, ".rtf");
	return filename;
}
//відкриття файлів, перевірка наявності файлу та відповідальність користувача за вже існуючий подібний файл
int OpenFile(FILE*& fpf_rtf, FILE*& fpf_txt, char**& argv)
{
	fopen_s(&fpf_txt, argv[1], "rt");
	if (!fpf_txt)
	{
		printf("\nCan't open file!\n\n");
		return 1;
	}
	else
	{
		printf("\nIf the file exists, it will be rewritten\n");
		printf("\nif you agree with it press 0 and the file will be rewritten\nor\nif you don't agree with it press 1 and rename the source file\n");
		int choise = 1;
		printf("\nYour choice: ");
		scanf("%d",&choise);
		switch (choise)
		{
		case 0:
			fopen_s(&fpf_rtf, RtfFileName(argv), "wt");
			break;
		case 1:
			printf("\nRTF file was not created\n\n");
			return 1;
			break;
		default:
			return 1;
			break;
		}
		return 0;
	}
}
//збереження файлів
void SaveFile(FILE*& fpf_rtf, FILE*& fpf_txt)
{
	fclose(fpf_txt);
	fclose(fpf_rtf);
	fpf_txt = nullptr;
	fpf_rtf = nullptr;
}
//запис Заголовку до RTF файлу (формування структури RTF - {заголовок}-тіло-закінченн)
void WriteHeaderToFile(FILE*& fpf)
{
	int len = Length(header);
	for (int i = 0; i < len; ++i)
	{
		fprintf(fpf,"%s",header[i]);
	}
}
//конвертація існуючого файлу до розмітки RTF та запис до файлу RTF (формування структури RTF - заголовок-{тіло}-закінченн)
void TxtToRtf(FILE*& fpf_rtf, FILE*& fpf_txt)
{
	int c = 0;
	while ((c = getc(fpf_txt)) != EOF)//read from txt
	{
		switch (c)
		{
		case 0x0d: case 0x0a:// cr and lf are characters
			fprintf(fpf_rtf,"%s","\n\\par ");//write to rtf
			break;
		case 0x09:// horisontal tab is characters
			fprintf(fpf_rtf,"%s","\\tab ");//write to rtf
			break;
		case 0x7b:// '{'
			fprintf(fpf_rtf, "%s", "\\{ ");//write to rtf
			break;
		case 0x7d:// '}'
			fprintf(fpf_rtf, "%s", "\\} ");//write to rtf
			break;
		case 0x5c:// '\'
			fprintf(fpf_rtf, "%s", "\\\\");//write to rtf
			break;
		default://other symbols
			if (c != 0x09)
				fprintf(fpf_rtf,"%c", (char)c);//write to rtf
			break;
		}
	}
}
//запис Закінчення до RTF файлу (формування структури RTF - заголовок-тіло-{закінченн})
void WriteFooterToFile(FILE*& fpf)
{
	int len = Length(footer);
	for (int i = 0; i < len; ++i)
	{
		fprintf(fpf, "%s", footer[i]);
	}
}
//створення конвертованого RTF файлу згідно структури
void ConvertTxtToRtf(FILE*& fpf_rtf, FILE*& fpf_txt)
{
	WriteHeaderToFile(fpf_rtf);
	TxtToRtf(fpf_rtf, fpf_txt);
	WriteFooterToFile(fpf_rtf);
}
//запуск процесу конвертації даних
int RunConvert(char**& argv)
{
	FILE* pf_txt_r = nullptr;//read .txt
	FILE* pf_rtf_w = nullptr;//write .rtf
	if (OpenFile(pf_rtf_w, pf_txt_r, argv) == 0)//перевірка
	{
		ConvertTxtToRtf(pf_rtf_w, pf_txt_r);
		SaveFile(pf_rtf_w, pf_txt_r);
		printf("\nRTF file was created\n\n");
		return 0;
	}
	else return 1;
}
int Help()
{
	printf("\nYou should enter for example: Convertor20160519.exe filename.cpp\n");
	printf("\nThe file should have text format and ASCII character set\n");
	printf("\nThe file must have a file extension, like this but not limit *.txt, *.c, *.cpp\n\n");
	return 1;
}
#ifndef _define_h_
#define _define_h_
/*{
	char* setcol;
};*/
struct RtfInsert
{
	char* setcol;
};

extern char open[];
extern char close[];
extern RtfInsert header[];
extern RtfInsert footer[];

char* RtfFileName(char**& argv);
int Length(RtfInsert* insert);
int OpenFile(FILE*& fpf_rtf, FILE*& fpf_txt, char**& argv);
void SaveFile(FILE*& fpf_rtf, FILE*& fpf_txt);
void WriteHeaderToFile(FILE*& fpf);
void TxtToRtf(FILE*& fpf_rtf, FILE*& fpf_txt);
void WriteFooterToFile(FILE*& fpf);
void ConvertTxtToRtf(FILE*& fpf_rtf, FILE*& fpf_txt);
int RunConvert(char**& argv);
int Help();

#endif
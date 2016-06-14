#include <iostream>
#include <ctime>
using namespace std;
int* CrArr(unsigned int f_SIZE);
void ShowArr(int*& f_dyn_arr, unsigned int &f_SIZE);
//void LoadDataBin(int*& f_dyn_arr, unsigned int &f_SIZE);
void SaveDataTxt(int*& f_dyn_arr, unsigned int &f_SIZE);
int main()
{	srand(time(0));
	int* dyn_arr_1 = nullptr;
	unsigned int SIZE = 10;
	//working with an array
	dyn_arr_1 = CrArr(SIZE);//Create
	ShowArr(dyn_arr_1, SIZE);//Show an array
	SaveDataTxt(dyn_arr_1, SIZE);
	//delete[] dyn_arr_2;
	return 0;
}
int* CrArr(unsigned int f_SIZE)
{	int* temp = new int[f_SIZE] {0};
	return temp;
}
void ShowArr(int*& f_dyn_arr, unsigned int &f_SIZE)
{	for (unsigned int i = 0; i < f_SIZE; ++i)
	{cout << " [" << f_dyn_arr[i] << "],";	}
	cout << "\n";
}
//void LoadDataBin(int*& f_dyn_arr, unsigned int &f_SIZE)
//{//	FILE* pf = nullptr;
//	f_dyn_arr = new int[f_SIZE];
//	fopen_s(&pf, "arr.data", "rb");
//	for (unsigned int i = 0; i < f_SIZE; ++i)
//	{fread(&f_dyn_arr[i], sizeof(f_dyn_arr[i]), f_SIZE, pf);//	}
//	fclose(pf);
//	delete pf;
//	pf = nullptr;
//}
void SaveDataTxt(int*& f_dyn_arr, unsigned int &f_SIZE)
{	FILE* pf = nullptr;
 	fopen_s(&pf, "arr.txt", "wt");
	for (unsigned int i = 0; i < f_SIZE; ++i)
	{
		fprintf(pf, " [%d],", f_dyn_arr[i]);
	}
	fclose(pf);
	delete pf;
	pf = nullptr;}




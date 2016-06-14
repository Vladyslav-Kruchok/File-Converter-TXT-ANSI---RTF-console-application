#include <stdio.h>
#include "define.h"


int main(int argc, char* argv[])
{
	if (argc == 2)
		return RunConvert(argv);
	else
		return Help();
}

#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
	int arg1,arg2,res;
	if(argc !=2)
	{
	return -1;
	}
	arg1= atoi(argv[1]);
	arg2= atoi(argv[2]);
	res = arg1+ arg2;
	printf("result: %d",res);
	return 0;
}

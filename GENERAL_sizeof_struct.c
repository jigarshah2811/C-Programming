#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct registers
{
	int intPending;
	float intMasking;
	double status;
	char* devName;
};

int main()
{
	struct registers networkDevReg, *pnetworkDevReg, *temp;
	temp = pnetworkDevReg = &networkDevReg;
	
	networkDevReg.intPending = 0x12345678;
	networkDevReg.intMasking = 3.5;
	networkDevReg.status = 4.55;
	networkDevReg.devName = "Network Device";
	printf("sizeof networkDevReg = %d %d %d %d %d\n", sizeof(int), sizeof(float), sizeof(double), sizeof(networkDevReg.devName), sizeof(networkDevReg));
	temp = pnetworkDevReg++;
	printf("sizeof struct pointer = %x %x\n", sizeof(temp), sizeof(pnetworkDevReg));
	
	return 0;
}

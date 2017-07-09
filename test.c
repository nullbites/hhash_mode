#include <stdio.h>
#include <string.h>

#include "hhash.h"

int main()
{
	unsigned char *message = "Luna is best pony";
	unsigned char digest[32]; //256 bits
	int i, iv = 2048000;
	printf("message = %s\n", message);
//	for(i=0;i<50000;i++)
		hhash_compute(message, digest, strlen(message), iv);
	printf("digest at iv(%d) = ", iv);
	for(i=0;i<32;i++)
	{
		printf("%02x",digest[i]);
	}
	printf("\n");
}

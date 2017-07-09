#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define DIGEST_LEN 32

/* This code is currently for educational purposes only,
it is not permitted to be used in commercial enviroments at this time */

/* the algorithm behind this code is designed to renforce the one-wayedness of 
cryptographic hashes in a "modal" fasion much like how cryptographic modes
renforce the strenght of the algorithm

hhash mode (the h is the first letter of my last name) is an effort to make
hash calculation take more memory. This in theory should degrade the performance
of brute forcing GPU and CPU hashing. 

ALG:

1. perform hash alg(a) on msg(m) (iv) number of times... or is that a nonce? w/e 
2. keep the n0 hash of a(m)*iv, which should be just n0 = a(m), we will use this as a "key"
3. from the IVth hash we generate our h_box
4. the h_box is defined as a matrix of the len (L x L) where L is the digest len
5. the h_box is populated by the subsequent hashes from a(m),IV -> a(m),(IV+L) 
	5.5 (NOTE: the end state of h_box (IV+L) can be modified by a multiplier or a skip value)
6. using the byte of the n0 hash corosponding to the line number of the sbox we mod that value with L+1
7. the value taken from c = n0[x] % L is then used as the value to take from line x of h_box
8. c is then inserted into the x value of the output paramater
9. rinse and repeat until your output is filled
*/

void hhash_compute(unsigned char *in, unsigned char *out, int msg_len, int iv)
{
	int i,j;
	unsigned char n0[DIGEST_LEN];
	unsigned char temp[DIGEST_LEN];
	unsigned char state[DIGEST_LEN];

	unsigned char h_box[DIGEST_LEN][DIGEST_LEN];

	SHA256(in, msg_len, n0); 

	memcpy(temp, n0, DIGEST_LEN);

	for(i=1;i<iv;i++) // index from 1 to compensate for the naught hash
	{
		SHA256(temp,DIGEST_LEN, state);
		memmove(temp, state, DIGEST_LEN); //swap, just to get to the state we need to begin the byte selection
	}
	
	/* fill the hash box with subsiquent hashes*/
	
	for(i=0;i<DIGEST_LEN;i++)
	{
		SHA256(temp,DIGEST_LEN,state);
		memcpy(h_box[i],state,DIGEST_LEN);
		memmove(temp,state,DIGEST_LEN);
	}

	/*for(i=0;i<DIGEST_LEN;i++)
	{
		for(j=0;j<DIGEST_LEN;j++)
		{
			printf("%02x",h_box[i][j]);
		}
		printf("\n");
	}*/

	// any sort of modifications to the box could occur here
	unsigned short int sel_byte;
	for(i=0;i<DIGEST_LEN;i++)
	{
		sel_byte = n0[i] % DIGEST_LEN+1; // to include DIGEST_LENth byte
		out[i] = h_box[i][sel_byte];
	}

	return;
}

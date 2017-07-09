# hhash_mode
an experiment in "modes" for hashing

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
8. h_box[x][c] is then inserted into the output[x]
9. rinse and repeat until your output is filled

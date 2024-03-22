/*
* Simple One-Time Pad implementation. It isn't very random or safe, since it
* uses /dev/random as a source of aleatory bytes.
*/

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

short unsigned
decrypt(char *file_name, char *key_name)
{
 	FILE *fp, *kp;
	char buffer[BUFFER_SIZE];
	char pad_buffer[BUFFER_SIZE];
	char xor_buffer[BUFFER_SIZE];
	short unsigned i, nmemb;
 	
 	fp = fopen(file_name, "rb");
 	kp = fopen(key_name, "rb");

	while ((nmemb = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
		if (fread(pad_buffer, 1, nmemb, kp) == 0) {
			fprintf(stderr, "Error: pad is too small!");
			return 1;
		}
		
		for (i = 0;i < nmemb;i++)
			xor_buffer[i] = buffer[i] ^ pad_buffer[i];
				
		if (fwrite(xor_buffer, 1, nmemb, stdout) == 0)
			return 1;
	}	
	
	return 0;
}

short unsigned
encrypt(char *file_name)
{
	FILE *fp, *random, *kp, *output;
	char buffer[BUFFER_SIZE];
	char pad_buffer[BUFFER_SIZE];
	char xor_buffer[BUFFER_SIZE];
	short unsigned i, nmemb;
	
	fp = fopen(file_name, "rb");
	random = fopen("/dev/random", "rb");
	kp = fopen("key", "wb");
	output = fopen("output_file", "wb");
	
	while ((nmemb = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
		if (fread(pad_buffer, 1, nmemb, random) == 0) {
			fprintf(stderr, "Error: could not read from /dev/random");
			return 1;
		}
		fwrite(pad_buffer, 1, nmemb, kp);
	
		for (i = 0;i < nmemb;i++)
			xor_buffer[i] = buffer[i] ^ pad_buffer[i];

		if (fwrite(xor_buffer, 1, nmemb, output) == 0)
			return 1;
	}	

	return 0;
}

int
main(int argc, char **argv)
{
	if (argc < 3) {
		fprintf(stderr, "Usage: program [-e or -d] [file to encrypt] {key}");
		return 1;
	}	

	if (strcmp("-d", argv[1]) == 0)
		if (decrypt(argv[2], argv[3]) == 0)
			return 0;
		else
			return 1;
	else
		if (encrypt(argv[2]) == 0)
			return 0;
		else
			return 1;
}

#include <float.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_NUM_TYPE 0
#define FORMAT_OPTIONS 11

#define RANDU8 ((uint8_t)rand())
#define RANDI8 ((int8_t)rand())
#define RANDU16 ((uint16_t)rand())
#define RANDI16 ((int16_t)rand())
#define RANDU32 (((uint32_t)rand() << 1) ^ (uint32_t)rand()) /* Hack because rand() max is 2^31 - 1 */
#define RANDI32 (((int32_t)rand() << 1) ^ (int32_t)rand())
#define RANDU64 (((((uint64_t)rand() << 32) | (uint64_t)rand()) << 1) ^ (uint64_t)rand())
#define RANDI64 (((((uint64_t)rand() << 32) | (uint64_t)rand()) << 1) ^ (uint64_t)rand())
#define RANDFLT ((rand() % 2) ? (rand()/(RAND_MAX/FLT_MAX)) : ((rand()/(RAND_MAX/FLT_MAX) * -1)))
#define RANDDBL ((rand() % 2) ? (rand()/(RAND_MAX/DBL_MAX)) : ((rand()/(RAND_MAX/DBL_MAX) * -1)))
#define RANDLDBL ((rand() % 2) ? (rand()/(RAND_MAX/LDBL_MAX)) : ((rand()/(RAND_MAX/LDBL_MAX) * -1)))

struct format {
	char	*input;
	void	(*num_gen)(FILE *);
};

void
randu8(FILE *fp)
{
	fprintf(fp, "\t%"PRIu8"", RANDU8);
}

void
randi8(FILE *fp)
{
	fprintf(fp, "\t%"PRIi8"", RANDI8);
}

void
randu16(FILE *fp)
{
	fprintf(fp, "\t%"PRIu16"", RANDU16);
}

void
randi16(FILE *fp)
{
	fprintf(fp, "\t%"PRIi16"", RANDI16);
}

void
randu32(FILE *fp)
{
	fprintf(fp, "\t%"PRIu32"", RANDU32);
}

void
randi32(FILE *fp)
{
	fprintf(fp, "\t%"PRIi32"", RANDI32);
}

void
randu64(FILE *fp)
{
	fprintf(fp, "\t%"PRIu64"", RANDU64);
}

void
randi64(FILE *fp)
{
	fprintf(fp, "\t%"PRIi64"", RANDI64);
}
 
void
randflt(FILE *fp)
{
	fprintf(fp, "\t%f", RANDFLT);
}

void
randdbl(FILE *fp)
{
	fprintf(fp, "\t%lf", RANDDBL);
}

void
randldbl(FILE *fp)
{
	fprintf(fp, "\t%Lf", RANDLDBL);
}

void
print_usage(void)
{
	puts("format specifiers:");
	puts("int8 -> 8-bit signed integer");
	puts("uint8 -> 8-bit unsigned integer");
	puts("int16 -> 16-bit signed integer");
	puts("uint16 -> 16-bit unsigned integer");
	puts("int32 -> 32-bit signed integer");
	puts("uint32 -> 32-bit unsigned integer");
	puts("int64 -> 64-bit signed integer");
	puts("uint64 -> 64-bit unsigned integer");
	puts("float -> float");
	puts("double -> double");
	puts("longdouble -> long double");
	puts("usage: matrixGen ROWSxCOLUMNS [format_specifier] [output file]");
	exit(EXIT_SUCCESS);
}

void
matrix_gen(FILE *fp, uint64_t rows, uint64_t cols, struct format *fmt)
{
	uint64_t i, j;

	srand(time(NULL));
	for (i = 0;i < rows;i++) {
		for (j = 0;j < cols;j++)
			fmt->num_gen(fp);
		fprintf(fp, "\n");
	}
}

int
main(int argc, char **argv)
{
	struct format fmt_lookup[] = {
		{"int8", &randi8},
		{"uint8", &randu8},
		{"int16", &randi16},
		{"uint16", &randu16},
		{"int32", &randi32},
		{"uint32", &randu32},
		{"int64", &randi64},
		{"uint64", &randu64},
		{"float", &randflt},
		{"double", &randdbl},
		{"longdouble", &randldbl}
	};
	struct format *fmt;
	FILE *fp;
	uint64_t rows, cols;
	int i, is_file;

	if (argc < 2 || argc > 4)
		print_usage();

	sscanf(argv[1], "%" SCNu64 "x%" SCNu64, &rows, &cols);

	for (fp = stdout, fmt = &fmt_lookup[DEFAULT_NUM_TYPE], argc -= 2, argv += 2, is_file = 1; argc > 0; argc--, argv++, is_file = 1) {
		for (i = 0;i < FORMAT_OPTIONS;i++) {
			if (strcmp(*argv, fmt_lookup[i].input) == 0) {
				fmt = &fmt_lookup[i]; 
				is_file = 0;
				break;
			}
		}
		if (is_file)
			fp = fopen(*argv, "w");
	}

	matrix_gen(fp, rows, cols, fmt);
	fclose(fp);

	return 0;
}

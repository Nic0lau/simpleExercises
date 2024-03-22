/* Program to convert a text file with machine code into a
   binary file with the same machine code. Currently supports
   constants with #, includes with ! and labels with : and _. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256
#define STACK_SIZE 16
#define MAX_LABEL_AMNT 128
#define MAX_CONST_AMNT 128

enum {
	LINE_END = -1,
	INCLUDE = -2,
	USE_LABEL = -3,
	CONST = -4,
	CREATE_LABEL = -5
};

struct res_n {
	long	long n;
	int	size;
};
struct node {
	struct	node *next;
	long	long val;
	int	size;
	char	*key;
};

FILE *stack[STACK_SIZE] = {NULL};
static int sp, passes;
static long long unsigned offset;
struct node *labels[MAX_LABEL_AMNT] = {NULL};
struct node *consts[MAX_CONST_AMNT] = {NULL};

long long
power(int n, int exp)
{
	long long j = 1;
	for (;exp > 0;exp--)
		j *= n;
	return j;
}
int
determineSize(int n) {
	int i;
	for (i = 8;i <= 32;i *= 2)
		if (n < power(2, i))
			return i/8;
	return 8;
}
struct res_n
atoh(char *s)
{
	struct res_n n;
	long long x;
	int i, sz, p;
	printf("String: ");
	for (i = 0;isxdigit(s[i]); i++)
		putchar(s[i]);
	puts("");
	for (sz = 0, p = 0, i = 15, x = 0;i >= 0;i--) {
		if (!isxdigit(s[i]))
			continue;
		printf("Num:%lld Letter:%c Index:%d Offset:%llx\n", x, s[i], i, offset);
		x += (isupper(s[i]) ? (s[i] - 'A' + 10) * power(16, p) : 
		     (islower(s[i]) ? (s[i] - 'a' + 10) * power(16, p) : 
		     (s[i] - '0') * power(16, p)));
		sz++;
		p++;
	}
	printf("Num: %lld Size: %d\n", x, sz);
	n.n = x;
	n.size = sz/2;	
	offset += n.size;
	return n;
}
int
hashGen(char *s)
{
	unsigned val;
	for (val = 42069;*s != '\0';s++)
		val = ((val << 5) + val) + *s;
	return val % MAX_LABEL_AMNT;
}
struct node *
nodeSearch(struct node **list, char *key)
{
	struct node *p;
	for (p = list[hashGen(key)];p != NULL;p = p->next)
		if (strcmp(key, p->key) == 0)
			return p;
	return NULL;
}
struct node *
nodeAppend(struct node **list, char *key, long long val, int size) {
	struct node *p;
	int hashVal;
	
	printf("Val: %lld Name: %s\n", val, key);
	if ((p = nodeSearch(list, key)) != NULL) {
		p->val = val;
		p->size = size;
		return p;
	} else {
		p = (struct node *) malloc(sizeof(struct node));
		if (p == NULL || (p->key = strdup(key)) == NULL)
			return NULL;		
		hashVal = hashGen(key);
		p->next = list[hashVal];
		list[hashVal] = p;
 		p->val = val;
 		p->size = size;
 	}
 
	return p;
}
void
copySkippingChars(char *s, char *t, int i)
{
	int j;
        for (j = 0;s[i] != '\0' && s[i] != '\n';i++, j++)
        	t[j] = s[i];
        t[j] = '\0';
}
                        
struct res_n
parseConst(struct node **list, char *s, long long val)
{
	int i = 0, j = 0, p = 0, create = 0, sz = 0;
	char op;
	char name[BUF_SIZE/2] = {'\0'};
	char secondOperand[BUF_SIZE/2] = {'\0'};
	char num[16] = {'\0'};
	long long n, operands[4] = {0};
	struct node *t = NULL;
	struct res_n r;

	if (s[i] == '_')
		create = 1;

	for (;isalnum(s[i+1]) || s[i+1] == '_';i++)
		name[i] = s[i+1];

	op = s[i+1];
	printf("Operation: %x\n", op);

	if ((op == '=' || op == ' ') && create == 0) {
		if (passes == 0) {
			r.size = -1;
			return r;
		}
		if (op == ' ')
			i = -1; // Reading the line from the beggining
		for (i += 2;s[i] != '\0' && s[i] != '\n';i++) {
			printf("First operand char:%c ", s[i]);
			if (isalpha(s[i]) || s[i] == '_') {
				for (j = 0;isalpha(s[i]) || s[i] == '_';i++, j++) {
					secondOperand[j] = s[i];
				}
				if (s[i] == '\0' || s[i] == '\n')
					i--;
				secondOperand[j] = '\0';
				if ((t = nodeSearch(consts, secondOperand)) == NULL) {
					if ((t = nodeSearch(labels, secondOperand)) == NULL) {
				     		r.size = -2;
				     		return r;
				     	} else {
				     		operands[p++] = t->val;
				     	}
				} else {
					operands[p++] = t->val;
				}
			}
			if (isdigit(s[i])) {
				for (j = 0;isdigit(s[i]);i++, j++) {
					num[j] = s[i];
				}
				if (s[i] == '\0' || s[i] == '\n')
					i--;
				num[j] = '\0';
				n = atoll(num);
				operands[p++] = n;
			}	
			switch(s[i]) {
			case '+':
				operands[p-2] = operands[p-2] + operands[p-1];
				p--;
				break;
			case '-':
				operands[p-2] = operands[p-2] - operands[p-1];
				p--;
				break;
			case '*':
				operands[p-2] = operands[p-2] * operands[p-1];
				p--;
				break;
			case '/':
				operands[p-2] = operands[p-2] / operands[p-1];
				p--;
				break;
			case '\\':
				for (j = 0;isdigit(s[i+1]);i++, j++)
					num[j] = s[i+1];
				num[j] = '\0';
				sz = atoll(num);
				break;
			}
		}
		if (sz == 0)
			sz = determineSize(operands[0]);
		if (op == '=') {
			if ((t = nodeAppend(list, name, operands[0], sz)) == NULL)
				r.size = -2;
			else
				r.size = -1;
			printf("Final value: %lld\n", operands[0]);
		} else {
			r.n = operands[0];
			r.size = sz;
			offset += r.size;
			printf("Final value: %lld\n", operands[0]);
		}
	} else if (op == '\n' || op == '\0' || op == '\\') {
		if (op == '\\') {
			for (i += 2, j = 0;isdigit(s[i]);i++, j++)
				num[j] = s[i];
			num[j] = '\0';
			sz = atoll(num);
		}
		if (create == 1) {
			if (sz == 0)
				sz = determineSize(val);
			if ((t = nodeAppend(list, name, val, sz)) == NULL)
				r.size = -2;
			else
				r.size = -1;
		} else if (passes > 0) {
			t = nodeSearch(list, name);
			r.size = t->size;
			r.n = t->val;
			offset += r.size;
		} else {
			r.size = -1;
		}
	} else {
		r.size = -2;
	}

	return r;
}
struct res_n
parse(char *s)
{
	static int p;
	int i = 0;
	struct res_n res;
	char hex_buf[16] = {'\0'};
	for(;p < BUF_SIZE;p++) {
		if (p < 0)
			break;	
		if (!isxdigit(s[p])) {
			if (s[p] == '\0' || s[p] == '\n' || s[p] == ';') {
				p = LINE_END;
			} else if (s[p] == '!') {
				p = INCLUDE-1;
				continue;
			} else if (s[p] == ':'){
				res.n = p;
				p = USE_LABEL-1;
				continue;
			} else if (s[p] == '#'){ 
				res.n = p;
				p = CONST-1;
				continue;
			} else if (s[p] == '_') {
				res.n = p;
				p = CREATE_LABEL-1;
				continue;
			} else {
				p++;
			}
			return atoh(hex_buf);
		}
		hex_buf[i++] = s[p];
	}
	res.size = p;
	p = 0;
	return res;
}

int
main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "Usage: [program] [input file] [output]\n");
		return -1;
	}
	char buf[BUF_SIZE] = {'\0'};
	char buf2[BUF_SIZE] = {'\0'};
	struct res_n hexNum;
	FILE *fpb;
	if ((stack[sp] = fopen(argv[1], "r")) == NULL) {
		perror("Error opening input file:\n");
		return -1;
	}
	if ((fpb = fopen(argv[2], "wb")) == NULL) {
		perror("Error opening output file:\n");
		return -1;
	}
	for (passes = 0;passes < 3;) {
		if (fgets(buf, BUF_SIZE, stack[sp]) == NULL) {
			fclose(stack[sp--]);
			if (sp < 0) {
				passes++;
				sp = 0;
				stack[sp] = fopen(argv[1], "r");
				offset = 0;
			}
			continue;
		}
		for (hexNum = parse(buf);hexNum.size != -1;hexNum = parse(buf)) {
			printf("Pass: %d Code:%d\n", passes, hexNum.size);
			if (hexNum.size == INCLUDE) {
				copySkippingChars(buf, buf2, 1);
				if ((stack[++sp] = fopen(buf2, "r")) == NULL) {
					fprintf(stderr, "Error opening %s at offset %llx\n", buf2, offset);
					return -1;
				}
				break;
			} else if (hexNum.size == USE_LABEL) {
				hexNum = parseConst(labels, buf, offset);
				if (hexNum.size < -1) {
					fprintf(stderr, "Error using label %s at offset %llx\n", buf, offset);
					return -1;
				}
				if (passes == 2) {
					printf("Number: %lld Size: %d\n", hexNum.n, hexNum.size);
					fwrite(&hexNum.n, hexNum.size, 1, fpb);
                                }
                                break;                
			} else if (hexNum.size == CONST) {
				hexNum = parseConst(consts, buf, 0);
				if (hexNum.size < -1) {
					fprintf(stderr, "Error with const %s at offset %llx\n", buf, offset);
					return -1;
				}
				if (hexNum.size == -1)
					break;
				if (passes == 2) {
					printf("Number: %lld Size: %d\n", hexNum.n, hexNum.size);
					fwrite(&hexNum.n, hexNum.size, 1, fpb);
                                }
                                break;			
			} else if (hexNum.size == CREATE_LABEL) {
				hexNum = parseConst(labels, buf, offset);
				if (hexNum.size < -1) {
					fprintf(stderr, "Error creating label %s at offset %llx\n", buf, offset);
					return -1;
				}
				break;
			}
			if (passes == 2) {
				printf("Number: %lld Size: %d\n", hexNum.n, hexNum.size);
				fwrite(&hexNum.n, hexNum.size, 1, fpb);
			}
		}
	}
	fclose(fpb);
	return 0;
}

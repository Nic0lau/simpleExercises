#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lexer.h"

enum parse_status {
	PARSE_STATUS_MISSING_PARENTHESIS,
	PARSE_STATUS_INVALID_EXPONENT,
	PARSE_STATUS_DIVISION_BY_ZERO,
	PARSE_STATUS_INVALID_OPERATOR,
	PARSE_STATUS_INVALID_OPERAND,
	PARSE_STATUS_OK
};

struct parser_cursor {
	struct lexer_cursor *lex_cur;
	struct token *tk;
	enum parse_status status;
};

extern void print_lexer_error(struct lexer_cursor *lc);
extern struct token *get_next_token(struct lexer_cursor *lc);
extern struct token *peek_next_token(struct lexer_cursor *lc);

void print_parser_error(struct parser_cursor *pc);
long double parse_number(struct parser_cursor *pc);
long double parse_parenthesis(struct parser_cursor *pc);
long double parse_power(struct parser_cursor *pc);
long double parse_product(struct parser_cursor *pc);
long double parse_sum(struct parser_cursor *pc);
long double parse_line(char *l);

void
print_parser_error(struct parser_cursor *pc)
{
	print_lexer_error(pc->lex_cur);

	switch (pc->status) {
	case PARSE_STATUS_MISSING_PARENTHESIS:
		fputs("ERROR: Missing parenthesis\n", stderr);
		break;
	case PARSE_STATUS_INVALID_EXPONENT:
		fputs("ERROR: Invalid exponent\n", stderr);
		break;
	case PARSE_STATUS_DIVISION_BY_ZERO:
		fputs("ERROR: Division by zero\n", stderr);
		break;
	case PARSE_STATUS_INVALID_OPERATOR:
		fputs("ERROR: Invalid Operator\n", stderr);
		break;
	case PARSE_STATUS_INVALID_OPERAND:
		fputs("ERROR: Invalid Operand\n", stderr);
		break;
	}
}

long double
parse_number(struct parser_cursor *pc)
{
	long double res;

	pc->tk = get_next_token(pc->lex_cur);

	if (pc->lex_cur->status != TOKEN_STATUS_OK) {
		print_lexer_error(pc->lex_cur);
		return 0;
	}

	if (pc->tk->type != TOKEN_NUMBER) {
		pc->status = PARSE_STATUS_INVALID_OPERAND;
		return 0;
	}

	res = strtold(pc->tk->token, NULL);

	return res;
}

long double
parse_parenthesis(struct parser_cursor *pc)
{
	struct token *tmp;
	long double res;

	tmp = peek_next_token(pc->lex_cur);

	if (tmp->token[0] != '(')
		return parse_number(pc);

	free(pc->tk);
	pc->tk = get_next_token(pc->lex_cur);

	res = parse_sum(pc);

	if (pc->status != PARSE_STATUS_OK)
		return res;

	tmp = peek_next_token(pc->lex_cur);

	if (tmp->token[0] != ')') {
		pc->status = PARSE_STATUS_MISSING_PARENTHESIS;
	} else {
		free(pc->tk);
		pc->tk = get_next_token(pc->lex_cur);
	}

	return res;
}

long double
parse_power(struct parser_cursor *pc)
{
	struct token *op;
	long double res, n;

	res = parse_parenthesis(pc);
	
	if (pc->status != PARSE_STATUS_OK)
		return res;

	op = peek_next_token(pc->lex_cur);

	if (pc->lex_cur->status != TOKEN_STATUS_OK)
		return res;

	if (op->token[0] != '^')
		return res;

	free(pc->tk);
	pc->tk = get_next_token(pc->lex_cur);

	n = parse_power(pc);

	if (n - LDBL_EPSILON < 0 && fabsl(res) < LDBL_EPSILON) {
		pc->status = PARSE_STATUS_INVALID_EXPONENT;
		return res;
	}

	free(op);

	return powl(res, n);
}

long double
parse_product(struct parser_cursor *pc)
{
	struct token *op;
	long double res, n;

	res = parse_power(pc);
	
	if (pc->status != PARSE_STATUS_OK)
		return res;

	while (1) {
		op = peek_next_token(pc->lex_cur);

		if (pc->lex_cur->status != TOKEN_STATUS_OK)
			return res;

		if (op->token[0] != '*' && op->token[0] != '/')
			return res;

		free(op);
		op = get_next_token(pc->lex_cur);

		n = parse_power(pc);

		if (pc->status != PARSE_STATUS_OK)
			return res;

		if (op->token[0] == '/') {
			if (fabsl(n - LDBL_EPSILON) < 0) {
				pc->status = PARSE_STATUS_DIVISION_BY_ZERO;
				return res;
			}
			res /= n;
		} else {
			res *= n;
		}

		free(op);
	}
}


long double
parse_sum(struct parser_cursor *pc)
{
	struct token *op;
	long double res, n;

	res = parse_product(pc);

	if (pc->status != PARSE_STATUS_OK)
		return res;

	while (1) {
		op = peek_next_token(pc->lex_cur);

		if (pc->lex_cur->status != TOKEN_STATUS_OK)
			return res;

		if (op->token[0] != '+' && op->token[0] != '-')
			return res;

		free(op);
		op = get_next_token(pc->lex_cur);

		n = parse_product(pc);

		if (pc->status != PARSE_STATUS_OK)
			return res;

		if (op->token[0] == '-')
			res -= n;
		else
			res += n;

		free(op);
	}
}

long double
parse_line(char *l)
{
	struct parser_cursor *pc;
	struct lexer_cursor *lc;
	long double res;

	if (!(pc = (struct parser_cursor *)calloc(1, sizeof(struct parser_cursor)))) {
		perror("calloc");
		return 0;
	}

	if (!(lc = (struct lexer_cursor *)calloc(1, sizeof(struct lexer_cursor)))) {
		perror("calloc");
		return 0;
	}

	lc->buf = l;
	lc->pos = 0;
	lc->status = TOKEN_STATUS_OK;

	pc->lex_cur = lc;
	pc->status = PARSE_STATUS_OK;

	res = parse_sum(pc);

	if (pc->status != PARSE_STATUS_OK)
		print_parser_error(pc);

	free(pc->lex_cur);
	free(pc);

	return res;
}

int
main(int argc, char **argv)
{
	char buf[BUF_SIZE];
	long double res;

	while (1) {
		memset(buf, '\0', BUF_SIZE);

		printf(">>> ");

		if (!fgets(buf, BUF_SIZE, stdin))
			return -1;

		res = parse_line(buf);

		printf("%Lf\n", res);
	}

	return 0;
}

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

static const char *operators[] = {"+", "-", "*", "/", "^", "&&", "||", "==", "=", "!=", "!", ">=", "<=", ">", "<"};

void
print_token(struct token *tk)
{
	switch (tk->type) {
	case TOKEN_PARENTHESIS:
		printf("Parenthesis, ");
		break;
	case TOKEN_IDENTIFIER:
		printf("Identifier, ");
		break;
	case TOKEN_SEMICOLON:
		printf("Semicolon, ");
		break;
	case TOKEN_OPERATOR:
		printf("Operator, ");
		break;
	case TOKEN_NUMBER:
		printf("Number, ");
		break;
	case TOKEN_END:
		printf("End");
		break;
	default:
		printf("Unknown, ");
		break;
	}

	printf("%s\n", tk->token);
}

void
print_lexer_error(struct lexer_cursor *lc)
{
	size_t start_pos, end_pos, i;

	start_pos = (lc->pos > DELTA_ERR) ? lc->pos - DELTA_ERR : 0;
	end_pos = (lc->pos + DELTA_ERR > (BUF_SIZE - 1)) ? BUF_SIZE - 1 : lc->pos + DELTA_ERR;

	for (i = start_pos; i < end_pos && lc->buf[i] != '\n'; i++) /* Print only around error */
		fputc(lc->buf[i], stderr);
	fputc('\n', stderr);

	for (i = start_pos; i < lc->pos; i++)
		if (lc->buf[i] == '\t')
			fputc('\t', stderr);
		else
			fputc(' ', stderr);

	fputs("^\n", stderr);

	switch (lc->status) {
	case TOKEN_STATUS_TOO_LONG:
		fprintf(stderr, "ERROR: Token too long, the max size is %d.\n The token will be separated in two.\n", MAX_TOKEN_SIZE - 1);
		break;
	case TOKEN_STATUS_UNKNOWN:
		fputs("ERROR: Unknown token that will be skipped.\n", stderr);
		break;
	}
}

struct token *
get_next_token(struct lexer_cursor *lc)
{
	struct token *tk;
	size_t i, j;

	if (!(tk = (struct token *)calloc(1, sizeof(struct token)))) {
		perror("calloc");
		return NULL;
	}

	while (isspace(lc->buf[lc->pos]))
		lc->pos++;

	tk->type = TOKEN_UNKNOWN;

	if (lc->buf[lc->pos] == '\0') {
		tk->type = TOKEN_END;
	} else if (lc->buf[lc->pos] == '(' || lc->buf[lc->pos] == ')') {
		tk->token[0] = lc->buf[lc->pos];
		lc->pos++;
		tk->type = TOKEN_PARENTHESIS;
	} else if (isdigit(lc->buf[lc->pos]) || ((lc->buf[lc->pos] == '+' || lc->buf[lc->pos] == '-') && isdigit(lc->buf[lc->pos + 1]))) {
		i = 0;
		if (!isdigit(lc->buf[lc->pos]))
			tk->token[i++] = lc->buf[lc->pos];
	
		for (; (isdigit(lc->buf[lc->pos + i]) || lc->buf[lc->pos + i] == '.') && i < MAX_TOKEN_SIZE - 1; i++)
			tk->token[i] = lc->buf[lc->pos + i];

			if (isdigit(lc->buf[lc->pos + i]))
				lc->status = TOKEN_STATUS_TOO_LONG;

			lc->pos += i;
			tk->type = TOKEN_NUMBER;
		} else if (isalpha(lc->buf[lc->pos]) || lc->buf[lc->pos] == '_') {
			for (i = 0; (isalnum(lc->buf[lc->pos + i]) || lc->buf[lc->pos + i] == '_') && i < MAX_TOKEN_SIZE - 1; i++)
				tk->token[i] = lc->buf[lc->pos + i];

			if (isalnum(lc->buf[lc->pos + i]) || lc->buf[lc-> pos + i] == '_')
				lc->status = TOKEN_STATUS_TOO_LONG;

			lc->pos += i;
			tk->type = TOKEN_IDENTIFIER;
		} else if (lc->buf[lc->pos] == ';') {
			tk->token[0] = lc->buf[lc->pos];
			lc->pos++;
			tk->type = TOKEN_SEMICOLON;
		} else {
			for (i = 0; i < OPERATOR_AMOUNT; i++) {
				if (lc->buf[lc->pos] == operators[i][0]) {
					if (strlen(operators[i]) != 1)
						if (lc->buf[lc->pos + 1] != operators[i][1])
							continue;

					for (j = 0; j < strlen(operators[i]); j++)
						tk->token[j] = lc->buf[lc->pos + j];
					lc->pos += j;
					tk->type = TOKEN_OPERATOR;
					break;
				}
			}
		}

		if (tk->type == TOKEN_UNKNOWN) {
			lc->status = TOKEN_STATUS_UNKNOWN;
			lc->pos++;
		}

		return tk;
	}

	struct token *
peek_next_token(struct lexer_cursor *lc)
{
	struct token *tk;
	size_t old_pos;

	old_pos = lc->pos;

	tk = get_next_token(lc);
	if (lc->status != TOKEN_STATUS_OK)
		print_lexer_error(lc);

	lc->pos = old_pos;

	return tk;
}

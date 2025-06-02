#ifndef LEXER_HEADER 
#define LEXER_HEADER

#define BUF_SIZE 1024
#define DELTA_ERR 32 /* How far from the error the program will go when reporting it */
#define MAX_TOKEN_SIZE 128 
#define OPERATOR_AMOUNT (sizeof(operators)/sizeof(operators[0]))

enum token_status {
	TOKEN_STATUS_TOO_LONG,
	TOKEN_STATUS_UNKNOWN,
	TOKEN_STATUS_OK
};

enum token_type {
	TOKEN_PARENTHESIS,
	TOKEN_IDENTIFIER,
	TOKEN_SEMICOLON,
	TOKEN_OPERATOR,
	TOKEN_UNKNOWN,
	TOKEN_NUMBER,
	TOKEN_END
};

struct token {
	char 			token[MAX_TOKEN_SIZE];
	enum token_type		type;
};

struct lexer_cursor {
	char 			*buf;
	size_t			pos;
	enum token_status	status;
};


#endif

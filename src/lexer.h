#include <stdio.h>
#include <stdint.h>

typedef enum {
	TOKEN_START,

	TOKEN_ID,

    TOKEN_INT,
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_END,

	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MUL,
	TOKEN_DIV,
	TOKEN_MOD,

	TOKEN_EQUALS,
	TOKEN_DEQUALS,

	TOKEN_LPAREN,
	TOKEN_RPAREN,

	TOKEN_SEMICOLON,
	TOKEN_NEWLINE,

	TOKEN_SQUOTE,
	TOKEN_DQUOTE,

	TOKEN_UNKNOWN
} TokenType;

inline void print_token_type(TokenType type) {
	switch (type) {
		case TOKEN_START: printf("TOKEN_START"); break;
		case TOKEN_ID: printf("TOKEN_ID"); break;
		case TOKEN_INT: printf("TOKEN_INT"); break;
		case TOKEN_IDENTIFIER: printf("TOKEN_IDENTIFIER"); break;
		case TOKEN_KEYWORD: printf("TOKEN_KEYWORD"); break;
		case TOKEN_OPERATOR: printf("TOKEN_OPERATOR"); break;
		case TOKEN_END: printf("TOKEN_END"); break;
		case TOKEN_PLUS: printf("TOKEN_PLUS"); break;
		case TOKEN_MINUS: printf("TOKEN_MINUS"); break;
		case TOKEN_MUL: printf("TOKEN_MUL"); break;
		case TOKEN_DIV: printf("TOKEN_DIV"); break;
		case TOKEN_MOD: printf("TOKEN_MOD"); break;
		case TOKEN_EQUALS: printf("TOKEN_EQUALS"); break;
		case TOKEN_DEQUALS: printf("TOKEN_DEQUALS"); break;
		case TOKEN_LPAREN: printf("TOKEN_LPAREN"); break;
		case TOKEN_RPAREN: printf("TOKEN_RPAREN"); break;
		case TOKEN_SEMICOLON: printf("TOKEN_SEMICOLON"); break;
		case TOKEN_NEWLINE: printf("TOKEN_NEWLINE"); break;
		case TOKEN_SQUOTE: printf("TOKEN_SQUOTE"); break;
		case TOKEN_DQUOTE: printf("TOKEN_DQUOTE"); break;
		case TOKEN_UNKNOWN: printf("TOKEN_UNK"); break;
	}
}

typedef struct {
    TokenType type;
    char* value;
} Token;

typedef struct {
	Token*   tokens;
	uint32_t token_capacity;
	uint32_t token_count;

	uint32_t current_input_idx;
} TokenBuffer;

TokenBuffer* init_token_buffer(uint32_t token_capacity);
void         free_token_buffer(TokenBuffer* buffer);
void         add_token(TokenBuffer* buffer, Token token);
void         print_tokens(const TokenBuffer* buffer);
void		 resize_buffer(TokenBuffer* buffer);
void		 read_buffer(TokenBuffer* buffer, const char* input);
void 		 get_next_token(TokenBuffer* buffer, const char* input);

Token init_token(TokenType type, const char *value);

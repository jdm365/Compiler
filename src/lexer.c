#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "lexer.h"

Token init_token(TokenType type, const char* value) {
	Token token;
	token.type = type;
	token.value = strdup(value);
	return token;
}

void get_next_token(TokenBuffer* buffer, const char* input) {
    while (input[buffer->current_input_idx] && isspace(input[buffer->current_input_idx])) {
		++(buffer->current_input_idx);
    }

	Token new_token = init_token(TOKEN_UNKNOWN, "");
	uint32_t start = buffer->current_input_idx;
	switch (input[buffer->current_input_idx]) {
		case '+':
			++(buffer->current_input_idx);
			new_token = init_token(TOKEN_PLUS, "+");
			break;
		case '-':
			++(buffer->current_input_idx);
			new_token = init_token(TOKEN_MINUS, "-");
			break;
		case '*':
			++(buffer->current_input_idx);
			new_token = init_token(TOKEN_MUL, "*");
			break;
		case '/':
			++(buffer->current_input_idx);
			new_token = init_token(TOKEN_DIV, "/");
			break;
		case '%':
			++(buffer->current_input_idx);
			new_token = init_token(TOKEN_MOD, "%");
			break;
		case '(':
			++(buffer->current_input_idx);
			new_token = init_token(TOKEN_LPAREN, "(");
			break;
		case ')':
			++(buffer->current_input_idx);
			new_token = init_token(TOKEN_RPAREN, ")");
			break;
		case '=':
			++(buffer->current_input_idx);
			if (input[buffer->current_input_idx] == '=') {
				++(buffer->current_input_idx);
				new_token = init_token(TOKEN_DEQUALS, "=");
			} else {
				new_token = init_token(TOKEN_EQUALS, "=");
			}
			break;
		case '\'':
			++(buffer->current_input_idx);
			new_token = init_token(TOKEN_SQUOTE, "'");
			break;
		case '"':
			++(buffer->current_input_idx);
			new_token = init_token(TOKEN_DQUOTE, "\"");
			break;
		case ';':
			++(buffer->current_input_idx);
			new_token = init_token(TOKEN_SEMICOLON, ";");
			break;
		case '\n':
			++(buffer->current_input_idx);
			new_token = init_token(TOKEN_NEWLINE, "\n");
			break;
		case '\0':
			new_token = init_token(TOKEN_END, "\0");
			break;
		case '0' ... '9':
			while (isdigit(input[buffer->current_input_idx])) {
				++(buffer->current_input_idx);
			}
			new_token = init_token(
					TOKEN_INT, 
					strndup(input + start, buffer->current_input_idx - start)
					);
			break;
		default:
			while (isalnum(input[buffer->current_input_idx])) {
				++(buffer->current_input_idx);
			}
			new_token = init_token(
					TOKEN_ID, 
					strndup(input + start, buffer->current_input_idx - start)
					);
			break;
	}

	add_token(buffer, new_token);
}

void read_buffer(TokenBuffer* buffer, const char* input) {
	Token prev_token = init_token(TOKEN_START, "");
	while (prev_token.type != TOKEN_END) {
		get_next_token(buffer, input);
		prev_token = buffer->tokens[buffer->token_count - 1];
	}
}

TokenBuffer* init_token_buffer(uint32_t token_capacity) {
	assert(token_capacity > 0);
	assert(token_capacity < UINT32_MAX);

	TokenBuffer* buffer = malloc(sizeof(TokenBuffer));
	buffer->token_capacity = token_capacity;
	buffer->tokens = malloc(sizeof(Token*) * token_capacity);
	buffer->token_count = 0;
	buffer->current_input_idx = 0;
	return buffer;
}

void free_token_buffer(TokenBuffer* buffer) {
	free(buffer->tokens);
	free(buffer);
}

void add_token(TokenBuffer* buffer, Token token) {
	if (buffer->token_count + 1 >= buffer->token_capacity) {
		resize_buffer(buffer);
	}
	buffer->tokens[buffer->token_count++] = token;
}

void print_tokens(const TokenBuffer* buffer) {
	for (uint32_t i = 0; i < buffer->token_count; i++) {
		uint32_t token_len = strlen(buffer->tokens[i].value);

		printf("Value: %s", buffer->tokens[i].value);
		for (uint32_t j = 0; j < 12 - token_len; j++) {
			printf(" ");
		}
		printf("Type: ");
		print_token_type(buffer->tokens[i].type);
		printf("\n");
	}
}

void resize_buffer(TokenBuffer* buffer) {
	uint32_t new_capacity = buffer->token_capacity * 2;

	assert(new_capacity > 0);
	assert(new_capacity < UINT32_MAX);
	printf("Resizing buffer\n"); fflush(stdout);
	printf("Old capacity: %d\n", buffer->token_capacity); fflush(stdout);
	printf("New capacity: %d\n", new_capacity); fflush(stdout);

	buffer->tokens = realloc(buffer->tokens, sizeof(Token) * new_capacity);
	buffer->token_capacity = new_capacity;
}

#include <stdint.h>

#include "lexer.h"

int main() {
	const char* input = "123 + 456";

	const uint32_t INIT_TOKEN_CAPACITY = 8192;

	TokenBuffer* buffer = init_token_buffer(INIT_TOKEN_CAPACITY);

	read_buffer(buffer, input);

	print_tokens(buffer);

	free_token_buffer(buffer);
	return 0;
}

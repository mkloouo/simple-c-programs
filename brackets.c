#include <unistd.h>

#define BRACKETS_OK "OK"
#define BRACKETS_ERROR "Error"
#define BRACKETS_TABLE_SIZE 4096

#define IS_OPENING_BRACKET(C) (C == '(' || C == '{' || C == '[')
#define IS_CLOSING_BRACKET(C) (C == ')' || C == '}' || C == ']')

#define IS_CURLY(A,B) ((A == '{' && B == '}'))
#define IS_PAREN(A,B) ((A == '(' && B == ')'))
#define IS_SQUARE(A,B) ((A == '[' && B == ']'))

#define IS_SAME_BRACKETS(A,B) (IS_CURLY(A,B) || IS_PAREN(A,B) || IS_SQUARE(A,B))

void print_string(const char* s)
{
	while (*s)
	{
		write(1, s++, 1);
	}
}

int is_valid_cursor_position(char c, int cursor)
{	
	return ((IS_OPENING_BRACKET(c) &&
		 cursor >= BRACKETS_TABLE_SIZE) ||
		(IS_CLOSING_BRACKET(c) && cursor == 0));
}

int is_valid_brackets(const char* s)
{
	char	table[BRACKETS_TABLE_SIZE];
	char	bracket;
	int	cur;

	if (s == 0)
		return (0);
	cur = 0;
	while (*s)
	{
		if (!is_valid_cursor_position(*s, cur))
			return (0);
		if (IS_OPENING_BRACKET(*s))
			table[cur++] = *s;
		else if (IS_CLOSING_BRACKET(*s))
		{
			bracket = table[--cur];
			if (!(IS_SAME_BRACKETS(bracket, *s)))
				return (0);
		}
		++s;
	}
	return (cur == 0);
}

int main(int args_count, char** args)
{
	int i;

	if (args_count == 1)
	{
		print_string("\n");
		return 1;
	}

	i = 1;
	while (i < args_count)
	{
		if (is_valid_brackets(args[i]))
			print_string(BRACKETS_OK "\n");
		else
			print_string(BRACKETS_ERROR "\n");
		++i;
	}
	return 0;
}

#define FTST_MAIN_FILE
#include "ftst.h"
#include <stdlib.h>
#include "../libft_old/libft.h"

TEST(ft_atoi)
{
	EQ(ft_atoi("-------++---42"), 0);
	EQ(ft_atoi("000000000000000000000042"), 42);
}

TEST(ft_strnstr)
{
	STR_EQ(ft_strnstr("000000123", "123", 9), "123");
}

TEST(ft_split)
{
	char **splited;
	char *description;

	description = "checking split with a string containing only delimiters | expected array of pointers with one element pointing to NULL";
	splited = ft_split("    ", ' ');
	NE(splited, NULL, p, EXPECT, description);
	if (splited) EQ(*splited, NULL, p, EXPECT, description);

	description = "checking split with empty string | expected array of pointers with one element pointing to NULL";
	splited = ft_split("", ' ');
	NE(splited, NULL, p, EXPECT, description);
	if (splited) EQ(*splited, NULL, p, EXPECT, description);

	description = "checking split with string and \\0 as delimiter";
	splited = ft_split("Hello, world!", '\0');
	NE(splited, NULL, p EXPECT, description);
	if (splited) NE(*splited, NULL, p EXPECT, description);
	if (splited && *splited) STR_EQ(*splited, "Hello, world!", EXPECT, description);

	description = "checking split with empty string and \\0 as delimiter | expected array of pointers with one element pointing to NULL";
	splited = ft_split("Hello, world!", '\0');
	NE(splited, NULL, p, EXPECT, description);
	if (splited) NE(*splited, NULL, p, EXPECT, description);
	if (splited) STR_EQ(*splited, "Hello, world!", EXPECT, description);

#if FTST_MALLOC_TEST
	LEAK_RESET();
	MALLOC_COUNTER_SET(3);

	EQ(ft_split("a b c d", ' '), NULL, p);

	IS_FALSE(LEAKS());
	MALLOC_CLEAN();
#endif
}

TEST(ft_substr)
{
	char *t;
	STR_EQ(t = ft_substr("1 2 3... RUN!", 9, 4), "RUN!"); free(t);
	STR_EQ(t = ft_substr("test", 1, 8), "est"); free(t);
	STR_EQ(t = ft_substr("HelloCat", 15, 3), "", EXPECT, "expected empty string. it is stupid, but fact :("); free(t);
}

TEST(ft_strtrim)
{
	char *t;
	STR_EQ(t = ft_strtrim("", " "), ""); free(t);
	STR_EQ(t = ft_strtrim("", ""), ""); free(t);
	STR_EQ(t = ft_strtrim("*@****@**A**A***@*", "*@"), "A**A"); free(t);
	STR_EQ(t = ft_strtrim("*@****@**A**A***@*", "*@"), "A**A"); free(t);
	STR_EQ(t = ft_strtrim("*@*..****@**@**....B....***@****..*@***", ".*@"), "B"); free(t);
	STR_EQ(t = ft_strtrim("*@****@*******@*C", "*@"), "C"); free(t);
	STR_EQ(t = ft_strtrim("D", "0123456789"), "D"); free(t);
}

char	ft_strmapi_test(unsigned int i, char c)
{
	return c + (i % 2);
}

TEST(ft_strmapi)
{
	char *t;
	STR_EQ(t = ft_strmapi("", ft_strmapi_test), ""); free(t);
}

int main()
{
	FTST_INIT(stdout);

	RUNTEST(ft_atoi);
	RUNTEST(ft_strnstr);
	RUNTEST(ft_split);
	RUNTEST(ft_substr);
	RUNTEST(ft_strtrim);
	RUNTEST(ft_strmapi);

	return FTST_EXIT();
}

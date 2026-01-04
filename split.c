#include "minishell.h"
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;
	int		size;

	size = 0;
	i = 0;
	while (s1[size])
		size++;
	ptr = (char *)malloc(size + 1);
	if (!ptr)
		return (0);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = (char *)malloc((len * sizeof(char)) + 1);
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[len] = '\0';
	return (str);
}

int	is_separator(char c, t_quotes quote)
{
	if (c == ' ' && quote == NOT_IN_QUOTES)
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == 32 || c == '\n' || c == '\t')
		return (1);
	else
		return (0);
}

static char	*extract_arg(const char *str, int *i)
{
	t_quotes	status;
	int			start;

	start = *i;
	status = NOT_IN_QUOTES;
	while (str[*i])
	{
		if (str[*i] == '\'' && status == NOT_IN_QUOTES)
			status = IN_SINGLE_QUOTES;
		else if (str[*i] == '\'' && status == IN_SINGLE_QUOTES)
			status = NOT_IN_QUOTES;
		else if (str[*i] == '"' && status == NOT_IN_QUOTES)
			status = IN_DOUBLE_QUOTES;
		else if (str[*i] == '"' && status == IN_DOUBLE_QUOTES)
			status = NOT_IN_QUOTES;
		else if (is_separator(str[*i], status))
			break;
		(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

static int	args_counter(char *str)
{
	int			i;
	int			count;
	t_quotes	status;

	i = 0;
	count = 0;
	status = NOT_IN_QUOTES;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		count++;
		while (str[i])
		{
			if (str[i] == '\'' && status == NOT_IN_QUOTES)
				status = IN_SINGLE_QUOTES;
            else if (str[i] == '\'' && status == IN_SINGLE_QUOTES)
                status = NOT_IN_QUOTES;
            else if (str[i] == '"' && status == NOT_IN_QUOTES)
                status = IN_DOUBLE_QUOTES;
            else if (str[i] == '"' && status == IN_DOUBLE_QUOTES)
                status = NOT_IN_QUOTES;
            else if (is_separator(str[i], status))
                break;
			i++;
		}
	}
	return (count);
}

char	**lexer_split(char *str)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char *) * (args_counter(str) + 1));
	if (!result)
		return (NULL);
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		result[j++] = extract_arg(str, &i);
	}
	result[j] = NULL;
	return (result);
}
char	*remove_quotes(char *str)
{
	int		i;
	char	*res;
	int		j;

	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"' || str[i] != '\'')
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

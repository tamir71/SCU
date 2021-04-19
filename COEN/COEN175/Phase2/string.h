/*
 * File:	string.h
 *
 * Description:	This file contains the function declarations for parsing
 *		and escaping C-style escape sequences in strings.
 */

# ifndef STRING_H
# define STRING_H
# include <string>

std::string parseString(const std::string &s);
std::string parseString(const std::string &s, bool &invalid, bool &overflow);
std::string escapeString(const std::string &s);

# endif /* STRING_H */

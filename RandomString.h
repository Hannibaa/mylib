#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <random>

//--------- RANDOM FORMULAS FOR ANY TYPE OF STRING OR CSTRING ----------------------
//       ENTER THIS FORMULAS AS REMPLACEMENT LATTER 'X' FOR PHONE NUMBER OR
//       ENTER '_' FOR ALPHABET LOWERCASE AND '-' FOR UPPER CASE
//       EXEMPLE : "XXX-XXX-XX4, REMPLACE ALL X BY RANDOM NUMBER
//                 "A___---S" REMPLACE ALL '-' BY ALPHABET UPPERCASE
//                      AND '_' LOWER CASE.

// todo  UNVALIDE CODE THAT MIXED C WITH C++ 
//           *** USING RANDOM TIME MIXED WITH RANDOM PURE C PROGRAM 
// 

char* RandomCString(const char* formula) // 
{
	std::random_device rd{};
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> rNum{ 0 , 1000 };

	int i = 0;
	int len = strlen(formula);
	char* str = new char[len];

	while (formula[i] != '\0')
	{

		switch (formula[i])
		{
		case 'X': str[i] = rNum(gen) % 10 + 48;
			break;

		case '_': str[i] = rNum(gen) % 26 + 97;
			break;

		case '-':str[i] = rNum(gen) % 26 + 65;
			break;
		default:
			str[i] = formula[i];
			break;

		}
		++i;
	}
	str[len] = '\0';
	return str;
}

const char* randstring(int length)  // 'a' = 97, 'z' = 122;
{
	std::random_device rd{};
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> rNum{ 0 , 1000 };

	if (length > 20 || length < 1)
	{
		std::cout << "No Acceptable length;  > 0 or =< 20\n";
		const char* str = "No Acceptable length;  > 0 or =< 20";
		return str;
	}

	char* str = new char[length + 1];

	for (int i = 0; i < length; i++) str[i] = 97 + rNum(gen) % 26;
	str[length] = '\0';
	return str;
}
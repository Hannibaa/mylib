#pragma once

// ############################# FUNCTION 1 #########################
//------------- CHECK IF PARENTHESIS IS OPEN OR CLOSE ---------------
//-------------- RETURN 1 IF CLOSED OR 0 IF IT OPEN -----------------
//-----2 First Parenthesis is Closed 3-- More Closed Parenthesis ----

int Parenthesis(string& s, char OpenParenthesis, char CloseParenthesis)
{

	int n = 0;
	int I = 0;
	int i;
	// Use C++ string 

	for (i = 0; i < s.length(); i++)
	{
		if (s[i] == OpenParenthesis) {
			n += 1; I++; continue;
		}

		if (s[i] == CloseParenthesis) {
			n += -1; I++;
		}
		if (s[i] == CloseParenthesis && I == 1) return 2;
	}

	if (I == 0) { return -1; }
	if (n == 0) { return 1; }
	else { if (n > 0) return 0; else return 3; }

 }

// ############################# FUNCTION 2 ##################################
// ------------------------- VALIDE PARENTHESIS ------------------------------
// 

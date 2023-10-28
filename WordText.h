#pragma once
#include <string.h>
#include <ctype.h>


//------------------------------ FUNCTION 0 --------------------------------------
//---------- CHECK STRING IF ITS A MIRROR RETURN TRUE OR FALSE -------------------
// 1 PERFECT MIRROR STRING EXP " ABCCBA "
// -1 IMPERFECT MIRROR STRING EXP " ABCBA "
// 0 NOT MIRROR

int IsMirror(char* s)
{
	int l = strlen(s);
	int k = 0;

	for (int i = 0; i < l / 2; i++)
		if (tolower(s[i]) == tolower(s[l - i - 1])) k++;

	if (k == l / 2) { if (l % 2 == 0) return 1; else return -1; }
	return 0;
}


//-------------------------- FUNCTION 1 -------------------------------------
//---------- MIRRORITY IS NUMBER OF SYMETRIC CHARACTER BY REFERENCE ---------
//------------------------ CENTER OF WORD------------------------------------

int Mirrority(char* s)
{
	int l = strlen(s);
	int k = 0;

	for (int i = 0; i < l / 2; i++)
		if (tolower(s[i]) == tolower(s[l - i - 1])) k++;
	return k;
}


//--------------------- FUNCTION 2 ------------------------
// -------CALCULATE FREQUENCY OF CHAR C IN STRING S -------
//----------- UPPPER AND LOWER CHAR ARE SAME --------------

int freqchar(char* s, char c)
{
	int i = 0;
	do
	{
		if (*s == toupper(c) || *s == tolower(c)) i++;
	} while (*s++ != '\0');
	return i;
}

//--------------------- FUNCTION 3 ------------------------
//-- CALCULATE NUMBER OF PRESENCE OF CHAR C IN STRING S ---
//----------- UPPPER AND LOWER CHAR NOT SAME --------------

int charinstr(char* s, char c)
{
	int i = 0;
	do
	{
		if (*s == c) i++;
	} while (*s++ != '\0');
	return i;
}


// ----------------------- FUNCTION 4 -------------------------------------
// ---- COMPAR TWO STRING RESPECT ORDER AND RETURN THE RESULT -------------
// ----------- IN STRING AS SET OF CHAR WITH REPITITION -------------------
// ---- RETURN INT OF NUMBER OF SET INTERSECTION WITH REPITITION ----------

int comparestr(char* s, char* c, char* result)
{
	int i = 0;
	int j = 0, k = 0;

	while (s[i] != '\0')
	{
		while (c[j] != '\0')
		{
			if (tolower(s[i]) == tolower(c[j]) )
			{
				result[k] = s[i];
				k++;
			}
			j++;
		}
		j = 0;
		i++;
	}

	result[k] = '\0';
	return k;
}


// -------------  FUNCTION 5 ------------------------------
// ------- PUT TITLE IN BOX TABLE -------------------------
// --------------------------------------------------------
void titlebox(char* c)
{
	int L_up_corner = 201;
	int R_up_corner = 187;
	int L_dn_corner = 200, R_dn_corner = 188;
	int h_Line = 205, vLine = 186;
	int i = strlen(c);

	printf("%c", L_up_corner);
	for (int j = 0; j < i + 1; j++)printf("%c", h_Line);
	printf("%c\n", R_up_corner);

	printf("%c%s %c\n", vLine, c, vLine);


	printf("%c", L_dn_corner);
	for (int j = 0; j < i + 1; j++)printf("%c", h_Line);
	printf("%c\n", R_dn_corner);

}
//---------------------------------------------------------------------------

//-------------  FUNCTION 6 -------------------------------------------------
// put them in string array W[][], REMOVE ONLY BLANCK SPACE -----------------

int wordofstring1(const char* c, char W[12][15])
{
	int i = 0, j = 0, b = 0;
	char* s; s = c;
	do
	{
		if (*s == ' ')
		{
			b++;
			if (*(s + 1) != ' ')
			{
				if (j != 0)
				{
					W[i][j] = '\0'; j = 0; i++;
				}
			}
		}
		else
		{
			W[i][j] = *s;
			j++;
		}

	} while (*(s++) != '\0');
	if (W[i][0] == '\0') i = i - 1;
	return i;
}
//-------------------- FUNCTION 7 -----------------------------------------------------------
// best version of extraction word from string or text and put it in word array--------------

int wordofstr(const char* c, char w[12][15])
{
	char ch;
	char* s;
	int b;
	int i = 0, j = 0;


	//extract only word with alphabet;
	s = c;
	while (*s != '\0')
	{
		b = 0;
		for (ch = 65; ch < 91; ch++)
		{
			if ((*s == ch) || (*s == (ch + 32)))
			{
				w[i][j] = *s; j++; b = 1; break;
			}
		}

		if (b == 0) {
			if (j == 0)
			{
				j = 0;
			}
			else {
				w[i][j] = '\0';
				i++;
				j = 0;
			}
		}


		s++;
	}
	w[i][j] = '\0';
	if (w[i][0] == '\0') i--;
	return i;
}
//----------------------- FUNCTION 8 -----------------------------------
// REPETITION OF PRINTED CHARACTER IN STRING ---------------------------
repcharstr(char* s)
{
	char c;
	int k = 0;
	int r = 0;

	for (c = 32; c < 127; c++)
	{

		while (s[k] != '\0')
		{
			if (s[k] == c) r++;
			k++;
		}
		if (r != 0) printf("repetition of\t [%c] : [%d]\n", c, r);
		r = 0; k = 0;
	}
}


//----------------------------- FUNCTION 9 ----------------------------------------
//--------------------REVERSING STRING OF CHARACTER -------------------------------
void reverstr(char* s)
{
	int l = 0;
	char sw;
	while (s[l] != '\0') l++;
	for (int i = 0; i < l / 2; i++)
	{
		sw = s[i];
		s[i] = s[l - i - 1];
		s[l - i - 1] = sw;
	}
}

// ----------------------- FUNCTION 10 ---------------------------------
// ------ CHECK TWO STRING IF IS ANAGRAM 'SOME SET OF CONSTITUTION -----
// ------------------- CHAR WITHout FREQUENCY --------------------------
// ------------- RETURN 0 IF NOT AND 1 IS YES ANAGRAM ------------------

int AreAnagram1(char* s, char* t)
{
	int k;

	for (int i = 0; i < strlen(s); i++)
	{
		if (!isalnum(s[i])) continue;
		k = 0;
		for (int j = 0; j < strlen(t); j++)
		{
			if (!isalnum(s[i])) continue;
			if (tolower(s[i]) == tolower(t[j])) { k++; break; }
		}
		if (k == 0) return 0;
	}


	for (int i = 0; i < strlen(t); i++)
	{
		if (!isalnum(t[i])) continue;
		k = 0;
		for (int j = 0; j < strlen(s); j++)
		{
			if (!isalnum(s[j])) continue;
			if (tolower(t[i]) == tolower(s[j])) { k++; break; }
		}
		if (k == 0) return 0;
	}

	return 1;
}

// ----------------------- FUNCTION 11 ---------------------------------
// ------ CHECK TWO STRING IF IS ANAGRAM 'SOME SET OF CONSTITUTION -----
// ------------------- CHAR WITH FREQUENCY -----------------------------
// ------------- RETURN 0 IF NOT AND 1 IS YES ANAGRAM ------------------

int AreAnagram(char* s, char* t)
{
	if (!AreAnagram1(s, t)) return 0;
	int f1, f2;
	for (int i = 0; i < strlen(s); i++)
	{
		if (!isalnum(s[i])) continue;
		f1 = freqchar(s, s[i]); f2 = freqchar(t, s[i]);
		//printf(" s[ %d ] = [ %c ] , freq s = [%d] , freq t = [%d]\n", i, s[i], f1, f2);
		if (f1 != f2) return 0;
	}

	return 1;
}

//------------------------- FUNCTION 12 -------------------------------------
//---------------- NUMBER OF ALPHABET IN STRING -----------------------------
//--------------- RETURN TOTAL NUMBER OF STRING -----------------------------
int numalpha(char* s)
{
	int k = 0;
	for (int i = 0; s[i] != '\0'; i++)
		if (isalpha(s[i])) k++;
	return k;
}

//--------------------------- FUNCTION 13 -----------------------------------
//--------------- CHECK TWO STRING IS ISOMORPHISME --------------------------
//----------------- RETURN 1 IF THRU 0 OTHERWISE ----------------------------
int AreIsomorph(char* s, char* t)
{
	// should two string have the same number of alphabet (lowercase all)
	int a[50], b[50];
	int k = 0, m = 0;
	for (int i = 0; i < 50; i++) { a[i] = -1; b[i] = -1; }

	if (numalpha(s) != numalpha(t)) return 0;

	// Check first string 

	for (int i = 0; s[i] != '\0'; i++)
	{
		if (a[i] != -1) continue;
		for (int j = i; s[j] != '\0'; j++)
			if (s[i] == s[j])  a[j] = k;
		
		k++;
	}

	// Check string in mapping b[] 
    // loop of comparaison of mapp a[] and b[]
	k = 0;
	for (int i = 0; t[i] != '\0'; i++)
	{
		if (b[i] != -1) continue;
		for (int j = i; t[j] != '\0'; j++)
			if (t[i] == t[j])  b[j] = k;
		if (a[i] != b[i]) return 0;
		k++;
	}

	
	/*

	for (int i = 0; s[i] != '\0'; i++)
	{
		printf(" %c - %i-> %d  %c --> %d\n", s[i], i, a[i], t[i], b[i]);
		if (a[i] != b[i]) return 0;
	}*/

	return 1;
}


//------------------------- FUNCTION 14 ----------------------------------------------------
// Longest Succession of valide alphabat substring in string
//------------------------------------------------------------------------------------------

int Longest_Succ_Alphabet(char* s)
{
	int k_last = 1;
	int i = 0, k = 0;

	while (s[i] != '\0')
	{
		while (s[k + i] == s[i] + k) {
			printf(" %c", s[k + i]); k++;
		}
		printf("\n");
		i = i + k;
		if (k_last < k) k_last = k;
		k = 0;
	}

	return k_last;
}

//------------------------- FUNCTION 14 ----------------------------------------------------
// Longest Succession of valide alphabat substring in string
//------------------------------------------------------------------------------------------

int isAnagram(char* s, char* t)
{
	if (strlen(s) != strlen(t)) return 0;
    printf("Start --------------------\n");
	int i = 0, j = 0; 
	while (s[i] != '\0')
	{
		while (s[i] != t[j] && t[j] != '\0') j++;
		if (t[j] == '\0') return 0;
		t[j] = ' ';
		printf(" %s\n", t);
		j = 0;
		i++;
	}
	return 1;
}

int Is_Anagram(char* s, char* t)
{
	int tab[26] = { 0 };
	while (*s) tab[*(s++) - 'a']++;
	while (*t) tab[*(t++) - 'a']--;
	for (int i = 0; i < 26; i++) if (tab[i] != 0) return 0;
	return 1;
}


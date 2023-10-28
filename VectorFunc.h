#pragma once
#include <vector>
using namespace std;

//-------------- MAXIMUM FUNCTION -------------------------
int max(vector<int>  w)
{
	int m = w.at(0);

	for (int i = 0; i < w.size(); i++)
		if (w.at(i) > m) m = w.at(i);
	return m;
}

//---------------- MINIMUM FUNCTION ------------------------
int min(vector<int>  w)
{
	int m = w.at(0);

	for (int i = 0; i < w.size(); i++)
		if (w.at(i) < m) m = w.at(i);
	return m;
}

//------------------ K'TH MAXIMUM FUNCTION ------------------
int maxkth(vector<int> v, int k)
{
	if (k >= v.size() || k == 0) return -1; //check 

	int Max = 0;
	int  I;
	for (int j = 0; j < k; j++)
	{
		Max = 0;
		for (int i = j; i < v.size(); i++)
		{
			if (v.at(i) > Max) {
				Max = v.at(i);
				I = i;
			}

		}
		v.at(I) = v.at(j);
		v.at(j) = Max;
	}

	return Max;
}

//------------------ K'TH MINIMUM FUNCTION ------------------
int minkth(vector<int> v, int k)
{
	if (k >= v.size() || k == 0) return -1;

	int Max = 0;
	int  I;
	for (int j = 0; j < k; j++)
	{
		Max = v.at(j);
		for (int i = j; i < v.size(); i++)
		{
			if (v.at(i) <= Max) {
				Max = v.at(i);
				I = i;
			}

		}
		v.at(I) = v.at(j);
		v.at(j) = Max;
	}

	return Max;
}

//------------------- SORT K'TH ELEMENT MAX -------------------------------
bool sortkth(vector<int>& v, int k)
{
	if ( k <= 0) return false; //check 
	if (k >= v.size()) k = v.size() - 1;

	int Max = 0;
	int  I;
	for (int j = 0; j < k; j++)
	{
		Max = 0;
		for (int i = j; i < v.size(); i++)
		{
			if (v.at(i) > Max) {
				Max = v.at(i);
				I = i;
			}

		}
		v.at(I) = v.at(j);
		v.at(j) = Max;
	}

	return true ;
}
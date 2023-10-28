#pragma once
#include <string>
#include <stringfunctionhelper.h>

namespace Excel {

	const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const std::string NUMBER   = "0123456789";

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    Function to Convert a title alphabetic to number so A10 = {1,10} = {0,9}in matrix 
	//    1. convertToTitle(int)
	//    2. titleToNumber(string)
	//    3. is it Exel coordinate
	//    4. convertToExcelCoord();
	//    5. random generator of Excel Coordinate
	// 
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string getRandomExcelCoord(short lengthX, short lengthY) {

		auto Xstr = Str::getRandomString(ALPHABET.c_str(), lengthX);
		auto Ystr = Str::getRandomString(NUMBER.c_str(), lengthY);

		return Xstr + Ystr;
	}

	std::string convertToTitle(int n) {
		std::string temp;

		if (n == 0) temp.push_back(' ');

		while (n != 0)
		{
			int digit = n % 26;

			if (digit == 0) digit = 26;

			temp.insert(0, 1, char(digit + 64));

			n = (n - digit) / 26;
		}

		return temp;
	}

	int titleToNumber(std::string str) {

		int n = 0;
		for (int i = 0; i < str.size() - 1; i++)
		{
			n = 26 * (n + (int(str[i]) - 64));
		}

		return n + int(str[str.size() - 1] - 64);
	}

	// Get Excel coordinate in pair separated {xstr,ystr}
	auto getExcelCoord(const std::string& str) {

		std::string Xstr;
		std::string Ystr;

		size_t pos = str.find_first_of(NUMBER);
		if (pos != str.npos) {
		       Xstr = str.substr(0, pos);
		       Ystr = str.substr(pos);
		}
		else {
			Xstr = str;
			Ystr = "";
		}

		Ystr = Str::removeUnusefullCharBiginning(Ystr);

		return std::make_pair(Xstr, Ystr);
	}

	// Check if xstr is verified excel coordinate, and also with ystr
	bool isXcoord(const std::string& xstr) {

		if (xstr == "") return false;

		if (xstr.find_first_not_of(ALPHABET) == xstr.npos) {
			
			return true;
		}

		return false;
	}

	// Check if ystr is coordinate for excel
	bool isYcoord(const std::string& ystr) {

		if (ystr == "") return false;

		if (ystr.find_first_not_of(NUMBER) == ystr.npos) return true;

		return false;
	}

	// Check if stringCoordinate is Excel valide coordinate
	bool isExcelCoord(const std::string& _strcoord) {

		std::string strcoord = _strcoord;

		if(strcoord[0] == ' ') Str::removeBlank(strcoord);

		if (ALPHABET.find_first_of(strcoord[0]) == strcoord.npos) return false;

		if (strcoord.find_first_not_of(ALPHABET + NUMBER) != strcoord.npos) return false;

		auto coord = getExcelCoord(strcoord);

		return isXcoord(coord.first) && isYcoord(coord.second);
	}

	auto convertExcelToCtype(const std::string& exlCoord) {

		auto exl = getExcelCoord(exlCoord);

		auto X = titleToNumber(exl.first) - 1;
		auto Y = std::atoi(exl.second.c_str()) - 1;

		return std::make_pair(X, Y);
	}
	
}

#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <MyLib/Console_Library/escape_code.h>

//#include <MyLib/chrono/to_day.h>
// make macro to construct 7 cell :

using uint = unsigned int;

namespace chr = std::chrono;

namespace Calendar {

	char DAYNAME[] = { 'M','T','W','T','F','S','S' };

	std::string DAYNAME2[] = { "Mo","Tu","We","Th","Fr","Sa","Su" };
	std::string DAYNAME3[] = { "Mon","Tue","Wed","Thu","Fri","Sat","Sun" };
	std::string _DAYNAME[] = { "Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday" };

	//

	constexpr int day_index(int day, int index) {
		return 8 - (day + 7 - index) % 7;
	}

	std::tuple<std::string, std::string, int> _MONTHS[] = {
		{"Jan","January",31},{"Feb","February",28}, {"Mar","March",31},{"Apr","April",30},
		{"May","May",31},{"Jun","June",30},{"Jul","July",31},{"Aug","August",31},
		{"Sep","September",31},{"Oct","October",31},{"Nov","November",30},{"Dec","December",31}
	};

	std::pair<std::string, int> MONTHS[] = {
		{"Jan",31},{"Feb",28}, {"Mar",31},{"Apr",30},{"May",31},{"Jun",30},{"Jul",31},{"Aug",31},
		{"Sep",31},{"Oct",31},{"Nov",30},{"Dec",31}
	};

	void makeDays(const char* str) {

		for (int i = 0; i < 7; ++i)
		{
			std::cout << CELL(2, right, str[i]);
			std::cout << SPACE(3);
		}
		newline_;
	}

	std::string makeDaysString(const char* str) {
		std::stringstream _str;
		for (int i = 0; i < 7; ++i)
		{
			_str << CELL(2, right, str[i]);
			_str << SPACE(3);
		}
		_str << '\n';
		return _str.str();
	}

	void putNumber(int start, int num, int today) {

		for (int i = 1; i < num + start; ++i)
		{
			if (i < start) {
				std::cout << CELL(2, right, " ");
				std::cout << SPACE(3);
			}
			else {
				if (today == i - start + 1)
					std::cout << YELLOW_BG << BLACK_FG << CELL(2, right, i - start + 1) << RESETMODE;
				else
					std::cout << CELL(2, right, i - start + 1);
				std::cout << SPACE(3);
			}

			if (i % 7 == 0) newline_;
		}

	}

	std::string putNumberInString(int start, int num, int today) {

		std::stringstream str;

		for (int i = 1; i < num + start; ++i)
		{
			if (i < start) {
				str << CELL(2, right, " ");
				str << SPACE(3);
			}
			else {
				if (today == i - start + 1)
					str << YELLOW_BG << BLACK_FG << CELL(2, right, i - start + 1) << RESETMODE;
				else
					str << CELL(2, right, i - start + 1);
				str << SPACE(3);
			}

			if (i % 7 == 0) str << '\n';
		}

		return str.str();
	}

	void Month(int month, int start, int today) {
		month = month - 1;
		std::cout << YELLOW_BG << BLACK_FG;
		std::cout << MONTHS[month].first << SPACE(29) << RESETMODE;
		newline_;
		makeDays(DAYNAME);
		putNumber(start, MONTHS[month].second, today);
		newline_;
	}

	// we goint to print all these thing in stream string matrix;
	// after we distubiting as we like 

	std::string MonthInString(int month, int start, int today) {
		month = month - 1;
		std::stringstream str;

		str << YELLOW_BG << BLACK_FG;
		str << MONTHS[month].first << SPACE(29) << RESETMODE;
		str << '\n';
		str << makeDaysString(DAYNAME);
		str << putNumberInString(start, MONTHS[month].second, today);
		str << '\n';

		return str.str();
	}

	auto putTextInLineStrings(const std::string& text) {

		if (text.empty()) return std::vector<std::string>{};

		size_t t1{}, t2{};
		std::vector<std::string> vString;

		while (true) {
			t2 = text.find('\n', t1);

			vString.push_back(text.substr(t1, t2 - t1));
			t1 = t2 + 1;
			if (t2 == text.npos || t1 == text.size()) break;
		}

		return vString;
	}

	bool isFullSpaceString(const std::string& str) {

		if (str.empty()) return true;

		for (auto& c : str)
			if (!std::isblank(c)) return false;

		return true;
	}

	void resizeVecString(std::vector<std::string>& vString, int new_size) {

		for (auto& str : vString) str.resize(new_size);

	}

	void PrintMonthAt(int x, int y, const std::vector<std::string>& vStr) {

		for (int i = 0; i < vStr.size(); ++i) {
			std::cout << MOVETO(x, y + i) << vStr[i];
		}
	}

	void ThisMonth(std::chrono::year_month_day ymd) {
         
		std::chrono::sys_days sd = std::chrono::sys_days(ymd);
		std::chrono::year_month_weekday ymwd = std::chrono::sys_days(sd);

		uint d =uint( ymd.day());
		uint index = uint(ymwd.index());

		uint val = 8 - (d + 7 - index) % 7;

		Month(uint(ymd.month()), val, uint(ymd.day()));

	}

	// FUNCTION INDEX OF DAY NUMBER 1 OF MONTH AND YEAR

	int day_one(chr::month m, chr::year y) {
		return {};
	}

	int day_one(chr::year y) {
		return day_one(chr::January, y);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//                  YEAR CALENDER
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	void makeMonths() {

		for (int i = 0; i < 12; ++i) {
			std::cout << CELL(6, right, MONTHS[i].first);
			std::cout << SPACE(3);
		}

		newline_;
	}

	void Year(const chr::year year) {

	}

}

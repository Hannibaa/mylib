/*
             KADDA AOUES LIBRARY 
			 Author : Kadda Aoues
			 Title  : today.h lib
			 Date   : ?? / ?? / 2023
			 1. TIME - DATE -
			 2. HEADER FILE -- TODAY.H --
			 3. Add String() function 1.11.23
			 4. Add extern function get_serial_at_time() function
*/




#pragma once
#include <utility>
#include <string_view>
#include <MyLib/Calender_utility.h>
#include <MyLib/random_generator.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//    we need to introduse time zone to complete all. current_zone();
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////


using namespace std::chrono;

class ToDay {

	static std::string str;

	static void update() {
		std::stringstream sstr;
		sys_seconds to_day_time = time_point_cast<seconds>( system_clock::now());
		sstr << to_day_time;
		str = sstr.str();
	}

public:

	static std::string String() {
		update();
		return str;
	}

	static auto second() { 
		update();
		return std::chrono::seconds(std::stoi( str.substr(str.size()-2))); 
	}

	static auto minute() {
		update();
		return std::chrono::minutes(std::stoi(str.substr(str.size() - 5, 2)));
	}

	static auto hour() { 
		update();
		return std::chrono::hours(std::stoi(str.substr(str.size()-8,2)));
	}

	static auto year() {
		update();
		return std::chrono::year(std::stoi(str.substr(0, 4)));
	}

	static auto month() {
		update();
		struct _month {
			std::chrono::month month;
			unsigned int index;
			std::string name;
		};

		std::chrono::month __month = std::chrono::month(std::stoi(str.substr(5, 2)));

		return  _month{
			.month = __month,
			.index = unsigned int(__month),
			.name = std::get<1>(Calendar::_MONTHS[unsigned int(__month) - 1])
		};

	}

	static auto day() {
		update();
		return std::chrono::day(std::stoi(str.substr(8, 2)));
	}

	static auto day_name() {

		sys_days to_day = time_point_cast<days>(system_clock::now());
		year_month_weekday ymw = sys_days(to_day);

		return ymw.weekday();
	}

	static auto date() {
		return sys_days(time_point_cast<days>(system_clock::now()));
	}

	static std::string date_hour() {

	}
};

std::string ToDay::str;

namespace to_day {

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    THIS FUNCTION WILL RETURN IN TIME DATE DDMMYYHHMMSS AS SERIAL NUMBER. 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////


	std::string get_serial_at_time() {

		auto str_time = ToDay::String();
		    str_time = Str::removeUnusefullCharAny(str_time, "-: ");
		return str_time;
	}

	// NEED FUNCTION THAT RETURN STRING AND CHRONO DATE IN RANDOM NUMBER.
	// NEED FUNCTION THAT RETURN STRING AND CHRONO TIME IN HOUR AND SECOND AND MINUTE

	// Need format = "hh:mm:ss", or "hh mm ss" or "hh===ss===mmmm", 
	// here should be double letter h m s or H M S, so we used in double or single
	// so what happen if "h:mm:sss" so what can gave us this format will investigate after.

	std::string get_random_hour(const std::string_view format) {

		// here we check the format how it made
		std::string str{format};
		// check if is valide format
 
		for (int i = 0; i < format.size(); ++i) {
			switch (format[i]) {
			case 'h':
			case 'H': str[i] = rand()%12;
				continue;
			case 'm':
			case 'M': str[i] = rand() % 60;
				continue;
			case 's':
			case 'S': str[i] = rand() % 60;
				continue;
			}
		}

		return {};
	}

	std::string get_random_date() {


		return {};
	}

	std::chrono::sys_days str_to_date(const std::string& str_date);

}
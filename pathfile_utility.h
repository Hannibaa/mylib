#pragma once
#include <string>
#include <chrono>

namespace path {

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//   FILENAME PATH MANIPULATION 
	//   1. EXTRACT FILENAME ALONE
	//   2. EXTRACT FILE EXTENSION
	//   3. EXTRACT FILE PATH
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename STR>
	STR getFilename(const STR& filepath) {

		return filepath.substr(filepath.find_last_of('\\') + 1);
	}

	std::string getFileextension(const std::string& filepath) {

		return filepath.substr(filepath.find_last_of('.') + 1);
	}

	std::string getFilenamNoextension(const std::string& filepath) {

		auto result = getFilename(filepath);

		return result.substr(0, result.find_last_of('.'));
	}

	bool isFilename(const std::string& filename) {

		return getFilename(filename) == filename;
	}

	std::string getFilepath(const std::string& filepath) {

		return filepath.substr(0, filepath.find_last_of('\\') + 1);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//      CONVERTING WIDE STRING TO STRING, AND STRING TO WIDE STRING
	// 
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string ws2s(const std::wstring& wstr) {

		return std::string(wstr.begin(), wstr.end());

	}

	std::wstring s2ws(const std::string& str) {

		return std::wstring(str.begin(), str.end());

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    CHECK IF PATH DONE BY FILENAME IS VALIDE IN STRING MODE
	// 
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool isValidPath(const std::string& path) {

		if (path == "") return false;

		for (auto& c : path)
		{
			if (!((c > 44 && c < 59)
				|| (c > 64 && c < 94)
				|| (c > 96 && c < 123)
				|| (c == '_')
				|| (c == ' ')
				|| (c == '+')))
			{
				return false;
			}

		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    GET LAST DATE
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::chrono::year_month_day get_last_write_date(const std::filesystem::path& path) {
		using namespace std::chrono;
		auto f_time = std::filesystem::last_write_time(path);
		year_month_day ymd = sys_days(time_point_cast<days>(clock_cast<system_clock>(f_time)));
		return ymd;
	}

	std::chrono::hh_mm_ss<std::chrono::seconds> get_last_write_time(const std::filesystem::path& path) {

		return{};
	}
}
#pragma once
#include <MyLib/strings/CWord.h>



namespace text {


	class CLine {   // we shoud change the designe of CLine, or we consider space as word also.
		std::vector<CWord> _line;
		const size_t       _max_char_inline;
		std::vector<int>   _space_count;
		
		constexpr bool is_line(const std::string& str_lines) {}

		constexpr int space_count_in_string(const std::string& text) {

		}

	public:

		CLine(const std::string& line, const size_t max_char_in_line = 125i64)
			: _max_char_inline{max_char_in_line}
		{
			// check if line is greater than 125;
			auto _line = line;
			if (line.size() > 125) _line = line.substr(0, 124);

			auto vString = Str::TextToWords(_line);


		}
		
	};




}
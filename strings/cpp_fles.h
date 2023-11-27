/*
 *****************************************************************************
 *                                                                           *
 *                                                                           *
 *                  C++ comment and todo comment list  Library               *
 *                                                                           *
 * Author: KADDA Aoues - haoues_k@yahoo.fr - 2023                            *
 * Date : 23 / 11 / 2023                                                     *
 *                                                                           *
 * Copyright notice:                                                         *
 * Free use of the Library CFile                                             *
 * is permitted under the guidelines and in accordance with the most current *
 * version of the MIT License.                                               *
 * http://www.opensource.org/licenses/MIT                                    *
 *                                                                           *
 *****************************************************************************
 *
 *
*/



#pragma once
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <MyLib/Console_Library/escape_code.h>
#include <MyLib/stringfunctionhelper.h>
#include <MyLib/CFile.h>

#pragma warning( disable : 4996)


namespace cpp {

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    Comment structure ;
	//     1. string 
	//     2. begining of line of comment b_line;
	//     3. ending of number of line of comment e_line;
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct comment {
		std::string    _comment;
		std::string    _file_;
		std::string    _time_;
		long long      time_since_last_mod;
		unsigned int   b_line;
		unsigned int   e_line;  // b_line = e_line mean some line otherwise from line to line.

		comment() = default;

		comment(const std::string& comment,const std::string& _file, const std::string& _time,
			long long _rep_time,
			uint _begin_line, uint _end_line = -1)
			: _comment{ comment }
			, _file_{_file}
			, _time_{_time}
			, time_since_last_mod{_rep_time}
			, b_line{ _begin_line }
			, e_line{ _end_line }
		{
			if (e_line == -1) e_line = b_line;
		}
	};

	using vecComments = std::vector<comment>;

	// comment identifier  //  /*  */
	std::string d_slash{ "//" };  //
	std::string b_slaph{ "/*" };
	std::string e_slaph{ "*/" };

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    LOADING ALL COMMENT IN COMMENT VECTOR STRUCTURES
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto read_comment_cpp(const fs::path cpp_file) {

		auto ss = std::stringstream{ File::loadFileToString(cpp_file) };
		Print_(color::Green, cpp_file.string()) << end_;
		print_ << "size of file character : " << ss.str().size() << end_;
		std::string _file_ = cpp_file.filename().string();

		long long last_time_ = fs::last_write_time(cpp_file).time_since_epoch().count();
		std::stringstream _ss; 
		_ss << fs::last_write_time(cpp_file);
		size_t sz = _ss.str().size();
		vecComments vec_comts;

		int i{};
		for (std::string line{}; std::getline(ss, line);) {
			
			// calculate n line;
			++i;
			//if (i == 100) break;

			size_t pos = line.find(d_slash);
			// TODO check if this pos not inside const char* like string.
			// is_comment_position(string ,pos)
			if (pos != _npos) {
				std::string comt = line.substr(pos);
			    comt = Str::removeUnusefullCharBiginning(comt, '/');
			    comt = Str::removeUnusefullCharEnd(comt, '/');
				Str::removeBlank(comt);
				vec_comts.emplace_back(comt,_file_,_ss.str().substr(0,sz-8), last_time_, (uint)i);

			}
		}
		return vec_comts;
	}

	auto read_todo_comment(const fs::path& cpp_file) {
		auto ss = std::stringstream{ File::loadFileToString(cpp_file) };

		vecComments vec_comts;
		std::string _file_ = cpp_file.filename().string();
		long long _last_time = fs::last_write_time(cpp_file).time_since_epoch().count();
		std::stringstream sstime;
		sstime << fs::last_write_time(cpp_file);
		size_t sz = sstime.str().size();

		int i{};
		for (std::string line{}; std::getline(ss, line);) {

			// TODO check if we found any comment in ss with / * ===== */;

			// calculate n line;
			++i;
			//if (i == 100) break;

			size_t pos = line.find(d_slash);
			// TODO check if this pos not inside const char* like string.
			// is_comment_position(string ,pos)
			if (pos != _npos) {
				std::string comt = line.substr(pos);

				// check is there any word 'to do' inside comment. transfer all string to lower case.
				pos = Str::str_tolower(comt).find("todo");
				if (pos != _npos) {
					comt = comt.substr(pos + 4);
					Str::removeBlank(comt, '/');
					Str::removeBlank(comt);
					vec_comts.emplace_back(comment{ comt, _file_,sstime.str().substr(0,sz-8), _last_time, (uint)i});
				}
			}
		}
		return vec_comts;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    printing a comment in some file:
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	void print_comments(const vecComments& comments, const std::string_view comment = "") {

		int l{};

		time_t _time{};

		for (const auto& c : comments) {

			if (l % 30 == 0) {
				wait_;
				esc::cls();
				// print comment
				Print_(color::Fuchsia, comment) << end_;
				// print head of table : | n    | location | comment 
				print_ << UNDERLINE 
					   << CELL(5, left ," n")
					   << "|" 
					   << CELL(11, left, " location")
					   << "|"
					   << CELL(75, left, " comment") 
					   << "|"
					   << CELL(30, left, " file ")
					   << "|" 
					   << CELL(20, left, " last modification")
					   << RESETMODE << end_;
			}

			if (l%2 == 0) print_ << _COLOR_BG256(238);
			print_ << CELL(5, left, ++l)
				   << "|"
				   << CELL(11, left, c.b_line)
				   << "| "
				   << COLOR(color::Green, CELL(74, left, c._comment));
				if (l % 2 == 0) print_ << _COLOR_BG256(238);
		    print_ << "|"
				   << CELL(30, left, c._file_ )
				   << "|"
				   << CELL(20, left, c._time_) << RESETMODE 
				   << end_;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    todo modification of todo list in file
	//    need to add fall path file.
	//    and in affich only name.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

}
/*
 *****************************************************************************
 *                                                                           *
 *                          Platform Independent                             *
 *                        String function  Library                           *
 *                                                                           *
 * Author: KADDA Aoues - haoues_k@yahoo.fr - 2023                            *
 *                                                                           *
 * URL :                                                                     *
 *                                                                           *
 * Copyright notice:                                                         *
 * Free use of the Library CFile                                             *
 * is permitted under the guidelines and in accordance with the most current *
 * version of the MIT License.                                               *
 * http://www.opensource.org/licenses/MIT                                    *
 *                                                                           *
 *****************************************************************************
*/


#pragma once
#include <string>
#include <cstring>
#include <sstream>
#include <utility>
#include <algorithm>
#include <vector>
#include <memory>
#include <filesystem>
#include <fstream>
#include <random>
#include <map>
#include "MyLib\random_generator.h"

#ifndef fs
namespace fs = std::filesystem;
#endif

#ifndef vecString
using  vecString = std::vector<std::string>;
#endif

#ifndef vecPath
using vecPath = std::vector<fs::path>;
#endif

#define _npos    std::string::npos

using byte = unsigned char;

namespace Str{
	// alphabet 
	const char* alphabet     = "abcdefghijklmnopqrstuvwxyz";
	const char* ALPHABET     = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char* all_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	const char* Number       = "0123456789";

	// function to check character always true
	bool always_true(int) { return true; }

	// type of comment header


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//     CODING A STRING OF 8 CARACTER IN INTEGER OF 8 BIT.
	//     REVERSE OPERATION .   
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	uint64_t str_to_integer(std::string_view word_8_chars) {
		int l = word_8_chars.length();
		if (l > 8) {
			std::cout << "the length of word is more than 8 characters\n";
			return {};
		}

		char c[8]{};
		for (int i = 0; i < l; ++i) c[i] = word_8_chars[i];

		return std::bit_cast<uint64_t>(c);
	}

	template<typename T>
	std::string integer_to_str(const T& value) {
		static_assert(std::is_integral_v<T>, "T should be integer type");

		char* c = (char*)&value;

		return std::string(c, c + sizeof(T));
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                   Is Alpha Numeric Character
	//                   Is Alphabet Character
	//                   All ctype functions here to char c;
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	bool isalnum(char c) {
		
		//return (c > 47 && c < 58) || (c > 64 && c < 91) || (c > 96 && c < 123);

		return std::isalnum(static_cast<unsigned char>(c));
	}

	bool isalphabet(char c) {
		//return (c > 64 && c < 91) || (c > 96 && c < 123);
		return std::isalpha(static_cast<unsigned char>(c));
	}

	bool isStringalpbabet(std::string& str) {
		for (int i = 0; i < str.size(); ++i) {
			if (!std::isalpha(static_cast<unsigned char>(str[i]))) return false;
		}

		return true;
	}

	bool isblank(char c) {
		return std::isblank(static_cast<unsigned char>(c));
	}

	bool isprint(char c) {
		return std::isprint(static_cast<unsigned char>(c));
	}

	

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                   REVERSE STRING
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Tchar>
	std::basic_string<Tchar> reverseString(std::basic_string<Tchar> str) {
		int l = str.size();
		for (int i = 0; i < l / 2; i++) {
			std::swap(str[i], str[l - i - 1]);
		}
		return str;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//      convert string to lower or upper case alphabet
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string str_tolower(std::string s)
	{
		std::transform(s.begin(), s.end(), s.begin(),
			// static_cast<int(*)(int)>(std::tolower)         // wrong
			// [](int c){ return std::tolower(c); }           // wrong
			// [](char c){ return std::tolower(c); }          // wrong
			[](unsigned char c) { return std::tolower(c); } // correct
		);
		return s;
	}

	std::string str_toupper(std::string s)
	{
		std::transform(s.begin(), s.end(), s.begin(),
			[](unsigned char c) { return std::toupper(c); } // correct
		);
		return s;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                        REMOVE SPACE FROM BEGINING AND END OF STRING 
	//                        GENERALIZED REMOVING NON MEANING CHARACTER
	//        
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	void removeBlank(std::string& str, char Nchar = ' ') {

		if (str.empty()) return;

		while (str[str.size() - 1] == Nchar) {
			str.pop_back();
			if (str.empty()) return;
		}

		int i = 0;

		while (str[i] == Nchar) {
              ++i;
			  if (i > str.size()) break;
		} 

		str = str.substr(i);
	}

	std::string removeUnusefullCharBiginning(const std::string& str, char Nchar = '0') {

		if (str.empty()) return str;
		int i{};
		while (str[i] == Nchar) ++i;

		return str.substr(i);
	}

	std::string removeUnusefullCharEnd(std::string str, char Nchar = '0') {

		if ( str.empty() ) return str;

		while (str[str.size() - 1] == Nchar) {
			str.pop_back();
			if (str.empty()) break;
		}

		return str;
	}

	std::string removeUnusefullCharAny(const std::string& _str, char Nchar = ' ') {

		if (_str.empty()) return {};
		std::string str;
		for (auto& c : _str)
		{
			if (c != Nchar) str.push_back(c);
		}

		return str;
	}

	std::string removeUnusefullCharAny(std::string _str, const std::string Nchar = " \n") {

		if (_str.empty()) return {};

		for (auto& c : Nchar)
		{
			_str = removeUnusefullCharAny(_str, c);
		}

		return _str;
	}

	std::string remove_char(const std::string& text, size_t begin_pos, size_t end_pos, char _char) {

		return text.substr(0, begin_pos) +
			Str::removeUnusefullCharAny(text.substr(begin_pos, end_pos - begin_pos + 1), ' ') +
			text.substr(end_pos + 1);
	}

	// remove successive repitition of char or blank; and leave one 
	std::string remove_successive_char(std::string text, char _char = ' ') {

		size_t pos{};

		text = Str::removeUnusefullCharBiginning(text, ' ');
		text = Str::removeUnusefullCharEnd(text, ' ');

		for (;;) {
			pos = text.find(_char, pos);

			if (pos == _npos) break; else {
				if (text[pos + 1] == _char) {
					text.erase(text.begin() + pos);
				}
				else pos = pos + 1;
			}
		}
		return text;
	}


    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //                   CONVERT BETWEEN STRING TYPE
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////


	template<typename Tchar, typename Tcharf = char>
	std::basic_string<Tchar>  to_char(const std::basic_string<Tcharf>& str) {

		std::basic_string<Tchar> newStr;
		newStr.resize(str.size());

		std::copy(str.begin(), str.end(), newStr.begin());

		return newStr;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                   GET ALL DIGIT THAT NEED TO WRITE NUMBER IN BASE 'B'
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string digitOfBase(const int base) {
		if (base < 2 || base > 36) { std::cout << "base should be between 2 and 35 \n"; return std::string{}; }
		std::string strBase;
		for (int i = 0; i < base; i++)
		{
			if (i < 10) strBase.push_back(char(i + 48));
			else strBase.push_back(char(i + 55));
		}

		return strBase;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//               CONVERT CHAR AND SHORT TO HEX
	// 
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string Base16 = digitOfBase(16);

	std::string toHex(char c) {

		return  std::string{ Base16[(c & 0xf0) >> 4] } + std::string{ Base16[c & 0x0f] };
	}

	std::string toHex(short s) {

		return  std::string{ Base16[(s & 0xf000) >> 12] } + std::string{ Base16[(s & 0x0f00) >> 8] }
		+ std::string{ Base16[(s & 0x00f0) >> 4] } + std::string{ Base16[s & 0x000f] };
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//					UTILITY OF IDENTIFY NUMBER BASE AND CHECK WHICH WRITEN BASE
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	int minimalBase(const std::string& str) {


		return 0;
	}

	template<int N>
	bool is_string_number(const std::string& str) {

		return true;
	}

	template<>
	bool is_string_number<10>(const std::string& str) {

		for (auto& c : str)
		{
			if (c < 48 || c > 57) return false;
		}

		return true;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                   PUT COMMENT HERE
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////


	bool is_string_bin(std::string str) {

		for (auto c : str)
		{
			if (c != '0' && c != '1') return false;
		}

		return true;
	}

	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                   PUT COMMENT HERE <use positif to shift right and negatif for left
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////


	std::string shift_left_string(const std::string& str, int n)
	{
		if (n == 0) return str;
		int sz = str.size();
		if (std::abs(n) > sz) return std::string{};

		std::string outstring;
		outstring.resize(sz - abs(n));

		if (n > 0) std::copy(str.begin() + n, str.end(), outstring.begin());
		if (n < 0) std::copy(str.begin(), str.end() + n, outstring.begin());

		return outstring;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                   REMOVE UNUSEFUL FROM STRING NUMBERS 
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string remove_unusefullZero(std::string str_number)
	{
		if (!is_string_number<10>(str_number)) return std::string{};
		int n_Zero = 0;

		for (auto& c : str_number)
		{
			if (c == '0') { ++n_Zero; continue; }
			break;
		}

		if (n_Zero == str_number.size()) return "0";

		return shift_left_string(str_number, n_Zero);
	}


      ///////////////////////////////////////////////////////////////////////////////////////////////////////
      //
      //                   GEOMETRY OF WORDS IN TEXT ALPHANUMERIC.
	  //                   AND OF CONVERTING STRING TO ANOTHER NUMERICAL STRUCTURE.
      //
      ///////////////////////////////////////////////////////////////////////////////////////////////////////


	template<typename Tchar>
	std::pair<uint32_t, uint32_t>  convertStrCoord(const std::basic_string<Tchar>& str) {

		uint32_t x{}, y{}, sz = str.size();

		for (uint32_t i = 0; i < sz / 2u; i++) {
			x += (uint32_t)str[i];
			y += (uint32_t)str[sz - i - 1];
		}

		if (sz % 2 != 0) {
			x += (uint32_t)str[sz / 2u];
			y += (uint32_t)str[sz / 2u];
		}

		return std::make_pair(x, y);
	}

	template<typename T, typename Tchar = char> 
	T convertStrInt(const std::basic_string<Tchar>& str  , T(*f)(const std::basic_string<Tchar>&) ) {

		return f(str);

	}

	template<typename rgb_t, typename Tchar = char>
	rgb_t stringTorgb(const std::basic_string<Tchar>& str, byte(*f256)(const std::string&)) {
		// cut string in three part  |abc..|de..|fg..| rgb_t.red,green,blue of unsigned char.
		rgb_t rgb{};

		// code...
		// devide string in three party

		return rgb;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                   LOAD WORDS FROM TEXT FILE 
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	std::vector<std::string> LoadWordsFromTextFile(const std::string& filename) {

		// get size of file
		size_t file_size = std::filesystem::file_size(filename);

		// check if file exist by using file size
		if (file_size == -1) {
			std::cout << "Error in loading file " << filename << "\n";
			return {};
		}

		std::ifstream ifs{ filename };

		std::vector<std::string> vStr;

		std::string temp;

		while (true) {
			char c;
			ifs.get(c);

			if (ifs.eof()) break;

			if ( !isalnum(c) ) {               //std::isspace(c)
				if (!temp.empty()) {
				     vStr.push_back(temp);
				     temp.clear();
				}
			}

			else temp.push_back(c); 
		}

		ifs.close();
		return vStr;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//      LOAD FILE IN STRING
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string LoadFileToString(const fs::path& filename) {

		std::ifstream ifs{ filename };

		if (!ifs.is_open()) {
			std::cout << "error in Opening file " << filename << '\n';
			return {};
		}

		std::string tempString;

		while (!ifs.eof()) {
			char c{};
			ifs.get(c);
			tempString.push_back(c);
		}

		ifs.close();

		return tempString;
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                  PRINT VECTOR OF STRING 
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Tchar>
	void PrintWords(const std::vector <std::basic_string<Tchar>>& vStr, int line = 60) {
		
		if (vStr.size() == 0) return;
		
		int n{};

		for (auto& w : vStr) {
			std::cout << std::setw(w.size()) << std::left << w ;
			std::cout << std::setw(2) << std::left << "  ";
			n += w.size();
			if (n > line) {
				n = 0;
				std::cout << '\n';
				std::cin.get();
			}
		}

	}

	// print v 2
	template<typename Tchar>
	void PrintWords2(const std::vector <std::basic_string<Tchar>>& vStr, int line = 60, char Esp = ' ') {

		if (vStr.size() == 0) return;

		int n{};
		std::cout << " ";
		for (auto& w : vStr) {
			std::cout << std::setw(w.size()) << std::left << w;
			std::cout << std::setw(2) << std::left << Esp;
			n += w.size();
			if (n > line) {
				n = 0;
				std::cout << '\n';
				std::cin.get();
			}
		}

	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                        GET RANDOM STRING a..z A..Z 01..9
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string getRandomString(int size) {
		// size should be positive
		RNG::RG<char> rchar('a','z');
		RNG::RG<char> Rchar('A', 'Z');
		RNG::RG<char> rNumb('0', '9');
		RNG::RG<int> r(0, 2);

		char c{};
		std::string str;

		for (int i = 0; i != size; ++i) {
			int j = r();
			if (j == 0 ) str.push_back(rchar());
			if (j == 1 ) str.push_back(Rchar());
			if (j == 2 ) str.push_back(rNumb());
		}

		return str;
	}

	std::string getRandomString(int size, const char* format) { // '-_@'
		
		RNG::RG<char> rchar('a', 'z');
		RNG::RG<char> Rchar('A', 'Z');
		RNG::RG<char> rNumb('0', '9');
		RNG::RG<int> r(0, 2);

		std::string str;
		int count{};

		while (*format != 0 && count < size ) {  
			if (*format == '-') str.push_back(Rchar());
			if (*format == '_') str.push_back(rchar());
			if (*format == '@') str.push_back(rNumb());
			if (*format != '-' && *format != '_' && *format != '@') str.push_back(*format);
			format++;
			++count;
		}

		for (; count < size; ++count) str.push_back(rchar());

		return str;
	}

	std::string getRandomString(const char* format) {   // '-_@'

		RNG::RG<char> rchar('a', 'z');
		RNG::RG<char> Rchar('A', 'Z');
		RNG::RG<char> rNumb('0', '9');

		std::string str;

		while (*format != 0) {
			if (*format == '-') str.push_back(Rchar());
			if (*format == '_') str.push_back(rchar());
			if (*format == '@') str.push_back(rNumb());
			if (*format != '-' && *format != '_' && *format != '@') str.push_back(*format);
			format++;
		}

		return str;
	}

	std::string getRandomString(const char* alphabet, size_t size) {

		if (alphabet == "") return{};

		RNG::RG<char> rchar{ std::string(alphabet) };

		std::string str;

		for (int i = 0; i != size; ++i) str.push_back(rchar[1]);

		return str;
	}

	std::string getRandomString2(int max_size) { // maximum size is max_size

		RNG::RG<int> sz(0, max_size);

		return getRandomString(sz());
	}

	std::string getRandomString2(const char* format) {

		int size = (int)std::strlen(format);

		RNG::RG<int> sz(0, size - 1);

		return getRandomString(format).substr(0, sz());
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//          READ A QUOTED TEXT OR STRING BETWEEN ' OR " , AND THERE GENERALIZATION
	//          readQuotString(const string&, char = '"');  
	//          returned to vector<string>;
	//           
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::vector<std::string> readQuotString(const std::string& stream, char pchar = '"') {

		std::vector<std::string> vString;
		std::string str;
		bool start = false;
	    
		for (auto& c : stream ) {

			if ( c == pchar) {
				start = !start;
				if (!str.empty()) { 
					str = str.substr(1);
					removeBlank(str);
					vString.push_back(str); 
					str.clear(); 
				}
			}   

			if (start) {
				str.push_back(c);
			}
		}
		return vString;

	}

	// get string first quoted text between _char0 = '"' and _char1 ='"' ;sdfsf "hello"sdfsf ---> [hello]
	// return last position of second looking of _char1 in stored in last

	std::string get_quoted(const std::string& str, size_t& last_pos, char _char0 = '"', char _char1 = '"')
	{

		size_t pos_1 = str.find(_char0, last_pos);
		if (pos_1 == _npos) return str;

		size_t pos_2 = str.find(_char1, pos_1 + 1);

		if (pos_2 == _npos) {
			last_pos = _npos;
			return {};
		}

		last_pos = pos_2;

		return str.substr(pos_1 + 1, pos_2 - pos_1 - 1);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    1. Put text in vector of string
	//    2. Put text in vector of words   
	//    3. Put text in vector of lines(length). 
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::vector<std::string> putTextInVectorLines(const std::string& text ,char Char = '\n') {

		if (text.empty()) return {};

		std::string line;
		std::vector<std::string> vlines;

		for (size_t i = 0; i < text.size(); ++i) {
			if (text[i] == Char) {
				vlines.push_back(line);
				line = "";
			}
			else
			line += text[i];
		}

		if (text[text.size() - 1] != Char) vlines.push_back(line);

		return vlines;
	}


	std::vector<std::string> putTextInVectorWords(const std::string& text, bool(*criter)(int) = always_true) {

		if (text.empty()) return {};

		std::string word;
		std::vector<std::string> vwords;
		bool b = false;

		size_t i{};

		for (size_t i = 0; i < text.size();++i) {

			if (isprint(text[i]) && isblank(text[i]) && criter(text[i])) {
				if (b) {
				       vwords.push_back(word);
				       word = "";
					   b = false;
				}
				word += text[i];
			}
			else {
				b = true;
			}
		}

		vwords.push_back(word);

		return vwords;
	}

	// using sstream 
	std::vector<std::string> TextToWords(const std::string& text) {

		std::vector<std::string> vec_words;
		std::istringstream  istr_stream(text);

		for (std::string buf; istr_stream >> buf;) vec_words.push_back(buf);

		return vec_words;
	}

	template<typename Char>
	std::vector<std::basic_string<Char>> put_text_in_box(const std::basic_string<Char>& text, size_t length)
	{
		std::vector<std::basic_string<Char>> vstr;
		int l = text.length() / length + 1;
		for (int n = 0; n < l; ++n) {
			vstr.push_back(text.substr(n * length, length));
			if (vstr.at(vstr.size() - 1).length() < length) break;
		}

		return vstr;
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    FUNCTION GET ALPHABETIC WORDS AND PUT THEM IN VECTOR OF STRINGS.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::vector<std::string> get_alpha_words(const std::string_view text) {

		std::string word;
		std::vector<std::string> vec_str;

		for (auto ichar = text.begin(); ichar != text.end(); ++ichar) {
			if (isalphabet(*ichar)) word.push_back(*ichar);
			else {
				if (!word.empty()) {
					vec_str.push_back(word);
					word.clear();
				}
			}
		}

		if (!word.empty())
			vec_str.push_back(word);

		return vec_str;
	}


    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //     Check if string is full of blank space  
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool isFullSpaceString(const std::string& str) {

		if (str.empty()) return true;

		for (auto& c : str)
			if (!std::isblank(c)) return false;

		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//   Resise a vector of string.
	//   
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename STRING>
	void resizeVecString(std::vector<STRING>& vString, size_t new_size) {

		for (auto& str : vString) str.resize(new_size);

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    replacing some char with another character.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Char>
	void replace_inplace(std::basic_string<Char>& text, Char c, Char by_c) {
		for (int i = 0; i != text.size(); ++i) {
			if (text[i] == c) text[i] = by_c;
		}
	}



	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//      MAPPING OF CHARS AND WORDS LEXICOGRAPHICS IN TEXT
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	// mapping all char repitition in text (char statistique).

	std::map<char, uint32_t> get_mapping_character_in_text(const std::string_view text) {

		std::map<char, uint32_t> char_map;

		//char_map[text[0]] = 0;

		for (auto& Char : text) {
			++char_map[Char];
		}

		return char_map;
	}



	// mapping words repitition in text (words statistiques).

	std::map<std::string, uint32_t> get_mapping_word_in_text(const std::string_view text) {

		std::map<std::string, uint32_t> word_map;

		std::stringstream str_stream{ std::string(text) };

		std::string word;

		while (str_stream >> word) {
			// we need function that remove any un-alphabet character from a word
			// what?{what} , end-of{end,of} , get_value_from() {get,value,from},...

			auto vec_words = Str::get_alpha_words(word);

			for (auto& Word : vec_words)
				++word_map[Word];

			word.clear();
		}

		return word_map;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    FUNCTION IS_ONE_OF().
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool is_one_of(char c, const std::string_view chars) {

		return std::find(chars.begin(), chars.end(), c) != chars.end();

	}

}

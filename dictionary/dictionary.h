#pragma once
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <string>
#include <string_view>
#include <map>
#include "MyLib/Console_Library/escape_code.h"
#include <MyLib/random_vector.h>
#include <MyLib/vector_utility1.h>
#include <MyLib/stringfunctionhelper.h>
#include <chrono>

namespace fs = std::filesystem;

namespace dictionary {

	using VecString = std::vector<std::string>;

	class Dictionary {

	public:

		Dictionary(const std::string& filename)
			: _file_name(filename)
		{
			load_dictionary();
			load_dictinary_alphebatecly();
		}

		~Dictionary() { clear(); }

		void clear() {
			_dictionary.clear();

			for (auto& element : _alphabetic_dictionary)
				_alphabetic_dictionary[element.first].clear();

			_alphabetic_dictionary.clear();
			_file_name.clear();
		}

		// get dictionar alphabet

		VecString get_dictionar_alphabet(char c) {

			if (c < 'a' && c > 'z') {
				std::cout << "char is not alphabet \n";
				return {};
			}

			return _alphabetic_dictionary[c];
		}

		// function to find exact word
		bool find(std::string word) {

			word = Str::str_tolower(word);

			auto find_ = find_word(word, _alphabetic_dictionary[word[0]]);

			return find_ != _alphabetic_dictionary[word[0]].end();
		}

		VecString find_all_suffix(std::string suffix, size_t end_position = 0) {

			std::string::size_type    find_{};
			std::vector<std::string>  vec_found;
			size_t position{};

			auto tp = std::chrono::steady_clock::now();
			std::chrono::duration<float> d{};
			suffix = Str::str_tolower(suffix);

			for (auto& word : _dictionary) {
				if (word.size() > suffix.size() - 1 + end_position) {
					find_ = word.find(suffix);
					position = word.size() - suffix.size() - end_position;
					if (find_ == position) vec_found.push_back(word);
				}
			}

			d = std::chrono::steady_clock::now() - tp;
			std::cout << "time that taken to look at word : " << d << " seconds\n";

			return vec_found;

		}

		VecString find_all_prefix(const std::string prefix) {
			return find_all_words(prefix, 0);
		}

		VecString find_all_words(std::string _word, size_t position = std::string::npos, size_t start = 0) {

			std::string::size_type    find_{};
			std::vector<std::string>  vec_found;

			auto tp = std::chrono::steady_clock::now();
			std::chrono::duration<float> d{};
			_word = Str::str_tolower(_word);

			for (auto& word : _dictionary) {
				find_ = word.find(_word, start);

				if (find_ != std::string::npos) {
					if (position == std::string::npos) vec_found.push_back(word);
					else {
						if (find_ == position) vec_found.push_back(word);
					}
				}
			}

			d = std::chrono::steady_clock::now() - tp;
			std::cout << "time that taken to look at word : " << d << " seconds\n";

			return vec_found;
		}

	private:
		std::vector<std::string>      _dictionary;
		std::string                   _file_name;
		std::map<char, VecString>     _alphabetic_dictionary;

		bool succefull;

		// load dictionary of each alphabet

		void load_dictinary_alphebatecly() {

			if (!succefull) {
				std::cout << "there no file to loading\n";
				return;
			}

			for (auto& word : _dictionary)
				_alphabetic_dictionary[word[0]].push_back(word);

		}

		// loading dictionary function

		void load_dictionary() {

			// should be existing file or close application
			fs::path file_path = _file_name;

			if (!fs::exists(file_path)) {
				std::cout << "file corresponding a dictionary not exit, or error in loading file\n";
				succefull = false;
				return;
			}

			// creating file 
			std::ifstream ifs{ file_path };
			if (!ifs.is_open()) {
				std::cout << ESC::Colors::_YELLOW_FG << "Error in founding file" << ESC::Colors::_RESETMODE << end_;
				succefull = false;
				return;

			}

			// load all word to memory as vector
			std::chrono::duration<float> duration{};
			auto tp = std::chrono::steady_clock::now();

			std::string word{};

			while (ifs >> word) {
				_dictionary.push_back(Str::str_tolower(word));
			}

			duration = std::chrono::steady_clock::now() - tp;
			print_ << "Loading time" << COLOR(color::Green, duration) << end_;
			ifs.close();

			succefull = true;
		}

		// define find function in generals

		VecString::const_iterator find_word(std::string_view word, const VecString& dictionary)
		{

			return std::find(dictionary.begin(), dictionary.end(), word);

		}

	};




	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//      laod text file in vector of string words
	//      this version load only alphabetic char, other just ignored.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	VecString load_text_file(const std::string& filename, bool to_lower = true) {

		fs::path dictionar_location{ filename };

		// should be existing file or close application
		if (!fs::exists(dictionar_location)) {
			std::cout << "file corresponding a dictionary not exit, or error in loading file\n";
			return {};
		}

		// creating file 
		std::ifstream ifs{ dictionar_location };
		if (!ifs.is_open()) {
			std::cout << ESC::Colors::_YELLOW_FG << "Error in founding file" << ESC::Colors::_RESETMODE << end_;
			return {};
		}

		// load all word to memory as vector
		std::chrono::duration<float> duration{};

		std::vector<std::string> vec_words{};
		std::string text_line{};
		auto tp = std::chrono::steady_clock::now();

		while (std::getline(ifs, text_line)) {
			auto Vwords = Str::get_alpha_words(text_line);
			for (auto& word : Vwords) {
				word = Str::str_tolower(word);
				vec_words.push_back(word);
			}
		}

		duration = std::chrono::steady_clock::now() - tp;
		print_ << "time of loading " << duration << end_;
		ifs.close();

		return vec_words;
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//      Load dictionary in vector string
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	VecString load_dictionary(const std::string& filename, bool to_lower = true) {

		fs::path dictionar_location{ filename };

		// should be existing file or close application
		if (!fs::exists(dictionar_location)) {
			std::cout << "file corresponding a dictionary not exit, or error in loading file\n";
			return {};
		}

		// creating file 
		std::ifstream ifs{ dictionar_location };
		if (!ifs.is_open()) {
			std::cout << ESC::Colors::_YELLOW_FG << "Error in founding file" << ESC::Colors::_RESETMODE << end_;
			return {};
		}

		// load all word to memory as vector
		std::chrono::duration<float> duration{};
		auto tp = std::chrono::steady_clock::now();

		VecString vec_words{};
		std::string word{};

		while (ifs >> word) {
			if (to_lower) word = Str::str_tolower(word);
			vec_words.push_back(word);
		}
		duration = std::chrono::steady_clock::now() - tp;
		print_ << "time of loading " << duration << end_;
		ifs.close();
		return vec_words;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//     finding all words
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	VecString find_words_has_subword(const std::string_view subword, const VecString& dictionary)
	{
		std::string::size_type    find_{};
		VecString                 vec_found;

		auto tp = std::chrono::steady_clock::now();
		std::chrono::duration<float> d{};

		for (auto& word : dictionary) {
			find_ = word.find(subword);

			if (find_ != std::string::npos) {
				vec_found.push_back(word);
			}
		}

		d = std::chrono::steady_clock::now() - tp;
		std::cout << "time that taken to look at word : " << COLOR(color::Green, d) << " seconds\n";

		return vec_found;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//      check if word exist in dictionary
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool find_word(const std::string_view word, const std::vector<std::string>& dictionary) {

		auto find = std::find(dictionary.begin(), dictionary.end(), word);

		return find != dictionary.end();
	}

}

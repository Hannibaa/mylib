#pragma once
#include <MyLib/strings/CGlyph.h>
#include <MyLib/stringfunctionhelper.h>

/*
              title  : Word class implementation
			  author : KADDA Aoues
			  date   : 23 / 10 / 2023
			  Note : 
*/



namespace text {

	class CWord {
		std::vector<text::CGlyph> _word;
		std::string               _color;

		// traitement of word as like continues alphabet + some character.
		std::string word_trait(const std::string& _string) { 
			// remove blank before and take only one continus words.
			std::string string = _string;
			Str::removeBlank(string);
			string = string.substr(0, string.find_first_of(' '));
			return string; 
		}

	public:
		CWord(const std::string& string, const std::string_view color = ESC::Colors::_WHITE_FG)
			: _color{color}
		{

			// check if is continue alphanum+(' and -)
            
			auto _string = word_trait(string);

			for (const auto& c : _string) {
				_word.emplace_back(c,_color);
			}
		}

		void set_color(const std::string_view color){
			for (auto& g : _word) g.g_color = color;
		}

		void set_color(const std::string_view color, size_t from, size_t to) {
			// from <= to < sizeof _word;

			if (from >= _word.size() || to >= _word.size()) return;
			if (from > to) std::swap(from, to);

			for (size_t t = from; t < to; ++t) _word[t].g_color = color;
		}

		std::string String() const { 
			std::string word;
			for (const auto& c : _word) word.push_back(c.glyph);
			return word; 
		}

		constexpr size_t size() const noexcept {
			return _word.size();
		}

		// Friend function

		friend std::ostream& operator << (std::ostream& os, const CWord& word) {
			for (const auto& g : word._word)
				os << g;

			return os;
		}
	};


}
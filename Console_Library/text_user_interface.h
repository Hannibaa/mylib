#pragma once
#include <MyLib/Console_Library/escape_code.h>



namespace cui {

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    Get maximum size of lines in string '\n' or general character as return to line
    //    Return pair of size_t type
    //    1. first is max length of lines
    //    2. second is number of lines.
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto get_max_length_line(const std::string text, char c = '\n') {
		size_t max = 0;
		size_t lines = 0;

		for (int i = 0; i < text.size(); ++i) {
			size_t count{};
			while (text[i] != c) { ++count; ++i; if (i >= text.size()) break; }
			max = (count >= max) ? count : max;
			++lines;
		}
		
		return std::pair{ max, lines };
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    Print Text at coordinate x,y
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	void print_text_lines_at(int x, int y, const std::string text, char rl = '\n') {

		for (int i = 0; i < text.size(); ++i) {
			std::string str;
			while (text[i] != rl) {
				str.push_back(text[i]);
				++i;
				if (i >= text.size()) break;
			}

			printm_(x, y++) << str;
			str.clear();
		}
	}


	class Message_Box {

		std::string _message_head;
		std::string _message_body;


		int _x;
		int _y;
		int _length;
		int _width;

		// Glyph drawing box
		const char line = '\xc4';
		const char bar = '\xb3';
		const char shap_L = '\xc0';
		const char shap_7 = '\xbf';
		const char shap_J = '\xd9';
		const char shap_F = '\xda';

	public:

		void operator()(int x, int y,
			const std::string& message_head, const std::string& message_body,
			int offset_width = 0, int offset_length = 0)
		{
			_x = x; _y = y;
			_message_head = message_head;
			_message_body = message_body;
			auto dim = get_max_length_line(_message_body);
			// calculate width and length
			_width = 4 + dim.first + offset_width;
			_length = 3 + dim.second + offset_length;

			make_box();
		}

		void make_box() {

			print_ << MOVETO(_x, _y) << shap_F << REPEAT(_width, line) << shap_7;
			for (int k = 1; k != _length + 1; ++k) {
				print_ << MOVETO(_x, _y + k) << bar
					<< MOVETO(_x + _width + 1, _y + k) << bar;
			}

			print_ << MOVETO(_x, _y + _length + 1) << shap_L << REPEAT(_width, line) << shap_J;

			print_ 
				<< MOVETO(_x + 1, _y) << '[' << _message_head << ']'
				<< MOVETO(_x + 2 + _message_body.size(), _y + 2);

			print_text_lines_at(_x + 2, _y + 2, _message_body);
		}

		void draw() {

		}
	};

	class Area_Text {

	};

}
#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <MyLib/Console_Library/escape_code.h>


namespace text {

	struct CGlyph {
		char           glyph;
		std::string    g_color;
	
		CGlyph(char c, const std::string_view _color = ESC::Colors::_WHITE_FG)
			: g_color{_color},
			  glyph{ c }
		{}

		CGlyph() :glyph{ ' ' }, g_color {ESC::Colors::_WHITE_FG} {}

		operator char() { return glyph; }

		friend std::ostream& operator << (std::ostream& os, const CGlyph& g) {
			os << g.g_color.c_str() << g.glyph << RESETMODE;
			return os;
		}

	};

}
/**********************************************************************************
 *
 * Copyright (c) 2022-2023 KADDA Aoues
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **********************************************************************************/

 /*
  *****************************************************************************
  *                                                                           *
  *                          Platform Independent                             *
  *                     ANSI Escape Code VT100 Library                        *
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
#include <iomanip>
#include <map>
#include <algorithm>
#include <chrono>

#include <MyLib\Console_Library\Unicode_table.h>
#include "MyLib/function_utility.h"


 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // 
 //   ANSI ESCAPE CODE ASCII SEQUENCES
 //   FUNCTION AND MACRO PREDEFINED HERE 
 // 
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////
 // 
 //    COMMENT :
 //    1. MACRO MOVETO(X,Y), X AND Y ALWAYS INTEGER, DON'T PUT FLOAT NOT WORKING.
 //    2. ANSI COLOR 
 //       FIRST 0 TO 15 IS ALWAYS USED COLOR
 //       FROM 16 TO 231 IS GRADUAL COLOR AND WORKING LIKE SHIFT OF 6 STEP BY COLOR
 //         16 + 6 * K ; AND K = 0 TO 36 , 16 + 6 * 36 NOT INCLUDE.
 //    3. DEFINE STRUCTURE sCONSOLE_TEXT { text; color_fg,color_bg, coordx,coordy}.
 // 
 //////////////////////////////////////////////////////////////////////////////////////////////////////////


using uint = unsigned int;
using uchar = unsigned char;

#define _STRING(str)  std::string str{#str}       // define string with his name of variable 
#define _CSTR(x)      std::to_string(x).c_str()   // usefull macro 
#define _CwSTR(x)     std::to_wstring(x).c_str()  // usefull macro 

#define _s(str)       #str
#define _w(wstr)      L#wstr

#define _R(r)                     (int( r << 16))
#define _G(g)                     (int(g << 8 ))
#define _B(b)                     (int(b))
#define RGB2INT(r,g,b)            (int(_R(r)|_G(g)|_B(b)))



#define end_      '\n'
#define BELL      '\a'
#define hTAB      '\t'
#define vTAB      '\v'
#define BACKSPACE '\b'
#define NEWPAGE   '\f'
#define CR        '\r'
#define ESCAPE    '\x1b'
#define _DELETE    '\x7F'


#define SET_MAX_LENGTH(n)        "\x1b[" << _CSTR(n) << " u" // ESC [ n u Sets maximum length of lines in window to n.
#define SET_MAX_LINES(n)         "\x1b[" << _CSTR(n) << " t" // ESC [ n t Sets maximum number of lines in window to n.
#define START_PIXEL_LEFT(x)      "\x1b[" << _CSTR(x) << "x"	// ESC[n x Starts text n pixels from left edge of window.
#define START_PIXEL_TOP(x)       "\x1b[" << _CSTR(x) << "y"	// ESC[n y Starts text n pixels from top edge of window.

#define DOUBLE_HTHalf              "\x1b # 3"	//  Change this line to double - height top half	ESC # 3
#define DOUBLE_HBHalf              "\x1b # 4"	// 	Change this line to double - height bottom half	ESC # 4
#define SINGLE_WSH5                "\x1b # 5"   //	Change this line to single - width single - height	ESC # 5
#define SINGLE_WSH6                "\x1b # 6"	//	Change this line to double - width single - height	ESC # 6

	// LED
	/*Programmable LEDs

		ESC[Ps; Ps; ...Ps q   */
#define  LED(n)        "\x1b[" << _CSTR(n) << "q";
#define  LEDOFF        "\x1b[ q";
		/*	Ps are selective parameters separated by semicolons(0738) and executed in order, as follows :

		0 or None	All LEDs Off
			1	L1 On
			2	L2 On
			3	L3 On
			4	L4 On                                                                 */

			// Cursor control
#define MOVEHOME                 "\x1b[H" // moves cursor to home position (0, 0)
#define MOVETO(X,Y)              "\x1b[" << _CSTR(Y) << ";" << _CSTR(X) << "H" // moves cursor to line #, column #
#define WMOVETO(X,Y)             L"\x1b[" << _CwSTR(Y) << L";" << _CwSTR(X) << L"H" // moves cursor to line #, column #
#define MOVEUPLINE(X)            "\x1b[" << _CSTR(X) << "A" // moves cursor up # lines
#define MOVEDNLINE(X)            "\x1b[" << _CSTR(X) << "B" // moves cursor down # lines
#define MOVERIGHT(X)             "\x1b[" << _CSTR(X) << "C" // moves cursor right # columns
#define MOVELEFT(X)              "\x1b[" << _CSTR(X) << "D" // moves cursor left # columns
#define MOVENXDNLINE(X)          "\x1b[" << _CSTR(X) << "E" // moves cursor to beginning of next line, #lines down
#define MOVEPRUPLINE(X)          "\x1b[" << _CSTR(X) << "F" // moves cursor to beginning of previous line, # lines up
#define MOVECOLM(X)              "\x1b[" << _CSTR(X) << "G" // moves cursor to column #
#define REQUES_CUR_POS           "\x1b[6n"           // request cursor position (reports as ESC[#;#R)
#define MOVEONELINEUP            "\x1b M"    // moves cursor one line up, scrolling if needed
#define SAVECURSORPOSITION       "\x1b 7"    // save cursor position (DEC)
#define RESTORCUR_SAVED_POS      "\x1b 8"	 // restores the cursor to the last saved position (DEC
#define SAVE_CURSOR_POSITION     "\x1b 7"    // save cursor position (DEC)
#define RESTOR_CURSOR_POSITION   "\x1b 8"
#define SAVECURSORPOSITION_       "\x1b[s"	 // save cursor position (SCO)
#define RESTORCUR_SAVED_POS_      "\x1b[u"	 // restores the cursor to the last saved position (SCO)

#define  CURSOR_INVISIBLE		 "\x1b[?25l"    // make cursor invisible
#define  CURSOR_VISIBLE     	 "\x1b[?25h"    // make cursor visible

	// Erase functions
#define ERASEDIS               "\x1b[J"   // erase in display (same as ESC[0J)
#define ERASEFCURDN            "\x1b[0J"  // erase from cursor until end of screen
#define ERASEFCURBG            "\x1b[1J"  // erase from cursor to beginning of screen
#define ERASESCREEN            "\x1b[2J"  // erase entire screen
#define ERASESVLINE            "\x1b[3J"  // erase saved lines

#define ERASEINLINE            "\x1b[K"   // erase in line (same as ESC[0K)
#define ERASEFCURENDLINE       "\x1b[0K"  // erase from cursor to end of line
#define ERASELINETOCUR         "\x1b[1K"  // erase start of line to the cursor
#define ERASELINE              "\x1b[2K"  // erase the entire line
	/*
		 Note: Erasing the line won't move the cursor, meaning that the cursor will
		 stay at the last position it was at before the line was erased. You can use \r
		 after erasing the line, to return the cursor to the start of the current line.
	*/

	/*     Esc[m	Turn off character attributes	SGR0
		   Esc[0m	Turn off character attributes	SGR0
		   Esc[1m	Turn bold mode on	SGR1
		   Esc[2m	Turn low intensity mode on	SGR2
		   Esc[4m	Turn underline mode on	SGR4
		   Esc[5m	Turn blinking mode on	SGR5
		   Esc[7m	Turn reverse video on	SGR7
		   Esc[8m	Turn invisible text mode on	SGR8
	*/

#define RESETMODE              "\x1b[m"   // reset all modes (styles and colors)
#define BOLD                   "\x1b[1m"  
#define ITALIC                 "\x1b[3m"  
#define LOW_INTENSITY          "\x1b[2m"
#define UNDERLINE              "\x1b[4m"
#define BLINKING               "\x1b[5m"
#define REVERSE_VIDEO          "\x1b[7m"
#define INVISIBLE_TEXT         "\x1b[8m"


	// Color
#define DEFAULT_FG             "\x1b[39"   //
#define BLACK_FG               "\x1b[30m"  //
#define WHITE_FG               "\x1b[37m"  //
#define RED_FG                 "\x1b[31m"  //
#define GREEN_FG               "\x1b[32m"  //
#define BLUE_FG                "\x1b[34m"  //
#define YELLOW_FG              "\x1b[33m"  //
#define CYAN_FG                "\x1b[36m"  //
#define MAGENTA_FG             "\x1b[35m"  //

#define BLACK_BG               "\x1b[40m"  //
#define RED_BG                 "\x1b[41m"  //
#define YELLOW_BG              "\x1b[43m"  //
#define GREEN_BG               "\x1b[42m"  //
#define BLUE_BG                "\x1b[44m"  //
#define MAGENTA_BG             "\x1b[45m"  //
#define CYAN_BG                "\x1b[46m"  //
#define WHITE_BG               "\x1b[47m"  //
#define DEFAULT_BG             "\x1b[49"   //

#define _FG "\x1b[38;2;"
#define _BG "\x1b[48;2;" 

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//   Useful Macro for editing text : 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

#define end_             '\n'
#define wend_            L'\n'
#define wait_            std::cin.get()
#define wwait_           std::wcin.get()
#define print_           std::cout 
#define wprint_          std::wcout
#define newline_         std::cout << end_
#define wnewline_        std::wcout << end_

#define CELL(SIZE,LeftOrRight,STR)   std::setw(SIZE) << std::LeftOrRight << STR 
#define SPACE(N)                     std::string(N,' ').c_str()
#define WSPACE(N)                    std::wstring(N,' ').c_str()
#define WREPEAT(N,WCHAR)             std::wstring(N,WCHAR).c_str()
#define REPEAT(N,CHAR)               std::string(N,CHAR).c_str()
#define _COLOR_FG256(i)                "\x1b[38;5;" << _CSTR(i) << "m"
#define _wCOLOR_FG256(i)              L"\x1b[38;5;" << _CwSTR(i) << L"m"
#define _COLOR_BG256(i)                "\x1b[48;5;" << _CSTR(i) << "m"
#define _wCOLOR_BG256(i)              L"\x1b[48;5;" << _CwSTR(i) << L"m"

// i6 0..5 ; k36 0..35
#define _wCOLOR_FG6(i, k)                _wCOLOR_FG256(i + 16 + 6 * k) 

// PRINTING MACRO AND COLORING 
#define Print_(color256, text)    print_ << _COLOR_FG256(color256) << text << RESETMODE 
#define WPrint_(color256, text)   wprint_ << _wCOLOR_FG256(color256) << text << RESETMODE 
#define COLOR(color256, text)     _COLOR_FG256(color256) << text << RESETMODE  
#define wCOLOR(color256, text)    _wCOLOR_FG256(color256) << text << RESETMODE  
#define Error_(text)              Print_(color::Red, text) << end_;
#define wError_(text)             WPrint_(color::Red, text) << wend_;

#define WTEXT_COLOR(fg, bg , text)   _wCOLOR_FG256(fg) << _wCOLOR_BG256(bg) << text << RESETMODE
#define TEXT_COLOR(fg, bg , text)    _COLOR_FG256(fg) << _COLOR_BG256(bg) << text << RESETMODE
	

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//   SCREEN MODE 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// BEGIN

#define SCREEN_MODE(value) 	       "\x1b[="#value"h"	 // Changes the screen width or type to the mode specified by value.
#define MODE_MONO_40X25_T		   "\x1b[=0h"                // 40 x 25 monochrome(text)
#define MODE_COLOR_40X25_T		   "\x1b[=1h"                // 40 x 25 color(text)
#define MODE_MONO_80X25_T		   "\x1b[=2h"                // 80 x 25 monochrome(text)
#define MODE_COLOR_80X25_T		   "\x1b[=3h"                // 80 x 25 color(text)
#define MODE_COLOR_320X200_4_G	   "\x1b[=4h"                // 320 x 200 4 - color(graphics)
#define MODE_MONO_320X200_G		   "\x1b[=5h"                // 320 x 200 monochrome(graphics)
#define MODE_MONO_640X200_G		   "\x1b[=6h"                // 640 x 200 monochrome(graphics)
#define MODE_ENABLE_LINE_WRAPPING  "\x1b[=7h"                // Enables line wrapping
#define MODE_320X200_G		       "\x1b[=13h"	             // 320 x 200 color(graphics)
#define MODE_640X200_G		       "\x1b[=14h"	             // 640 x 200 color(16 - color graphics)
#define MODE_MONO_640X350_G		   "\x1b[=15h"	             // 640 x 350 monochrome(2 - color graphics)
#define MODE_COLOR_640X350_G	   "\x1b[=16h"	             // 640 x 350 color(16 - color graphics)
#define MODE_MONO_640X480_G		   "\x1b[=17h"	             // 640 x 480 monochrome(2 - color graphics)
#define MODE_COLOR_640X480_G	   "\x1b[=18h"	             // 640 x 480 color(16 - color graphics)
#define MODE_COLOR_320X200_G	   "\x1b[=19h"	             // 320 x 200 color(256 - color graphics)

#define RESET(value)	           "\x1b[="#value"l"	  
						/*Resets the mode by using the same values that Set Mode uses,
						 except for 7, which disables line wrapping.The last character
						 in this escape sequence is a lowercase L.
						  Common Private Modes
						 These are some examples of private modes, which are not defined
						 by the specification, but are implemented in most terminals.
						 ESC Code Sequence	Description*/

#define  RESTORE_SCREEN		            "\x1b[?47l"    // restore screen
#define  SAVE_SCREEN		            "\x1b[?47h"    // save screen
#define  ENABLE_ALTERNATIVE_BUFFER	 	"\x1b[?1049h"	     // enables the alternative buffer
#define  DISABLE_ALTERNATIVE_BUFFER		"\x1b[?1049l"	     // disables the alternative buffer

 //------------------------------------ END -------------------------------------------------------





namespace ESC {


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    COLOR ENUMERATION AND NAME SPACES
	//    FUNCTION CONVERTING FROM AND TO COLOR ANSI CONSOLE
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// BEGIN

	namespace Colors {

		const char* _RESETMODE = "\x1b[0m";
		const char* _ITALIC = "\x1b[3m";
		const char* _BLACK_FG = "\x1b[30m";
		const char* _BLACK_BG = "\x1b[40m";
		const char* _RED_BG = "\x1b[31m";
		const char* _RED_FG = "\x1b[41m";
		const char* _GREEN_FG = "\x1b[32m";
		const char* _GREEN_BG = "\x1b[42m";
		const char* _YELLOW_FG = "\x1b[33m";
		const char* _YELLOW_BG = "\x1b[43m";
		const char* _BLUE_FG = "\x1b[34m";
		const char* _BLUE_BG = "\x1b[44m";
		const char* _MAGENTA_FG = "\x1b[35m";
		const char* _MAGENTA_BG = "\x1b[45m";
		const char* _CYAN_FG = "\x1b[36m";
		const char* _CYAN_BG = "\x1b[46m";
		const char* _WHITE_FG = "\x1b[37m";
		const char* _WHITE_BG = "\x1b[47m";
		const char* _DEFAULT_FG = "\x1b[39";
		const char* _DEFAULT_BG = "\x1b[49";

		const char* _FG_ = "\x1b[38;2;";
		const char* _BG_ = "\x1b[48;2;";

	}

	// END

	enum Color256 {
		Black = 0,
		Maroon,
		Green,
		Olive,
		Navy,
		Purple,
		Teal,
		Silver,
		Grey,
		Red,
		Lime,
		Yellow,
		Blue,
		Fuchsia,
		Aqua,
		White,  // = 15; 16 MASTER COLOR.
		// COLOR GRADIANT
		// you can get this color by macro _rgb(r,g,b) r,g and b varied from 0 to 5;
		// Grey : 
		Grey3 = 232,
		Grey7,
		Grey11,
		Grey15,
		Grey19,
		Grey23,
		Grey27,
		Grey30,
		Grey35,
		Grey39,
		Grey42,
		Grey46,
		Grey50,
		Grey54,
		Grey58,
		Grey62,
		Grey66,
		Grey70,
		Grey74,
		Grey78,
		Grey82,
		Grey85,
		Grey89,
		Grey93

	};



	constexpr std::string COLORFG256(uchar i) {

		std::string str = "\x1b[38;5;" + std::to_string(i) + "m";

		return str;
	}


	constexpr std::string COLORBG256(uchar i) {

		std::string str = "\x1b[48;5;" + std::to_string(i) + "m";

		return str;

	}

	enum FGBG  { FG = 38, BG = 48 };

	constexpr std::string rgbCOLOR_BG(uint r, uint g, uint b) {

		std::string str = _BG + std::to_string(r) + ";"
			+ std::to_string(g) + ";"
			+ std::to_string(b) + "m";
		return str;
	}

	constexpr std::string rgbCOLOR_FG(uint r, uint g, uint b) {

		std::string str = _FG + std::to_string(r) + ";"
			+ std::to_string(g) + ";"
			+ std::to_string(b) + "m";
		return str;

	}

	constexpr int ansi_color(int r, int g, int b) {
		r = std::clamp(r, 0, 5);
		g = std::clamp(g, 0, 5);
		b = std::clamp(b, 0, 5);
		return (36 * r) + (6 * g) + b + 16;
	}

	template<int r, int g, int b>
	constexpr int ansi_color(){ return ansi_color(r,g,b);	}

#define _rgb   esc::ansi_color


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                               /////////////////////////////////////////
	//    STRUCTURE SECTION DEFINITION OF ALL CONSOLE TYPES HERE	 /////////////////////////////////////////
	// 																 /////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	
		// Structure of point
	template<typename T>
	struct Point2d {
		T x;
		T y;

		Point2d(T _x = T{}, T _y = T{}) : x{ _x }, y{ _y } {}

		T& operator[](size_t t) {
			if (t == 0) return x;
			if (t == 1) return y;
			Print_(Color256::Red, "Undefined!!!") << end_;
		}

		T operator[](size_t t) const {
			if (t == 0) return x;
			if (t == 1) return y;
			Print_(Color256::Red, "Undefined!!!") << end_;
		}
	};


	// Structure for console text input Tchar
	template<typename Tchar>
	struct sCONSOLE_TEXT {
		std::basic_string<Tchar> text; // text to be affiched:
		int x;						   // coordinate in console, of first letter
		int y;						   // coordinate in console
		int fg_color;				   // foreground color or text color
		int bg_color;				   // background color
	};

	template<typename Tchar>
	struct cString : public std::basic_string<Tchar> {

		using std::basic_string<Tchar>::basic_string;

		void set_position(int a, int b) {
			x = a; y = b;
		}

		Point2d<int> get_position() const {
			return Point2d<int>{ x,y };
		}

		void set_color(int _foreground, int _background = 0) {
			fg_color = _foreground;
			bg_color = _background;
		}

		int get_foreGroundColor() const {
			return fg_color;
		}

		int get_backGroundColor() const {
			return bg_color;
		}

	private:
		int x;						   // coordinate in console, of first letter
		int y;						   // coordinate in console
		int fg_color;				   // foreground color or text color
		int bg_color;				   // background color
	};



	struct Init_Cursor {
		Init_Cursor() {
			print_ << CURSOR_INVISIBLE;
		}
		~Init_Cursor() {
			print_ << CURSOR_VISIBLE;
			print_ << "cursor visible\n";
		}
	};
	struct wInit_Cursor {
		wInit_Cursor() {
			wprint_ << CURSOR_INVISIBLE;
		}
		~wInit_Cursor() {
			wprint_ << CURSOR_VISIBLE;
			wprint_ << L"cursor visible\n";
		}
	};
	struct Init_Esc {

		Init_Esc() = default;

		Init_Esc(const char* back_ground, const char* fore_ground)
			:_bg{ back_ground }
			, _fg{ fore_ground }
		{
			std::cout << back_ground << fore_ground;
		}

		~Init_Esc() {
			print_ << "reset mode\n";
			std::cout << RESETMODE;
		}

		void re_init() const {
			std::cout << _bg << _fg;
		}

	private:
		std::string _bg;
		std::string _fg;
	};
	struct Wchar_Mode {
		Wchar_Mode() {
			SETMODE_WTTEXT;
		}

		~Wchar_Mode() {
			SETMODE_TEXT;
			print_ << "text mode\n";
		}
	};

#define INIT_CURSOR      ESC::Init_Cursor    init_cursor
#define WINIT_CURSOR     ESC::wInit_Cursor   init_cursor
#define WHIDE_CURSOR     WINIT_CURSOR
#define HIDE_CURSOR      INIT_CURSOR
#define INIT_WCHAR_TEXT  ESC::Wchar_Mode     init_wchart_text
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//       USEFUL FUNCTION FOR MANIPULATING TEXT   
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////

using color = ESC::Color256;

namespace ESC {

	void restor_mode() {
		print_ << RESETMODE;
	}

	void move_to(uint x, uint y) {
		print_ << MOVETO(x, y);
	}

	void cls() {
		print_ << ERASESCREEN << MOVEHOME;
	}

	void cls(int x, int y, int width, int length, int colour = color::Black) {
		for (int j = 0; j != length; ++j)
			print_ << MOVETO(x,y + j) << _COLOR_BG256(colour) << REPEAT(width,' ') << RESETMODE;
	}

	void clear_line(int x,int y) {
		print_ << MOVETO(x, y) << ERASELINE;
	}

	void wcls() {
		wprint_ << ERASESCREEN << MOVEHOME;
	}

	void wclear_line(int x, int y) {
		wprint_ << WMOVETO(x,y) << ERASELINE;
	}

	void print_wchar_chart(short from = 14i16, short to = SHRT_MAX, short char_in_line = 15i16, short max_char = 150i16)
	{
		for (short s = from; s < to; ++s) {

			wchar_t c = static_cast<wchar_t>(s);

			wprint_ << std::hex << s << '|' << c << L"  ";

			if (s % char_in_line == 0) wprint_ << wend_;
			std::wcin.clear();
			if (s % max_char == 0) wwait_;
			std::wcin.clear();
		}
	}

	template<typename Char>
	void print_CharType_chart(Char from = 14i16, Char to = Fn::max_of<Char>, short char_in_line = 15i16, short max_char = 150i16)
	{
		for (int s = from; s < to; ++s) {

			Char c = static_cast<Char>(s);

			wprint_ << std::hex << s << '|' << c << L"  ";

			if (s % char_in_line == 0) wprint_ << end_;
			std::wcin.clear();
			if (s % max_char == 0) wwait_;
			std::wcin.clear();
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    Printing text in box 
	//    1. Parameter
	//       1.1 text 
	//       1.2 maximum character in line 
	//       1.3 position posx and posy .
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Char>
	void print_text(const std::basic_string<Char>& text, size_t max_char_line, int posx = 0, int posy = 0)
	{
		int lines = text.length() / max_char_line + 1;

		wprint_ << MOVETO(posx, posy);
		for (int n = 0; n != lines; ++n) {
			wprint_ << text.substr(n * max_char_line, max_char_line);
			wprint_ << MOVEDNLINE(1) << MOVECOLM(posx);
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    Add color to any printing function to console
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Function, typename ...Ts>
	void _coloring(color _color, Function func, const Ts&...args) {
		wprint_ << _COLOR_FG256(_color);
		func(args...);
		wprint_ << RESETMODE;
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    custom any function for any style represented by escape code.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Style, typename Function, typename ...Ts>
	void customize(Style _style, Function _function, const Ts&...args) {
		wprint_ << _style;
		_function(args...);
		wprint_ << RESETMODE;
	}
    
	void put_string_at(int x, int y, const std::wstring& wstr, int _color = color::White) {
		wprint_ << WMOVETO(x, y)
			    << _wCOLOR_FG256(_color)
			    << wstr << RESETMODE;
	}

	void put_char_at(int x, int y, const char c, int _color) {
		wprint_ << WMOVETO(x, y)
			    << _wCOLOR_FG256(_color)
			    << c << RESETMODE;
	}

	void put_string_horizontal_at(int x, int y, const std::wstring& str, int color) {

		wprint_ << SAVECURSORPOSITION;
		for (int k = 0; k != str.size(); ++k) {
			wprint_ << MOVETO(x, y - k)
				<< wCOLOR(color, str[k]);
		}
		wprint_ << RESTORCUR_SAVED_POS;
	}

	void put_string_horizontal_up_at(int x, int y, const std::wstring& str, int color)
	{
		wprint_ << SAVECURSORPOSITION;
		for (int k = 0; k != str.size(); ++k) {
			wprint_ << MOVETO(x, y + k)
				<< wCOLOR(color, str[k]);
		}
		wprint_ << RESTORCUR_SAVED_POS;
		return;
	}

	void put_string_horizontal_up_at2(int x, int y, const std::wstring& str, int color)
	{
		size_t pos{};

		pos = str.find_last_of(L' ');
		put_string_horizontal_up_at(x - 2, y, str.substr(pos + 1), color);
		put_string_horizontal_up_at(x, y, str.substr(0, pos - 1), color);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    CONVERT RGB TO 256 CONSOLE COLORS.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	int _rgb_colors[256]{
                     0x000000,
                     0x800000,
                     0x008000,  // rgb(128, 0, 0); (r, g, b):
                     0x808000,
                     0x000080,
                     0x800080,
                     0x008080,
                     0xc0c0c0,
                     0x808080,
                     0xff0000,
                     0x00ff00,
                     0xffff00,
                     0x0000ff,
                     0xff00ff,
                     0x00ffff,
                     0xffffff,
                     0x000000,
                     0x00005f,
                     0x000087,
                     0x0000af,
                     0x0000d7,
                     0x0000ff,
                     0x005f00,
                     0x005f5f,
                     0x005f87,
                     0x005faf,
                     0x005fd7,
                     0x005fff,
                     0x008700,
                     0x00875f,
                     0x008787,
                     0x0087af,
                     0x0087d7,
                     0x0087ff,
                     0x00af00,
                     0x00af5f,
                     0x00af87,
                     0x00afaf,
                     0x00afd7,
                     0x00afff,
                     0x00d700,
                     0x00d75f,
                     0x00d787,
                     0x00d7af,
                     0x00d7d7,
                     0x00d7ff,
                     0x00ff00,
                     0x00ff5f,
                     0x00ff87,
                     0x00ffaf,
                     0x00ffd7,
                     0x00ffff,
                     0x5f0000,
                     0x5f005f,
                     0x5f0087,
                     0x5f00af,
                     0x5f00d7,
                     0x5f00ff,
                     0x5f5f00,
                     0x5f5f5f,
                     0x5f5f87,
                     0x5f5faf,
                     0x5f5fd7,
                     0x5f5fff,
                     0x5f8700,
                     0x5f875f,
                     0x5f8787,
                     0x5f87af,
                     0x5f87d7,
                     0x5f87ff,
                     0x5faf00,
                     0x5faf5f,
                     0x5faf87,
                     0x5fafaf,
                     0x5fafd7,
                     0x5fafff,
                     0x5fd700,
                     0x5fd75f,
                     0x5fd787,
                     0x5fd7af,
                     0x5fd7d7,
                     0x5fd7ff,
                     0x5fff00,
                     0x5fff5f,
                     0x5fff87,
                     0x5fffaf,
                     0x5fffd7,
                     0x5fffff,
                     0x870000,
                     0x87005f,
                     0x870087,
                     0x8700af,
                     0x8700d7,
                     0x8700ff,
                     0x875f00,
                     0x875f5f,
                     0x875f87,
                     0x875faf,
                     0x875fd7,
                     0x875fff,
                     0x878700,
                     0x87875f,
                     0x878787,
                     0x8787af,
                     0x8787d7,
                     0x8787ff,
                     0x87af00,
                     0x87af5f,
                     0x87af87,
                     0x87afaf,
                     0x87afd7,
                     0x87afff,
                     0x87d700,
                     0x87d75f,
                     0x87d787,
                     0x87d7af,
                     0x87d7d7,
                     0x87d7ff,
                     0x87ff00,
                     0x87ff5f,
                     0x87ff87,
                     0x87ffaf,
                     0x87ffd7,
                     0x87ffff,
                     0xaf0000,
                     0xaf005f,
                     0xaf0087,
                     0xaf00af,
                     0xaf00d7,
                     0xaf00ff,
                     0xaf5f00,
                     0xaf5f5f,
                     0xaf5f87,
                     0xaf5faf,
                     0xaf5fd7,
                     0xaf5fff,
                     0xaf8700,
                     0xaf875f,
                     0xaf8787,
                     0xaf87af,
                     0xaf87d7,
                     0xaf87ff,
                     0xafaf00,
                     0xafaf5f,
                     0xafaf87,
                     0xafafaf,
                     0xafafd7,
                     0xafafff,
                     0xafd700,
                     0xafd75f,
                     0xafd787,
                     0xafd7af,
                     0xafd7d7,
                     0xafd7ff,
                     0xafff00,
                     0xafff5f,
                     0xafff87,
                     0xafffaf,
                     0xafffd7,
                     0xafffff,
                     0xd70000,
                     0xd7005f,
                     0xd70087,
                     0xd700af,
                     0xd700d7,
                     0xd700ff,
                     0xd75f00,
                     0xd75f5f,
                     0xd75f87,
                     0xd75faf,
                     0xd75fd7,
                     0xd75fff,
                     0xd78700,
                     0xd7875f,
                     0xd78787,
                     0xd787af,
                     0xd787d7,
                     0xd787ff,
                     0xd7af00,
                     0xd7af5f,
                     0xd7af87,
                     0xd7afaf,
                     0xd7afd7,
                     0xd7afff,
                     0xd7d700,
                     0xd7d75f,
                     0xd7d787,
                     0xd7d7af,
                     0xd7d7d7,
                     0xd7d7ff,
                     0xd7ff00,
                     0xd7ff5f,
                     0xd7ff87,
                     0xd7ffaf,
                     0xd7ffd7,
                     0xd7ffff,
                     0xff0000,
                     0xff005f,
                     0xff0087,
                     0xff00af,
                     0xff00d7,
                     0xff00ff,
                     0xff5f00,
                     0xff5f5f,
                     0xff5f87,
                     0xff5faf,
                     0xff5fd7,
                     0xff5fff,
                     0xff8700,
                     0xff875f,
                     0xff8787,
                     0xff87af,
                     0xff87d7,
                     0xff87ff,
                     0xffaf00,
                     0xffaf5f,
                     0xffaf87,
                     0xffafaf,
                     0xffafd7,
                     0xffafff,
                     0xffd700,
                     0xffd75f,
                     0xffd787,
                     0xffd7af,
                     0xffd7d7,
                     0xffd7ff,
                     0xffff00,
                     0xffff5f,
                     0xffff87,
                     0xffffaf,
                     0xffffd7,
                     0xffffff,
                     0x080808,
                     0x121212,
                     0x1c1c1c,
                     0x262626,
                     0x303030,
                     0x3a3a3a,
                     0x444444,
                     0x4e4e4e,
                     0x585858,
                     0x626262,
                     0x6c6c6c,
                     0x767676,
                     0x808080,
                     0x8a8a8a,
                     0x949494,
                     0x9e9e9e,
                     0xa8a8a8,
                     0xb2b2b2,
                     0xbcbcbc,
                     0xc6c6c6,
                     0xd0d0d0,
                     0xdadada,
                     0xe4e4e4,
                     0xeeeeee
	};
    
    std::map<int, int>  _ansi_color;

	void make_color_map(std::map<int, int>& map, int* _array, size_t _size_array) {

		map.clear();

		for (int t = 0; t != _size_array; ++t)
			map[_array[t]] = t;
	}

#define    DEFINE_rgb2ansi   std::map<int, int>  esc::_ansi_color;                   \
	       esc::make_color_map(esc::_ansi_color, esc::_rgb_colors , 256) ;           \
	       esc::InterContainer rgb2ansi(&_ansi_color);                               \

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    CLASS ADAPTOR TO HANDLE READING VALUE THAT NOT FOUND IN MAP BY LOOKING FOR 
	//    CLOSEST VALUE TO IT THAT CONTAIN IN MAP.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Container>
		requires requires {
		typename Container::key_compare;
		typename Container::key_type;
		typename Container::mapped_type;
	}
	class InterContainer {

		Container* ptr_container;

		using mapped_type = typename Container::mapped_type;
		using key_type = typename Container::key_type;

		// mapped_type(*Function)(const key_type&);

		mapped_type inter_func(const key_type& key) {

			if (ptr_container->contains(key)) return ptr_container->at(key);

			auto it = ptr_container->upper_bound(key);

			if (it == ptr_container->end()) return {};// (--ptr_container->end())->second;

			return it->second;
		}

		// Interpolation function mapped_type _func(key_type, Container *);
	public:
		InterContainer(Container* _ptr)
			: ptr_container{ _ptr }
		{}

		~InterContainer() { ptr_container = nullptr; }

		mapped_type operator[](const key_type& key) {
			return inter_func(key);
		}
	};

	InterContainer rgb2ansi(&_ansi_color);

	int CGreen[]{ 2,10,22,28,29,34,35,40,41,42,46,47,48,71,77,78,82,83,84,85,107,108,
				 112,113,114,115,118,119,120,121,149,150,151,
				 154,155,156,157,158, 191,192,193, };

	////////////////////////////// END  RGB TO CONSOLE 256 COLOR ////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    Small class handle times elapsed in game loop
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	class Elapsed_Time {

		std::chrono::system_clock::time_point _start;
		std::chrono::duration<float> _duration;

	public:

		Elapsed_Time()
			: _start{ std::chrono::system_clock::now() }
			, _duration{}
		{}

		float operator()() {
			_duration = std::chrono::system_clock::now() - _start;
			_start = std::chrono::system_clock::now();
			return _duration.count();
		}
	};

}


// define these two structure for text in console;
using csString = ESC::cString<char>;
using cwString = ESC::cString<wchar_t>;

// define integer and float points
using Pint = ESC::Point2d<int>;
using Pfloat = ESC::Point2d<float>;

namespace esc = ESC;
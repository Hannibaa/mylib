/*
                General Utility for Console Escap Character and more
				
				Author : KADDA Aoues 
				Date   : September 2023
				Name   : escape_code



*/


#pragma once
#include <string>
#include <iomanip>
#include <MyLib\Console_Library\Unicode_table.h>
#include "MyLib/function_utility.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//   ANSI ESCAPE CODE ASCII SEQUENCES
//   FUNCTION AND MACRO PREDEFINED HERE 
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


using uint = unsigned int;
using uchar = unsigned char;

#define _STRING(str)  std::string str{#str}       // define string with his name of variable 
#define _CSTR(x)      std::to_string(x).c_str()   // usefull macro 
#define _CwSTR(x)     std::to_wstring(x).c_str()  // usefull macro 

#define _s(str)       #str
#define _w(wstr)     L#wstr

namespace ESC {

#define end_      '\n'
#define BELL      '\a'
#define hTAB      '\t'
#define vTAB      '\v'
#define BACKSPACE '\b'
#define NEWPAGE   '\f'
#define CR        '\r'
#define ESCAPE    '\x1b'
#define DELETE    '\x7F'

	
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
#define SAVECURSORPOSITION       "\x1b[s"	 // save cursor position (SCO)
#define RESTORCUR_SAVED_POS      "\x1b[u"	 // restores the cursor to the last saved position (SCO)

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
#define _wCOLOR_FG256(i)              L"\x1b[38;5;" << _CSTR(i) << "m"
#define _COLOR_BG256(i)                "\x1b[48;5;" << _CSTR(i) << "m"
#define _wCOLOR_BG256(i)              L"\x1b[48;5;" << _CSTR(i) << "m"

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    define string macro as const char *
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// BEGIN

	namespace Colors {

          const char * _RESETMODE   =  "\x1b[0m"    ;
          const char * _ITALIC      =  "\x1b[3m"	;
          const char * _BLACK_FG    =  "\x1b[30m"	;
          const char * _BLACK_BG    =  "\x1b[40m"	;
          const char * _RED_BG      =  "\x1b[31m"	;
          const char * _RED_FG      =  "\x1b[41m"	;
          const char * _GREEN_FG    =  "\x1b[32m"	;
          const char * _GREEN_BG    =  "\x1b[42m"	;
          const char * _YELLOW_FG   =  "\x1b[33m"	;
          const char * _YELLOW_BG   =  "\x1b[43m"	;
          const char * _BLUE_FG     =  "\x1b[34m"	;
          const char * _BLUE_BG     =  "\x1b[44m"	;
          const char * _MAGENTA_FG  =  "\x1b[35m"	;
          const char * _MAGENTA_BG  =  "\x1b[45m"	;
          const char * _CYAN_FG     =  "\x1b[36m"	;
          const char * _CYAN_BG     =  "\x1b[46m"	;
          const char * _WHITE_FG    =  "\x1b[37m"	;
          const char * _WHITE_BG    =  "\x1b[47m"	;
          const char * _DEFAULT_FG  =  "\x1b[39"	;
          const char * _DEFAULT_BG  =  "\x1b[49"	;
          
          const char * _FG_ = "\x1b[38;2;"          ;
          const char * _BG_ = "\x1b[48;2;"          ; 
          
	}

	// END

	enum Color256 {
		Black = 0        ,
		Maroon           ,
		Green            ,
		Olive            ,
		Navy             ,
		Purple           ,
		Teal             ,
		Silver           ,
		Grey             ,
		Red		         ,
		Lime             ,
		Yellow           ,
		Blue             ,
		Fuchsia          ,
		Aqua             ,
		White            ,
		Grey0            ,
		NavyBlue         ,
		DarkBlue		 ,
		Blue3			 ,
		Blue1			 ,
		DarkGreen		 ,
		DeepSkyBlue40	 ,
		DeepSkyBlue41	 ,
		DeepSkyBlue42	 ,
		DodgerBlue3		 ,
		DodgerBlue2		 ,
		Green4			 ,
		SpringGreen4	 ,
		Turquoise4		 ,
		DeepSkyBlue30	 ,
		DeepSkyBlue31	 ,
		DodgerBlue1

	};

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



	// END


	constexpr std::string COLORFG256(uchar i) {

		std::string str = "\x1b[38;5;" + std::to_string(i) + "m";

		return str;
	}


	constexpr std::string COLORBG256(uchar i) {

		std::string str = "\x1b[48;5;" + std::to_string(i) + "m";

		return str;

	}

	enum FGBG { FG = 38, BG = 48 };

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

#define Print_(color256, text)    print_ << _COLOR_FG256(color256) << text << RESETMODE 
#define WPrint_(color256, text)   wprint_ << _wCOLOR_FG256(color256) << text << RESETMODE 
#define COLOR(color256, text)     _COLOR_FG256(color256) << text << RESETMODE  
#define wCOLOR(color256, text)    _wCOLOR_FG256(color256) << text << RESETMODE  
#define Error_(text)              Print_(color::Red, text) << end_;
#define wError_(text)             WPrint_(color::Red, text) << wend_;


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

		Init_Esc(const char* back_ground,const char* fore_ground)
			:_bg{back_ground}
			,_fg{fore_ground}
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

#define INIT_CURSOR      Init_Cursor    init_cursor
#define WINIT_CURSOR     wInit_Cursor   init_cursor
#define INIT_WCHAR_TEXT  Wchar_Mode     init_wchart_text
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

	void clear_line() {
		print_ << ERASELINE;
	}

	void wcls() {
		wprint_ << ERASESCREEN << MOVEHOME;
	}

	void wclear_line() {
		wprint_ << ERASELINE;
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


	template<typename Function, typename ...Ts>
	void _coloring(color _color, Function func, const Ts&...args) {
		wprint_ << _COLOR_FG256(_color);
		func(args...);
		wprint_ << RESETMODE;
	}

	template<typename Style, typename Function, typename ...Ts>
	void customize(Style _style, Function _function, const Ts&...args) {
		wprint_ << _style;
		_function(args...);
		wprint_ << RESETMODE;
	}

}

namespace esc = ESC;
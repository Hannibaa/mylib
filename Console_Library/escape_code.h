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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//   ANSI ESCAPE CODE ASCII SEQUENCES
//   FUNCTION AND MACRO PREDEFINED HERE 
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


using uint = unsigned int;
using uchar = unsigned char;

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

	// Cursor control
#define MOVEHOME                 "\x1b[H"
#define MOVETO(X,Y)              "\x1b[" << Y << ";"<< X <<"H"
#define MOVEUPLINE(X)            "\x1b[" << X << "A"
#define MOVEDNLINE(X)            "\x1b[" << X << "B"
#define MOVERIGHT(X)             "\x1b[" << X << "C"
#define MOVELEFT(X)              "\x1b[" << X << "D"
#define MOVENXDNLINE(X)          "\x1b[" << X << "E"
#define MOVEPRUPLINE(X)          "\x1b[" << X << "F"
#define MOVECOLM(X)              "\x1b[" << X << "G"
#define REQUEST                  "\x1b[6n"

	// Erase functions
#define ERASEDIS           "\x1b[J"
#define ERASEFCURDN        "\x1b[0J"
#define ERASEFCURBG        "\x1b[1J"
#define ERASESCREEN        "\x1b[2J"
#define ERASESVLINE        "\x1b[3J"

#define ERASEINLINE            "\x1b[K"
#define ERASEFCURENDLINE       "\x1b[0K"
#define ERASELINETOCUR         "\x1b[1K"
#define ERASELINE              "\x1b[2K"

    // Color
#define RESETMODE              "\x1b[0m"
#define ITALIC                 "\x1b[3m"
#define BOLD                   "\x1b[22m"
#define BLACK_FG               "\x1b[30m"
#define RED_FG                 "\x1b[31m"
#define GREEN_FG               "\x1b[32m"
#define YELLOW_FG              "\x1b[33m"
#define BLUE_FG                "\x1b[34m"
#define DEFAULT_FG             "\x1b[39"
#define CYAN_FG                "\x1b[36m"
#define MAGENTA_FG             "\x1b[35m"
#define WHITE_FG               "\x1b[37m"
#define BLACK_BG               "\x1b[40m"
#define RED_BG                 "\x1b[41m"
#define YELLOW_BG              "\x1b[43m"
#define GREEN_BG               "\x1b[42m"
#define BLUE_BG                "\x1b[44m"
#define MAGENTA_BG             "\x1b[45m"
#define CYAN_BG                "\x1b[46m"
#define WHITE_BG               "\x1b[47m"
#define DEFAULT_BG             "\x1b[49"

#define _FG "\x1b[38;2;"
#define _BG "\x1b[48;2;" 

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//   Useful Macro for editing text : 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

#define end_      '\n'
#define wait_     std::cin.get()
#define print_    std::cout 
#define wprint_   std::wcout
#define newline_  std::cout << end_

#define CELL(SIZE,LeftOrRight,STR)   std::setw(SIZE)<< std::LeftOrRight << STR 
#define SPACE(N)                     std::string(N,' ').c_str()
#define REPEAT(N,WCHAR)              std::wstring(N,WCHAR)
#define REPEAT(N,CHAR)               std::string(N,CHAR)
#define _COLOR_FG256(i)              (("\x1b[38;5;" + std::to_string(i) + "m").c_str())

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

#define SCREEN_MODE(value) 	       "\x1b[=" << value << "h"	 // Changes the screen width or type to the mode specified by value.
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

#define RESET(value)	           "\x1b[=" << value << "l"	  
	                    /*Resets the mode by using the same values that Set Mode uses, 
			             except for 7, which disables line wrapping.The last character 
			             in this escape sequence is a lowercase L.
		                  Common Private Modes
		                 These are some examples of private modes, which are not defined
			             by the specification, but are implemented in most terminals.
		                 ESC Code Sequence	Description*/

#define  CURSOR_INVISIBLE		        "\x1b[?25l"    // make cursor invisible
#define  CURSOR_VISIBLE     	        "\x1b[?25h"    // make cursor visible
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

#define Print_(color256, text)   print_ << _COLOR_FG256(color256) << text << RESETMODE 
#define WPrint_(color256, text)  wprint_ << _COLOR_FG256(color256) << text << RESETMODE 
#define COLOR(color256, text)    _COLOR_FG256(color256) << text << RESETMODE  

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

	//Init_Esc Init;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//       USEFUL FUNCTION FOR MANIPULATING TEXT   
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////

using color = ESC::Color256;
void restor_mode() {
	print_ << RESETMODE;
}

void move_to(uint x, uint y){
	print_ << MOVETO(x, y);
}
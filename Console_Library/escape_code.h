#pragma once
#include <string>
#include <iomanip>

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
#define MOVEHOME           "\x1b[H"
#define MOVETO(X,Y)            "\x1b[" << Y << ";"<< X <<"H"
#define MOVEUPLINE(X)            "\x1b[" << X << "A"
#define MOVEDNLINE(X)            "\x1b[" << X << "B"
#define MOVERIGHT(X)            "\x1b[" << X << "C"
#define MOVELEFT(X)  "\x1b[" << X << "D"
#define MOVENXDNLINE(X)  "\x1b[" << X << "E"
#define MOVEPRUPLINE(X)  "\x1b[" << X << "F"
#define MOVECOLM(X)  "\x1b[" << X << "G"
#define REQUEST      "\x1b[6n"

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
#define RESETMODE     "\x1b[0m"
#define ITALIC        "\x1b[3m"
#define BOLD          "\x1b[22m"
#define BLACK_FG         "\x1b[30m"
#define BLACK_BG         "\x1b[40m"
#define RED_BG         "\x1b[41m"
#define RED_FG         "\x1b[31m"
#define GREEN_FG         "\x1b[32m"
#define GREEN_BG         "\x1b[42m"
#define YELLOW_FG         "\x1b[33m"
#define YELLOW_BG         "\x1b[43m"
#define BLUE_FG         "\x1b[34m"
#define BLUE_BG         "\x1b[44m"
#define MAGENTA_FG         "\x1b[35m"
#define MAGENTA_BG         "\x1b[45m"
#define CYAN_FG         "\x1b[36m"
#define CYAN_BG         "\x1b[46m"
#define WHITE_FG         "\x1b[37m"
#define WHITE_BG         "\x1b[47m"
#define DEFAULT_FG      "\x1b[39"
#define DEFAULT_BG      "\x1b[49"

#define _FG "\x1b[38;2;"
#define _BG "\x1b[48;2;" 

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//   Useful Macro for editing text : 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////


#define wait_     std::cin.get()
#define print_    std::cout 
#define newline_  std::cout << '\n';

#define CELL(SIZE,LeftOrRight,STR)   std::setw(SIZE)<< std::LeftOrRight << STR 
#define SPACE(N)             std::string(N,' ').c_str()

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    define string macro as const char *
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// BEGIN

	namespace Colors {

          const char * _RESETMODE   =  "\x1b[0m"  ;
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
          const char * _DEFAULT_bG  =  "\x1b[49"	;
          
          const char * _FG_ = "\x1b[38;2;";
          const char * _BG_ = "\x1b[48;2;"; 
          
	}

	// END
	std::string COLORFG256(uchar i) {

		std::string str = "\x1b[38;5;" + std::to_string(i) + "m";

		return str;
	}

	std::string COLORBG256(uchar i) {

		std::string str = "\x1b[48;5;" + std::to_string(i) + "m";

		return str;

	}

	enum FGBG { FG = 38, BG = 48 };

	std::string rgbCOLOR(uint r, uint g, uint b, FGBG fgbg) {

		std::string bg{};

		if (fgbg == FG) bg = _FG; else bg = _BG;

		std::string str = bg + std::to_string(r) + ";"
			+ std::to_string(g) + ";"
			+ std::to_string(b) + "m";
		return str;
	}

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
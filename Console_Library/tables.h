/*
 *****************************************************************************
 *                                                                           *
 *                                                                           *
 *                  Console Table Manipulation  Library                      *
 *                                                                           *
 * Author: KADDA Aoues - haoues_k@yahoo.fr - 2023                            *
 * Date : 27 / 11 / 2023                                                     *
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

#define bg_color(i)      "\x1b[48;5;"#i"m" 
#define fg_color(i)      "\x1b[38;5;"#i"m"

struct TITLE {
    std::string _name;
    std::string _fgcolor;
    std::string _bgcolor;
    int         _width;
    char        _sep0;
    char        _sep1;
};

// Contructor for TITLE stuct
#define CellCtor(T,name, bg, fg, width, sep0 , sep1 )     	TITLE T;     \
   /* define background color */     T._bgcolor = bg_color(bg);			 \
   /* define text color */           T._fgcolor = fg_color(fg);			 \
   /* define name of cell */         T._name = #name;					 \
   /* define width of cell */        T._width = width;					 \
   /* define first separator '|' */  T._sep0 = sep0;					 \
   /* define last separator '|' */   T._sep1 = sep1;					 \

// macro table formatting
#define _cell(t,right_left)             t._sep0                \
                                     << t._fgcolor             \
                                     << t._bgcolor             \
                                     << std::setw(t._width)    \
                                     << std::right_left        \
                                     << t._name << RESETMODE   \
                                     << t._sep1                \

// Macro : Draw from struct title 
#define _cellv(t,right_left, value)   t._sep0 << t._fgcolor << t._bgcolor << std::setw(t._width)   \
                                       << std::right_left << value << RESETMODE << t._sep1 \

#define _cellr(sleft, fg, bg, width, right_left , value , srigth)       sleft                 \
                            << fg << bg << std::setw(width)          \
                            << std::right_left << value << RESETMODE << srigth  \



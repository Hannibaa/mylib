/*
 *****************************************************************************
 *                                                                           *
 *                                                                           *
 *                  Console Table Manipulation  Library                      *
 *                                                                           *
 * Author : KADDA Aoues - haoues_k@yahoo.fr - 2023                           *
 * Date   : 27 / 11 / 2023                                                   *
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
// Todo documenting this header files

#pragma once

#include <iomanip>
#include "MyLib/Console_Library/escape_code.h"


#define bg_color(i)      "\x1b[48;5;"#i"m" 
#define fg_color(i)      "\x1b[38;5;"#i"m"

// here will define table box for making table in char;
// 1. table box

#define table_vline                         '\xb3'
#define table_hline                         '\xc4'
#define table_tee_left                      '\xb4'
#define table_tee_right                     '\xc3'
#define table_tee_up                        '\xc1'
#define table_tee_down                      '\xc2'
#define table_xross                         '\xc5'
#define table_corner_upleft                 '\xda'
#define table_corner_upright                '\xbf'
#define table_corner_dnleft                 '\xc0'
#define table_corner_dnright                '\xd9'


// 2. solid 
#define  table_solid_left         '\xdd'
#define  table_solid_right        '\xde'
#define  table_solid_complete     '\xdb'
#define  table_solid_up           '\xdf'
#define  table_solid_down         '\xdc'
#define  table_solid_center       '\xfe'


namespace table {
    // making global variable 
    int _xPos{};
    int _yPos{};

    // function initialize these varible
    void init_coordinate_table(const int x, const int y) {
        _xPos = x;
        _yPos = y;
    }

    // style for cells 
    struct STYLE {
        int   _fg_color;     // foreground color , text color
        int   _bg_color;     // background color , back area color
        int   _width;        // width of cell , 
        char  _b_sep;   // b for beginerdelemeter of cell like bar '|' or another glyph bars
        char  _e_sep;   // end delemeter if not equal to beginer, or is null,
    };

    // function to constructe styles in place
    STYLE make_style(int fg_col, int bg_col, int width, char begin, char end) {
        return STYLE{
            ._fg_color = fg_col,
            ._bg_color = bg_col,
            ._width    = width,
            ._b_sep    = begin,
            ._e_sep    = end,
       };
    }

    // make macro that affect any text to cell style: we keep separator uncolored
    #define    _cell(text, style, left_right)       style._b_sep << _COLOR_BG256( style._bg_color)    \
                                                   << _COLOR_FG256(style._fg_color)    \
                                                   << std::setw(style._width)    \
                                                   << std::left_right            \
                                                   << text << RESETMODE          \
                                                   << style._e_sep          \
    
    // make macro for _cell underline;
#define    _cell_uline(text, style, left_right)    style._b_sep << UNDERLINE << _COLOR_BG256( style._bg_color)    \
                                                   << _COLOR_FG256(style._fg_color)    \
                                                   << std::setw(style._width)    \
                                                   << std::left_right            \
                                                   << text << RESETMODE          \
                                                   << style._e_sep          \


    void make_simple_table( const std::string& title,        STYLE s_title,
                            const std::string& sub_title_l,  STYLE s_sub_left,
                            const std::string& sub_title_r,  STYLE s_sub_right  );


    template<typename T>
    std::string add_line_table(const T& cell_l, STYLE sleft, const T& cell_r, STYLE sright) {
        std::stringstream ss;

        ss << UNDERLINE << _cell(std::to_string(cell_l), sleft, right)
           << UNDERLINE << _cell(std::to_string(cell_r), sright, right) << end_;

        return ss.str();
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //     CLASS TABLE
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////


    class ITable {
    public:

        virtual void set_style(const STYLE&) = 0;
        virtual void draw() const = 0;

        virtual ~ITable() {}
    };


    class DTable {
    public:
        Pint _pos;                  // upper left coordinate of table

        // style of cell should be one;
        STYLE               _style;
        STYLE               _style_title;
        STYLE               _style_cells;
        STYLE               _style_head;

        std::string         _title;
        std::string         _Xtitle;
        std::string         _Ytitle;

        DTable(int x, int y, const std::string_view& title, 
            const STYLE& unique_style = STYLE{})  // todo define predefined style
            :_pos{x,y}
            ,_title{title}
            , _Xtitle{}
            , _Ytitle{}
            , _style{unique_style}
            , _style_title{unique_style}
            , _style_head{unique_style}
            , _style_cells{unique_style}
        {}

        virtual ~DTable() {}
    };


    // this table only for two element
    // will making multicolomne element in Excel.

    template<typename Xtype, typename Ytype>
    class Table : private DTable , public ITable {

        std::vector<Xtype>   _vecX;
        std::vector<Xtype>   _vecY;

    public:

        Table(int x, int y, std::string_view title)
            :DTable(x,y,title)
            , _vecX{}
            , _vecY{}
        {}


        virtual void set_style(const STYLE& style) override {
           _style = style;
        }

        void set_style_title(const STYLE& style) {
            _style_title = style;
        }

        void set_style_cell(const STYLE& style) {
            _style_cells = style;
        }

        void set_style_head(const STYLE& style) {
            _style_head = style;
        }

        void set_title(const std::string_view title)  {
            _title = title;
        }

        void set_titlesXY(const std::string_view titleX, const std::string_view titleY) {
            _Xtitle = titleX;
            _Ytitle = titleY;
        }

        void add_line(const Xtype& x, const Ytype& y)  {
            _vecX.push_back(x);
            _vecY.push_back(y);
        }

        void add_lines(const std::vector<Xtype>& vx, const std::vector<Ytype>& vy) {
            _vecX.insert(_vecX.end(), vx.begin(), vx.end());
            _vecY.insert(_vecY.end(), vy.begin(), vy.end());
        }

        virtual void draw() const override {

            // making begin style and end style 
            STYLE send = _style_cells;
            send._b_sep = 0;

            STYLE hend = _style_head;
            hend._b_sep = 0;


            printm_(_pos.x + 3, _pos.y - 2) << _cell(_title, _style_title, left);

            printm_(_pos.x, _pos.y) ;
            print_ << _cell_uline(_Xtitle, _style_head, left)
                   << _cell_uline(_Ytitle, hend, left)  ;

            for (int j = 0; j < _vecX.size(); ++j) {
                printm_(_pos.x, _pos.y + j + 1);
                print_ << _cell(_vecX[j], _style_cells, left)
                       << _cell(_vecY[j], send, left);
            }

        }
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //     Multicolomn Table
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    class IMTable {
    public:
        
        virtual void draw() const = 0;


        ~IMTable() {}
    };

    class DMTable {
    public:

        using sTitle = std::pair<std::string, STYLE>;
#define  _tcell(stitle, left_right)  _cell(stile.first, stitle.second, left_right)
#define  _utcell(stitle, left_right) _cell_uline(stitle.first, stitle.second, left_right)

        Pint                        _pos;

        sTitle                      _title;
        std::vector<sTitle>         _Vtitles;

        DMTable(int x, int y, std::string_view title, STYLE title_style)
            :_pos(x, y)
            ,_title{title,title_style}
        {}

        virtual void set_cellHead(const std::string_view stitle, const STYLE& style) = 0;

        ~DMTable() {}
    };

    template<typename...Ts >
    class MTable : private DMTable, public IMTable {

        std::tuple<std::vector<Ts>...>  Values;
        constexpr size_t Column = sizeof...(Ts);

    public:

        MTable(int x, int y, const std::string_view title, STYLE title_style)
            :DMTable(x,y, title, title_style)
            , Values{}
        {}

        virtual void set_cellHead(const std::string_view title, const STYLE& style) override {
            _Vtitles.emplace_back(title, style);
        }

        void 


        virtual void draw() override const {
            // making begin style and end style 

            printm_(_pos.x + 3, _pos.y - 2) << _tcell(_title, left);

            printm_(_pos.x, _pos.y);
            for (const auto& Xtitle : _Vtitles)
                print_ << _utcell(Xtitle, left);


            for (int j = 0; j < _vecX.size(); ++j) {
                printm_(_pos.x, _pos.y + j + 1);
                for (int i = 0; i < Column; ++i)
                    print_ << _tcell(std::get<i>(Values)[j], left);
            }
        }

    };


}
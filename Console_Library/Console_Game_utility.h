#pragma once
/*
* 
        THIS UTILITY MADE FOR ONLY GAME CONSOLE 
        WE TAKING SOME IDEA FROM OTHER LIBRERY LIKE
        SFML AND OPENGL;
        WE DEFINING HERE SOME TEMPLATE
        2D VECTOR 
        LOGIC FUNCTION
        STRUCTURE
        SCREEN VIEW
        SCREEN SHOW

*/
#include <vector>
#include <string>

#define F2d(X,A,B,C)  A*X*X+B*X+C   

using namespace std;

int nScreenWidth = 144;
int nScreenHeight = 35;

int sz_screen = nScreenHeight * nScreenWidth;

wchar_t* screen;
const int Max_Size = 10;   // THIS NOT STANDARD IS JUST TO DEFINING SOME FUNCTION IN 

template<typename T>              // POINT 2D TEMPLATE
struct Point2d {
	T x;
	T y;
};

template<typename T>              // RECTANGLE STRUCTURE FOR LOGICAL EXPRESSION
struct Rect {
	T top;
	T left;
	T width;
	T height;
};

typedef Rect<float>    RectFloat;       // RECT DEFINITION
typedef Rect<int>      RectInt;
typedef Point2d<float> Point2df;
typedef Point2d<int>   Point2di;

RectInt screenRecti{ 0, 0, nScreenWidth, nScreenHeight };
RectFloat screenRectf{ 0.f, 0.f, float(nScreenWidth), float(nScreenHeight) };

template<typename T>
bool IsPointInRect(Point2d<T> p, Rect<T> rect)    // Condition in  
{
	if (p.x > rect.left &&
		p.x < rect.left + rect.width &&
		p.y > rect.top &&
		p.y < rect.top + rect.height) return true;

	return false;
}

bool IsRectInRect(Point2di p, Point2di dim, RectInt rect)
{
	if (p.x > rect.left &&
		p.x + dim.x < rect.left + rect.width &&
		p.y > rect.top &&
		p.y + dim.y < rect.top + rect.height) return true;

	return false;
}

struct ScrBuffer {                                //  Class used for storing buffer of text 
	vector<wstring> vwString;
	Point2di position;
	Point2di Dimension;

	ScrBuffer(vector<wstring> vBuff)
		: vwString{ vBuff },
		position{ 10,10 }
	{
		Dimension = getBoundRect();
	}
	void push_Buffer(wstring wstr) {
		vwString.push_back(wstr);
		Dimension = getBoundRect();
	}

	void push_Buffer(vector<wstring> vBuffer) {
		for (auto& str : vBuffer) vwString.push_back(str);
		Dimension = getBoundRect();
	}

	const Point2di& getBoundRect() const {
		// width is maximum string length of vector buffer element
		// height is size of vector buffer
		Point2di dim_;
		dim_.y = vwString.size();
		dim_.x = ( * max_element(vwString.begin(), vwString.end(),
			[](wstring a, wstring b) { return a.size() < b.size(); })).size();        // THIS SHOULD BE REMOVED 

		return dim_;
	}

	void setPosition(Point2di p) {
		position = p;
	}
	void setPosition(int x, int y) {
		position.x = x;
		position.y = y;
	}

	void draw()
	{
		
		for (int i = 0; i < vwString.size(); i++)
		{
			for (int j = 0; j < vwString[i].size(); j++)
			{
				if (iswprint(vwString[i][j]))
				{
					if ( IsRectInRect({j,i},Dimension,screenRecti))
					screen[j+position.x + (i+position.y) * nScreenWidth] = vwString[i][j];
				}
			}
		}
	}
};

template<typename T>
struct _Screen {                                            // Screen 

	void operator () (Point2d<T> p, wchar_t glyph) {
		Point2di pint{ int(p.x), int(p.y) };                                                    // WE NEED TO PUT THE CONDITION HERE
		screen[pint.x + pint.y * nScreenWidth] = glyph;           // THAT WILL PUT COORD IN RECTANGLE OF SCREEN
	}

	void operator () (Point2d<T> p, const wstring wstr) {
		Point2di pint{ int(p.x), int(p.y) };
		for (int i = 0; i < wstr.size(); i++)
		{
			if (IsRectInRect(p,{0,wstr.size()}, screenRecti))
			screen[(p.x + i) + p.y * nScreenWidth] = wstr[i];
		}
	}


};

_Screen<int>    Screen ;
_Screen<float>  Screenf;

void pointScr(Point2di position, wchar_t glyph)
{
	if (IsPointInRect(position, screenRecti))
		Screen(position, glyph);
}

void pointScrf(Point2df position, wchar_t glyph)
{
	if (IsPointInRect<float>(position, screenRectf))
		Screenf(position, glyph);
}


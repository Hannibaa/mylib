#pragma once
#include <vector>
#include <array>
#include <algorithm>
#include "C:\Users\Acer\source\MyLib\vector_utility1.h"
#include "C:\Users\Acer\source\MyLib\geometry2d_utility.h"

const int MAX_LEVEL = 3;
const int MINIMUM_POINTS = 15;

template<typename T>
struct Rect {
	T x;
	T y;
	T width;
	T height;

	Rect()
		: x{}, y{}, width{}, height{}
	{}

	Rect(T _x, T _y , T _w, T _h)
		:x{_x} , y{_y} , width{_w} , height{_h}
	{}

	template<typename U>
	Rect<U> as() {
		
		U _x = static_cast<U>(x);
		U _y = static_cast<U>(y);
		U _width = static_cast<U>(width);
		U _height = static_cast<U>(height);

		return Rect<U>(_x,_y, _width,_height);
	}

	void clear() {
		x = T{};
		y = T{};
		width = T{};
		height = T{};
	}

	/*template<template<typename> class Point = Pair>
	bool contain(const Point<T>& point)
	{
		auto X = getCoord(point, 0);
		auto Y = getCoord(point, 1);
		return x <= X && X <= x + width &&
			y <= Y && Y <= y + height;
	}*/
};

template<typename T>
constexpr bool isPointInRect(const std::pair<T, T>& point, const Rect<T>& rect)
{
	return rect.x <= point.first  && point.first <= rect.x + rect.width &&
		   rect.y <= point.second && point.second <= rect.y + rect.height;
}

template<typename T, template<typename> class P>
constexpr bool isPointInRect(const P<T>& point, const Rect<T>& rect)
{
	return rect.x <= point.x && point.x <= rect.x + rect.width &&
		   rect.y <= point.y && point.y <= rect.y + rect.height;
}

template<typename T, template<typename>class Point = Pair >
struct Region {
	Rect<T> rectangle;
	std::vector<Point<T>> vPoints;

	size_t numberPoints;

	Region() : rectangle(), numberPoints{} {};
	 
	Region(const Rect<T>& rect, std::vector<Point<T>>& _vPoints)
		:rectangle(rect)
	{
		// check if point include in region rect ?
		for (int i = 0; i < _vPoints.size() ; i++)
		{
			if (isPointInRect(_vPoints[i], rectangle)) {
				vPoints.push_back(_vPoints[i]);
				_vPoints.erase(_vPoints.begin() + i);
				--i;
			}
		}
		numberPoints = vPoints.size();
	}

	void clear() {
		vPoints.clear();
		numberPoints = 0;
		rectangle.clear();
	}
};

template<typename T, template<typename> class Point = Pair>
struct QuadTree {
	Region<T,Point> data;
	std::shared_ptr<QuadTree> q00;
	std::shared_ptr<QuadTree> q01;
	std::shared_ptr<QuadTree> q10;
	std::shared_ptr<QuadTree> q11;
	bool isleaf;

	QuadTree(const Rect<T>& rect, std::vector<Point<T>>& _vPoint)
		: data(rect,_vPoint)
		, q00{ nullptr }
		, q01{ nullptr }
		, q10{ nullptr }
		, q11{ nullptr }
		, isleaf{true}
	{}

	QuadTree(const Region<T, Point>& region)
		:data(region)
		, q00{ nullptr }
		, q01{ nullptr }
		, q10{ nullptr }
		, q11{ nullptr }
		, isleaf{true}
	{}

};

template<typename T>
std::array<Rect<T>, 4> makeSubRect(const Rect<T>& rect) {
	std::array<Rect<T>, 4> vRect;
	T w = rect.width / T(2);
	T h = rect.height / T(2);
	// 1. rectangle 00
	vRect[0].x = rect.x;
	vRect[0].y = rect.y;
	vRect[0].width = w;
	vRect[0].height = h;
	// 2. rectangle 01
	vRect[1].x = rect.x + w;
	vRect[1].y = rect.y;
	vRect[1].width = w;
	vRect[1].height = h;
	// 3. rectangle 10
	vRect[2].x = rect.x;
	vRect[2].y = rect.y + h;
	vRect[2].width = w;
	vRect[2].height = h;
	// 4. rectangle 11
	vRect[3].x = rect.x + w;
	vRect[3].y = rect.y + h;
	vRect[3].width = w;
	vRect[3].height = h;

	return vRect;
}

// MAKE SUB REGION OF QUADTREE
template<typename T, template<typename> class Point = Pair>
std::array<Region<T, Point>, 4> makeSubRegion( Region<T, Point>& region)
{
	std::array<Region<T, Point>, 4> vRegion;
	std::array<Rect<T>, 4> vRect = makeSubRect(region.rectangle);
	vRegion[0] = Region<T,Point>(vRect[0], region.vPoints);
	vRegion[1] = Region<T,Point>(vRect[1], region.vPoints);
	vRegion[2] = Region<T,Point>(vRect[2], region.vPoints);
	vRegion[3] = Region<T,Point>(vRect[3], region.vPoints);

	region.numberPoints = region.vPoints.size();

	return vRegion;
}

// MAKE CHILD BY SPLITE RECTANGLE 
template<typename T, template<typename> class Point = Pair>
void makeChildQuadTree_(QuadTree<T, Point>& qtree)
{
	if (&qtree == nullptr) return;
	if (qtree.data.numberPoints == 0) return;
	qtree.isleaf = false;

	std::array<Rect<T>, 4> vRect = makeSubRect(qtree.data.rectangle);
	Region<T, Point> region;
	// make shared and alocate for four quadrants
	// check if this rectangle have points if not we dont create this quadchild
	region = Region(vRect[0], qtree.data.vPoints);
	if ( region.numberPoints != 0 ) 
	     qtree.q00 = std::make_shared<QuadTree<T,Point>>(region);
	region.clear();
	
	region = Region(vRect[1], qtree.data.vPoints) ; 
	if (region.numberPoints != 0)
		qtree.q01 = std::make_shared<QuadTree<T, Point>>(region);
	region.clear();

	region = Region(vRect[2], qtree.data.vPoints);
	if (region.numberPoints != 0)
		qtree.q10 = std::make_shared<QuadTree<T, Point>>(region);
	region.clear();

	region = Region(vRect[3], qtree.data.vPoints);
	if (region.numberPoints != 0)
		qtree.q11 = std::make_shared<QuadTree<T, Point>>(region);
	region.clear();

}


// MAKE CHILD BY REGION ... not use 
template<typename T, template<typename> class Point>
void makeChildQuadTree(QuadTree<T, Point>& qtree)
{
	// condition  for no creation of subdivision
	if (&qtree == nullptr) return;
	if (qtree.data.numberPoints == 0) {
		qtree.isleaf = true;
		return;
	}

	qtree.isleaf = false;

	std::array<Region<T, Point>, 4> vData = makeSubRegion(qtree.data);

	if (vData[0].numberPoints != 0)
		qtree.q00 = std::make_shared<QuadTree<T, Point>>(vData[0]);
	if (vData[1].numberPoints != 0)
		qtree.q01 = std::make_shared<QuadTree<T, Point>>(vData[1]);
	if (vData[2].numberPoints != 0)
		qtree.q10 = std::make_shared<QuadTree<T, Point>>(vData[2]);
	if (vData[3].numberPoints != 0)
		qtree.q11 = std::make_shared<QuadTree<T, Point>>(vData[3]);

	
}

// MAKE CHILD BY REGION < for spacial information
template<typename T, template<typename> class Point>
void makeChildQuadTree2(QuadTree<T, Point>& qtree)
{
	// condition  for no creation of subdivision
	if (&qtree == nullptr) return;
	if (qtree.data.numberPoints == 0) {
		qtree.isleaf = true;
		return;
	}

	qtree.isleaf = false;

	std::array<Region<T, Point>, 4> vData = makeSubRegion(qtree.data);

		qtree.q00 = std::make_shared<QuadTree<T, Point>>(vData[0]);
		qtree.q01 = std::make_shared<QuadTree<T, Point>>(vData[1]);
		qtree.q10 = std::make_shared<QuadTree<T, Point>>(vData[2]);
		qtree.q11 = std::make_shared<QuadTree<T, Point>>(vData[3]);

}

// MAKE CHILD DEPEND TO NUMBER OF POINTS
template<typename T, template<typename> class Point>
void makeChildQuadTree3(QuadTree<T, Point>& qtree,size_t num_points = MINIMUM_POINTS)
{
	// condition  for no creation of subdivision
	if (&qtree == nullptr) return;

	// if there are no points dont create child == 0
	// minimum required points to create childs == MINIMUM_POINTS
	if (num_points > 20) num_points = MINIMUM_POINTS;
	if (qtree.data.numberPoints == 0 || qtree.data.numberPoints < num_points + 1) {
		qtree.isleaf = true;
		return;
	}

	qtree.isleaf = false;

	std::array<Region<T, Point>, 4> vData = makeSubRegion(qtree.data);

	qtree.q00 = std::make_shared<QuadTree<T, Point>>(vData[0]);
	qtree.q01 = std::make_shared<QuadTree<T, Point>>(vData[1]);
	qtree.q10 = std::make_shared<QuadTree<T, Point>>(vData[2]);
	qtree.q11 = std::make_shared<QuadTree<T, Point>>(vData[3]);

}



// MAKE TREE OF LEVEL UP TO 3 AS MAXIMUM WITH QUADTREE
template<typename T, template<typename> class Point = Pair>
void makeChildQuadTreeLevel(QuadTree<T, Point>& qtree, size_t level) {
	if (level == 0) return;

	makeChildQuadTree2<T,Point>(qtree);
	for(size_t i = 0; i < level && i < MAX_LEVEL ; i++)
	    {
		    if (qtree.q00 != nullptr) 
                if (qtree.q00->data.numberPoints != 0 ) makeChildQuadTreeLevel<T, Point>(*qtree.q00, level - i - 1);
			if (qtree.q01 != nullptr) 
                if (qtree.q01->data.numberPoints != 0 ) makeChildQuadTreeLevel<T, Point>(*qtree.q01, level - i - 1);
			if (qtree.q10 != nullptr) 
                if (qtree.q10->data.numberPoints != 0 ) makeChildQuadTreeLevel<T, Point>(*qtree.q10, level - i - 1);
			if (qtree.q11 != nullptr) 
				if (qtree.q11->data.numberPoints != 0 ) makeChildQuadTreeLevel<T, Point>(*qtree.q11, level - i - 1);
	    }
}

// MAKE QUAD TREE DEPEND TO THE MINIMUM NUMBER OF POINTS IN TREES LEAF;
template<typename T, template<typename> class Point = Pair>
void makeChildQuadTreeComplete(QuadTree<T, Point>& qtree, size_t min_number_points = MINIMUM_POINTS) {
	
	if (&qtree == nullptr) return;

	makeChildQuadTree3<T, Point>(qtree,min_number_points);

		if (qtree.q00 != nullptr)
			if (qtree.q00->data.numberPoints > min_number_points )
				makeChildQuadTreeComplete<T, Point>(*qtree.q00, min_number_points);
		if (qtree.q01 != nullptr)
			if (qtree.q01->data.numberPoints > min_number_points)
				makeChildQuadTreeComplete<T, Point>(*qtree.q01, min_number_points);
		if (qtree.q10 != nullptr)
			if (qtree.q10->data.numberPoints > min_number_points)
				makeChildQuadTreeComplete<T, Point>(*qtree.q10, min_number_points );
		if (qtree.q11 != nullptr)
			if (qtree.q11->data.numberPoints > min_number_points)
				makeChildQuadTreeComplete<T, Point>(*qtree.q11, min_number_points );

}


//  PRINTING QTREE FIRST ARROW
template<typename T, template<typename> class Point = Pair>
void PrindQt(const QuadTree<T, Point>& qtree)
{
	std::cout << "Rectangle ----------------------------\n";
	std::cout << "Point [ " << qtree.data.rectangle.x << " , " << qtree.data.rectangle.y << " ], w;h = "
		<< qtree.data.rectangle.width << " ; " << qtree.data.rectangle.height << '\n';
	//std::cin.get();
	std::cout << "Points --- " << qtree.data.numberPoints << " ------------\n";
	/*int count{};
	for (auto& v : qtree.data.vPoints) {
		std::cout << ++count << " [ " << getCoord(v,0) << " , " << getCoord(v,1) << " ]\n";
		if (count % 20 == 0) std::cin.get();
	}
	std::cin.get();*/
	// check if there are child 
	if (qtree.q00 != nullptr) std::cout << " q00 exit ?!\n";else std::cout << " q00 Not exit\n";
	if (qtree.q01 != nullptr) std::cout << " q01 exit ?!\n";else std::cout << " q01 Not exit\n";
	if (qtree.q10 != nullptr) std::cout << " q10 exit ?!\n";else std::cout << " q10 Not exit\n";
	if (qtree.q11 != nullptr) std::cout << " q11 exit ?!\n";else std::cout << " q11 Not exit\n";
}

// PRINT POINT OF FIRST CHILD OF QUADTREE
template<typename T, template<typename> class Point = Pair>
void PrintChildsQtree(const QuadTree<T, Point>& qtree)
{
	// check if there are child 
	std::cout << "----- Print Children ---\n";
	if (qtree.q00 != nullptr )
	{
		PrindQt(*qtree.q00);
	}

	if (qtree.q01 != nullptr )
	{
		PrindQt(*qtree.q01);
	}

	if (qtree.q10 != nullptr )
	{
		PrindQt(*qtree.q10);
	}

	if (qtree.q11 != nullptr )
	{
		PrindQt(*qtree.q11);
	}
}

// PRINT ALL DATA OF QUADTREE AND ALL SUB TREES
template<typename T, template<typename> class Point = Pair>
void printQuadTree(const QuadTree<T, Point>& qt)
{
	if (&qt == nullptr) return;
	// if this quad tree have point than printed if no dont let me know
	if ( qt.data.numberPoints != 0)	PrindQt(qt);
	std::cin.get();
	// print all child if not nullptr
	if (qt.q00 != nullptr)
	{
		printQuadTree(qt.q00);
	}

	if (qt.q01 != nullptr)
	{
		printQuadTree(qt.q01);
	}

	if (qt.q10 != nullptr)
	{
		printQuadTree(qt.q10);
	}

	if (qt.q11 != nullptr)
	{
		printQuadTree(qt.q11);
	}

}

template<typename T, template<typename> class Point = Pair>
void printQuadTree(std::shared_ptr<QuadTree<T, Point>> qt)
{
	printQuadTree(*qt);
}

// Looking for points
template<typename T, template<typename> class Point = Pair>
void printQTinPoint(const Point<T>& point, const QuadTree<T, Point>& rootQT)
{
	if (rootQT.data.numberPoints != 0) {
		if (isPointInRect(point, rootQT.data.rectangle))
		{
			std::cout << "Check root\n";
			PrindQt(rootQT);
			return;
		}
	}
	// if numberPoint = 0 mean there leafs
	// check leaf not nullptr
	if (rootQT.q00 != nullptr) 
		if (isPointInRect(point, rootQT.q00->data.rectangle))
		    if (rootQT.q00->data.numberPoints != 0  )
		    {
				std::cout << "Check 1\n";
		        PrindQt(*rootQT.q00);
		        return;
			}
			else {
				printQTinPoint<T,Point>(point,*rootQT.q00);
			}

	if (rootQT.q01 != nullptr)
		if (isPointInRect(point, rootQT.q01->data.rectangle))
			if (rootQT.q01->data.numberPoints != 0 )
			{
				std::cout << "Check 2\n";
				PrindQt(*rootQT.q01);
				return;
			}
			else {
				printQTinPoint<T,Point>(point, *rootQT.q01);
			}

	if (rootQT.q10 != nullptr)
		if (isPointInRect(point, rootQT.q10->data.rectangle))
			if (rootQT.q10->data.numberPoints != 0 )
			{
				std::cout << "Check 3\n";
				PrindQt(*rootQT.q10);
				return;
			}
			else {
				printQTinPoint<T,Point>(point, *rootQT.q10);
			}

	if (rootQT.q11 != nullptr)
		if (isPointInRect(point, rootQT.q11->data.rectangle))
			if (rootQT.q11->data.numberPoints != 0 )
			{
				std::cout << "Check 4\n";
				PrindQt(*rootQT.q11);
				return;
			}
			else {
				printQTinPoint<T,Point>(point, *rootQT.q11);
			}

}


template<typename T, template<typename> class Point = Pair >
 void getVectorPoint(const Point<T>& point, const QuadTree<T, Point>& rootQT, std::vector<Point<T>>& tmpPoints)
 {
	 if (rootQT.data.numberPoints != 0) {
		if (isPointInRect(point, rootQT.data.rectangle))
		{
			std::cout << "check root\n";
			tmpPoints = rootQT.data.vPoints;
			return;
		}
	}
	// if numberPoint = 0 mean there leafs
	// check leaf not nullptr
	if (rootQT.q00 != nullptr)
		if (isPointInRect(point, rootQT.q00->data.rectangle))
			if (rootQT.q00->data.numberPoints != 0)
			{
				std::cout << "check 1\n";
				tmpPoints =  rootQT.q00->data.vPoints ;
			//	printfVec(tmpPoints);
				return ;
			}
			else {
				getVectorPoint<T, Point>(point, *rootQT.q00,tmpPoints);
			}

	if (rootQT.q01 != nullptr)
		if (isPointInRect(point, rootQT.q01->data.rectangle))
			if (rootQT.q01->data.numberPoints != 0)
			{
				std::cout << "check 2\n";
				tmpPoints = rootQT.q01->data.vPoints;
				return ;
			}
			else {
				getVectorPoint<T, Point>(point, *rootQT.q01, tmpPoints);
			}

	if (rootQT.q10 != nullptr)
		if (isPointInRect(point, rootQT.q10->data.rectangle))
			if (rootQT.q10->data.numberPoints != 0)
			{
				std::cout << "check 3\n";
				tmpPoints = rootQT.q10->data.vPoints;
				return ;
			}
			else {
				getVectorPoint<T, Point>(point, *rootQT.q10,tmpPoints);
			}

	if (rootQT.q11 != nullptr)
		if (isPointInRect(point, rootQT.q11->data.rectangle))
			if (rootQT.q11->data.numberPoints != 0)
			{
				std::cout << "check 4\n";
				tmpPoints = rootQT.q11->data.vPoints;
				return ;
			}
			else {
				getVectorPoint<T, Point>(point, *rootQT.q11, tmpPoints);
			}

}

 template<typename T, template<typename> class Point = Pair>
 void getRegion(const Point<T>& point, const QuadTree<T, Point>& rootQT, Region<T,Point>& region)
 {
	 if (rootQT.data.numberPoints != 0) {
		 if (isPointInRect(point, rootQT.data.rectangle))
		 {
			 std::cout << "check root\n";
			 region = rootQT.data;
			 return;
		 }
	 }
	 // if numberPoint = 0 mean there leafs
	 // check leaf not nullptr
	 if (rootQT.q00 != nullptr)
		 if (isPointInRect(point, rootQT.q00->data.rectangle))
			 if (rootQT.q00->data.numberPoints != 0)
			 {
				 std::cout << "check 1\n";
				 region = rootQT.q00->data;
				 return;
			 }
			 else {
				 getRegion<T, Point>(point, *rootQT.q00, region);
			 }

	 if (rootQT.q01 != nullptr)
		 if (isPointInRect(point, rootQT.q01->data.rectangle))
			 if (rootQT.q01->data.numberPoints != 0)
			 {
				 std::cout << "check 2\n";
				 region = rootQT.q01->data;
				 return;
			 }
			 else {
				 getRegion<T, Point>(point, *rootQT.q01, region);
			 }

	 if (rootQT.q10 != nullptr)
		 if (isPointInRect(point, rootQT.q10->data.rectangle))
			 if (rootQT.q10->data.numberPoints != 0)
			 {
				 std::cout << "check 3\n";
				 region = rootQT.q10->data;
				 return;
			 }
			 else {
				 getRegion<T, Point>(point, *rootQT.q10, region);
			 }

	 if (rootQT.q11 != nullptr)
		 if (isPointInRect(point, rootQT.q11->data.rectangle))
			 if (rootQT.q11->data.numberPoints != 0)
			 {
				 std::cout << "check 4\n";
				 region = rootQT.q11->data;
				 return;
			 }
			 else {
				 getRegion<T, Point>(point, *rootQT.q11, region);
			 }
 }

 // Get Quad Tree of Points belong to it ////////////////////////////////////////////////////////////
 template<typename T, template<typename> class Point = Pair>
 void getQuadTree(const Point<T>& point, const QuadTree<T, Point>& rootQT, std::shared_ptr<QuadTree<T, Point>>& qtree)
 {
	 //if (rootQT.data.numberPoints != 0) {
		// if (isPointInRect(point, rootQT.data.rectangle))
		// {
		//	 std::cout << "check root\n";
		//	 qtree = rootQT;
		//	 return;
		// }
	 //}
	 // if numberPoint = 0 mean there leafs
	 // check leaf not nullptr
	 if (rootQT.q00 != nullptr)
		 if (isPointInRect(point, rootQT.q00->data.rectangle))
			 if (rootQT.q00->data.numberPoints != 0)
			 {
				 std::cout << "check 1\n";
				 qtree = rootQT.q00;
				 return;
			 }
			 else {
				 getQuadTree<T, Point>(point, *rootQT.q00, qtree);
			 }

	 if (rootQT.q01 != nullptr)
		 if (isPointInRect(point, rootQT.q01->data.rectangle))
			 if (rootQT.q01->data.numberPoints != 0)
			 {
				 std::cout << "check 2\n";
				 qtree = rootQT.q01;
				 return;
			 }
			 else {
				 getQuadTree<T, Point>(point, *rootQT.q01, qtree);
			 }

	 if (rootQT.q10 != nullptr)
		 if (isPointInRect(point, rootQT.q10->data.rectangle))
			 if (rootQT.q10->data.numberPoints != 0)
			 {
				 std::cout << "check 3\n";
				 qtree = rootQT.q10;
				 return;
			 }
			 else {
				 getQuadTree<T, Point>(point, *rootQT.q10, qtree);
			 }

	 if (rootQT.q11 != nullptr)
		 if (isPointInRect(point, rootQT.q11->data.rectangle))
			 if (rootQT.q11->data.numberPoints != 0)
			 {
				 std::cout << "check 4\n";
				 qtree = rootQT.q11;
				 return;
			 }
			 else {
				 getQuadTree<T, Point>(point, *rootQT.q11, qtree);
			 }
 }


// INSERTION OF POINT AND VECTOR OF POINTS
template<typename T, template<typename> class Point = Pair >
void insertPoint(const Point<T>& point,const QuadTree<T>& qtree) {
	// check this points which quad tree belong to
	std::shared_ptr<QuadTree<T, Point>> tmpChild;
	getQuadTree<T,Point>(point, qtree, tmpChild);

	// insertion and check if satisfy the condition to subdivise quad tree
	tmpChild->data.vPoints.push_back(point);
	tmpChild->data.numberPoints++;
	
	// make subtree
	if (tmpChild->data.numberPoints > MINIMUM_POINTS)
		makeChildQuadTree3(*tmpChild);
}

template<typename T, template<typename> class Point = Pair>
void insertVecPoints(const std::vector<Point<T>>& vPoints, QuadTree<T>& qtree) {
	for (auto v : vPoints) insertPoint(v, qtree);
}

template<typename T>
int getLevelQuadt(const QuadTree<T>& qtree)
{ 
	return 0;
}

template<typename T, template<typename> class Point = Pair>
Point<T> findClosestPoint(const Point<T>& point,std::vector<Point<T>>& vPoints) {
	// 1. create QuadTree for search
	T x = getCoord(point, 0);
	T y = getCoord(point, 1);

	// 2. create :
	// 1.1 create rectangle of Quadtree min_x, min_y , max_x, max_y;use template
	std::array<T, 4> vRect = getRect<T,Point>(vPoints);
	if (x < vRect[0]) vRect[0] = x; else if (x > vRect[2]) vRect[2] = x;
	if (y < vRect[1]) vRect[1] = y; else if (y > vRect[3]) vRect[3] = y;

	Rect<T> rect(vRect[0],vRect[1],vRect[2]-vRect[0],vRect[3]-vRect[1]);

	// make quad tree with minimum of point 15;
	QuadTree<T, Point> qtree(rect, vPoints);
	makeChildQuadTreeComplete<T,Point>(qtree);
	std::vector<Point<T>> vP;
	getVectorPoint<T,Point>(point, qtree, vP);
	
	T tmp = norm2d<T,Point>(point, vP[0]);
	//vP.pop_back();

	Point<T> tmp_point{};
	for (auto p : vP)
	{
		T r = norm2d<T,Point>(point, p);
		if (r < tmp) {
			tmp = r ;
			tmp_point = p;
		}
	}

	return tmp_point;
}

template<typename T, template<typename> class Point = Pair>
Point<T> findClosestPointInTree(const Point<T>& point, const QuadTree<T,Point>& qtree) {
	// 1. create QuadTree for search
	T x = getCoord(point, 0);
	T y = getCoord(point, 1);

	std::vector<Point<T>> vP;
	getVectorPoint<T, Point>(point, qtree, vP);

	T tmp = norm2d<T, Point>(point, vP[0]);
	//vP.pop_back();

	Point<T> tmp_point{};
	for (auto p : vP)
	{
		T r = norm2d<T, Point>(point, p);
		if (r < tmp) {
			tmp = r;
			tmp_point = p;
		}
	}

	return tmp_point;
}



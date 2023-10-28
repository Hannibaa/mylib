#pragma once
#include <iostream>
#include <vector>
#include <fstream>

#define end '\n'

using namespace std;

struct fPoint {
	float x;
	float y;
};

fPoint make_rPoint() {
	fPoint p;
	p.x = float(rand() % 1200);
	p.y = float(rand() % 800);
	return p;
}


struct Curve {
	size_t nPoints;
	vector<fPoint> vPoints;

	Curve(size_t _n) : nPoints{ _n } { vPoints.resize(nPoints); }
};

template<size_t N>
struct podCurve {
	size_t n{ N };
	fPoint vP[N];
};

Curve make_rCurve() {
	size_t sz = rand() % 6 + 1;
	Curve c(sz);
	for (int i = 0; i < c.vPoints.size(); i++)
		c.vPoints[i] = make_rPoint();
	return c;
}


void printCurve(const Curve& c) {
	cout << "Curve size : " << c.nPoints << end;
	for (int i = 0; i < c.nPoints; i++)
		cout << "Point[ " << i << " ] : " << c.vPoints[i].x << " , " << c.vPoints[i].y << end;
	cout << "--------------- end ------------------------\n";
}

void writeCurve(ofstream& of, Curve& c) {
	size_t sz = c.nPoints;
	fPoint* vp = c.vPoints.data();

	// first write size, after points, so : |size_t|pionts...points|size_t|pionts...points|....
	of.write(reinterpret_cast<char*>(&sz), sizeof(sz));
	of.write(reinterpret_cast<char*>(vp), sz * sizeof(fPoint));
}

Curve readCurve(ifstream& ifs) {
	
	size_t sz;
	fPoint p{};
	// read the first input is size
	ifs.read(reinterpret_cast<char*>(&sz), sizeof(size_t));

	if (ifs.eof()) {
		return Curve(0);
	}

	Curve c(sz);

	// read the vector of points
	for (int i = 0; i < sz; i++) {
		ifs.read(reinterpret_cast<char*>(&p), sizeof(p));
		c.vPoints[i] = p;
	}

	return c;
}

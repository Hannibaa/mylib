#pragma once

#include <limits>
#include <chrono>
#include "C:\Users\Acer\source\MyLib\random_generator.h"

template<typename T>
struct Range {
	T min;
	T max;

	Range() : min{}, max{} {}
	Range(T _max) : min{}, max{ _max } {}
	Range(T min, T max) : min{ min }, max{ max } {}
};



using namespace std::chrono;

template<typename T>
class RW1 {   // random walk value
	static_assert(std::is_arithmetic<T>::value, "should be arithmetic type");

	steady_clock::time_point   tp1;
	duration<float>            elapsed_time{};

	T x0;
	float x;
	float v_max;
	float v_min;
	float speed;
	milliseconds t;

	Range<T>            minmax;
	Range<float>        speed_range;
	Range<milliseconds> time_range;

	RG<void> rg;

	void update()
	{
		elapsed_time = steady_clock::now() - tp1;

		x += speed;

		if (elapsed_time > t  ) 
		{	
			upDate();
			speed = -speed;
		}

		if (x > v_max) {
			speed = -speed;
		}
		
		if (x < v_min) {
			speed = -speed;
		}

	}

	void upDate() {
		t = milliseconds(rg((int)time_range.min.count(),(int) time_range.max.count()));

		tp1 = steady_clock::now();

		speed = rg(speed_range.min, speed_range.max);

		v_max = rg(float(minmax.min), float(minmax.max));
		v_min = rg(float(minmax.min), v_max);

	}

public:
	RW1(T _x0, const Range<T>& minmax, const Range<float>& speed_range, const Range<milliseconds>& time_range)
		: x0{ _x0 }
		, x{ float(x0) }
		, minmax{ minmax }
		, speed_range{ speed_range }
		, time_range{ time_range }
	{
		t = milliseconds(rg((int)time_range.min.count(), (int)time_range.max.count()));
		std::cout << "time " << t.count() << std::endl;
		tp1 = steady_clock::now();
		std::cout << " tp1 " << tp1.time_since_epoch().count() << std::endl;
		speed = rg(speed_range.min, speed_range.max);
		std::cout << "speed " << speed << '\n';
		v_max = rg(x, float(minmax.max));
		std::cout << "vmax " << v_max << '\n';
		v_min = rg(float(minmax.min), v_max);
		std::cout << "vmin " << v_min << '\n';
	}

	operator T () {
		update(); return x;
	}
};
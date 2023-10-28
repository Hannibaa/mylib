#pragma once
#include <chrono>

typedef enum _TimeType{ Elapsed = 0, DeltaTime } TimeType;

class Timer
{
public:
	Timer() {
		_start_time = _current_time = _last_delta_tick = std::chrono::system_clock::now();
		last_delta_t = _last_delta_tick.time_since_epoch().count();
		_delta_time = std::chrono::duration<float>(0);

	}
	// RESTART THE START TIME TO NOW, WHICH BASICALLY RESETS THE ELAPSED TIME COUNT
	void Restart() {
		_start_time = std::chrono::system_clock::now();
	}

	// RETURNS THE AMOUNT OF TIME SINCE THE LAST LAST CALL TO THIS FUNCTION ////////////////////
	float GetDeltaTime() {
		_current_time = std::chrono::system_clock::now();
		_delta_time = _current_time - _last_delta_tick;
		_last_delta_tick = _current_time;
		return _delta_time.count();
	}
	// RETURNS THE AMOUNT OF TIME SINCE LAST RESTART //////////////////////////////////////////
	float GetElapsedTime() {
		_current_time = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsed_time = _current_time - _start_time;
		return elapsed_time.count();
	}

	////////////////////////////// TEMPLATE RETURN TIME UNIT ////////////////////////////////////////
	template<typename T = uint64_t>
	auto getElapsedTime() {
		_current_time = std::chrono::system_clock::now();
		auto elapsed_time = _current_time - _start_time;
		return std::chrono::duration_cast<std::chrono::duration<T>>( elapsed_time);
	}

	template<typename T>
	auto getElapsedTime_() {
		
		_current_time = std::chrono::system_clock::now();
		auto elapsed_time = _current_time - _start_time;
		return std::chrono::duration_cast<T>(elapsed_time);

	}
	////////////////////////////////////// Every seconds flow return true //////////////////////////////


	////////////////////////////////////// Every one unit duration flow return true ///////////////////

	uint64_t operator () (TimeType TT = TimeType::Elapsed) {

		if (TT == TimeType::Elapsed )
			return (std::chrono::system_clock::now().time_since_epoch().count() -
				_start_time.time_since_epoch().count());

		if ( TT == TimeType::DeltaTime ){
			_current_time = std::chrono::system_clock::now();
			delta_t = _current_time.time_since_epoch().count() - last_delta_t;
			last_delta_t = _current_time.time_since_epoch().count();
			return delta_t;
		};

		return 0;
	}

	void stopWatch() {

	}

	template<typename T>
	bool ElapsedTime(T time_) {
		return true;
	}

    bool everySeconds(std::chrono::nanoseconds _seconds) {

	
	    if ((std::chrono::system_clock::now() - _start_time) > _seconds) {
	    	_start_time = std::chrono::system_clock::now();
	    	return true;
	    }

	    return false;
    }

private:
	std::chrono::system_clock::time_point _start_time, _current_time, _last_delta_tick;
	std::chrono::duration<float> _delta_time;
	uint64_t delta_t{}, last_delta_t;
};

bool everySeconds(std::chrono::nanoseconds _seconds) {

	static auto start_time = std::chrono::steady_clock::now();

	if ((std::chrono::steady_clock::now() - start_time) > _seconds) {
		start_time = std::chrono::steady_clock::now();
		return true;
	}

	return false;
}


template<typename T, bool>
struct is_Time { static const bool value = false; };

template<>
struct is_Time<std::chrono::seconds, true> { static const bool value = true; };
template<>
struct is_Time<std::chrono::minutes, true> { static const bool value = true; };
template<>
struct is_Time<std::chrono::milliseconds, true> { static const bool value = true; };
template<>
struct is_Time<std::chrono::microseconds, true> { static const bool value = true; };


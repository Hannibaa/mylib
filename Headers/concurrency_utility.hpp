#pragma once

#include <iostream>
#include <syncstream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <conio.h>

#include <MyLib/Console_Library/escape_code.h>

#define time_now            std::chrono::system_clock::now()
#define now_time            time_now
#define Seconds(n)          std::chrono::seconds(n)
#define Milliseconds(n)     std::chrono::milliseconds(n)
#define Sleep(n)            std::this_thread::sleep_for(n)
#define synprint_           std::osyncstream(std::cout) 
#define thread_id           std::this_thread::get_id()


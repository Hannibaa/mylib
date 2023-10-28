#pragma once
#include <cstdio>

struct Lifetime {
	// default ctor
	Lifetime() { puts("Lifetime() [default constructor]"); ++number_deft_ctor; }

	// conversion constructor
	Lifetime(float _value) : value(_value) { puts("Lifetime(float) [conversion constructor]");
	                                         ++number_convertion_ctor; }

	// copy ctor
	Lifetime(const Lifetime&) noexcept {
		puts("Lifetime(const Lifetime&) [copy constructor]");
		++number_copy_ctor;
	}

	// move ctor
	Lifetime(Lifetime&&) noexcept {
		puts("Lifetime(Lifetime&&) [move constructor]");
		++number_move_ctor;
	}

	// copy assignement
	Lifetime& operator=(const Lifetime&) noexcept {
		puts("operator=(const Lifetime&) [copy assignment]");
		++number_copy_asg;
	}

	// move assignment 
	Lifetime& operator=(Lifetime&&) noexcept {
		puts("operator=(Lifetime&&) [move assignment]");
		++number_move_asg;
	}

	// get a value and set functions
	void setValue(float _value) { value = _value; }
	float getValue() const { return value; }

	// use one overloading function
	void Value(float _value) { value = _value; }
	float Value() const { return value; }

	// using one function to reference
	float& value_() { return value; }

	static void print_result() {
		std::cout << "number of default         constructor  " << number_deft_ctor << '\n';
		std::cout << "number of copy            constructor  " << number_copy_ctor << '\n';
		std::cout << "number of move            constructor  " << number_move_ctor << '\n';
		std::cout << "number of copy assignment constructor  " << number_copy_asg << '\n';
		std::cout << "number of move assignment constructor  " << number_move_asg << '\n';
		std::cout << "number of conversion      constructor  " << number_convertion_ctor << '\n';
	}

	static void print_result_dtor() {
		std::cout << "number of destructor             call  " << number_destructor << '\n';
	}

	~Lifetime() noexcept { puts("~Lifetime() [destructor]"); ++number_destructor; }

private:
	float value{};
	static size_t number_deft_ctor;
	static size_t number_copy_ctor;
	static size_t number_move_ctor;
	static size_t number_copy_asg;
	static size_t number_move_asg;
	static size_t number_destructor;
	static size_t number_convertion_ctor;

};

size_t Lifetime::number_convertion_ctor{};
size_t Lifetime::number_copy_ctor{};
size_t Lifetime::number_move_ctor{};
size_t Lifetime::number_copy_asg{};
size_t Lifetime::number_move_asg{};
size_t Lifetime::number_deft_ctor{};
size_t Lifetime::number_destructor{};


#pragma once
#include "C:\Users\Acer\source\MyLib\file_loader_inmemory.h"



namespace File {

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //      USING FILE AS DATA 
    //      USING ANY FILE AND LOADED IT IN DATA TYPE AS FUNCTION OR GRAPH OR COORDINATE 
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////


	template<typename T>
	std::vector<std::pair<T,T>> 
	makeGraphicalFile(const std::string& filename, T Xscal, T Yscal) {

		static_assert(std::is_scalar<T>::value, "T type should be scalar type");

		auto v = File::LoadFileToMemoryVec<T>(filename).first;

		auto minmax = std::minmax_element(v.begin(), v.end());

		std::cout << *minmax.first << " " << *minmax.second << std::endl;

		T cx = Xscal / T(v.size());
		T cy = Yscal / (*minmax.second - *minmax.first);

		std::cout << " cy " << cy << std::endl;

		std::vector<std::pair<T, T>> vPoint;

		for (size_t i = 0; i < v.size(); ++i) {
			vPoint.emplace_back(cx * T(i), cy * v[i]);
		}

		return vPoint;
	}

}

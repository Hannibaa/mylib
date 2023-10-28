#pragma once
#include <fcntl.h>
#include <io.h>

#define SETMODE_UNICODE        	_setmode(_fileno(stdout), _O_U16TEXT)


namespace Unicode {

	inline namespace Box {
		const wchar_t uplc = L'\x250F';     // upper left corner
		const wchar_t uprc = L'\x2513';     // upper right corner
		const wchar_t dnlc = L'\x2517';     // down left corner
		const wchar_t dnrc = L'\x251B';     // down right corner
		const wchar_t vLine = L'\x2503';    // vertical line
		const wchar_t hLine = L'\x2501';    // horizotal line
		
		const wchar_t Box[] = {
			L'\x2500',L'\x2501',L'\x2502',L'\x2503',L'\x2504',L'\x2505',L'\x2506',L'\x2507',
			L'\x2508',L'\x2509',L'\x250A',L'\x250B',L'\x250C',L'\x250D',L'\x250E',L'\x250F',

			L'\x2510',L'\x2511',L'\x2512',L'\x2513',L'\x2514',L'\x2515',L'\x2516',L'\x2517',
			L'\x2518',L'\x259',L'\x251A',L'\x251B',L'\x251C',L'\x251D',L'\x251E',L'\x251F',

			//L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',
			//L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',

			//L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',
			//L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',

			//L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',
			//L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',

			//L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',
			//L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',

			//L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',
			//L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',

			//L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',
			//L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',L'\x25',

		};
	}
}
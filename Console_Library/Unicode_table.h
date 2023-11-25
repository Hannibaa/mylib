/*
 *****************************************************************************
 *                                                                           *
 *                          Platform Independent                             *
 *                      Unicode and Wchar_t Library                          *
 *                                                                           *
 * Author: KADDA Aoues - haoues_k@yahoo.fr - 2023                            *
 *                                                                           *
 * URL :                                                                     *
 *                                                                           *
 * Copyright notice:                                                         *
 * Free use of the Library CFile                                             *
 * is permitted under the guidelines and in accordance with the most current *
 * version of the MIT License.                                               *
 * http://www.opensource.org/licenses/MIT                                    *
 *                                                                           *
 *****************************************************************************
*/


/**********************************************************************************
 *
 * Copyright (c) 2022-2023 KADDA Aoues
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **********************************************************************************/



#pragma once
#include <fcntl.h>
#include <io.h>

// _O_WTEXT

#define SETMODE_UNICODE        	  _setmode(_fileno(stdout), _O_U16TEXT)
#define SETMODE_WTTEXT            _setmode(_fileno(stdout), _O_WTEXT)
#define SETMODE_TEXT              _setmode(_fileno(stdout), _O_TEXT)



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
			L'\x2518',L'\x2590',L'\x251A',L'\x251B',L'\x251C',L'\x251D',L'\x251E',L'\x251F',
		};
	}

	inline namespace Solid {
		const wchar_t solid[] = {L'\x2580',	 L'\x2584',	 L'\x2584', // 0,1,2
								 L'\x2588',	 L'\x258c',	 L'\x2590', // 3,4,5
								 L'\x2591',	 L'\x2592',	 L'\x2593', // 6,7,8
								 L'\x25a0',  L'\x25aa',  L'\x25ac', // 9,10,11
								 L'\x25d8',  L'\x25d9',  L'\x25ac'  // 11,12,13
		};

		const wchar_t solid1 = L'\x2588'  ;
		const wchar_t solid2 = L'\x25a0'  ;
		const wchar_t solid3 = L'\x2584'  ;
		const wchar_t solid4 = L'\x2580'  ;
		const wchar_t solid5 = L'\x258c'  ;
	}
}

namespace wchar = Unicode;
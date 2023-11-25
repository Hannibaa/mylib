/*
 *****************************************************************************
 *                                                                           *
 *                          Platform Independent                             *
 *                   Windows Event For Console Library                       *
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
#include <Windows.h>

#define KeyOn(Key)           GetAsyncKeyState(Key) & 0x8000
#define KeyReleased(Key)     GetAsyncKeyState(Key) & 0x0001
#define KeyPressed(Key)      GetAsyncKeyState(Key) & 0x8001

#define TITLE(wtitle)         SetConsoleTitle(wtitle)

#define _u(Char)            ((unsigned)Char)

bool get_out() {

	if ( KeyOn(VK_ESCAPE)) return true;
	else return false;
	
}
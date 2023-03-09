/*
	File: main.c

	Created: 28/10/2014

	Copyright (c) 2014, Jordan Less'ard-Springett. All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:
	
	1. 	Redistributions of source code must retain the above copyright
		notice, this list of conditions and the following disclaimer.

	2. 	Redistributions in binary form must reproduce the above copyright
		notice, this list of conditions and the following disclaimer in the
		documentation and/or other materials provided with the distribution.

	3. 	Neither the name of the copyright holders nor the names of
     	contributors may be used to endorse or promote products derived
     	from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
 */

#define F_CPU 1000000UL

#include <util/delay.h>
#include "io.h"

int song_a[] = {
1,  0,  2,  1,  3,  4,  4,  0,  3,  1,  3,  3,  4,  2,  3,  1,  4,  0,  4,  2,  
4,  1,  1,  1,  4,  2,  1,  2,  2,  3,  0,  1,  2,  2,  2,  2,  1,  3,  1,  0,  
3,  1,  0,  0 , 1 , 0 , 0,  1,  2,  0,  1,  1,  3,  3  ,2  ,0  ,2  ,1  ,3  ,3 ,
 1 , 3,  1,  1,  3 , 3 , 0 , 2 , 1 , 0 , 0  ,3  ,1  ,0  ,0 , 3  ,4 , 3 , 3 , 0 , 
 4 , 0 , 0 , 2 , 0 , 2 , 4  ,2 , 3 , 1 , 2 , 2, 1,  4,  2, 0,  1,  3 , 0,  4,
};


//////////////////////////////////////////////////////////////////////////
///
/// Entry Function
/// 
//////////////////////////////////////////////////////////////////////////
int main(void)
{
	int curr_index = 0;

	io_set_mode(PORT_B, 0, OUTPUT);
	io_set_mode(PORT_B, 1, OUTPUT);
	io_set_mode(PORT_B, 2, OUTPUT);
	io_set_mode(PORT_B, 3, OUTPUT);
	io_set_mode(PORT_B, 4, OUTPUT);

	while(1) {
		curr_index++;
		if(curr_index == 100) {
			curr_index = 0;
		}

		io_write(PORT_B, song_a[curr_index], HIGH);

		_delay_ms(3000);

		io_write(PORT_B, song_a[curr_index], LOW);

		_delay_ms(6500);
	}

	return 0;
}
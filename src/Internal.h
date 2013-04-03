/*

    libmemAlMan
    Copyright (C) 2013 Jason Doyle

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Contact Information:

    Original Author: Jason Doyle (jdoyle1983@gmail.com)
	
*/

#ifndef __INTERNAL_H__
#define __INTERNAL_H__

#define bool short
#define true 1
#define false 0

typedef struct
{
	unsigned long i;
	unsigned long r;
	unsigned long s;
	void* m;
} AllocUnit;

void AllocUnit_Delete(AllocUnit* u);
AllocUnit* AllocUnit_GetById(unsigned long Id);
AllocUnit* AllocUnit_New();

#endif
/*
 * mb_ss_ll.c: Pair of stores vs. reversed pair of loads, no barriers.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * Copyright (c) 2009 Paul E. McKenney, IBM Corporation.
 */

#define THREAD_0 \
	do { \
		state.a = 1; \
		state.b = 1; \
		while (state.f > 0) \
			barrier(); \
		if (state.y == 1 && state.x == 0) { \
			state.badcount++; \
			break; \
		} \
	} while (0)

#define THREAD_1 \
	do { \
		state.y = state.b; \
		state.x = state.a; \
	} while (0)

/* #define THREAD_2 */
/* #define THREAD_3 */
/* #define THREAD_4 */

#include "mbtest.h"

struct cache_preload cache_preload[] = {
	{ 0, &state.b },
	{ 1, &state.a },
	{ 1, &state.x },
	{ 1, &state.y },
	{-1, NULL },
};

struct thread_assignment thread_assignment[] = {
	{ 0, thread_0 },
	{ 1, thread_1 },
	{-1, NULL },
};

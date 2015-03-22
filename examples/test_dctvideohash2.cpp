/*

    pHash, the open source perceptual hash library
    Copyright (C) 2009 Aetilius, Inc.
    All rights reserved.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Evan Klinger - eklinger@phash.org
    David Starkweather - dstarkweather@phash.org
    Anton Pomozov - pomozoff@mail.ru

*/


#include "stdio.h"
#include "pHash.h"
#include "CImg.h"
#include "cimgffmpeg.h"

ulong64* calc_hash_for_file(const char* file_name, int& length) {
	ulong64* hash;

	printf("file: %s\n", file_name);
	hash = ph_dct_videohash(file_name, length);
	if (hash) {
		printf("length: %d\n", length);
		for (int i = 0; i < length; ++i) {
			printf("hash[%d]: %llx\n", i, hash[i]);
		}
	} else {
		printf("hash is null");
	}

	return hash;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("not enough input arguments\n");
		return -1;
	}

	const char* file1 = argv[1];
	const char* file2 = argv[2];

	if (!file1 || !file2) {
		printf("not enough arguments\n");
		exit(1);
	}

	int length1;
	ulong64* hash1 = calc_hash_for_file(file1, length1);
	if (!hash1) {
		exit(2);
	}

	int length2;
	ulong64* hash2 = calc_hash_for_file(file2, length2);
	if (!hash2) {
		free(hash1);
		exit(3);
	}

	double sim = ph_dct_videohash_dist(hash1, length1, hash2, length2, 21);
	printf("similarity: %f\n", sim);

	free(hash1);
	free(hash2);

	hash1 = NULL;
	hash2 = NULL;

	printf("done\n");

	return 0;
}


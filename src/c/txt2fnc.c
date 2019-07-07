/*
 * txt2fnc.c - A text to function tool for ARM inline assembly.
 * Copyright 2015 Bernard Jacobs (Omega2058)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define ARGC_MAX		3
#define ALIGNED_SIZE		4

int main(int argc, char *argv[]) {
	int i = 0;
	int blocks = 0;
	int strSize = 0;
	int fileSize = 0;
	char *strInBuf = NULL;
	FILE *out = NULL;
	char filename[1024];

	// Self explanatory.
	if (argc < 4) {
		printf("Usage: %s <outfile> <function_name> <string>", argv[0]);
		exit(1);
	}

	// Open the file for writing.
	sprintf(filename, "%s.h", argv[1]);
	out = fopen(filename, "a");

	// If file exists (size > 0) then don't increment by a new line.
	fseek(out, 0, SEEK_END);
	fileSize = ftell(out);
	fseek(out, 0, SEEK_SET);

	if (fileSize > 0) {
		fputs("\n", out);
	}

	// Write out the head of the function comment.
	fputs("/**\n * Function containing text \"", out);
	if (argc > ARGC_MAX) {
		// Print out the string with a space, but only
		// if there aren't more arguments available.
		for (i = ARGC_MAX; i < argc; i++) {
			fputs(argv[i], out);
			if (i != argc - 1) {
				fputs(" ", out);
			}
		}
	} else {
		fputs(argv[3], out);
	}
	// Prints the tail of the function comment.
	fputs("\".\n */", out);

	// Write the function and its name.
	fputs("\n__attribute__ ((naked)) void ", out);
	fputs(argv[2], out);
	fputs("(void) {\n", out);

	// Calculate the length of the strings, while adding
	// an extra amount for spaces if there aren't more
	// arguments available.
	for (i = ARGC_MAX; i < argc; i++) {
		strSize += strlen(argv[i]);
		if (i != argc - 1) {
			strSize += 1;
		}
	}

	// Allocate memory for the strings and finally concatenate them
	// after clearing memory in case of extra garbage.
	strInBuf = (char*) aligned_alloc(strSize, 4);
	memset(strInBuf, 0, sizeof(char));
	for (i = ARGC_MAX; i < argc; i++) {
		strcat(strInBuf, argv[i]);
		if (i != argc - 1) {
			strcat(strInBuf, " ");
		}
	}

	// Make sure the string size is divisible by 4. If not, add another
	// block to print the remaining data.
	if (strSize % ALIGNED_SIZE == 0) {
		blocks = strSize / ALIGNED_SIZE;
	} else {
		blocks = (strSize / ALIGNED_SIZE) + 1;
	}

	// Write the appropriate data based on the blocks given.
	for (i = 0; i < blocks * ALIGNED_SIZE; i += ALIGNED_SIZE) {
		fputs("\tasm ( \".long 0x", out);
		fprintf(out, "%08X",
				strInBuf[i] | strInBuf[i + 1] << 8 | strInBuf[i + 2] << 16
						| strInBuf[i + 3] << 24);
		fputs("\" );\n", out);
	}

	// Write the tail.
	fputs("}\n", out);

	// Self explanatory.
	free(strInBuf);
	fclose(out);
	return EXIT_SUCCESS;
}

/*
 *  Copyright (c) 2015 Ryan McCullagh <me@ryanmccullagh.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define D_SMART_STRING_SIZE 16

typedef struct SmartString {
	size_t length;
	size_t capacity;
	char* buffer;
} SmartString;

SmartString* smart_string_new()
{
	SmartString* ss;
	if((ss = malloc(sizeof(SmartString))) == NULL) {
		return NULL;
	}
	ss->length = 0;
	ss->capacity = D_SMART_STRING_SIZE;
	if((ss->buffer = malloc(ss->capacity)) == NULL) {
		free(ss);
		return NULL;
	}
	ss->buffer[ss->length] = '\0';
	return ss;
}

bool smart_string_append(SmartString* ss, const char* str)
{
	if(ss == NULL) { return false; }
	if(str == NULL) { return false; }
	
	size_t part_length = strlen(str);
	size_t i;
	size_t current_position;
	size_t new_length;
	
	if(part_length == 0) {
		return true;
	}
	
	new_length = part_length + ss->length;
	current_position = ss->length;
	
	if(new_length >= ss->capacity) {
		ss->capacity *= 2;
		if((ss->buffer = realloc(ss->buffer, ss->capacity)) == NULL) {
			return false;
		} 
	}
	
	for(i = 0; i < part_length; i++) {
		ss->buffer[current_position++] = str[i];
	}
	
	ss->length = new_length;
	ss->buffer[current_position] = '\0';
	
	return true;
}

void smart_string_destroy(SmartString* ss)
{
	free(ss->buffer);
	free(ss);
}

bool smart_string_starts_with(SmartString* ss, const char* str)
{
		if((ss == NULL) || (str == NULL)) { return false; }
		size_t part_length = strlen(str);
		size_t i;
		if(part_length == 0) {
			return false;
		}
		if(part_length != ss->length) {
			return false;
		}
		for(i = 0; i < part_length; i++) {
			if(ss->buffer[i] != str[i]) {
				return false;
			}
		}

		return true;
}

int main()
{
	SmartString* ss = smart_string_new();
	if(!ss) {
		return 1;
	}
	
	smart_string_append(ss, "http://")
	smart_string_append(ss, "www.google.com");
	smart_string_append(ss, "?");
	smart_string_append(ss, "tracking=1");
	smart_string_append(ss, "&");
	smart_string_append(ss, "browser=chrome");
	smart_string_append(ss, "&sk=true");
	
	if(!smart_string_starts_with(ss, "http")) {
		printf("only accepting https\n"); 
	} else {
		printf("%s\n", ss->buffer);
	}
	
	smart_string_destroy(ss);
	
	return 0;
}














#pragma once

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Hashmap.h"

int isFile(const char*);
void displayFileContents(hashmap_char*);

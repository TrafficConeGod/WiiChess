#include "Resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

bool Resource::IsOfType(short id) {
    return id == ID || Actor::IsOfType(id);
}

void Resource::Load(DataStream& stream) {
    Actor::Load(stream);
    path.Load(stream);
    int code = access(path, F_OK);
    if (code != 0) {
        ShowConsole();
		PrintFmt("File %s not found, code: %d\n", (const char*)path, code);
        Error("File not found");
	}
}
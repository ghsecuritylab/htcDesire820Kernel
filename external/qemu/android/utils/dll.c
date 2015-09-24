/* Copyright (C) 2011 The Android Open Source Project
**
** This software is licensed under the terms of the GNU General Public
** License version 2, as published by the Free Software Foundation, and
** may be copied, distributed, and modified under those terms.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/
#include <android/utils/dll.h>
#include <android/utils/system.h>
#include <android/utils/path.h>

#include <stdlib.h>

static char*
append_string( const char* str1, const char* str2 )
{
    int   len1   = strlen(str1);
    int   len2   = strlen(str2);
    char* result = malloc(len1+len2+1);

    if (result != NULL) {
        memcpy(result, str1, len1);
        memcpy(result + len1, str2, len2);
        result[len1+len2] = '\0';
    }
    return result;
}

#ifdef _WIN32

#include <windows.h>

static char*
reverse_slashes( const char* path )
{
    int   len    = strlen(path);
    char* result = malloc(len+1);
    int   nn;

    for (nn = 0; nn < len; nn++) {
        int ch = path[nn];
        if (ch == '/') {
            ch = '\\';
        }
        result[nn] = (char)ch;
    }
    result[nn] = '\0';

    return result;
}

ADynamicLibrary*
adynamicLibrary_open( const char*  libraryName,
                      char**       pError)
{
    char*  libName = (char*) libraryName;
    void*  result;

    
    if (strchr(libraryName,'.') == NULL) {
        libName = append_string(libraryName, ".dll");
    }

    
    *pError = NULL;
    result = (ADynamicLibrary*) LoadLibrary( libName );
    if (result == NULL) {
        *pError = ASTRDUP("Could not load DLL!");
    }

    
    if (libName != libraryName) {
        free(libName);
    }

    return (ADynamicLibrary*) result;
}

void*
adynamicLibrary_findSymbol( ADynamicLibrary*  lib,
                            const char*       symbolName,
                            char**            pError)
{
    void* result;

    *pError = NULL;

    if (lib == NULL) {
        *pError = strdup("NULL library pointer");
        return NULL;
    }
    if (symbolName == NULL || symbolName[0] == '\0') {
        *pError = strdup("NULL or empty symbolName");
        return NULL;
    }
    result = GetProcAddress( (HMODULE)lib, symbolName );
    if (result == NULL) {
        *pError = ASTRDUP("Could not find symbol");
    }
    return result;
}

void
adynamicLibrary_close( ADynamicLibrary*  lib )
{
    if (lib != NULL) {
        FreeLibrary( (HMODULE)lib );
    }
}

#else 

#include <dlfcn.h>
#include <stdlib.h>

ADynamicLibrary*
adynamicLibrary_open( const char*  libraryName,
                      char**       pError)
{
    char*  libName = (char*) libraryName;
    void*  result;

#ifdef __APPLE__
#  define SO_EXTENSION ".dylib"
#else
#  define SO_EXTENSION ".so"
#endif

    
    if (strchr(libraryName,'.') == NULL) {
        libName = append_string(libraryName, SO_EXTENSION);
    }

    
    *pError = NULL;
    result  = dlopen( libName, RTLD_LAZY );
    if (result == NULL) {
        *pError = strdup(dlerror());
    }

    
    if (libName != (char*)libraryName) {
        free(libName);
    }

    return (ADynamicLibrary*) result;
}

void*
adynamicLibrary_findSymbol( ADynamicLibrary*  lib,
                            const char*       symbolName,
                            char**            pError)
{
    void* result;

    *pError = NULL;

    if (lib == NULL) {
        *pError = strdup("NULL library pointer");
        return NULL;
    }
    if (symbolName == NULL || symbolName[0] == '\0') {
        *pError = strdup("NULL or empty symbolName");
        return NULL;
    }
    result = dlsym(lib, symbolName);
    if (result == NULL) {
        *pError = strdup(dlerror());
    }
    return result;
}

void
adynamicLibrary_close( ADynamicLibrary*  lib )
{
    if (lib != NULL) {
        dlclose(lib);
    }
}

#endif 
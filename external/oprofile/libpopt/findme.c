

#include "system.h"
#include "findme.h"
#include <unistd.h>

const char * findProgramPath(const char * argv0)
{
    char * path = getenv("PATH");
    char * pathbuf;
    char * start, * chptr;
    char * buf;

    if (argv0 == NULL) return NULL;	
    
    if (strchr(argv0, '/'))
	return xstrdup(argv0);

    if (path == NULL) return NULL;

    start = pathbuf = alloca(strlen(path) + 1);
    buf = malloc(strlen(path) + strlen(argv0) + sizeof("/"));
    if (buf == NULL) return NULL;	
    strcpy(pathbuf, path);

    chptr = NULL;
    
    do {
	if ((chptr = strchr(start, ':')))
	    *chptr = '\0';
	sprintf(buf, "%s/%s", start, argv0);

	if (!access(buf, X_OK))
	    return buf;

	if (chptr) 
	    start = chptr + 1;
	else
	    start = NULL;
    } while (start && *start);
    

    free(buf);

    return NULL;
}

/*
 * Copyright 2012, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <portability.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <errno_portable.h>
#include <filefd_portable.h>
#include <signal_portable.h>
#include <sys/atomics.h>

#define PORTABLE_TAG "filefd_portable"
#include <log_portable.h>


static char *fd_env_name = "ANDROID_PORTABLE_MAPPED_FILE_DESCRIPTORS";
static char *type_env_name = "ANDROID_PORTABLE_MAPPED_FILE_TYPES";
static enum filefd_type filefd_mapped_file[__FD_SETSIZE];
static int  filefd_FD_CLOEXEC_file[__FD_SETSIZE];

static volatile int filefd_mapped_files = 0;
static volatile int filefd_enabled = 1;

#if __FD_SETSIZE >= 10000
#error MAX_ENV_SIZE must be increased
#endif

#define MAX_ENV_SIZE (__FD_SETSIZE * 5)

static int export_fd_env()
{
    const int max_env_size = MAX_ENV_SIZE;
    int type_env_bytes_remaining = max_env_size;
    char *type_env_allocated = NULL, *type_env;
    int fd_env_bytes_remaining = max_env_size;
    char *fd_env_allocated = NULL, *fd_env;
    int exported_file_descriptors = 0;
    enum filefd_type fd_type;
    int overwrite = 1;
    int fd_count = 0;
    int saved_errno;
    int fd_cloexec;
    int len;
    int rv1;
    int rv2;
    int rv;
    int fd;

    ALOGV("%s:() {", __func__);

    saved_errno = *REAL(__errno)();

    type_env_allocated = malloc(max_env_size);
    fd_env_allocated = malloc(max_env_size);
    if (type_env_allocated == NULL || fd_env_allocated == NULL) {
        ALOGE("%s: type_env_allocated:%p, fd_env_allocated:%p; FIXME!", __func__,
                   type_env_allocated,    fd_env_allocated);

        rv = -1;
        goto done;
    } else {
        ALOGV("%s: type_env_allocated:%p, fd_env_allocated:%p;", __func__,
                   type_env_allocated,    fd_env_allocated);
    }

    type_env = type_env_allocated;
    fd_env = fd_env_allocated;

    for (fd = 0; fd < __FD_SETSIZE; fd++) {
        fd_type = filefd_mapped_file[fd];
        if (fd_type != UNUSED_FD_TYPE) {
            ++fd_count;
            ALOGV("%s: fd_type = %d = filefd_mapped_file[fd:%d]; ++fdcount:%d;", __func__,
                       fd_type,                          fd,       fd_count);

            fd_cloexec = filefd_FD_CLOEXEC_file[fd];
            ALOGV("%s: fd_cloexec = %d = filefd_FD_CLOEXEC_file[fd:%d];", __func__,
                       fd_cloexec,                              fd);

            if (fd_cloexec == 0) {
                rv = snprintf(fd_env, fd_env_bytes_remaining, "%d,", fd);
                ASSERT(rv > 0);
                fd_env += rv;
                fd_env_bytes_remaining -= rv;
                rv = snprintf(type_env, type_env_bytes_remaining, "%d,", filefd_mapped_file[fd]);
                ASSERT(rv > 0);
                type_env += rv;
                type_env_bytes_remaining -= rv;
                exported_file_descriptors++;
            }

            if (fd_count == filefd_mapped_files)
                break;
        }
    }
    if (fd_count != filefd_mapped_files) {
        ALOGE("%s: fd_count:%d != filefd_mapped_files:%d; [Likely Race; add futex?]", __func__,
                   fd_count,      filefd_mapped_files);

    }
    if (exported_file_descriptors == 0) {
        rv1 = unsetenv(fd_env_name);
        rv2 = unsetenv(type_env_name);
        if (rv1 != 0 || rv2 != 0) {
            ALOGV("%s: Note: unsetenv() failed!", __func__);
        }
        rv = 0;
    } else {
        if (fd_env > fd_env_allocated) {
            fd_env--;                           
        }
        *fd_env = '\0';

        if (type_env > type_env_allocated) {
            type_env--;                         
        }
        *type_env = '\0';

        rv = setenv(fd_env_name, fd_env_allocated, overwrite);
        if (rv != 0) {
            ALOGE("%s: rv:%d = setenv(fd_env_name:'%s', fd_env_allocated:'%s' ...);", __func__,
                       rv,            fd_env_name,      fd_env_allocated);
        } else {
            ALOGV("%s: rv:%d = setenv(fd_env_name:'%s', fd_env_allocated:'%s' ...);", __func__,
                       rv,            fd_env_name,      fd_env_allocated);
        }
        if (rv != 0) goto done;

        rv = setenv(type_env_name, type_env_allocated, overwrite);

        if (rv != 0) {
            ALOGE("%s: rv:%d = setenv(type_env_name:'%s', type_env_allocated:'%s' ...);",
            __func__,  rv,            type_env_name,      type_env_allocated);
        } else {
            ALOGV("%s: rv:%d = setenv(type_env_name:'%s', type_env_allocated:'%s' ...);",
            __func__,  rv,            type_env_name,      type_env_allocated);
        }
    }

done:
    if (type_env_allocated)
        free(type_env_allocated);

    if (fd_env_allocated)
        free(fd_env_allocated);

    *REAL(__errno)() = saved_errno;

    ALOGV("%s: return(rv:%d); }", __func__, rv);
    return rv;
}


static int import_fd_env(int verify)
{
    char *type_env_allocated = NULL;
    char *fd_env_allocated = NULL;
    char *type_token_saved_ptr;
    char *fd_token_saved_ptr;
    enum filefd_type fd_type;
    char *type_env, *fd_env;
    int saved_errno;
    char *type_token;
    char *fd_token;
    int rv = 0;
    int fd;

    ALOGV("%s:(verify:%d) {", __func__, verify);

    saved_errno = *REAL(__errno)();

    fd_env = getenv(fd_env_name);
    if (fd_env == NULL) {
        ALOGV("%s: fd_env = NULL = getenv('%s');", __func__,
                                   fd_env_name);
        goto done;
    } else {
        ALOGV("%s: fd_env = '%s' = getenv('%s');", __func__,
                   fd_env,         fd_env_name);

        fd_env_allocated = malloc(strlen(fd_env)+1);
        if (fd_env_allocated == NULL) {
            ALOGE("%s: fd_env_allocated = NULL; malloc failed", __func__);
            goto done;
        }
        strcpy(fd_env_allocated, fd_env);
    }

    type_env = getenv(type_env_name);
    if (type_env == NULL) {
        ALOGV("%s: type_env = NULL = getenv(type_env_name:'%s');", __func__,
                                            type_env_name);
        goto done;
    } else {
        ALOGV("%s: type_env = '%s' = getenv(type_env_name:'%s');", __func__,
                   type_env,                type_env_name);

        type_env_allocated = malloc(strlen(type_env)+1);
        if (type_env_allocated == NULL) {
            ALOGE("%s: type_env_allocated = NULL; malloc failed", __func__);
            goto done;
        }
        strcpy(type_env_allocated, type_env);
    }

    fd_token = strtok_r(fd_env_allocated, ",", &fd_token_saved_ptr);
    type_token = strtok_r(type_env_allocated, ",", &type_token_saved_ptr);
    while (fd_token && type_token) {
        fd = atoi(fd_token);
        ASSERT(fd >= 0 );
        ASSERT(fd < __FD_SETSIZE);

        fd_type = (enum filefd_type) atoi(type_token);
        ASSERT(fd_type > UNUSED_FD_TYPE);
        ASSERT(fd_type < MAX_FD_TYPE);

        if (fd >= 0 && fd < __FD_SETSIZE) {
            if (fd_type > UNUSED_FD_TYPE && fd_type < MAX_FD_TYPE) {
                if (verify) {
                    ASSERT(filefd_mapped_file[fd] == fd_type);
                    ALOGV("%s: filefd_mapped_file[fd:%d] == fd_type:%d;", __func__,
                                                  fd,       fd_type);
                } else {
                    ASSERT(filefd_mapped_file[fd] == UNUSED_FD_TYPE);

                    __atomic_inc(&filefd_mapped_files);
                    ALOGV("%s: ++filefd_mapped_files:%d;", __func__,
                                 filefd_mapped_files);

                    filefd_mapped_file[fd] = fd_type;
                    ALOGV("%s: filefd_mapped_file[fd:%d] = fd_type:%d;", __func__,
                                                  fd,      fd_type);
                }
            }
        }

        fd_token = strtok_r(NULL, ",", &fd_token_saved_ptr);
        type_token = strtok_r(NULL, ",", &type_token_saved_ptr);
    }

done:
    if (type_env_allocated)
        free(type_env_allocated);
    if (fd_env_allocated)
        free(fd_env_allocated);

    *REAL(__errno)() = saved_errno;

    ALOGV("%s: return(rv:%d); }", __func__, rv);
    return rv;
}


static void __attribute__ ((constructor)) linker_import_fd_env(void)
{
    int rv;
    int verify_consistancy = 0;

    ALOGV(" ");
    ALOGV("%s() {", __func__);

    rv = import_fd_env(verify_consistancy);     

    ALOGV("%s: }", __func__);
}


__hidden void filefd_opened(int fd, enum filefd_type fd_type)
{
    ALOGV("%s(fd:%d) {", __func__, fd);

    if (fd >= 0 && fd < __FD_SETSIZE) {
        if (filefd_mapped_file[fd] == UNUSED_FD_TYPE) {
            __atomic_inc(&filefd_mapped_files);
            filefd_mapped_file[fd] = fd_type;
        }
        ASSERT(filefd_mapped_file[fd] == fd_type);
    }

    ALOGV("%s: }", __func__);
}

__hidden void filefd_closed(int fd)
{
    ALOGV("%s(fd:%d) {", __func__, fd);

    if (fd >= 0 && fd < __FD_SETSIZE) {
        if (filefd_mapped_file[fd] != UNUSED_FD_TYPE) {
            filefd_mapped_file[fd] = UNUSED_FD_TYPE;
            filefd_FD_CLOEXEC_file[fd] = 0;
            __atomic_dec(&filefd_mapped_files);
        }
    }
    ALOGV("%s: }", __func__);
}


__hidden void filefd_CLOEXEC_enabled(int fd)
{
    ALOGV("%s:(fd:%d) {", __func__, fd);

    if (fd >= 0 && fd < __FD_SETSIZE) {
        filefd_FD_CLOEXEC_file[fd] = 1;
    }

    ALOGV("%s: }", __func__);
}

__hidden void filefd_CLOEXEC_disabled(int fd)
{
    ALOGV("%s:(fd:%d) {", __func__, fd);

    if (fd >= 0 && fd < __FD_SETSIZE) {
        filefd_FD_CLOEXEC_file[fd] = 0;
    }

    ALOGV("%s: }", __func__);
}


__hidden void filefd_disable_mapping()
{
    ALOGV("%s:() {", __func__);

    filefd_enabled = 0;

    ALOGV("%s: }", __func__);
}


int WRAP(close)(int fd)
{
    int rv;

    ALOGV(" ");
    ALOGV("%s(fd:%d) {", __func__, fd);

    rv = REAL(close)(fd);
    filefd_closed(fd);

    ALOGV("%s: return(rv:%d); }", __func__, rv);
    return rv;
}


int WRAP(read)(int fd, void *buf, size_t count)
{
    int rv;
    enum filefd_type fd_type;

    ALOGV(" ");
    ALOGV("%s(fd:%d, buf:0x%p, count:%d) {", __func__,
              fd,    buf,      count);

    fd_type = filefd_mapped_file[fd];
    ALOGV("%s:fd_type:%d", __func__,
              fd_type);

    switch (fd_type) {
    
    case UNUSED_FD_TYPE:
    case EVENT_FD_TYPE:
    case INOTIFY_FD_TYPE:
    case TIMER_FD_TYPE:
        rv = REAL(read)(fd, buf, count);
        break;

    
    case SIGNAL_FD_TYPE:
        if (filefd_enabled) {
            rv = read_signalfd_mapper(fd, buf, count);
        } else {
            rv = REAL(read)(fd, buf, count);
        }
        break;

    default:
        ALOGE("Unknown fd_type:%d!", fd_type);
        rv = REAL(read)(fd, buf, count);
        break;
    }

    ALOGV("%s: return(rv:%d); }", __func__, rv);
    return rv;
}


int WRAP(execve)(const char *filename, char *const argv[],  char *const envp[])
{
    int rv;
    int mapped_files = filefd_mapped_files;
    int verify_consistancy = 1;

    ALOGV(" ");
    ALOGV("%s(filename:%p, argv:%p, envp:%p) {", __func__,
              filename,    argv,    envp);

    export_fd_env();

    if (mapped_files != filefd_mapped_files) {
        export_fd_env();
    }
    import_fd_env(verify_consistancy);          

    rv = REAL(execve)(filename, argv, envp);

    ALOGV("%s: return(rv:%d); }", __func__, rv);
    return rv;
}

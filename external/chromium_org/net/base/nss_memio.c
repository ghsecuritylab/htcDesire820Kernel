// Copyright (c) 2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// Written in NSPR style to also be suitable for adding to the NSS demo suite


#include <stdlib.h>
#include <string.h>

#include <prerror.h>
#include <prinit.h>
#include <prlog.h>

#include "nss_memio.h"



struct memio_buffer {
    int head;     
    int tail;     
    int bufsize;  
    PRErrorCode last_err;
    char *buf;
};


struct PRFilePrivate {
    
    struct memio_buffer readbuf;

    
    struct memio_buffer writebuf;

    
    PRNetAddr peername;

    
    int eof;

    int read_requested;
};



static void memio_buffer_new(struct memio_buffer *mb, int size);

static void memio_buffer_destroy(struct memio_buffer *mb);

static int memio_buffer_used_contiguous(const struct memio_buffer *mb);

static int memio_buffer_wrapped_bytes(const struct memio_buffer *mb);

/* How many bytes can be written into the buffer without wrapping */
static int memio_buffer_unused_contiguous(const struct memio_buffer *mb);

/* Write n bytes into the buffer.  Returns number of bytes written. */
static int memio_buffer_put(struct memio_buffer *mb, const char *buf, int n);

static int memio_buffer_get(struct memio_buffer *mb, char *buf, int n);

static void memio_buffer_new(struct memio_buffer *mb, int size)
{
    mb->head = 0;
    mb->tail = 0;
    mb->bufsize = size;
    mb->buf = malloc(size);
}

static void memio_buffer_destroy(struct memio_buffer *mb)
{
    free(mb->buf);
    mb->buf = NULL;
    mb->head = 0;
    mb->tail = 0;
}

static int memio_buffer_used_contiguous(const struct memio_buffer *mb)
{
    return (((mb->tail >= mb->head) ? mb->tail : mb->bufsize) - mb->head);
}

static int memio_buffer_wrapped_bytes(const struct memio_buffer *mb)
{
    return (mb->tail >= mb->head) ? 0 : mb->tail;
}

/* How many bytes can be written into the buffer without wrapping */
static int memio_buffer_unused_contiguous(const struct memio_buffer *mb)
{
    if (mb->head > mb->tail) return mb->head - mb->tail - 1;
    return mb->bufsize - mb->tail - (mb->head == 0);
}

/* Write n bytes into the buffer.  Returns number of bytes written. */
static int memio_buffer_put(struct memio_buffer *mb, const char *buf, int n)
{
    int len;
    int transferred = 0;

    
    len = PR_MIN(n, memio_buffer_unused_contiguous(mb));
    if (len > 0) {
        
        memcpy(&mb->buf[mb->tail], buf, len);
        mb->tail += len;
        if (mb->tail == mb->bufsize)
            mb->tail = 0;
        n -= len;
        buf += len;
        transferred += len;

        
        len = PR_MIN(n, memio_buffer_unused_contiguous(mb));
        if (len > 0) {
            
            memcpy(&mb->buf[mb->tail], buf, len);
            mb->tail += len;
            if (mb->tail == mb->bufsize)
                mb->tail = 0;
            transferred += len;
        }
    }

    return transferred;
}


static int memio_buffer_get(struct memio_buffer *mb, char *buf, int n)
{
    int len;
    int transferred = 0;

    
    len = PR_MIN(n, memio_buffer_used_contiguous(mb));
    if (len) {
        memcpy(buf, &mb->buf[mb->head], len);
        mb->head += len;
        if (mb->head == mb->bufsize)
            mb->head = 0;
        n -= len;
        buf += len;
        transferred += len;

        
        len = PR_MIN(n, memio_buffer_used_contiguous(mb));
        if (len) {
            memcpy(buf, &mb->buf[mb->head], len);
            mb->head += len;
            if (mb->head == mb->bufsize)
                mb->head = 0;
            transferred += len;
        }
    }

    return transferred;
}


static PRStatus PR_CALLBACK memio_Close(PRFileDesc *fd)
{
    struct PRFilePrivate *secret = fd->secret;
    memio_buffer_destroy(&secret->readbuf);
    memio_buffer_destroy(&secret->writebuf);
    free(secret);
    fd->dtor(fd);
    return PR_SUCCESS;
}

static PRStatus PR_CALLBACK memio_Shutdown(PRFileDesc *fd, PRIntn how)
{
    
    return PR_SUCCESS;
}

static int PR_CALLBACK memio_Recv(PRFileDesc *fd, void *buf, PRInt32 len,
                                  PRIntn flags, PRIntervalTime timeout)
{
    struct PRFilePrivate *secret;
    struct memio_buffer *mb;
    int rv;

    if (flags) {
        PR_SetError(PR_NOT_IMPLEMENTED_ERROR, 0);
        return -1;
    }

    secret = fd->secret;
    mb = &secret->readbuf;
    PR_ASSERT(mb->bufsize);
    rv = memio_buffer_get(mb, buf, len);
    if (rv == 0 && !secret->eof) {
        secret->read_requested = len;
        if (mb->last_err)
            PR_SetError(mb->last_err, 0);
        else if (secret->writebuf.last_err)
            PR_SetError(secret->writebuf.last_err, 0);
        else
            PR_SetError(PR_WOULD_BLOCK_ERROR, 0);
        return -1;
    }

    secret->read_requested = 0;
    return rv;
}

static int PR_CALLBACK memio_Read(PRFileDesc *fd, void *buf, PRInt32 len)
{
    
    return memio_Recv(fd, buf, len, 0, PR_INTERVAL_NO_TIMEOUT);
}

static int PR_CALLBACK memio_Send(PRFileDesc *fd, const void *buf, PRInt32 len,
                                  PRIntn flags, PRIntervalTime timeout)
{
    struct PRFilePrivate *secret;
    struct memio_buffer *mb;
    int rv;

    secret = fd->secret;
    mb = &secret->writebuf;
    PR_ASSERT(mb->bufsize);

    if (mb->last_err) {
        PR_SetError(mb->last_err, 0);
        return -1;
    }
    rv = memio_buffer_put(mb, buf, len);
    if (rv == 0) {
        PR_SetError(PR_WOULD_BLOCK_ERROR, 0);
        return -1;
    }
    return rv;
}

static int PR_CALLBACK memio_Write(PRFileDesc *fd, const void *buf, PRInt32 len)
{
    
    return memio_Send(fd, buf, len, 0, PR_INTERVAL_NO_TIMEOUT);
}

static PRStatus PR_CALLBACK memio_GetPeerName(PRFileDesc *fd, PRNetAddr *addr)
{
    
    struct PRFilePrivate *secret = fd->secret;
    *addr = secret->peername;
    return PR_SUCCESS;
}

static PRStatus memio_GetSocketOption(PRFileDesc *fd, PRSocketOptionData *data)
{
    if (PR_SockOpt_Nonblocking == data->option) {
        data->value.non_blocking = PR_TRUE;
        return PR_SUCCESS;
    }
    PR_SetError(PR_OPERATION_NOT_SUPPORTED_ERROR, 0);
    return PR_FAILURE;
}



static struct PRIOMethods  memio_layer_methods = {
    PR_DESC_LAYERED,
    memio_Close,
    memio_Read,
    memio_Write,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    memio_Shutdown,
    memio_Recv,
    memio_Send,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    memio_GetPeerName,
    NULL,
    NULL,
    memio_GetSocketOption,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

static PRDescIdentity memio_identity = PR_INVALID_IO_LAYER;

static PRStatus memio_InitializeLayerName(void)
{
    memio_identity = PR_GetUniqueIdentity("memio");
    return PR_SUCCESS;
}


PRFileDesc *memio_CreateIOLayer(int readbufsize, int writebufsize)
{
    PRFileDesc *fd;
    struct PRFilePrivate *secret;
    static PRCallOnceType once;

    PR_CallOnce(&once, memio_InitializeLayerName);

    fd = PR_CreateIOLayerStub(memio_identity, &memio_layer_methods);
    secret = malloc(sizeof(struct PRFilePrivate));
    memset(secret, 0, sizeof(*secret));

    memio_buffer_new(&secret->readbuf, readbufsize);
    memio_buffer_new(&secret->writebuf, writebufsize);
    fd->secret = secret;
    return fd;
}

void memio_SetPeerName(PRFileDesc *fd, const PRNetAddr *peername)
{
    PRFileDesc *memiofd = PR_GetIdentitiesLayer(fd, memio_identity);
    struct PRFilePrivate *secret = memiofd->secret;
    secret->peername = *peername;
}

memio_Private *memio_GetSecret(PRFileDesc *fd)
{
    PRFileDesc *memiofd = PR_GetIdentitiesLayer(fd, memio_identity);
    struct PRFilePrivate *secret =  memiofd->secret;
    return (memio_Private *)secret;
}

int memio_GetReadRequest(memio_Private *secret)
{
    return ((PRFilePrivate *)secret)->read_requested;
}

int memio_GetReadParams(memio_Private *secret, char **buf)
{
    struct memio_buffer* mb = &((PRFilePrivate *)secret)->readbuf;
    PR_ASSERT(mb->bufsize);

    *buf = &mb->buf[mb->tail];
    return memio_buffer_unused_contiguous(mb);
}

int memio_GetReadableBufferSize(memio_Private *secret)
{
    struct memio_buffer* mb = &((PRFilePrivate *)secret)->readbuf;
    PR_ASSERT(mb->bufsize);

    return memio_buffer_used_contiguous(mb);
}

void memio_PutReadResult(memio_Private *secret, int bytes_read)
{
    struct memio_buffer* mb = &((PRFilePrivate *)secret)->readbuf;
    PR_ASSERT(mb->bufsize);

    if (bytes_read > 0) {
        mb->tail += bytes_read;
        if (mb->tail == mb->bufsize)
            mb->tail = 0;
    } else if (bytes_read == 0) {
        
        ((PRFilePrivate *)secret)->eof = PR_TRUE;
    } else  {
        mb->last_err = bytes_read;
    }
}

void memio_GetWriteParams(memio_Private *secret,
                          const char **buf1, unsigned int *len1,
                          const char **buf2, unsigned int *len2)
{
    struct memio_buffer* mb = &((PRFilePrivate *)secret)->writebuf;
    PR_ASSERT(mb->bufsize);

    *buf1 = &mb->buf[mb->head];
    *len1 = memio_buffer_used_contiguous(mb);
    *buf2 = mb->buf;
    *len2 = memio_buffer_wrapped_bytes(mb);
}

void memio_PutWriteResult(memio_Private *secret, int bytes_written)
{
    struct memio_buffer* mb = &((PRFilePrivate *)secret)->writebuf;
    PR_ASSERT(mb->bufsize);

    if (bytes_written > 0) {
        mb->head += bytes_written;
        if (mb->head >= mb->bufsize)
            mb->head -= mb->bufsize;
    } else if (bytes_written < 0) {
        mb->last_err = bytes_written;
    }
}


#ifdef TRIVIAL_SELF_TEST
#include <stdio.h>

#define TEST_BUFLEN 7

#define CHECKEQ(a, b) { \
    if ((a) != (b)) { \
        printf("%d != %d, Test failed line %d\n", a, b, __LINE__); \
        exit(1); \
    } \
}

int main()
{
    struct memio_buffer mb;
    char buf[100];
    int i;

    memio_buffer_new(&mb, TEST_BUFLEN);

    CHECKEQ(memio_buffer_unused_contiguous(&mb), TEST_BUFLEN-1);
    CHECKEQ(memio_buffer_used_contiguous(&mb), 0);

    CHECKEQ(memio_buffer_put(&mb, "howdy", 5), 5);

    CHECKEQ(memio_buffer_unused_contiguous(&mb), TEST_BUFLEN-1-5);
    CHECKEQ(memio_buffer_used_contiguous(&mb), 5);
    CHECKEQ(memio_buffer_wrapped_bytes(&mb), 0);

    CHECKEQ(memio_buffer_put(&mb, "!", 1), 1);

    CHECKEQ(memio_buffer_unused_contiguous(&mb), 0);
    CHECKEQ(memio_buffer_used_contiguous(&mb), 6);
    CHECKEQ(memio_buffer_wrapped_bytes(&mb), 0);

    CHECKEQ(memio_buffer_get(&mb, buf, 6), 6);
    CHECKEQ(memcmp(buf, "howdy!", 6), 0);

    CHECKEQ(memio_buffer_unused_contiguous(&mb), 1);
    CHECKEQ(memio_buffer_used_contiguous(&mb), 0);

    CHECKEQ(memio_buffer_put(&mb, "01234", 5), 5);

    CHECKEQ(memio_buffer_used_contiguous(&mb), 1);
    CHECKEQ(memio_buffer_wrapped_bytes(&mb), 4);
    CHECKEQ(memio_buffer_unused_contiguous(&mb), TEST_BUFLEN-1-5);

    CHECKEQ(memio_buffer_put(&mb, "5", 1), 1);

    CHECKEQ(memio_buffer_unused_contiguous(&mb), 0);
    CHECKEQ(memio_buffer_used_contiguous(&mb), 1);

    

    printf("Test passed\n");
    exit(0);
}

#endif

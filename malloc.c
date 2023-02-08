#include <stdio.h>
#include <unistd.h>

void *FIRST_CHUNK;

void *first_time(size_t block)
{
    FIRST_CHUNK = sbrk(block);
    if (FIRST_CHUNK == (void *)-1)
    {
        fprintf(stderr, "Line %d | %s: sbrk error\n", __LINE__, __func__);
        return (NULL);
    }
    return (FIRST_CHUNK);
}

void *new_block(void *ptr, size_t block)
{
	(void) ptr;
    void *new_ptr = sbrk(block);
    if (new_ptr == (void *)-1)
    {
        fprintf(stderr, "Line %d | %s: sbrk error\n", __LINE__, __func__);
        return (NULL);
    }
    return (new_ptr);
}

void *_malloc(size_t size)
{
    static void *current = NULL;
    static size_t total = 0;

    if (!current)
    {
        total = size;
        current = first_time(total);
        if (!current)
            return (NULL);
    }
    else
    {
        void *new_ptr = new_block(current, size);
        if (!new_ptr)
            return (NULL);
        current = new_ptr;
        total += size;
    }
    return (current);
}

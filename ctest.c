/**
 * @file ctest.c
 * @brief Source code file for WVU CTest testing framework
 * @author Brian Powell
 * @version 1.3
 *
 * Place this file in the same directory as your own source code and add it to your project.
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 * 
 * Requries the following linker flags for GCC in Visual Studio:
 * -Wl,--no-as-needed -ldl
 *
 * No linker flags required for Xcode.
 */

#include "ctest.h"
#include <dlfcn.h>
#include <stdio.h>

// OS-specific includes
#ifdef __APPLE__
	#include <malloc/malloc.h>
#else
	#include <malloc.h>
#endif

/**
 * @brief Tracks the location of original malloc function
 */
static void* (*real_malloc)(size_t) = NULL;

size_t ctest_get_malloc_size(void* ptr)
{
	// See if pointer is valid
	if (ptr == NULL)
	{
		return 0;
	}

	// If pointer is 0xFFFFFFFFFFFFFFFF, indicating memory was not set to anything, return size as 0
	if (ptr == (void*) 0xFFFFFFFFFFFFFFFF)
	{
		return 0;
	}

	// Get size
	#ifdef __APPLE__ 
		return malloc_size(ptr);
	#else 
		return malloc_usable_size(ptr);
	#endif 
}

void* malloc(size_t size)
{
	// Store original malloc function prior to remapping
	if (real_malloc == NULL)
	{
		// Locate original malloc function
		real_malloc = dlsym(RTLD_NEXT, "malloc");

		// Check for errors
		if (real_malloc == NULL)
		{
			fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
		}
	}

	// Pointer to new memory
	void* memoryPtr = NULL;

	// Call original malloc function
	memoryPtr = real_malloc(size);

	// If memory was allocated, set it to 0xFFFFFFFFFFFFFFFF
	if (memoryPtr != NULL)
	{
		memset(memoryPtr, 0xFF, size);
	}

	return memoryPtr;
}

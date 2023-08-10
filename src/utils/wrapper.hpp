// #define DEBUG_WRAPPERS
#include <stdlib.h>

#ifdef _MSC_VER
	#define Inline
	typedef void DIR;
#else 
	#define Inline __attribute((always_inline))
#endif
/**
 * Wrapper class around a C object allocated with malloc
 */
#include <cstring>
template <typename T>
class Wrap {
	public:
		T o;
		/**
		 * Creates a wrapper object around a pointer that points to memory allocated by malloc()
		 * @param alloc A pointer pointing to memory allocated by malloc 
		 */
		Inline Wrap(void *alloc) {
			#ifdef DEBUG_WRAPPERS
				printf("wrap construct\n");
			#endif
			o = (T) alloc;
		}

		Inline Wrap(int size) {
			#ifdef DEBUG_WRAPPERS
				printf("wrap construct\n");
			#endif
			o = (T) malloc(size);
			memset(o, 0, size);
		}

		Inline ~Wrap() {
			#ifdef DEBUG_WRAPPERS
				printf("wrap destruct\n");
			#endif
			free(o);
		}

		Inline operator T() {
			return o;
		}

		Inline T operator ->() {
			return o;
		}

};


#include <cstdio>
/**
 * Wrapper class around a C file handle
 */
class FWrap {
	public:
		FILE *f;
		/**
		 * Creates a wrapper around a C file handle to be able to implicitely close it when it falls
		 * out of scope
		 * @param path Path to a file
		 * @param mode Mode to open the file in
		 */
		Inline FWrap(const char *path, const char *mode) {
			#ifdef DEBUG_WRAPPERS
				printf("fwrap construct\n");
			#endif
			f = fopen(path, mode);
		}

		/**
		 * Creates a wrapper around a C file handle to be able to implicitely close it when it falls
		 * out of scope
		 * @param handle A C file handle
		 */
		Inline FWrap(FILE *handle) {
			#ifdef DEBUG_WRAPPERS
				printf("fwrap construct\n");
			#endif
			f = handle;
		}

		Inline ~FWrap() {
			#ifdef DEBUG_WRAPPERS
				printf("fwrap destruct\n");
			#endif
			if (f) fclose(f);
		}

		Inline operator FILE*() {
			return f;
		}
};

#ifndef _MSC_VER
	#include <dirent.h>
#endif

/**
 * Wrapper class around a C directory handle
 */


class DWrap {
	public:
		DIR *d;
		/**
		 * Creates a wrapper around a C directory handle
		 * @param path Path to a directory
		 */
		Inline DWrap(const char *path) {
			#ifdef DEBUG_WRAPPERS
				printf("dwrap construct\n");
			#endif
			#ifndef _MSC_VER
				d = opendir(path);
			#endif
			return;
		}

		 ~DWrap() {
			#ifdef DEBUG_WRAPPERS
				printf("dwrap destruct\n");
			#endif
			#ifndef _MSC_VER
				closedir(d);
			#endif
			return;
		}

		Inline operator DIR*() const {
			return d;
		}
};

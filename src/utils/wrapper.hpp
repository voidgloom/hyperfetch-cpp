// #define DEBUG_WRAPPERS

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
		__attribute((always_inline)) Wrap(void *alloc) {
			#ifdef DEBUG_WRAPPERS
				printf("wrap construct\n");
			#endif
			o = (T) alloc;
		}

		__attribute((always_inline)) Wrap(int size) {
			#ifdef DEBUG_WRAPPERS
				printf("wrap construct\n");
			#endif
			o = (T) malloc(size);
			bzero(o, size);
		}

		__attribute((always_inline)) ~Wrap() {
			#ifdef DEBUG_WRAPPERS
				printf("wrap destruct\n");
			#endif
			free(o);
		}

		__attribute((always_inline)) operator T() {
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
		__attribute((always_inline)) FWrap(const char *path, const char *mode) {
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
		__attribute((always_inline)) FWrap(FILE *handle) {
			#ifdef DEBUG_WRAPPERS
				printf("fwrap construct\n");
			#endif
			f = handle;
		}

		__attribute((always_inline)) ~FWrap() {
			#ifdef DEBUG_WRAPPERS
				printf("fwrap destruct\n");
			#endif
			if (f) fclose(f);
		}

		__attribute((always_inline)) operator FILE*() {
			return f;
		}
};

#include <dirent.h>

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
		__attribute((always_inline)) DWrap(const char *path) {
			#ifdef DEBUG_WRAPPERS
				printf("dwrap construct\n");
			#endif
			d = opendir(path);
		}

		 ~DWrap() {
			#ifdef DEBUG_WRAPPERS
				printf("dwrap destruct\n");
			#endif
			closedir(d);
		}

		__attribute((always_inline)) operator DIR*() const {
			return d;
		}
};

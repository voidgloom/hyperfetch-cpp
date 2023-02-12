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
		Wrap(void *alloc) {
			#ifdef DEBUG_WRAPPERS
				printf("wrap construct\n");
			#endif
			o = (T) alloc;
		}
		Wrap(int size) {
			#ifdef DEBUG_WRAPPERS
				printf("wrap construct\n");
			#endif
			o = (T) malloc(size);
			bzero(o, size);
		}

		~Wrap() {
			#ifdef DEBUG_WRAPPERS
				printf("wrap destruct\n");
			#endif
			free(o);
		}

		operator T() {
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
		inline FWrap(const char *path, const char *mode) {
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
		inline FWrap(FILE *handle) {
			#ifdef DEBUG_WRAPPERS
				printf("fwrap construct\n");
			#endif
			f = handle;
		}

		inline ~FWrap() {
			#ifdef DEBUG_WRAPPERS
				printf("fwrap destruct\n");
			#endif
			fclose(f);
		}

		inline operator FILE*() {
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
		inline DWrap(const char *path) {
			#ifdef DEBUG_WRAPPERS
				printf("dwrap construct\n");
			#endif
			d = opendir(path);
		}

		inline ~DWrap() {
			#ifdef DEBUG_WRAPPERS
				printf("dwrap destruct\n");
			#endif
			closedir(d);
		}

		inline operator DIR*() const {
			return d;
		}
};

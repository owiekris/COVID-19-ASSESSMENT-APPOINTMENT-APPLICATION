#ifndef TDEBUG_H
#define TDEBUG_H

#define DEBUG 1

#define SNAP_INT(X) printf("\nvariable " #X "= %d", X);
#define SNAP_STR(X) printf("\nstring " #X "= %s", X);

#define debug_print(fmt, ...) \
        do { if (DEBUG) fprintf(stderr, "\n%s\n:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

#endif

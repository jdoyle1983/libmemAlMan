# libmemAlMan

> A simple memory management library, to ease the burden of memory management.

## Features

* Reference counting interface to automatically clean up objects that are no
  longer being used.
* Maintenance routine to keep the library memory footprint small for long
  running applications.
* Global clean up routine to ensure all memory used is properly freed.
* Multi-Threading ready, routines in place to lock the data to ensure multiple
  threads can play nice with managed memory. (Application must implement locking
  mechanism).
  
## Building

### Linux - Production
``` make
make
```
OR
``` make
make static
```
OR
``` make
make shared
```

### Linux - Debug Mode
``` make
make FLAGS="-g -DDEBUG"
```
OR
``` make
make static FLAGS="-g -DDEBUG"
```
OR
``` make
make shared FLAGS="-g -DDEBUG"
```

### Windows - Production
``` make
mingw32-make -f Makefile.win
```
OR
``` make
mingw32-make -f Makefile.win static
```
OR
``` make
mingw32-make -f Makefile.win shared
```

### Windows - Debug Mode
``` make
mingw32-make -f Makefile.win FLAGS="-g -DDEBUG"
```
OR
``` make
mingw32-make -f Makefile.win static FLAGS="-g -DDEBUG"
```
OR
``` make
mingw32-make -f Makefile.win shared FLAGS="-g -DDEBUG"
```

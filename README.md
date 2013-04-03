libmemAlMan

A simple memory management library, to ease the burden of memory management.

Features:
* Reference counting interface to automatically clean up objects that are no
  longer being used.
* Maintainence routine to keep the library memory footprint small for long
  running applications.
* Global cleanup routine to ensure all memory used is properly freed.
* Multi-Threading ready, routines in place to lock the data to ensure multiple
  threads can play nice with managed memory. (Application must implement locking
  mechanism).
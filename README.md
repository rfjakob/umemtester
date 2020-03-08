umemtester - Micro-Memtester
============================

Very simple memory tester - the tiny sibling of
[memtester](http://pyropus.ca/software/memtester/).

What it does:

1) Allocate `SIZE_MIB` megabytes of RAM and `mlockall()` it
2) Fill it with pseudorandom data
3) Verify the contents

Usage
-----

```
./umemtester SIZE_MIB
```

Example
-------

```
$ ./umemtester 1000
testing 1000 MiB
warning: could not lock memory: Cannot allocate memory
writing
verifying
ok
```

Exit Value
----------

* 0 = ok
* 1 = usage error
* 2 = memory corruption

# how to profile #
  * mkdir build-d
  * cd build-d
  * cmake ..
  * ensure build type is debug and coverage
  * make test
  * run all the tests

  * mkdir build-p
  * cd build-p
  * cmake ..
  * edit CMakeCache.txt
    * compile in release mode
    * change -O3 to -O2
    * add -fno-omit-frame-pointer
  * make trucov

  * install oprofile apt-get install oprofile
  * configure oprofile: opcontrol --setup --no-vmlinux --callgraph=16 --separate=lib --event=CPU\_CLK\_UNHALTED:0x0:0:1
    * you may need to change the event, use opcontrol --list-events or ophelp to see what's available. or just use --event=default
  * opcontrol --start
  * run this for a while
    * while true; do build-p/trucov <your options here>; done
  * opcontrol --shutdown
  * opreport -callgraph --symbols <path/to/trucov>/build-p/trucov > results.oprofile
  * you can just look at the results file or go on to get a better gui view
  * cat results.oprofile | python gprof2dot.py --format=oprofile --node-thes=1.0 --skew=0.0001 | dot -Tsvg -o results.svg

# Future Optimizations #
15% Parser\_builder::store\_count
I suspect that fixing Parser\_builder would yield more than 15%, maybe up to 20%.

Blocks are copied a lot.  Giving them move constructors and using c++0x could yield 10%.  Otherwise the sort\_blocks method is biggest offender of block copying O(nlgn) in the std::sort,  if the design of block\_sort can be improved to avoid copying it might yield some improvement.
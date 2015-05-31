

# How to use Trucov #
Using Trucov is broken up intro three steps:<br>
<ol><li>Building source code with GCC coverage flags.<br>
</li><li>Executing testing framework.<br>
</li><li>Running Trucov over the project directory<br></li></ol>

<h2>Build Source Code</h2>
Build the source code with coverage flags: '-fprofile-arcs' '-ftest-coverage'. Link gcov with your executable. When compiled, a Gcno file (filename.gcno) will be created for every source file.<br>
<pre><code>   g++ -fprofile-arcs -ftest-coverage -c test_cat.cc <br>
   g++ -fprofile-arcs -ftest-coverage -lgcov -o run main.cpp test_cat.o<br>
</code></pre>
or<br>
<pre><code>   gcc -fprofile-arcs -ftest-coverage -c test_cat.c <br>
   gcc -fprofile-arcs -ftest-coverage -lgcov -o run main.c test_cat.o<br>
</code></pre>

<h2>Execute Tests</h2>
Execute the binary and/or testing framework. When executed, A Gcda file (filename.gcda) will be created for every source file.<br>
<pre><code>   $ ./all_unittest<br>
   [ RUN      ] Test1.case1<br>
   [       OK ] Test1.case1<br>
   [ RUN      ] Test2.case2<br>
   [       OK ] Test2.case2<br>
   ...<br>
   234 / 244 Tests Passed<br>
</code></pre>

<h2>Execute Trucov</h2>
Execute Trucov over your project directory. The project directory should contain all Gcno, Gcda, and source files. The files may be contained in sub-directories; Trucov will automatically search the directory structure to find these files.<br>
<pre><code>   project/<br>
     -&gt; src/<br>
          -&gt; foo.cpp<br>
          -&gt; main.cpp<br>
          -&gt; ...<br>
     -&gt; include/<br>
          -&gt; foo.h<br>
          -&gt; ...<br>
     -&gt; build/<br>
          -&gt; foo.gcno<br>
          -&gt; foo.gcda<br>
          -&gt; main.gcno<br>
          -&gt; main.gcda<br>
          -&gt; ...<br>
</code></pre>
How to Invoke Trucov:<br>
<pre><code>   $ pwd<br>
   /home/user/Desktop/Project/<br>
   $ ls<br>
   src/<br>
   include/<br>
   build/   <br>
   $ trucov report<br>
</code></pre>

<h1>Basic Usage</h1>

<h2>Trucov Commands</h2>
<pre><code>Usage: trucov [ command ] [ option... ] [ selection... ] <br>
<br>
   trucov list            // Prints all functions found.<br>
   trucov status          // Prints all functions found with their coverage percentage.<br>
   trucov report          // Creates a textual coverage report for every source file.  <br>
   trucov dot             // Creates a dot file describing all functions.<br>
   trucov dot_report      // Creates a dot file for every source file.<br>
   trucov render          // Creates a graphical coverage report describing all functions. <br>
   trucov render_report   // Creates a graphical coverage report for every source file.<br>
   trucov all_report      // Creates a textual and graphical coverage report for every source file.<br>
</code></pre>

<h2>Specify Source and Build Directories</h2>
The '--srcdir --builddir' flags can be used to run trucov with different project directory setups.<br>
<pre><code>   /home/project/<br>
     -&gt; build/<br>
        -&gt; main.gcno<br>
        -&gt; main.gcda<br>
     -&gt; build2/<br>
        -&gt; foo.gcno<br>
        -&gt; foo.gcda<br>
        -&gt; foo_test.gcno<br>
        -&gt; foo_test.gcda<br>
     -&gt; include/<br>
        -&gt; foo.h<br>
     -&gt; src/<br>
        -&gt; main.cpp<br>
     -&gt; test/<br>
        -&gt; foo_test.cpp<br>
 <br>
     // Lists functions from main.cpp, foo.h, and foo_test.cpp.<br>
     $ trucov list <br>
     <br>
     // Lists functions from main.cpp and foo.h.<br>
     $ trucov list --srcdir src/ --srcdir include/<br>
<br>
     // Lists functions from main.cpp.<br>
     $ trucov list --builddir build/<br>
<br>
     // Lists functions from all external libraries included by the binary.<br>
     $ trucov list --srcdir /usr/include/         <br>
</code></pre>

<h2>Using Selection</h2>
The Trucov selection may be used to choose what functions and/or source files Trucov will output coverage information on. Trucov selection is specified by any non-flag words after the command; thus, a command must be present for a selection to be specified on the command line. Selection supports regular expressions; remember to use quotes around regular expressions to escape reserved command line characters.<br>
<pre><code>     // Lists everything from cat.h, but not main.cpp.<br>
     $ trucov list cat.h<br>
<br>
     // Lists all functions that contain 'foo' or 'cat' in their name.<br>
     $ trucov list foo cat<br>
<br>
     // Lists all functions that contain 'foo' and 'cat' in their name.<br>
     $ trucov list --and foo cat<br>
<br>
     // Lists all functions named 'foo'.<br>
     $ trucov list --full-match foo<br>
<br>
     // Lists all functions with signature foo(int).<br>
     $ trucov list --signature-match "foo(int)"<br>
<br>
     // Lists all functions that match the supplied regular expressions.<br>
     $ trucov list "(.*cat)|([A-Z]a*)" "[a-z]*"<br>
<br>
     // Wrong: Attempts to run the 'foo' command.<br>
     $ trucov foo<br>
</code></pre>

<h1>Advanced Usage</h1>

<h2>Setup the Configuration File</h2>
The $HOME/.trucovrc file or the '--config-file' flag may be used to configure the Trucov default settings. The '--config-help' command lists which options are available in the configuration file.<br>
<pre><code>     $ cd $HOME<br>
     $ cat .trucovrc<br>
     --srcdir source/<br>
     --srcdir include/<br>
     --build  build/<br>
</code></pre>
The configuration specified above will search for source files under source/ and include/ and will search for Gcno and Gcda files under build/ by default. These defaults are still overridden by command line flags. If a default directory does not exists, then Trucov will print a warning message and continue running.<br>
<pre><code>     // If exists, Trucov uses the config file $HOME/.trucovrc<br>
     $ trucov list<br>
<br>
     // Uses the config file custom.txt instead of $HOME/.trucovrc<br>
     $ trucov --config-file /home/configs/custom.txt<br>
</code></pre>
The default command, selection, build directories, source directories, revision script, and graph image format may all be specified by the configuration file.<br>
<br>
<h2>Manually Rendering Dot Files</h2>
The dot and dot_report commands may be used to create dot files describing graphical coverage report. A dot file can be rendered into a graphical coverage report. Run the graphviz dot command on the .dot files to create image files (ps, svg, jpg, ...).<br>
<pre><code>     $ dot -Tps graph1.dot -o graph1.ps,<br>
     $ dot -Tsvg graph1.dot -o graph1.svg<br>
     $ dot -Tpdf graph1.dot -o graph1.pdf<br>
</code></pre>
Now view any of the image files with an image viewer that supports the image format used.<br>
<br>
<h1>Common Problems</h1>

<h2>No Parsing Files Found</h2>
Parsing files not being found usually occurs from improper compilation, not executing the test framework, or running Trucov over the wrong directory.<br>
<pre><code>     // Actual<br>
     $ trucov report<br>
     Parsing gcno and gcda files .<br>
<br>
     // Expected<br>
     $ trucov report<br>
     Parsing gcno and gcda files ........<br>
</code></pre>
<ol><li>Ensure you compiled with '-ftest-coverage -fprofile-arcs' flags.<br>
</li><li>Ensure you executed the testing framework or binary.<br>
</li><li>Ensure the Gcno and Gcda files are in the project directory. If the configuration file is using the '--builddir' flag, then Trucov will only search those directories relative to the current directory, unless overridden with command line flags.</li></ol>

<h2>Gcno Parsing Failures</h2>
Failure to parse a Gcno file often occurs when the Gcno file is corrupted; this often occurs when another program is currently using or has modified a Gcno file.<br>
<pre><code>     $ trucov report<br>
     Parsing gcno and gcda files ...<br>
     ERROR: Failed to parse Gcda file main.cpp.gcno<br>
     ERROR: Failed to parse Gcda file foo.cpp.gcno<br>
</code></pre>
<ol><li>Ensure the Gcno files are not being used by another program.<br>
</li><li>Try deleting the Gcno files and recompiling your code.</li></ol>

<h2>Gcda Parsing Failures</h2>
Failure to parse a Gcda file often occurs when the Gcda file is corrupted. This often occurs from the testing framework halting or Gcda corruption after recompiling. It is good practice to remove all Gcda files before every execution.<br>
<pre><code>     $ trucov report<br>
     Parsing gcno and gcda files ...<br>
     ERROR: Failed to parse Gcda file main.cpp.gcda<br>
     ERROR: Failed to parse Gcda file foo.cpp.gcda<br>
</code></pre>
<ol><li>Ensure you do not halt the binary in the middle of execution.<br>
</li><li>If you are getting Merge Mismatch warnings, try recompiling.<br>
</li><li>Try deleting the Gcda files and re-executing the binary or testing framework.<br>
</li><li>Try removing all Gcno and Gcda files, recompiling, and re-executing the binary or testing framework.</li></ol>

<h2>Control Flow Graphs are Wrong</h2>
Control flow graphs often do not reflect the actual code when compiling in release mode or with optimization flags.<br>
<ol><li>Ensure you are not compiling with optimiziation flags (For advanced users only).<br>
</li><li>Ensure you are not compiling in release mode (For advanced users only).<br>
</li><li>In optimized / release mode, the compiler will insert the code of inline functions into the caller code, and will sometimes reorder code. Running Trucov over optimized code is intended for advanced users only.</li></ol>

<h2>Selection is Broken</h2>
Selection often appears to be broken when the configuration file specifies a default selection, the wrong selection flags are being used, or when command line reserved characters are not being escaped.<br>
<ol><li>Ensure the $HOME/.trucovrc (or the config file you're using) is not specifying a default selection. By default, when Trucov is executed, it will output coverage information on every function and source file found; however, when the configuration specifies a selection, Trucov will use that as the default instead.<br>
</li><li>Ensure you are properly using the selection flags --and, --or, --partial-match, --full-match, and --signature-match. By default, --or is enabled, --partial-match is enabled, and --signature-match is disabled, unless specified otherwise by the config file or on the command line.<br>
</li><li>Ensure you escape the following regular expression characters on the command line: . <b>{ } ( ) | [ ]</li></ol></b>

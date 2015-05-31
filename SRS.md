

# Introduction #
Trucov is an open source program that works with the GCC compiler to display the control flow of a program and its test coverage information.
## Purpose ##
Trucov provides developers with a way to accurately measure and satisfy test coverage requirements.
It is difficult to completely map out and display all test coverage data. This results in occurrence of untested code and leads to error-prone software. As a result, test engineers do not have a standardized method for checking whether or not all test requirements have been met. Trucov provides solutions to these problems.

## Scope ##
Trucov shall convert the data from GCNO and GCDA files into coverage information for each source file in the form of a text coverage file or visual dot file.

Trucov shall be invoked over a project directory and shall search for all the files it needs. Trucov need not compile source code or execute any tests.

## Dictionary ##
Trucov = True Coverage (project name).<br>
GCC = GNU Compiler Collection.<br>
GCNO = GNU Compiler Code Structure File.<br>
GCDA = GNU Compiler Coverage Data File.<br>
DOT = Visual Graph Coverage File.<br>
Graphviz = Graph Visualization Software.<br>
Spirit = Boost Parsing Framework.<br>
Arc = A path between function blocks.<br>
Arc taken = A given path between function blocks has been executed.<br>
Branch = A block with multiple non-fake arcs exiting it.<br>
Tree Arc = An arc exiting a branch.<br>
Fake Arc = A compiler generated arc. A fake arcs is not counted unless it has been taken.<br>
Fallthrough Arc = A path to the next line of code.<br>
Block = A block of code contained within a function.<br>
Fake Block = A block which is entered into only by fake arcs or from another fake block.<br>

<h1>Interface Requirements</h1>

<h2>Project Directory Traversing</h2>
Trucov shall recursively search the project directory to find all source, GCNO, and GCDA files of a project. Trucov shall produce a DOT file or Coverage File for each source file in the source directory depending on program options. Trucov shall exith with an error if no build or output directory is found and print a warning for each failure.<br>
<br>
<h2>Trucov Usage</h2>

Trucov shall be invoked from the command line using the following format:<br>
<pre><code>    trucov [ command ] [ option... ] [ selection... ]<br>
</code></pre>
Commands specify the behavior and output of Trucov. Options specify settings for use at run time. Selection specifies for which functions coverage data will be output. Trucov shall not exit when a default/config-file directory isn't found. Trucov shall not print a warning for not found default/config-file directories. Trucov shall print a warning when a cmdline directory isn't found. Trucov may exit when a cmdline directory isn't found (do whatever is easier). These apply to source directories, build directories, etc.<br>
Output directories shall be created if they do not exist.<br>
<br>
<h2>Commands</h2>
The default command is status.<br>
Output files will shall follow the following format:<br>
<pre><code>    path##found##to##filename.&lt;command_extension&gt;<br>
</code></pre>

<ul><li><b>status</b>: Prints a coverage summary for each function to stdout.</li></ul>

<ul><li><b>list</b>: Prints the name of each function to stdout.</li></ul>

<ul><li><b>report</b>: Creates multiple text coverage files. Creates or overwrites a coverage file for each source file to the path 'output_dir/file_path_and_name.trucov'.</li></ul>

<ul><li><b>dot</b>: Creates or overwrites a single dot file. The dot file will show the coverage control flow of all functions to the path 'output_dir/coverage.dot'.</li></ul>

<ul><li><b>dot_report</b>: Creates multiple dot files. Creates or overwrites a dot file for each source file to the path 'file_path_and_name.dot'.</li></ul>

<ul><li><b>graph</b>: Creates or overwrites a single pdf file. The pdf file will show the control flow of all functions to the path 'output_dir/coverage.pdf'.</li></ul>

<ul><li><b>graph_report</b>: Creates multiple pdf files. Creates or overwrites a pdf file for each source file to the path 'output_dir/file_path_and_name.pdf'.</li></ul>

<ul><li><b>all_report</b>: Performs the report and graph_report commands.</li></ul>

<h2>Selection</h2>
The default selection will select all functions in all source files.<br>
Multiple selections union together by default.<br>
The selection will be partially matched to source files and functions by default.<br>
<br>
<h3>Selection Usage</h3>
Multiple selections may be listed after the commands and options. A selection can be given to match functions or files.<br>
<br>
The following is an example of Trucov selection given functions: foof, barb, foobar.<br>
<br>
<pre><code>  trucov list foo                  // Matches foof, foobar<br>
  trucov list bar                  // Matches barb, foobar<br>
  trucov --or list foo bar         // Matches foof, barb, foobar<br>
  trucov --and list foo bar        // Matches foobar<br>
  trucov --full-match list foo.    // Matches foof (notice .)<br>
  trucov list all                  // Matches foof, barb, foobar<br>
</code></pre>

<h3>Regex</h3>
A selection may be written as a regular expression. Regular expressions will perform a partial match by default. A full match can be performed by specifying the --full-match option.<br>
<br>
Selections shall only match the name of functions, not the signatures.<br>
<br>
The mangled name of functions shall be matched when the --mangle option is set. The demangled name of functions shall be matched when the --demangle option is set.<br>
<br>
<h2>Options</h2>

Trucov shall evaluate options from left to right in the Command Line. If conflicts exists between options, then the option most to the right shall take priority over the previous options.<br>
<br>
<table><thead><th>Option</th><th>Short Flag</th><th>Default value</th><th>Option Mode</th><th>Range</th><th>Where</th><th>Description</th></thead><tbody>
<tr><td>--help</td><td>-h        </td><td>Disabled     </td><td>Enable / Disable</td><td>N/A  </td><td>Command Line</td><td>Prints each command, the usage of the command, and the description of the command. Prints each option name, the short name, and the description of each option that may be used on the command line.</td></tr>
<tr><td>--help-config</td><td>None      </td><td>Disabled     </td><td>Enable / Disable</td><td>N/A  </td><td>Command Line</td><td>Prints the option name, the short name, and the description of each option that may be used in the config file.</td></tr>
<tr><td>--version</td><td>-v        </td><td>Disabled     </td><td>Enable / Disable</td><td>N/A/ </td><td>Command Line</td><td>Prints out the working version number of Trucov.</td></tr>
<tr><td>--chdir</td><td>-c        </td><td>Current Working Directory</td><td>Override   </td><td>Directory path</td><td>Command Line</td><td>Specifies the directory where trucov will run.</td></tr>
<tr><td>--builddir</td><td>-b        </td><td>Current Working Directory</td><td>Accumulate </td><td>Directory path</td><td>Command Line, Config File</td><td>Specifies the root directorie(s) of the GCNO and GCDA files.</td></tr>
<tr><td>--srcdir</td><td>-s        </td><td>Current Working Directory</td><td>Accumulate </td><td>Directory path</td><td>Command Line, Config File</td><td>Specifies the root directorie(s) of the source files.</td></tr>
<tr><td>--output</td><td>-o        </td></tr>
<tr><td>--cachefile</td><td>-f        </td><td>trucov.cache </td><td>Override   </td><td>File path</td><td>Command Line, Config File</td><td>Specifies the cache file to be used.</td></tr>
<tr><td>--debug</td><td>-d        </td><td>None         </td><td>Accumulate </td><td>all, parser, config, control</td><td>Command Line</td><td>Prints out debug and testing information.</td></tr>
<tr><td>--brief</td><td>None      </td><td>Disabled     </td><td>Enable / Disable</td><td>N/A  </td><td>Command Line</td><td>Only prints function summaries in coverage reports.</td></tr>
<tr><td>--only-missing</td><td>None      </td><td>Disabled     </td><td>Enable / Disable</td><td>N/A  </td><td>Command Line</td><td>Only outputs coverage information on functions with less than 100% coverage.</td></tr>
<tr><td>--show-fake / --hide-fake</td><td>None      </td><td>Hide         </td><td>Enable / Disable</td><td>N/A  </td><td>Command Line</td><td>Shows or hides output of coverage information on fake arcs and fake blocks.</td></tr>
<tr><td>--show-external-inline / --hide-external-inline</td><td>None      </td><td>Hide         </td><td>Enable / Disable</td><td>N/A  </td><td>Command Line</td><td>Shows or hides output of coverage information for inlined blocks from source files not within the default or specified source folders.</td></tr>
<tr><td>--mangle / --demangle</td><td>None      </td><td>Demangle     </td><td>Enable / Disable</td><td>N/A  </td><td>Command Line</td><td>Outputs the demangled or mangled names of functions.</td></tr>
<tr><td>--per-source  /  --per-function</td><td>None      </td><td>Per-Source   </td><td> Enable / Disable</td><td>N/A/ </td><td>Command Line, Config File</td><td>For commands report, dot_report, graph_report, and all_report; Creates report files per source or per function</td></tr>
<tr><td>--revision-script</td><td>None      </td><td>'None'       </td><td>Override   </td><td>File path or 'None'</td><td>Command Line, Config File</td><td>Specifies the script to be used to get revision information for the source files.</td></tr>
<tr><td>--default-command</td><td>None      </td><td>status       </td><td>Override   </td><td>status, list, report, dot, dot_report, graph, graph_report</td><td>Config File</td><td>Changes default command.</td></tr>
<tr><td>--default-selection</td><td>None      </td><td>all          </td><td>Accumulate </td><td>Any valid selections</td><td>Config File</td><td>Changes default selection.</td></tr>
<tr><td>--and / --or</td><td>None      </td><td>or           </td><td>Enable / Disable</td><td>N/A  </td><td>Command Line, Config File</td><td>Specifies a selection that will be matched, but may or may not be required to match.</td></tr>
<tr><td>--full-match / --partial-match</td><td>None      </td><td>partial      </td><td>Enable / Disable</td><td>N/A  </td><td>Command Line</td><td>Specifies any following selections shall be matched fully or partially.</td></tr>
<tr><td>--signature-match</td><td>None      </td><td>Disabled     </td><td>Enable / Disable</td><td>N/A  </td><td>Command Line</td><td>Specifies any following selections for functions shall be matched using the full function signature.</td></tr>
<tr><td>--config-file</td><td>None      </td><td>$HOME/.trucovrc</td><td>Override   </td><td>File path</td><td>Command Line</td><td>Specifies a file a config file.</td></tr>
<tr><td>--render-format</td><td>None      </td><td>svg          </td><td>Override   </td><td>svg, pdf</td><td>Command Line, Config File</td><td>Specifies the output format of graph files for the graph commands.</td></tr></tbody></table>

<h1>Input</h1>

<h2>Config File</h2>
Trucov shall save configurable options in the file $HOME/.trucovrc.  Trucov shall read configurable options from both the config file and the command line options. Command line options shall be selected over configurable options if there are conflicts between them.<br>
<br>
<h3>Config File Contents</h3>
The default value of options may be specified in the config file. The default-command, default-selection, and any default path may be specified in the config file.<br>
<br>
Trucov shall accept the default paths as either absolute or relative paths.<br>
<br>
If a default option is set twice in the configurable file, then the latter assignment shall be selected as the default value.<br>
<br>
If an invalid option_name or option_value is specified, then trucov shall print a error message at runtime, ignore the option assignment, and execute as normal.<br>
<br>
<h3>Config File Format</h3>
An options default value shall be set by using the following syntax:<br>
<pre><code>  #&lt;Comment&gt;<br>
  &lt;option_name&gt; &lt;= option_value&gt;<br>
  &lt;option_name&gt;<br>
</code></pre>
Where option_name is the name of the configurable option, and option_value is the new default value of the option.<br>
<br>
Examples of the config file format are as follows:<br>
<pre><code>  #default-command = status    This is a comment<br>
  --default-command = dot_report<br>
  --builddir = build_directory/<br>
  --show-blocks<br>
</code></pre>
This example sets dot_report to the default command. The directory /home/buster/trucov_project/ will be selected as the default directory instead of the current working directory. The build directory will default to build_directory/ relative to the current directory.<br>
<br>
<h2>Revision Script</h2>
The Revision script is an external program that Trucov can use to get version control information for the source files in the source directories. This allows Trucov to optionally, output the revision information of each source file along with the coverage information. The revision script can be in the form of any executable as long as it meets the input and output requirements.<br>
<br>
<h3>Revision Script Usage</h3>
The revision script file path may be specified in the command line or the config file. If the path specified is invalid, Trucov shall print a warning and treat the command as if 'None' was specified. Trucov shall invoke the revision script, gather the output, and attempt to match revision information with the files it runs over.<br>
<br>
<h3>Revision Script Input</h3>
The Revision script takes a single command line argument. The argument specifies a file.<br><br>

<h3>Revision Script Output</h3>
For a file under version control, the revision script will output one line of revision script information to stdout. Files not found or have no revision information should output an empty line.<br>
<br>
Example:<br>
<pre><code>   ./revision_script_svn foo.cpp<br>
   54<br>
   <br>
   ./revision_script_svn foo.h<br>
   77<br>
</code></pre>
<h1>Output</h1>
<h2>Coverage File</h2>
<h3>Coverage File Contents</h3>

Trucov shall create a test coverage file in text for each source file. The coverage file shall list how many times each function was executed, list which branches of code were executed at least once, and list the source and line number of blocks that were not executed in the coverage file.<br>
<br>
<h3>Coverage File Format</h3>

Trucov shall produce coverage files with the directory name, followed by two # symbols, then the source file name with a .trucov extension.<br>
<pre><code>   output_directory/path##to##source_file.cpp.trucov<br>
</code></pre>
A function's coverage percentage shall always consist of 4 characters, including the numbers and the % sign, and shall be right aligned.<br>
<br>
<h4>Function Without Coverage Data</h4>
Functions without coverage data will list the function signature and "no coverage information (missing gcda)" text.<br>
<pre><code>  &lt;function_signature&gt; no coverage information (missing gcda)<br>
</code></pre>
Example:<br>
<pre><code>  dog::lay() no coverage information (missing gcda)<br>
</code></pre>

<h4>Function With No Branches</h4>
Functions with no branches shall list 0% or 100%, the function name, and "no branches" text.<br>
<pre><code>   &lt;percentage&gt;% &lt;function_signature&gt; no branches<br>
</code></pre>
Example:<br>
<pre><code>   100% dog::walk(int &amp;) no branches<br>
</code></pre>

<h4>Function With Branches</h4>
Functions with branches will list the coverage percentage, list the function name, and list the ratio of branches taken to the total number of branches. Any branch without full coverage will have its missing arc lines listed below the branch summary.<br>
<pre><code>   &lt;coverage&gt;% &lt;function_signature&gt; ( &lt;#_branches_taken&gt; / &lt;#_branches_total&gt; ) branches<br>
</code></pre>
Example:<br>
<pre><code>    66% dog::bark(const string &amp;) (3/6) branches<br>
        path_name/dog.cpp:10: 2/4 branches: &lt;src_line&gt;<br>
           path_name/dog.cpp:14:destination:&lt;src line&gt;<br>
           path_name/dog.cpp:23:destination:&lt;src line&gt;<br>
        path_name/dog.cpp:25: 1/2 branches: &lt;src_line&gt;<br>
           path_name/dog.cpp:29:destination:&lt;src line&gt;<br>
   100% dog::wagtail() (2/2) branches<br>
</code></pre>
<h2>DOT File</h2>

<h3>DOT File Contents</h3>

Trucov shall optionally produce a DOT file for each source file or for the entire project.<br>
<br>
DOT files shall contain a description for a control flow graph for each function in the source file.<br>
<br>
The graph description shall contain information regarding how many times each arc and block were executed.<br>
<br>
<h3>DOT File Arc Visual Format</h3>

The DOT file shall use color coding and line styles to describe the program control flow.<br>
<br>
<table><thead><th>Arc Type</th><th>Taken True</th><th>Taken False</th><th>Unknown</th></thead><tbody>
<tr><td>Normal  </td><td>Solid Blue</td><td>Solid Red  </td><td>Solid Purple</td></tr>
<tr><td>Fake    </td><td>Dotted Blue</td><td>Dotted Red </td><td>Dotted Purple</td></tr>
<tr><td>Fallthrough</td><td>Dashed Blue</td><td>Dashed Red </td><td>Dashed Purple</td></tr></tbody></table>

<h3>DOT File Block Visual Format</h3>

The DOT file will use different shapes for normal blocks, branches, fake blocks, and fake branches.<br>
Each function will be drawn as its own graph, and every function shall have a start block. All types of blocks will display the lines making up that block. If the debug option is used, the block flag and number will also be shown. Additionally, the start block will display the source file and function signature.<br>
<br>
<table><thead><th>Block type</th><th>Complete Coverage True</th><th>Complete Coverage False</th></thead><tbody>
<tr><td>Normal    </td><td>White Ellipse         </td><td>Indian Red Ellipse     </td></tr>
<tr><td>Fake      </td><td>White Inverted Triangle</td><td>Indian Red Inverted Triangle</td></tr>
<tr><td>Branch    </td><td>White Diamond         </td><td>Indian Red Diamond     </td></tr>
<tr><td>EndBlock  </td><td>White Triangle        </td><td>Indian Red Triangle    </td></tr></tbody></table>

<h1>Settings Requirements</h1>
Trucov requires a working development environment to run in. Trucov shall work with the GCNO and GCDA files produced by the GCC compiler. The GCNO file is created by compiling source code with the -fprofile-arcs flag. The GCDA file is created by compiling source code with the -ftest-coverage flag and then executing the resulting binary executable.<br>
<br>
<h2>GCC</h2>
Trucov requires an installation of the GCC compiler version 4.0 and above for both the compilation and generation of the GCNO notes and GCDA data files.<br>
<br>
<h2>Boost</h2>
The C++ Boost libraries are required for their Program Options and Regex libraries that Trucov relies upon.<br>
<br>
<h2>popen()</h2>
This function is part of the stdio.h library, however, Microsoft Windows users may need to install Cygwin onto their systems in order to use this function.<br>
<br>
<h2>c++filt</h2>
This program demangles the mangled names contained within the GCNO file. It is a part of the GNU binutils toolset. Microsoft Windows users will need to install Cygwin onto their systems in order to use this command.<br>
<br>
<h2>Graphviz</h2>
The dot tool is used to generate PostScript or PDF documents from any DOT file(s) that the Trucov tool outputs.<br>
<br>
<h2>HOME environment variable</h2>
Needed for location of $HOME/.trucovrc config file.<br>
<br>
<h1>Performance Requirements</h1>
The Trucov tool shall generate coverage information in 1 second per 10000 lines of code.<br>
<br>
<h2>Caching</h2>
Trucov shall use a caching system to cache coverage data after every run. Trucov shall produce a cache file in current project directory for the current run. Trucov shall only parse files that are not found in the caching system and have not been updated since the last run. If either no cache file is provided or if 'none' is specified, then the cache file trucov.cache shall be used.<br>
<br>
<h1>Algorithm Requirements</h1>

<h2>GCNO and GCDA File Parsing</h2>
The Trucov parser shall take input from the GCNO and GCDA file pairs produced by the GCC compiler.<br>
<br>
The Trucov parser shall use Boost Spirit technology to parse the GCNO and GCDA files.<br>
<br>
The GCNO and GCDA file grammars shall be defined in Spirit's EBNF syntax.<br>
<br>
The parsing shall use rules, tokens, aliases, and primitives to construct the grammar in documentation and implementation.<br>
<br>
The Trucov parser shall test for big or little endian byte ordering in order to be compatible with both Intel and PowerPC systems.<br>
<br>
<h3>Tokens</h3>
Tokens are symbols used to match specific values in the input. Tokens shall have one value and those values can never be changed.<br>
Token identifiers shall contain only Capital alphas and underscores. Tokens shall be used in grammars directly.<br>
<br>
<h3>Primitives</h3>
Primitives are sub parsers which return a value determined by the input and the sub parsers grammar. Two types of primitives exist, static and dynamic.<br>
Primitive identifiers shall contain only Capital alphas and numbers. Primitives shall not be used in grammars directly, but instead Aliases associated with primitives shall be used in the grammar instead. The primitives shall handle calculating the values from big endian and little endian input files.<br>
<br>
<h4>TOKEN</h4>
Reads in a 32 bit integer from a raw data stream, and attempts to match a value supplied to the value read. If the value fails to match, the parsing fails and aborts.<br>
<br>
<h4>INT32</h4>
Consumes 4 bytes from a raw data stream and produces a 32 bit integer.<br>
<br>
<h4>NONZERO</h4>
Consumes 4 bytes from a raw data stream and produces a 32 bit integer if it is non zero. If the value is zero, the parsing fails, otherwise, the parsing was successful.<br>
<br>
<h4>INT64</h4>
Consumes 8 bytes from a raw data stream and produces a 64 bit integer.<br>
<br>
<h4>STRING</h4>
Reads in a string from a raw data stream in the following format: Read an INT32, which represents the size of the string in the data stream. The size of the string is measured in units of 4 characters. Then, read a string that's terminated by a null character. Last, read in the padding which is the remaining characters in the data stream up to the specified size.<br>
<br>
<h3>Aliases</h3>
An alias is a sub rule that is specifically associated with a primitive and only that primitive. Aliases are used to apply specific names to the primitives needed in a rule. Aliases shall be used in the grammar directly. Alias identifiers shall contain only lower case alphas and numbers.<br>
<br>
<h3>Rules</h3>
Rules shall define the grammar. A Rule is composed of tokens, aliases, and the ENBF syntax. Rules do not directly contain primitives; if a primitive is to be added to a rule, then an alias shall be created to represent that primitive in the Rule. Rule identifiers shall contain an upper case alpha, followed by alphas and numbers, and will always contain at least of lower case alpha.<br>
<br>
<h3>Flag Bit Definitions</h3>
An arc with the lowest bit not set shall be counted and recorded in the GCDA file. All non-counted arcs shall rely on a normalization function which will assign their counts.<br>
<br>
<table><thead><th>Combined Flags</th><th>Combined Flags (Binary)</th><th>Fallthrough Flag</th><th>Fake Flag</th><th>On_Tree Flag</th><th>Description</th></thead><tbody>
<tr><td>0             </td><td>000                    </td><td>                </td><td>         </td><td>            </td><td>Normal, Counted</td></tr>
<tr><td>1             </td><td>001                    </td><td>                </td><td>         </td><td>X           </td><td>Normal, Not Counted</td></tr>
<tr><td>2             </td><td>010                    </td><td>                </td><td>X        </td><td>            </td><td>Exception, Counted</td></tr>
<tr><td>3             </td><td>011                    </td><td>                </td><td>X        </td><td>X           </td><td>Exception, Not Counted</td></tr>
<tr><td>4             </td><td>100                    </td><td>X               </td><td>         </td><td>            </td><td>Jump, Counted</td></tr>
<tr><td>5             </td><td>101                    </td><td>X               </td><td>         </td><td>X           </td><td>Jump, Not Counted</td></tr></tbody></table>

<h3>GCNO File Grammar</h3>

<h4>Token Definitions</h4>
<pre><code> ZERO_32         0x00000000 &lt;br&gt;<br>
 MAGIC           0x67636E6F (gcno)&lt;br&gt;<br>
 TAG_FUNCTION    0X01000000 &lt;br&gt;<br>
 TAG_BLOCKS      0x01410000 &lt;br&gt;<br>
 TAG_ARCS        0x01430000 &lt;br&gt;<br>
 TAG_LINES       0x01450000<br>
</code></pre>
<h4>Alias Definitions</h4>
<pre><code> version:        INT32 &lt;br&gt;<br>
 stamp:          INT32 &lt;br&gt;<br>
 rLength:        INT32 &lt;br&gt;<br>
 rIdent:         INT32 &lt;br&gt;<br>
 rChecksum:      INT32 &lt;br&gt;<br>
 rName:          STRING &lt;br&gt;<br>
 rSource:        STRING &lt;br&gt;<br>
 rLineno:        INT32 &lt;br&gt;<br>
 bLength:        INT32 &lt;br&gt;<br>
 bFlags:         INT32 &lt;br&gt;<br>
 aLength:        INT32 &lt;br&gt;<br>
 aBlockno:       INT32 &lt;br&gt;<br>
 destBlock:      INT32 &lt;br&gt;<br>
 aFlags:         INT32 &lt;br&gt;<br>
 lLength:        INT32 &lt;br&gt;<br>
 lBlockno:       INT32 &lt;br&gt;<br>
 lName:          STRING &lt;br&gt;<br>
</code></pre>
<h4>Rule Definitions</h4>
<pre><code> GcnoFile:       MAGIC , Version , Stamp , {Record} ;&lt;br&gt;<br>
 Record:         AnnounceFunction , BasicBlocks , (bLength - 1 * Arcs) , {Lines} ;<br>
 AnnouceFunction: TAG_FUNCTION , rLength , rIdent , rChecksum , rName, rSource, rLineno ;<br>
 BasicBlocks:    TAG_BLOCKS , bLength , (bLength * bFlags) ;<br>
 Arcs:           TAG_ARCS , aLength, aBlockno, (aLength * Arc) ;<br>
 Arc:            destBlock, aFlags ;<br>
 Lines:          TAG_LINES , lLength , lBlockno , *Line , ZERO_32 , ZERO_32 ;<br>
 Line:           lLineno | ZERO_32 , lName , lLineno | ZERO_32 , lName ;<br>
</code></pre>
<h3>GCDA File Grammar</h3>

<h4>Token Definitions</h4>
<pre><code> ZERO_32             0x00000000 &lt;br&gt;<br>
 MAGIC               0x67636461 (gcda)&lt;br&gt;<br>
 TAG_FUNCTION        0x01000000 &lt;br&gt;<br>
 TAG_COUNTER_BASE    0x01A10000 &lt;br&gt;<br>
 TAG_OBJECT_SUMMARY  0xA1000000 &lt;br&gt;<br>
 TAG_PROGRAM_SUMMARY 0xA3000000<br>
</code></pre>
<h4>Alias Definitions</h4>
<pre><code> version:        INT32 &lt;br&gt;<br>
 stamp:          INT32 &lt;br&gt;<br>
 rLength:        INT32 &lt;br&gt;<br>
 rIdent:         INT32 &lt;br&gt;<br>
 rChecksum:      INT32 &lt;br&gt;<br>
 aCount:         INT64 &lt;br&gt;<br>
 aLength:        INT32 &lt;br&gt;<br>
 oChecksum:      INT32 &lt;br&gt;<br>
 oLength:        INT32 &lt;br&gt;<br>
 oCounts:        INT32 &lt;br&gt;<br>
 oRuns:          INT32 &lt;br&gt;<br>
 oSumall:        INT64 &lt;br&gt;<br>
 oRunmax:        INT64 &lt;br&gt;<br>
 oSummax:        INT64 &lt;br&gt;<br>
 pChecksum:      INT32 &lt;br&gt;<br>
 pLength:        INT32 &lt;br&gt;<br>
 pCounts:        INT32 &lt;br&gt;<br>
 pRuns:          INT32 &lt;br&gt;<br>
 pSumall:        INT64 &lt;br&gt;<br>
 pRunmax:        INT64 &lt;br&gt;<br>
 pSummax:        INT64 &lt;br&gt;<br>
</code></pre>
<h4>Rule Definitions</h4>
<pre><code> GcdaFile:        MAGIC , Version , Stamp , {Record} , ObjectSummary , {ProgramSummary} ;<br>
 Record:          AnnounceFunction , {Counters} ;<br>
 AnnouceFunction: TAG_FUNCTION , rLength , rIdent , rChecksum ;<br>
 Counters:        TAG_COUNTER_BASE , aLength , ( aLength / 2 ) * aCount ;<br>
 ObjectSummary:   TAG_OBJECT_SUMMARY , oLength , oChecksum , oCounts , oRuns , oSumall , oRunmax , oSummax ;<br>
 ProgramSummary:  TAG_PROGRAM_SUMMARY , pLength , pChecksum , pCounts , pRuns , pSumall , pRunmax , pSummax ;<br>
</code></pre>
<h1>Appendix</h1>
<h2>References</h2>
'''<a href='http://www.graphviz.org/doc/info/lang.html'>The DOT Language</a>'''<br>
<br>
'''<a href='http://www.graphviz.org/'>Graphviz</a>'''<br>
<br>
'''<a href='http://linuxcommand.org/man_pages/gcov1.html'>gcov man page</a>'''<br>
<br>
'''<a href='http://gcc.gnu.org/onlinedocs/gcc/Gcov-Intro.html#Gcov-Intro'>About Gcov</a>'''<br>
<br>
'''<a href='http://www.cmake.org/'>Cmake Homepage</a>'''<br>
<br>
'''<a href='http://gcc.gnu.org/'>Gcc Homepage</a>'''<br>
<br>
'''<a href='http://www.google.com/codesearch/p?hl=en#TBt53jeThWE/gcc-3.4.4/gcc/gcov-io.h'>gcov-io.h</a>'''<br>
<br>
'''<a href='http://www.google.com/codesearch/p?hl=en#A7TBhdHDU50/test/decode-gcov.c'>decode-gcov.c</a>'''<br>
<br>
<h3>Dot File Grammar</h3>
<pre><code> graph  	:  	[ strict ] (graph | digraph) [ ID ] '{' stmt_list '}'<br>
 stmt_list 	: 	[ stmt [ ';' ] [ stmt_list ] ]<br>
 stmt	 	: 	node_stmt<br>
 		| 	edge_stmt<br>
 		| 	attr_stmt<br>
 	 	| 	ID '=' ID<br>
 	 	| 	subgraph<br>
 attr_stmt 	: 	(graph | node | edge) attr_list<br>
 attr_list 	: 	'[' [ a_list ] ']' [ attr_list ]<br>
 a_list 	: 	ID [ '=' ID ] [ ',' ] [ a_list ]<br>
 edge_stmt 	: 	(node_id | subgraph) edgeRHS [ attr_list ]<br>
 edgeRHS 	: 	edgeop (node_id | subgraph) [ edgeRHS ]<br>
 node_stmt 	: 	node_id [ attr_list ]<br>
 node_id 	: 	ID [ port ]<br>
 port	 	: 	':' ID [ ':' compass_pt ]<br>
 		| 	':' compass_pt<br>
 subgraph 	: 	[ subgraph [ ID ] ] '{' stmt_list '}'<br>
 compass_pt 	: 	(n | ne | e | se | s | sw | w | nw | c | _)<br>
</code></pre>

<a href='http://selcov.eecs.wsu.edu/svn/selcov/Documents/SND.jpg'>High Level Design</a>

[[Category:Documentation]]
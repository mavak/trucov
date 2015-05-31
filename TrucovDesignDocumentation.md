[Data Flow Diagram](http://code.google.com/p/trucov/wiki/TrucovDesignDocumentation#Data_Flow_Diagram)<br>
<a href='http://code.google.com/p/trucov/wiki/TrucovDesignDocumentation#Component_Diagram'>Component Diagram</a><br>
<a href='http://code.google.com/p/trucov/wiki/TrucovDesignDocumentation#Control_System'>Control System</a><br>
<a href='http://code.google.com/p/trucov/wiki/TrucovDesignDocumentation#Spirit_Parsing_Framework'>Spirit Parsing Framework</a><br>
<a href='http://code.google.com/p/trucov/wiki/TrucovDesignDocumentation#Parser_Data_Construction'>Parser Data Construction</a><br>
<a href='http://code.google.com/p/trucov/wiki/TrucovDesignDocumentation#Debugging'>Debugging</a><br>

<h1>Data Flow Diagram</h1>

<img src='http://trucov.googlecode.com/hg/docs/design/data_flow.png' />

<h1>Component Diagram</h1>

<img src='http://trucov.googlecode.com/hg/docs/design/component_diagram.png' />

<h2>Control System</h2>
The control system parses user input, invokes the Parser data construction, and implements the trucov commands.<br>
<br>
<h2>Parser Data Model</h2>
The Parser Data Model provides an interface to the control flow and coverage data of functions found in the GCNO and GCDA files.<br>
<br>
<h2>Parser Data Construction</h2>
The Parser Data Construction system handles constructing the data model and normalizing the GCNO and GCDA raw data.<br>
<br>
<h2>Spirit Parsing Framework</h2>
The Spirit Parsing Framework implements grammars and tools needed to parse the GCNO and GCDA files.<br>
<br>
<h1>Control System</h1>

<img src='http://trucov.googlecode.com/hg/docs/design/control_system.png' />

<h2>Config</h2>

The Config class provides all data from the command line input and config file input. It is a singleton, and will provide an interface to get any data specified on the command line.<br>
<br>
<h2>Command</h2>
The Command class implements all the commands of the trucov tool.<br>
<br>
<h2>Coverage_creator</h2>
The Coverage_creator class implements the methods needed to execute the report command.<br>
<br>
<h2>Dot_creator</h2>
The Dot_creator class implements the methods needed to execute the dot, dot_report, render, and render_report commands.<br>
<br>
<h1>Spirit Parsing Framework</h1>

<img src='http://trucov.googlecode.com/hg/docs/design/spirit_parser_class_diagram.png' />

<h2>Primitives</h2>
A primitive is used to parse a basic type from the raw data stream. The primitive file defines the primitives used in the Gcno and Gcda grammar. Every primitive is implemented from a functor.<br>
<br>
<h2>Common Actors</h2>
The common_actors file defines all semantic actions that assign values to variables from the input data.<br>
<br>
<h2>Gcno Actors</h2>
The gcno_actors file defines the semantic actions used for building the data structure. The actions will pass the control flow data to a Parser_builder object for data construction.<br>
<br>
<h2>Gcda Actors</h2>
The gcda_actors file defines the semantic actions used for building the data structure.<br>
The actions will pass the coverage data to a Parser_builder object for data construction.<br>
<br>
<h2>Gcno Grammar</h2>
The Gcno_grammar class defines the grammar of the GCNO file. The grammar is defined in EBNF form and must be compatible for the Spirit framework for parsing.<br>
<br>
<h2>Gcda Grammar</h2>
The Gcda_grammar class defines the grammar of the GCDA file. The grammar is defined in EBNF form and must be compatible for the Spirit framework for parsing.<br>
<br>
<h1>Parser Data Construction</h1>

<img src='http://trucov.googlecode.com/hg/docs/design/parser_data_construction.png' />

<h2>Parser</h2>
The Parser class creates a Parser_builder object when the parse method is called. The Parser passes references to the internal data structure during construction of the Parser_builder object.<br>
<br>
<h2>Parser Builder</h2>
The Parser_builder constructs the data structure. It provides an interface to the Spirit parsing framework to construct the data structure.<br>
<br>
<h2>Spirit Parsing Framework</h2>
The semantic actions pass the parsed data to the Parser_builder object.<br>
<br>
<h2>Selection</h2>
The Selector class determines which functions will be stored in the data structure and which will not.<br>
<br>
<h2>Revision Script</h2>
The Revision_script_manager gets the revision script number for source files found under version control.<br>
<br>
<h1>Parser Data Model</h1>

<img src='http://trucov.googlecode.com/hg/docs/design/parser_data_model.png' />

<h2>Parser</h2>
The Parser class contains a list of Source_file objects. The Parser class will provide an interface to access the source file objects.<br>
<br>
<h2>Source File</h2>
The Source_file class contains a list of Record objects representing functions. The Source_file class provides an interface to access the record objects.<br>
<br>
<h2>Record</h2>
The Record class contains a list of Block objects representing the functions basic blocks. The Record class provides an interface to access the block objects.<br>
<br>
<h2>Block</h2>
The Block class contains a list of Arc objects representing the function outgoing arcs of the Block. The Block class provides an interface to access the arc objects.<br>
<br>
<h2>Arc</h2>
The Arc class contains data about an arc.<br>
<br>
<h2>Lines Data</h2>
The Lines_data class contains data about a blocks line data.<br>
<br>
<h1>Debugging</h1>
Debugging specified by the --debug flag will be handled by the Debugger class.<br>
The Debugger class defines public enumerations for the different types of debugging: all, parser, config, and control. The <br>
The Debugger defines the following public enumeration and public static methods:<br>
<pre><code>enum debug_type { parser = 1, config = 2, control = 4, all = 0xFFFF };<br>
static void set_debug_flag(short flag) const;<br>
static void debug_print(debug_type, const string &amp; format, ...) const;<br>
static int get_debug_flag() const;<br>
</code></pre>

<h2>set_debug_flag</h2>
Stores the debug flag in the Debugger class (The debug flag variable must be static).<br>
The flag parameter should contain a value to set all corresponding flags specified by the debug_flag enumeration.<br>
<br>
<h2>debug_print</h2>
If the debug_type parameter, is specified by the internal debug flag, then the method will print a debug message to stderr using a format string, and a variable amount of arguments (similar to printf).<br>
<br>
<h2>get_debug_flag</h2>
Returns the internal debug_flag.
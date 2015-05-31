# Introduction #

Selection is complicated.  The problem comes from the shear number of ways that we could want to filter our results.

Which field to filter on:
  * function name
  * function signature
  * function mangle
  * file path
  * file name

How are regexes applied:
  * must match entire string
  * must match some part of string

How are multiple selections combined:
  * all selections must match
  * at least one selection must match
  * what about selecting functions that don't match

How to combine the combinations?  Selecting functions that don't match is hardly useful if it isn't accompanied by normal regexes.

### Some rejected ideas ###

prefix inverted regexes with **-**.  That could work but it's odd.

use find style options, where various selections can be combined with _-and_, _-or_, and _-not_ commandline args between.  This would require custom command line args parsing.  I don't now how useful it would be as most see find's logical operators to be awkward and difficult to remember.


# How it works now #

# How it should work #

I'd like to embed Lua to handle our selection woes.

The selection command would be a Lua fragment, but the average end user does not need to know that.  They could easily learn the small subset we're using and never know that there is a whole language underneath.

## Basics ##

A selection uses a small string prefix to a regular expression that when it matches a function attribute causes the function to be selected.

```
<prefix>"<regex>"
```

Available `<prefix>`s
|Short prefix|Long prefix|Description|
|:-----------|:----------|:----------|
| **n**      | **name**  |     Use the accompanying `<regex>` on the function names.|
| **s**      | **signature** |Use the accompanying `<regex>` on the function signatures.|
| **m**      | **mangle** |   Use the accompanying `<regex>` on the function mangled names.|
| **f**      | **file**  |     Use the accompanying `<regex>` on the file name that has been stripped of its path.|
| **p**      | **path**  |     Use the accompanying `<regex>` on the full file path.|

The settings will determine whether the `<regex>` tries to fully or partially match the attribute.  There are two prefix modifers
  * **`f`** and **`_full`**: for short and long prefixes respectively will force the `<regex>` to only use full matching.
  * **`p`** and **`_part`**: for short and long prefixes respectively will force the `<regex>` to use partial matching.

Some examples:
  * **`s"foo"`**: Match signature against foo using the default setting for full vs partial matching.
  * **`sf"foo"`**: Perform a full match of full against the function signatures.  This would only match an `extern "C"` function named foo.
  * **`file_part"foo"`**: Perform a partial regex match against file name looking for foo.
  * **`f_full"foo"`**: An invalid prefix.  It would be caught and reported to the user as soon as trucov was ran (before parsing the gcno/gcda files).

## Advanced ##
More advanced users and dip into the logical operators.  At this point they could probably  realize that the selection is full featured language.  The again the syntax subset is small enough they won't need to know it's Lua.

Logical operators
  * **or**: logical _or_ of two `<regex>`s.  If either matches the function is selected.
  * **and**: logical _and_ of two `<regex>`s.  The function will only be selected if both match.
  * **not**: logical _not_ or a `<regex>`.  The function will only be selected if the there is not a match.
  * **()**: logical grouping.  Override the default logical grouping, by evaluating the expression in the _()_ before those outside.  Nesting of _()_ is allowed.

Some examples:
  * `np"foo" and not nf"foobar"`: match function with _foo_ in their name but not _foobar_.

## Use Cases ##
### Class methods without constructors/destructors ###
This arises often enough.  I want to get a coverage report for a particular class.  However, the crazy constructors destructors are artificially lowering my total percentage.  So I want to look at my coverage excluding results from the constructors/destructors.

```
s"Foobar::" and not ( m"C[123]E" or m"D[0123]Ev")

--# more verbosely
signature"Foobar::" and not ( mangle"C[123]E" or mangle"D[0123]Ev")   
```

Admittedly the regex syntax for finding constructors/desctructors is complicated but I've actaually needed to do this once and I had the expertise needed to select only constructors or destructors but I didn't have a way to get trucov to filter it.

### Future function traits ###
We may be able to expand what field can be selected on by parsing debug info.  A few that would be immediate value:
  * dynamically linked functions
  * return type
  * a parameter type

Both return type and parameter type could be achieved with clever regexes but I for one am not up to the task.  I would use it if trucov gave it to me for free though.

```
--# select all dynamically linked functions that return an int and have a float parameter
return_type("int") and dynamic and param_type("float")
```

### API for selection plugins ###
If a user finds that a particular selection is very useful but non-trivial to write on the command line they could quickly create create a plugin.  He could push the plugin back the trucov and we could include it in the default release.  All without having to recompile.

rudimentary API
```
--#return the current function's name
api.name()
--#return the current function's signature
api.signature()
--# more

--#return true if regex fully/partially matches string.
--#could perform internal caching to speed up regex compilation.
api.regex_full( regex, string )
api.regex_part( regex, string )

--#perform regex match using default, either full or partial
api.regex( regex, string )
```

example plugin
```
function constructor_destructor()
   --#return true if function is constructor/destructor
   return api.regex_part( 'C[123]E|D[012]Ev', api.mangle() )
end
c = constructor_destructor
```

example usage
```
--#select Foobar:: methods, ignoring the constructor/destructor
s"Foobar::" and not c()
```
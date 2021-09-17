The modules are single header files which are used with namespaces.
They are intended to be directly included into source files

Most of them don't have include guards.

I tried just putting the namespaces in the main file
e.g.

namespace misc {
    #include "something.h";
    #include "somethingelse.h";
}

but this appears to cause problems for the standard headers.  I believe that because they are only compiled once their functionality is being hidden inside the namespace.


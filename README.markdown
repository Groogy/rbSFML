This is the Ruby bindings of the [SFML library](https://github.com/LaurentGomila/SFML) developed and maintained by Groogy

I hope you enjoy using rbSFML. If you make anything in it then we are very interested in hearing about it.
We can always be reached at http://www.sfml-dev.org/forum for support, ideas or just have a nice chat.

If you have questions or need help then please post it on the forum or write us an email. The issue tracker is for bugs
and suggestions only please. If you are uncertain then write it on the forum instead.

Dependencies
============

Of course this means this library depends on SFML so you'll have to install SFML2 on your development machine in order to compile rbSFML. rbSFML comes with a cloned module from the SFML Github repository that rbSFML is known to compile against but you can try and use the latest version of SFML as long as SFML has not come with anything API breaking. If that is the case then you don't even need to recompile rbSFML but only replace the SFML shared libraries.

Recommended is this setup: (lowers or highers versions might work too)

- [SFML - commit 2e22038be7](https://github.com/LaurentGomila/SFML/tree/2e22038be7f30702f8acd653d67534de99a8f441)
- [Ruby 1.9.3-p327](http://www.ruby-lang.org/en/downloads/)
- [Rake 10.0.2](https://rubygems.org/gems/rake)
- [Yard 0.8.3](https://rubygems.org/gems/yard)
- [Git 1.8.0.1](http://git-scm.com/download)

Installation
============

Windows
-------

1.  Install Ruby. The simple [Ruby Installer](http://rubyinstaller.org/downloads) works fine.

2.  [Download](https://github.com/LaurentGomila/SFML) and [compile](http://sfml-dev.org/tutorials/2.0/compile-with-cmake.php) SFML.

3.  Open `cmd` and navigate to a folder where you want to install rbSFML source files.

4.  Clone this repository with `git clone git@github.com:Groogy/rbSFML.git`.

5.  Ensure that your C++ compiler's location is in your PATH environment variable. Run `rake verbose` to see what compiler Ruby thinks you have. If the SFML headers and libraries are not in your compiler's default search paths, set the `SFML_INCLUDE` and `SFML_LIB` environment variables to their locations.

6.  Run one of the following commands in your terminal:

  * `rake` - Build all SFML as shared libraries (need DLLs) - recommended.
  * `rake static` - Build all SFML as static libraries (don't need DLLs).
  * `rake graphics` - Build only the graphics module (and its dependencies). You can use any other module (`audio`, `system` and `window`) with it. You can also add `static`.

7.  If you built SFML as a shared library, you will need the SFML DLLs in your PATH in order to `require` any of the rbSFML files (this can be accomplished by copying them to the directory where rbSFML is being `require`d).

8.  Run `rake test` to ensure everything is working and then `rake gem` to package rbSFML as a Ruby gem.

9.  You can build the documentation (at doc/frames.html) with `rake doc` and run the samples with `rake samples`.

Linux
-----

1.  Install Ruby. If your flavor of Linux does not provide a package for this (which is unlikely), you can compile Ruby from [source](http://www.ruby-lang.org/pt/downloads/) and follow its instructions for installation.

2.  You must have a recent build of SFML installed. If your flavor of Linux does not provide a package for this (which **is** likely), you will need to compile SFML from [source](https://github.com/LaurentGomila/SFML) and follow its [instructions](http://sfml-dev.org/tutorials/2.0/compile-with-cmake.php) for installation.

3.  Ensure that the SFML headers and libraries are in your C++ compiler's search paths. The easiest way is to try compiling and running a simple SFML app.

4.  Navigate to a folder where you want to install rbSFML source files.

5.  Clone this repository with `git clone git@github.com:Groogy/rbSFML.git`.

6.  From the rbSFML directory, run one of the following commands in your terminal:

  * `rake` - Build all SFML as shared libraries.
  * `rake graphics` - Build only the graphics module (and its dependencies). You can use any other module (`audio`, `system` and `window`) with it.

7.  Run `rake test` to ensure everything is working and then `rake gem` to package rbSFML as a Ruby gem.

8.  You can build the documentation (at doc/frames.html) with `rake doc` and run the samples with `rake samples`.

Questions?
==========

[Open a issue](https://github.com/Groogy/rbSFML/issues/new).

Contact
=======

**Groogy:**

- E-mail: groogy@groogy.se
- Forum:  http://www.sfml-dev.org/forum/profile.php?mode=viewprofile&u=921
- Github: https://github.com/Groogy

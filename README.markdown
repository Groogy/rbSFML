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

1.  Open `cmd` and navegate to a folder where you want to install rbSFML source files.

2.  Clone this repository with `git clone git@github.com:Groogy/rbSFML.git`.

3.  Download and compile SFML. (you can find how to do it [here](http://sfml-dev.org/tutorials/2.0/compile-with-cmake.php))

4.  Copy the `include` and `lib` folders from SFML to the rbSFML folder. If you built SFML as a shared library, move all `.dll` files from `lib` to your `ruby\bin` directory Wor any directory you find fitting that places in the environment variable PATH.

5.  Run one of the following commands in your terminal:

  * `rake` - Build all SFML as shared libraries (need DLLs) - recommended.
  * `rake static` - Build all SFML as static libraries (don't need DLLs).
  * `rake graphics` - Build only the graphics module (and its dependencies). You can use any other module (`audio`, `system` and `window`) with it. You can also add `static`.

6.  Run `rake install`. (Needs administrative permission to access ruby installation directory)

7.  You can now use rbSFML in any ruby application. 

8.  You can run `rake test` to ensure everything is working and `rake doc` to build and open the documentation (at `doc/frames.html`).

9.  To run samples run `rake samples`. All samples are in `samples` folder.

Linux
-----

1.  You must compile Ruby from source. If you didn't do it, download the most recent stable Ruby sources from [here](http://www.ruby-lang.org/pt/downloads/). Unpack them to a folder of your choice and navigate to this folder with a terminal. Run `./configure`, then `make` and finally `sudo make install`.

2.  Navegate to a folder where you want to install rbSFML source files.

3.  Clone this repository with `git clone git@github.com:Groogy/rbSFML.git`.

4.  Download, compile and install SFML. (you can find how to do it [here](http://sfml-dev.org/tutorials/2.0/compile-with-cmake.php))

5.  Copy the `include` and `lib` folders from SFML to the rbSFML folder.

6.  Run one of the following commands in your terminal:

  * `rake` - Build all SFML as shared libraries.
  * `rake graphics` - Build only the graphics module (and its dependencies). You can use any other module (`audio`, `system` and `window`) with it.

7.  Run `sudo rake install`.

8.  You can now use rbSFML in any ruby application.

9.  You can run `rake test` to ensure everything is working and `rake doc` to build and open the documentation (at `doc/frames.html`).

10.  To run samples run `rake samples`. All samples are in `samples` folder.

Questions?
==========

[Open a issue](https://github.com/Groogy/rbSFML/issues/new).

Contact
=======

**Groogy:**

- E-mail: groogy@groogy.se
- Forum:  http://www.sfml-dev.org/forum/profile.php?mode=viewprofile&u=921
- Github: https://github.com/Groogy

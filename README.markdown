This is the Ruby bindings of the [SFML2 library](https://github.com/LaurentGomila/SFML) developed and maintained by Groogy, Trickster and LBg. 

I hope you enjoy using rbSFML. If you make anything in it then we are very interested in hearing about it.  
We can always be reached at http://www.sfml-dev.org/forum for support, ideas or just have a nice chat.

Dependencies
============

Of course this means this library depends on SFML2 so you'll have to install SFML2 on your development machine in order to compile rbSFML. rbSFML comes with a cloned module from the SFML Github repository that rbSFML is known to compile against but you can try and use the latest version of SFML as long as SFML has not come with anything API breaking. If that is the case then you don't even need to recompile rbSFML but only replace the SFML shared libraries.

Recommended is this setup: (lowers or highers versions might work too)

- [SFML2 - commit 01254d4122](https://github.com/LaurentGomila/SFML/tree/01254d41228d1fa6a186ca94c387da4984a0576c)
- [Ruby 1.9.3p0](http://www.ruby-lang.org/en/downloads/)
- [Rake 0.9.2](https://rubygems.org/gems/rake)
- [Yard 0.7.2](https://rubygems.org/gems/yard)

Installation (on Windows)
=========================

1.  Clone this repository with `git clone git@github.com:Groogy/rbSFML.git`.

2.  Download and compile SFML2. (you can find how to do it [here](http://sfml-dev.org/tutorials/2.0/compile-with-cmake.php))

3.  Copy the `include` folder from SFML and the `lib` folder (there should be `.a` files) to the rbSFML folder. Move the `.dll` files from `lib` to your `ruby\bin` directory.

4.  Run one of the following commands in your terminal:

  * `rake` - Build all SFML as shared libraries (need DLLs) - recommended.
  * `rake static` - Build all SFML as static libraries (don't need DLLs).
  * `rake graphics` - Build only the graphics module (and its dependencies). You can use any other module (`audio`, `system` and `window`) with it. You can also add `static`.

5.  Run `rake install`. (Needs administrative permission to access ruby installation directory)

6.  You can now use rbSFML in any ruby application with `require "sfml/all"`. 

7.  You can run `rake test` to ensure everything is working and `rake doc` to build the documentation (at `doc/frames.html`).

Questions? [Open a issue](https://github.com/Groogy/rbSFML/issues/new).

Contact
=======

**Groogy:**

- E-mail: groogy@groogy.se
- Forum:  http://www.sfml-dev.org/forum/profile.php?mode=viewprofile&u=921
- Github: https://github.com/Groogy

**Trickster:**

- Forum:  http://www.sfml-dev.org/forum/profile.php?mode=viewprofile&u=869
- Github: https://github.com/TricksterGuy

**LBg:**

- E-mail: lb-guilherme@live.com
- Forum:  http://www.sfml-dev.org/forum/profile.php?mode=viewprofile&u=4527
- Github: https://github.com/LBg

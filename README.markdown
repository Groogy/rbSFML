This is the Ruby bindings of the [SFML2 library](https://github.com/LaurentGomila/SFML) developed and maintained by Groogy, Trickster and LBg. 

I hope you enjoy using rbSFML. If you make anything in it then we are very interested in hearing about it.  
We can always be reached at http://www.sfml-dev.org/forum for support, ideas or just have a nice chat.

Dependencies
============

Of course this means this library depends on SFML2 so you'll have to install SFML2 on your development machine in order to compile rbSFML. rbSFML comes with a cloned module from the SFML Github repository that rbSFML is known to compile against but you can try and use the latest version of SFML as long as SFML has not come with anything API breaking. If that is the case then you don't even need to recompile rbSFML but only replace the SFML shared libraries.

**For Windows users:** Currently you'll have to place SFML2 include headers and static library files in sub-folder of the rbSFML library in Windows for it to find them. Hopefully this will be fixed. Place the SFML include folder in a folder called "include" and the static libraries in a folder called "lib".

Recommended is this setup: (lowers versions might work too)

- [SFML2 - Latest revision](https://github.com/LaurentGomila/SFML)
- [Ruby-1.9.2p290](http://www.ruby-lang.org/en/downloads/)
- [Rake, version 0.9.2](https://rubygems.org/gems/rake)
- [Yard, version 0.7.2](https://rubygems.org/gems/yard)

Instalation
===========

Open up your choice of command-line terminal. Navigate to the folder where you have placed the rbSFML source. From here you can run different commands depending on what you want to do. 

- `rake`

  This command just simply builds all the different modules.

- `rake -T`

  Show all available commands.

- `rake install`

  This command will build the modules and copy them to your ruby folder.  
  **For Windows users:** If you got Vista or higher this operation might fail depending on your settings for adminstrators and where you actually placed your ruby installation. The path to place it manually is: `<pathto>\ruby192\lib\ruby\site_ruby\1.9.1\i386-msvcrt\sfml\` The last folder "sfml" is probably one you'll have to create manually.

- `rake doc`

  Builds the documentation of the library (requires yard).

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

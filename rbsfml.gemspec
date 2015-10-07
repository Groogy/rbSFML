Gem::Specification.new do |s|
  s.name    = "rbSFML"
  s.version = "0.1.0"
  s.summary = "SFML for Ruby"
  s.author  = "Henrik Valter Vogelius Hansson"

  s.files = Dir.glob("ext/**/*.{cpp,rb}") +
            Dir.glob("lib/**/*.rb")

  s.extensions << "ext/rbsfml/extconf.rb"

  s.add_development_dependency "rake-compiler"
end
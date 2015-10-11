require 'rake/extensiontask'
spec = Gem::Specification.load('rbsfml.gemspec')
Rake::ExtensionTask.new('rbsfml', spec)

task :test => [:compile] do
	sh "rspec spec"
end
require 'mkmf'

have_library('pthread')
have_library('objc') if RUBY_PLATFORM =~ /darwin/
$CPPFLAGS += " -Wall" unless $CPPFLAGS.split.include? "-Wall"
$CPPFLAGS += " -g" unless $CPPFLAGS.split.include? "-g"
$CPPFLAGS += " -rdynamic" unless $CPPFLAGS.split.include? "-rdynamic"
$CPPFLAGS += " -fPIC" unless $CPPFLAGS.split.include? "-rdynamic" or RUBY_PLATFORM =~ /darwin/

CONFIG['LDSHARED'] = '$(CXX) -shared' unless RUBY_PLATFORM =~ /darwin/
if CONFIG['warnflags']
  CONFIG['warnflags'].gsub!('-Wdeclaration-after-statement', '')
  CONFIG['warnflags'].gsub!('-Wimplicit-function-declaration', '')
end
if enable_config('debug')
  $CFLAGS += " -O0 -ggdb3"
end

LIBV8_COMPATIBILITY = '~> 3.16.14'

begin
  require 'rubygems'
  gem 'libv8', LIBV8_COMPATIBILITY
rescue Gem::LoadError
  warn "Warning! Unable to load libv8 #{LIBV8_COMPATIBILITY}."
rescue LoadError
  warn "Warning! Could not load rubygems. Please make sure you have libv8 #{LIBV8_COMPATIBILITY} installed."
ensure
  warn 'warn warn warn warn warn warn warn warn'
  warn ENV['GEM_HOME']
  require '/usr/local/lib/ruby/gems/2.3.0/gems/libv8-3.16.14.15-x86_64-darwin-14/lib/libv8'
end

warn Libv8::VERSION
Libv8.configure_makefile

create_makefile('v8/init')

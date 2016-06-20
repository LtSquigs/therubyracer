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

require '/opt/rubies/2.3.0/lib/ruby/gems/2.3.0/gems/libv8-3.16.14.15-x86_64-linux/lib/libv8'

warn Libv8::VERSION

Libv8.configure_makefile

create_makefile('v8/init')
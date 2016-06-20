pid = Process.spawn('/opt/rubies/2.3.0/bin/ruby libv8conf.rb', { unsetenv_others: true })
Process.wait pid

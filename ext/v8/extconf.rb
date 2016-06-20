pid = Process.spawn('ruby libv8conf.rb', { unsetenv_others: true })
Process.wait pid

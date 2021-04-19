make:
	ulimit -v unlimited
	gcc -o turboguacamole.run benchmark.c 

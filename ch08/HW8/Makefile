all: nice_testing

nice_testing: nice_testing.c
	gcc nice_testing.c -o nice_testing
	setcap CAP_SYS_NICE+ep nice_pro

clean: nice_testing
	rm nice_testing

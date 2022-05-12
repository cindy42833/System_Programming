all: mylogin

mylogin: mylogin.c
	gcc mylogin.c -o mylogin
	sudo chown root:root mylogin
	sudo chmod +s mylogin

clean: mylogin
	rm mylogin
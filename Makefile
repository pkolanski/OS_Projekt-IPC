receive:receive.c
	gcc receive.c -o receive
send:send.c
	gcc send.c -o send
clean:
	rm send receive

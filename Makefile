CC=gcc
WINC=x86_64-w64-mingw32-gcc
SRC=src/linux/main
WSRC=src/windows/main
DEPS=src/linux/headers
WDEPS=src/windows/headers
TARGETS=targets
SRS=$(SRC)/airfryer.c $(SRC)/fencrypt.c $(SRC)/fdecrypt.c $(SRC)/iterated.c
WSRS=$(WSRC)/airfryer.c $(WSRC)/fencrypt.c $(WSRC)/fdecrypt.c $(WSRC)/iterated.c

airfryer: $(SRC) $(TARGETS)
	$(CC) -o $@ $(SRS) -I $(DEPS)
win: $(WSRS) $(TARGETS)
	$(WINC) -o airfryer.exe $(WSRS) -I $(WDEPS)
$(TARGETS):
	if ! [ -d $(TARGETS) ]; then 		\
		mkdir $(TARGETS);		\
	fi
	- cp * -r $(TARGETS)
clean:
	rm -f airfryer
	rm -f *.exe
	rm -rf $(TARGETS)

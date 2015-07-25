
CFLAGS  = -Wall

LDFLAGS = `pkg-config --cflags --libs gtk+-3.0` -lm

PATH_TO_SRC = ./Sources/Ghodbcalc.c

PATH_TO_BIN = ./Sources/Ghobdcalc

PATH_TO_ICON = ./Sources/Ghobdcalc_icon.png


PATH_TO_DESKTOP = ./Sources/Ghobdcalc.desktop

PATH_TO_README = ./Sources/README


BIN = Ghobdcalc

all : $(PATH_TO_SRC)
	$(CC) $(CFLAGS) $(PATH_TO_SRC) $(LDFLAGS) -o $(BIN)

install :
	@if `test ! -d /usr/share/Ghobdcalc` ; then \
	mkdir /usr/share/Ghobdcalc ;  \
	mkdir /usr/share/Ghobdcalc/Icon ; \
	mkdir /usr/share/Ghobdcalc/README ; \
	cp $(PATH_TO_README)/* /usr/share/Ghobdcalc/README ; \
	cp $(PATH_TO_ICON) /usr/share/Ghobdcalc/Icon ; fi   

	@if `test ! -f /usr/bin/Ghobdcalc` ; then     \
		install -m 0755 $(BIN) /usr/bin ; fi

	@if `test -d /usr/share/applications` && ! `test -f /usr/share/applications/Ghobdcalc.desktop` ; then \
	cp $(PATH_TO_DESKTOP) /usr/share/applications/ ; fi
	@echo Ghobdcalc installation successfull...
	@echo Enjoy to use Ghobdcalc !!!

uninstall :
	rm /usr/bin/Ghobdcalc
	rm -R /usr/share/Ghobdcalc
	@if `test -d /usr/share/applications` && `test -f /usr/share/applications/Ghobdcalc.desktop` ; then \
	rm /usr/share/applications/Ghobdcalc.desktop ; fi

clean :
	rm Ghobdcalc

SOURCE_FILES= $(wildcard *.c)
OBJ_FILES= $(patsubst %.c,%.o,$(SOURCE_FILES))
CFLAGS= -Wall -g -pg

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man/man1

all: test kroman clean

test: $(SOURCE_FILES)
	clang -o kroman_test $^ $(CFLAGS)
	./kroman_test

kroman: $(SOURCE_FILES)
	@echo start compiling kroman
	clang -o $@ $^ $(CFLAGS)
	@echo finish compiling kroman

clean:
	rm -f *.o kroman kroman_test

install: kroman
	@echo "Installing program to $(DESTDIR)$(BINDIR) ..."
	@mkdir -p $(DESTDIR)$(BINDIR)
	@install -pm0755 kroman $(DESTDIR)$(BINDIR)/$(TARGET) || \
	echo "Failed. Try "make PREFIX=~ install" ?"
	@echo "Installing manpage to $(DESTDIR)$(MANDIR) ..."
	@mkdir -p $(DESTDIR)$(MANDIR)
	@install -pm0644 kroman.1 $(DESTDIR)$(MANDIR)/ || \
	echo "Failed. Try "make PREFIX=~ install" ?"

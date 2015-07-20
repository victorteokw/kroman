SOURCE_FILES= $(wildcard *.c)
OBJ_FILES= $(patsubst %.c,%.o,$(SOURCE_FILES))
CFLAGS= -Wall -g -pg

all: test kroman clean

test: $(SOURCE_FILES)
	@echo start testing
	clang -o kroman_test $^ $(CFLAGS)
	./kroman_test
	@echo end testing

kroman: $(SOURCE_FILES)
	@echo start compiling kroman
	clang -o $@ $^ $(CFLAGS)
	@echo end compiling kroman

clean:
	@echo Does nothing for clean


 
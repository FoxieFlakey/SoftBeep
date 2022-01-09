SRC_DIR=./src/
OUTPUT=main
##################################
##     Compiler and linker      ##
##################################

SANITIZER_FLAG=
#-fsanitize-address-use-after-scope -fsanitize=address -fsanitize=undefined  
CFLAGS=-g -I./include -O0 -fPIE -fPIC -xc -nostdlib++ -fblocks $(SANITIZER_FLAG) -I$(SRC_DIR) -I/usr/include/SDL2/ -O0
LFLAGS=-g -fPIE -fPIC -rdynamic -lBlocksRuntime $(SANITIZER_FLAG) -L./libs -lSDL2 -lpthread -lm
#-static-libsan

C_COMPILER=clang
LINKER=clang

##################################
SRCS=$(shell find $(SRC_DIR) -regex .+[.]c)
OBJS=$(SRCS:.c=.o)

.PHONY: all 
all: $(OBJS) 
	$(MAKE) link

$(OBJS): %.o: %.c
	$(C_COMPILER) $(CFLAGS) -c -o $@ $<

link:
	$(LINKER) $(OBJS) $(LFLAGS) -o $(OUTPUT)  

clean:
	rm $(OBJS) $(OUTPUT) 








testName=sha256

# Remove temp cil files from c_files folder
$(shell if test -d "./c_files"; then rm -f ./c_files/*; else mkdir c_files; fi)

CILPATH=../../../
REMOTE_HOST=localhost
CFLAGS += -DREMOTE_HOST=$(REMOTE_HOST) -O0 -g

all: ./a.out

$(testName).o: $(testName).c
	$(CC) -Wall $(CFLAGS) -include obliv_bits.h -I ../../../src/ext/oblivc -I. -c sha256.c
./a.out: $(testName).oc $(testName).o $(CILPATH)/_build/libobliv.a
	$(CILPATH)/bin/oblivcc $(CFLAGS) -I . $(testName).oc $(testName).o -lcrypto

clean:
	@rm -f a.out c_files/cil* *.o
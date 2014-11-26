CC	:= gcc
CFLAGS	:= -std=c99 -D_GNU_SOURCE=1 -Wall -Werror -fPIC -g
SECCOMP	:= /home/nickolai/refsrc/libseccomp
PROGS	:= plain-32-0 plain-32-1 plain-32-2 plain-32-3 \
	   plain newuid newuid-chroot seccomp shellcode.bin \
	   bloat

all:	$(PROGS) .gitignore

%.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS) $(TGTCFLAGS)

%-32-nossp.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS) $(TGTCFLAGS) -m32 -fno-stack-protector

%-32-ssp.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS) $(TGTCFLAGS) -m32

plain newuid newuid-chroot: %: %.o net.o req.o
	$(CC) $^ -o $@

plain-32-0: plain-32-nossp.o net-32-nossp.o req-32-nossp.o
	$(CC) $^ -o $@ -m32
	execstack -s $@

plain-32-1: plain-32-nossp.o net-32-nossp.o req-32-nossp.o
	$(CC) $^ -o $@ -m32

plain-32-2: plain-32-ssp.o net-32-ssp.o req-32-ssp.o
	$(CC) $^ -o $@ -m32

plain-32-3: plain-32-ssp.o net-32-ssp.o req-32-ssp.o
	$(CC) $^ -o $@ -m32 -pie

seccomp.o: TGTCFLAGS:=-I$(SECCOMP)/include
seccomp: seccomp.o net.o req.o
	$(CC) $^ -o $@ $(LDFLAGS) -L$(SECCOMP)/src -lseccomp

shellcode.o: shellcode.S
	$(CC) $< -c -o $@ -m32

shellcode.bin: shellcode.o
	objcopy -S -O binary -j .text $< $@

.PHONY: .gitignore
.gitignore:
	( cat $@ ; for A in $(PROGS); do echo /$$A; done ) | sort | uniq > $@~
	mv $@~ $@

.PHONY: clean
clean:
	rm -f *.o $(PROGS)


OUT=test args cat id ls swapd rm cp sleep mkdir pwd kill mv stat \
	dumpsect fstab rmdir touch strings xargs echo du \
	tput basename uname fmt purge printf ps rcsdo changed \
	which true false whoami egrep fgrep awk cc [ view ascii \
	dirname

OBJS= args.o basename.o cat.o changed.o chmod.o cp.o du.o dumpsect.o \
	echo.o fmt.o fstab.o id.o kill.o ls.o mkdir.o \
	mv.o printf.o ps.o purge.o pwd.o rcsdo.o rm.o rmdir.o \
	sleep.o stat.o strings.o swapd.o test.o touch.o tput.o \
	uname.o wc.o which.o xargs.o dump.o operators.o true.o \
	false.o whoami.o egrep.o fgrep.o awk.o cc.o [.o view.o \
	ascii.o dirname.o

include ../../makefile.all

SHPROGS=hostname man more mt reboot shutdown stty

rcsdo: rcsdo.o
	$(LD) $(LDFLAGS) -o rcsdo $(CRT0) rcsdo.o -lc

changed: changed.o
	$(LD) $(LDFLAGS) -o changed $(CRT0) changed.o -lc

uname: uname.o
	$(LD) $(LDFLAGS) -o uname $(CRT0) uname.o -lc

basename: basename.o
	$(LD) $(LDFLAGS) -o basename $(CRT0) basename.o -lc

tput: tput.o
	$(LD) $(LDFLAGS) -o tput $(CRT0) tput.o -ltermcap -lc

touch: touch.o
	$(LD) $(LDFLAGS) -o touch $(CRT0) touch.o -lc

rmdir: rmdir.o
	$(LD) $(LDFLAGS) -o rmdir $(CRT0) rmdir.o -lc

fstab: fstab.o
	$(LD) $(LDFLAGS) -o fstab $(CRT0) fstab.o -lc

stat: stat.o
	$(LD) $(LDFLAGS) -o stat $(CRT0) stat.o -lc

dump.o: ../testsh/dump.c
	$(CC) $(CFLAGS) -c ../testsh/dump.c

dumpsect: dumpsect.o dump.o
	$(LD) $(LDFLAGS) -o dumpsect $(CRT0) dumpsect.o dump.o -lc

mv: mv.o
	$(LD) $(LDFLAGS) -o mv $(CRT0) mv.o -lc

pwd: pwd.o
	$(LD) $(LDFLAGS) -o pwd $(CRT0) pwd.o -lc

kill: kill.o
	$(LD) $(LDFLAGS) -o kill $(CRT0) kill.o -lc

mkdir: mkdir.o
	$(LD) $(LDFLAGS) -o mkdir $(CRT0) mkdir.o -lc

sleep: sleep.o
	$(LD) $(LDFLAGS) -o sleep $(CRT0) sleep.o -lc

cp: cp.o
	$(LD) $(LDFLAGS) -o cp $(CRT0) cp.o -lc

rm: rm.o
	$(LD) $(LDFLAGS) -o rm $(CRT0) rm.o -lc

swapd: swapd.o
	$(LD) $(LDFLAGS) -o swapd $(CRT0) swapd.o -lc

ls: ls.o
	$(LD) $(LDFLAGS) -o ls $(CRT0) ls.o -lusr -lc

id: id.o
	$(LD) $(LDFLAGS) -o id $(CRT0) id.o -lusr -lc

cat: cat.o
	$(LD) $(LDFLAGS) -o cat $(CRT0) cat.o -lc

test: test.o operators.o
	$(LD) $(LDFLAGS) -o test $(CRT0) test.o operators.o -lc

args: args.o
	$(LD) $(LDFLAGS) -o args $(CRT0) args.o -lc

echo: echo.o
	$(LD) $(LDFLAGS) -o echo $(CRT0) echo.o -lc

xargs: xargs.o
	$(LD) $(LDFLAGS) -o xargs $(CRT0) xargs.o -lc

strings: strings.o
	$(LD) $(LDFLAGS) -o strings $(CRT0) strings.o -lc

du: du.o
	$(LD) $(LDFLAGS) -o du $(CRT0) du.o -lc

chmod: chmod.o
	$(LD) $(LDFLAGS) -o chmod $(CRT0) chmod.o -lc

fmt: fmt.o
	$(LD) $(LDFLAGS) -o fmt $(CRT0) fmt.o -lc

purge: purge.o
	$(LD) $(LDFLAGS) -o purge $(CRT0) purge.o -lc

wc: wc.o
	$(LD) $(LDFLAGS) -o wc $(CRT0) wc.o -lc

printf: printf.o
	$(LD) $(LDFLAGS) -o printf $(CRT0) printf.o -lc

ps: ps.o
	$(LD) $(LDFLAGS) -o ps $(CRT0) ps.o -lusr -lc

which: which.o
	$(LD) $(LDFLAGS) -o which $(CRT0) which.o -lc

true: true.o
	$(LD) $(LDFLAGS) -o true $(CRT0) true.o -lc

false: false.o
	$(LD) $(LDFLAGS) -o false $(CRT0) false.o -lc

whoami: whoami.o
	$(LD) $(LDFLAGS) -o whoami $(CRT0) whoami.o -lc

cc: cc.o
	$(LD) $(LDFLAGS) -o cc $(CRT0) cc.o -lc

egrep: egrep.o
	$(LD) $(LDFLAGS) -o egrep $(CRT0) egrep.o -lc

fgrep: fgrep.o
	$(LD) $(LDFLAGS) -o fgrep $(CRT0) fgrep.o -lc

awk: awk.o
	$(LD) $(LDFLAGS) -o awk $(CRT0) awk.o -lc

[: [.o
	$(LD) $(LDFLAGS) -o [ $(CRT0) [.o -lc

view: view.o
	$(LD) $(LDFLAGS) -o view $(CRT0) view.o -lc

ascii: ascii.o
	$(LD) $(LDFLAGS) -o ascii $(CRT0) ascii.o -lc

dirname: dirname.o
	$(LD) $(LDFLAGS) -o dirname $(CRT0) dirname.o -lc

install: all
	strip $(OUT)
	cp $(OUT) $(ROOT)/bin
	for x in $(SHPROGS) ; do cp $$x.sh $(ROOT)/bin/$$x ; done

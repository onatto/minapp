########################################################################################
OPT=-O2
FLAGS=-I3rdparty -Wno-incompatible-pointer-types -fno-stack-protector -fno-exceptions
LIBS=-lcimgui
########################################################################################
LNXFLAGS=$(OPT) $(FLAGS) -DWIN_=0 -DLNX_=1 -fvisibility=hidden -g
LNXLIBDIRS=-Lextlibs/lnx -Lruntime/lnx/
LNXSTRIP=strip
LNXOUT=runtime/lnx
LNXEXT=extlibs/lnx
LNXOBJ=$(LNXEXT)/amalgam.o
LNXLIBS=$(LNXOBJ) -ldl -lm -lpthread -lX11 -lGL  
LNXCC=gcc $(LNXFLAGS) $(LNXLIBDIRS)
########################################################################################
WINFLAGS=$(OPT) $(FLAGS) -DLNX_=0 -DWIN_=1
WINLIBDIRS=-Lextlibs/mingw -Lruntime/win/
WINSTRIP=x86_64-w64-mingw32-strip
WINOUT=runtime/win
WINEXT=extlibs/mingw
WINOBJ=$(WINEXT)/amalgam.o
WINLIBS=$(WINOBJ) -lgdi32
WINCC=x86_64-w64-mingw32-gcc $(WINFLAGS) $(WINLIBDIRS)
########################################################################################

src/app.c:
	$(LNXCC) $*.c $(LIBS) $(LNXLIBS) -o runtime/lnx/app
	$(WINCC) $*.c $(LIBS) $(WINLIBS) -o runtime/win/app.exe

3rdparty/amalgam.c:
	$(LNXCC) -c $*.c $(LNXLIBS) $(LIBS) -o $(LNXEXT)/amalgam.o
	$(WINCC) -c $*.c $(WINLIBS) $(LIBS) -o $(WINEXT)/amalgam.o

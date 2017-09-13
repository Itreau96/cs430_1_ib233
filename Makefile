# Simple makefile

# Set compiler and linking variables
CPP = cl
CFLAGS = /nologo /W4 /EHsc /Za

# High level build
build: ppmrw

# Create ppmrw.exe
ppmrw: ppmrw.obj reader.obj writer.obj
	$(CPP) $(CFLAGS) /Fe$@ $**

# Create obj files
ppmrw.obj: main_program.c reader.obj writer.obj
	$(CPP) $(CFLAGS) /Fo$@ $**
reader.obj: reader.c
	$(CPP) $(CFLAGS) /Fo$@ $**
writer.obj: writer.c
	$(CPP) $(CFLAGS) /Fo$@ $**

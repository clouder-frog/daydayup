
=================================================================================
#foo = abcd		// echo Huh
foo = $(bar)
#foo = abcd		// echo abcd 这里是最后一次赋值
bar = $(ugh)
ugh = Huh
all:
	echo $(foo)
#################################################################################
# 注意变量赋值时顺序
#################################################################################

=================================================================================
a = $(b)
b = $(a)

all:
	echo $(a)
#################################################################################	
# Makefile:2: *** Recursive variable `a' references itself (eventually).  Stop.
#################################################################################

=================================================================================
b = world			b := world				b = world
a := $(b)			a := $(b)				a = $(b)
b = hello			b := hello				b = hello

all:				all:					all:
	@echo $(b)			@echo $(b)				@echo $(b)
	@echo $(a)			@echo $(a)				@echo $(a)
#################################################################################
#hello				hello					hello
#world				world					hello
#################################################################################


=================================================================================
current_addr := $(shell pwd)
a = `pwd`

all:
	@echo $(current_addr)
	@echo $(a)
#################################################################################
#/mnt/hgfs/linux2win/tmpTest
#/home/aston/linux2win/tmpTest
#################################################################################

=================================================================================
dir := /foo/bar		#just test			dir := /foo/bar
mydir := $(dir)/file					mydir := $(dir)/file

all:									all:
	@echo $(mydir)							@echo $(mydir)
#################################################################################
#/foo/bar  /file						/foo/bar/file
#################################################################################
#################################################################################
#################################################################################
#################################################################################
#################################################################################
#################################################################################


=================================================================================







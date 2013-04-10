.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################
# Project Name (generate executable with this name)
TARGET = cs296_base

# Project Paths
PROJECT_ROOT := ${CURDIR}
#PROJECT_ROOT=/home/nilesh/dev/RubeGoldberg/cs296_base_code
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/obj
BINDIR = $(PROJECT_ROOT)/bin
DOCDIR = $(PROJECT_ROOT)/doc
RESOURCESDIR = $(PROJECT_ROOT)/resources

INSTALL_PATH=/home/nilesh/Desktop
# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL 

# Compiler and Linker flags
CPPFLAGS =-g  -std=c++0x -pthread -O2 -O3
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include 			
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib 

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


.PHONY: all setup doc clean distclean dist install 

all: setup $(BINDIR)/$(TARGET)

setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p obj
	@mkdir -p bin

$(BINDIR)/$(TARGET):  $(PROJECT_ROOT)/external/lib/libBox2D.a $(OBJS) 
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include $(OBJS:.o=.d)


$(PROJECT_ROOT)/external/lib/libBox2D.a:
	@rm -rf $(EXTERNAL_ROOT)/src/Box2D
	@rm -rf $(EXTERNAL_ROOT)/src/include/*
	@rm -rf $(EXTERNAL_ROOT)/src/lib/*
	@tar -xzf $(EXTERNAL_ROOT)/src/Box2D.tgz -C $(EXTERNAL_ROOT)/src
	@mkdir $(EXTERNAL_ROOT)/src/Box2D/build296
	@cd $(EXTERNAL_ROOT)/src/Box2D/build296;cmake -DCMAKE_BUILD_TYPE=Debug ../ 
	@make -C $(EXTERNAL_ROOT)/src/Box2D/build296
	@make -C $(EXTERNAL_ROOT)/src/Box2D/build296 install


$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"

pythonPlots:
		@cp src/main_non_gui.cpp.bak src/main.cpp
		@make
		@mkdir -p data
		@mkdir -p plots
		@python3 scripts/g28_gen_csv.py
		@python3 scripts/g28_gen_plots.py
		@python3 scripts/convertImages.py
		@cp src/main_gui.cpp.bak src/main.cpp

report: 
	@echo "Generating report"
	@make -C $(DOCDIR)	
	@python3 scripts/g28_gen_html.py
	
#source files Box2d tar, src , documentation,Makefile, scripts
dist:distclean 
	@$(RM) -rf external/include external/lib external/src/Box2D	
	@sh scripts/tarProject.sh

install:distclean doc 
	@make
	@cp -r $(BINDIR) $(INSTALL_PATH)
	@cp -r scripts $(INSTALL_PATH)
	@cp -r $(DOCDIR) $(INSTALL_PATH)
	@cp -r $(RESOURCESDIR) $(INSTALL_PATH)
		
clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~ $(BINDIR)
	@$(RM) -rf data plots
	@$(ECHO) "Done"

distclean: clean
	@$(RM) -rf $(BINDIR) $(DOCDIR)/html
	@$(RM) -rf external/include external/lib external/src/Box2D	


#first change the main.cpp to the one to be used to generate plots	
plot01: setup
	@cp src/main_non_gui.cpp.bak src/main.cpp
	@rm -rf plots
	@mkdir plots
	@make
	@rm -rf data/temp.csv
	@chmod 755 scripts/*.sh
	@./scripts/gen_data.sh
	@./scripts/gen_csv.sh
	@./scripts/temp.sh
	@gnuplot> load 'scripts/g28_plot01.gpt'
	@gnuplot> load 'scripts/g28_plot02.gpt'
	@gnuplot> load 'scripts/g28_plot03.gpt'
	@gnuplot> load 'scripts/g28_plot04.gpt'
	@gnuplot> load 'scripts/g28_plot05.gpt'
	@gnuplot> load 'scripts/g28_plot06.gpt'
	@rm -rf *.dat data/lab05_g28_data_temp.csv load 
	@cp src/main_gui.cpp.bak src/main.cpp
plot02: setup
	@cp src/main_non_gui.cpp.bak src/main.cpp
	@rm -rf data/temp.csv
	@make
	@chmod 755 scripts/*.sh
	@mkdir plots
	@make
	@./scripts/gen_data_csv.sh
	@./scripts/temp.sh
	@gnuplot> load 'scripts/g28_plot01.gpt'
	@gnuplot> load 'scripts/g28_plot02.gpt'
	@gnuplot> load 'scripts/g28_plot03.gpt'
	@gnuplot> load 'scripts/g28_plot04.gpt'
	@gnuplot> load 'scripts/g28_plot05.gpt'
	@gnuplot> load 'scripts/g28_plot06.gpt'
	@rm -rf *.dat data/lab05_g28_data_temp.csv load
	@cp src/main_gui.cpp.bak src/main.cpp

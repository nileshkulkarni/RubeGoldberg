
SHELL   = bash
CC      = g++
LD      = ld
RM      = rm
MV      = mv
ECHO    = /bin/echo
CAT     = cat
PRINTF  = printf
SED     = sed
DOXYGEN = doxygen
LATEX   = latex
BIBTEX  = bibtex
PDFLATEX = pdflatex
all:report

report:
	@$(ECHO) -n "Generating Report ...  "
	@$(LATEX) report.tex
	@dvipdf report.dvi
	@rm report.dvi
	@$(ECHO) "Done"



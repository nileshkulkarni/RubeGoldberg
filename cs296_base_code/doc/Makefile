
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
	@$(LATEX) report_project_g28.tex
	@$(LATEX) report_project_g28.tex
	@dvipdf report_project_g28.dvi
	@rm report_project_g28.dvi
	@$(ECHO) "Done"



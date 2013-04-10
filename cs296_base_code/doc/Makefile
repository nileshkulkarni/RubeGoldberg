
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
	@cd ../; python3 scripts/convertImages.py
	@$(LATEX) report_project_g28.tex
	@$(BIBTEX) report_project_g28.aux
	@$(LATEX) report_project_g28.tex
	@dvipdf report_project_g28.dvi
	@rm report_project_g28.dvi
	@cd ../; python3 scripts/deleteImages.py
	@$(ECHO) "Done"



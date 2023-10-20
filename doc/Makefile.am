EXTRA_DIST = ref.tex gaa.html/index.html gaa.ps gaa.tex img1.png tut.tex gaa.css
dist_gaadoc_DATA = gaa.html/index.html gaa.ps img1.png gaa.css

TEX_OBJECTS = ref.tex gaa.tex tut.tex

$(TEX_OBJECTS):
	if test ! -e $@ && test -e $(srcdir)/$@; then \
	  cp $(srcdir)/$@ .; \
	elif test ! -e $@ && test -e $(builddir)/$@; then \
	  cp $(builddir)/$@ .; \
	elif ! -e $@ && test -d ../.git && test -x "`which git`"; then \
	  if test -n "`git status -s $@ | grep D`"; then \
	    echo "$@ appears to have been deleted; attempting to restore it..."; \
	    git restore $@; \
	  else \
	    echo "something weird appears to have happened with $@"; \
	    touch $@; \
	  fi; \
	else \
	  touch $@; \
	fi

gaa.dvi: $(TEX_OBJECTS)
	for neededfile in $(TEX_OBJECTS); do \
	  if test ! -e $${neededfile}; then \
	    $(MAKE) $${neededfile}; \
	  fi; \
	  if test ! -e $${neededfile} && test -e $(srcdir)/$${neededfile}; then \
	    cp $(srcdir)/$${neededfile} .; \
	  elif test ! -e $${neededfile} && test -e $(builddir)/$${neededfile}; then \
	    cp $(builddir)/$${neededfile} .; \
	  elif test ! -e $${neededfile}; then \
	    touch $${neededfile}; \
	  fi; \
	done; \
	if test -x "$(LATEX_BIN)"; then \
	  $(LATEX_BIN) gaa.tex && $(LATEX_BIN) gaa.tex; \
	elif test -x "`which latex`"; then \
	  latex gaa.tex && latex gaa.tex; \
	elif test -x "$(LATEX)"; then \
	  $(LATEX) gaa.tex && $(LATEX) gaa.tex; \
	elif test -x "$(TEXI2DVI_BIN)" && test -e gaa.texi && test -e $(srcdir)/version.texi; then \
	  $(TEXI2DVI_BIN) gaa.texi; \
	elif test -x "$(TEXI2DVI)" && test -e gaa.texi && test -e $(srcdir)/version.texi; then \
	  $(TEXI2DVI) gaa.texi; \
	elif test -x "`which texi2dvi`" && test -e gaa.texi && test -e $(srcdir)/version.texi; then \
	  texi2dvi gaa.texi; \
	else \
	  touch gaa.dvi; \
	fi

gaa.ps: gaa.dvi
	if test -x "$(DVIPS_BIN)"; then \
	  $(DVIPS_BIN) gaa.dvi -o gaa.ps; \
	elif test -x "$(DVIPS)"; then \
	  $(DVIPS) gaa.dvi -o gaa.ps; \
	elif test -x "`which dvips`"; then \
	  dvips gaa.dvi -o gaa.ps; \
	else \
	  touch gaa.ps; \
	fi

gaa.tex.html: $(TEX_OBJECTS)
	-if test -x "$(LATEX2HTML_BIN)"; then \
	  $(LATEX2HTML_BIN) gaa.tex -no_navigation -no_subdir 1 -split 0 -local_icons -html_version 3.2,math -info "" -white; \
	elif test -x "$(LATEX2HTML)"; then \
	  $(LATEX2HTML) gaa.tex -no_navigation -no_subdir 1 -split 0 -local_icons -html_version 3.2,math -info "" -white; \
	elif test -x "`which latex2html`"; then \
	  latex2html gaa.tex -no_navigation -no_subdir 1 -split 0 -local_icons -html_version 3.2,math -info "" -white; \
	else \
	  touch gaa.tex.html; \
	fi

info_TEXINFOS = gaa.texi

distclean-local:
	if test "x$(srcdir)" != "x$(builddir)"; then \
	  for junkfile in tut.tex gaa.aux gaa.log ref.tex gaa.toc gaa.tex; do \
	    if test -e $(builddir)/$${junkfile}; then \
	      if test -e $(srcdir)/$${junkfile} -a -w $(builddir); then \
	        rm -fv $(builddir)/$${junkfile}; \
	      elif test -w $(srcdir) -a ! -e $(srcdir)/$${junkfile}; then \
	         mv -v $(builddir)/$${junkfile} $(srcdir)/$${junkfile}; \
	      elif test -r $(builddir)/$${junkfile} -a -w $(builddir); then \
	        rm -fv $(builddir)/$${junkfile}; \
	      fi; \
	    fi; \
	  done; \
	fi

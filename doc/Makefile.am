EXTRA_DIST = ref.tex gaa.html/index.html gaa.ps gaa.tex img1.png tut.tex gaa.css
dist_gaadoc_DATA = gaa.html/index.html gaa.ps img1.png gaa.css gaa.dvi

TEX_OBJECTS = ref.tex gaa.tex tut.tex

$(TEX_OBJECTS):
	if test ! -e $@ && test -e $(srcdir)/$@; then \
	  cp $(srcdir)/$@ .; \
	elif test ! -e $@ && test -e $(builddir)/$@; then \
	  cp $(builddir)/$@ .; \
	elif test ! -e $@ && test -d ../.git && test -x "`which git`"; then \
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

gaa.html/index.html:
	if test ! -e $@ && test -d ../.git && test -x "`which git`"; then \
	  echo "gaa.html/index.html might be missing; checking with git..."; \
	  if test -n "`git status -s gaa.html/index.html 2>/dev/null | grep D`"; then \
	    echo "gaa.html/index.html appears to have been deleted; attempting to restore it..."; \
	    git restore gaa.html/index.html; \
	  elif test -d gaa.html -a -r gaa.html -a -w gaa.html; then \
	    stat gaa.html && cp -v `file gaa.html/* | grep "HTML document"` $@; \
	  else \
	    touch $@; \
	  fi; \
	elif test ! -e $@ && test -e $(srcdir)/$@; then \
	  cp -v $(srcdir)/$@ $@; \
	elif test ! -e $@ && test -e $(builddir)/$@; then \
	  cp -v $(builddir)/$@ $@; \
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
	  echo "attempting rebuild of $@ with LATEX_BIN ($(LATEX_BIN))"; \
	  $(LATEX_BIN) gaa.tex && $(LATEX_BIN) gaa.tex; \
	elif test -x "`which latex`"; then \
	  echo "attempting rebuild of $@ with whichever latex is first in PATH"; \
	  latex gaa.tex && latex gaa.tex; \
	elif test -x "$(LATEX)"; then \
	  echo "attempting rebuild of $@ with LATEX ($(LATEX))"; \
	  $(LATEX) gaa.tex && $(LATEX) gaa.tex; \
	elif test -x "$(TEXI2DVI_BIN)" && test -e gaa.texi && test -e $(srcdir)/version.texi; then \
	  echo "attempting rebuild of $@ with $(TEXI2DVI_BIN)"; \
	  $(TEXI2DVI_BIN) gaa.texi; \
	elif test -x "$(TEXI2DVI)" && test -e gaa.texi && test -e $(srcdir)/version.texi; then \
	  echo "attempting rebuild of $@ with TEXI2DVI ($(TEXI2DVI))"; \
	  $(TEXI2DVI) gaa.texi; \
	elif test -x "`which texi2dvi`" && test -e gaa.texi && test -e $(srcdir)/version.texi; then \
	  echo "attempting rebuild of $@ with whichever texi2dvi is 1st in PATH"; \
	  texi2dvi gaa.texi; \
	else \
	  touch gaa.dvi; \
	fi

gaa.ps: gaa.dvi
	if test -x "$(DVIPS_BIN)"; then \
	  echo "attempting rebuild of $@ with DVIPS_BIN ($(DVIPS_BIN))"; \
	  $(DVIPS_BIN) gaa.dvi -o gaa.ps; \
	elif test -x "$(DVIPS)"; then \
	  echo "attempting rebuild of $@ with DVIPS ($(DVIPS))"; \
	  $(DVIPS) gaa.dvi -o gaa.ps; \
	elif test -x "`which dvips`"; then \
	  echo "attempting rebuild of $@ with whichever dvips is first in PATH"; \
	  dvips gaa.dvi -o gaa.ps; \
	else \
	  touch gaa.ps; \
	fi

gaa.tex.html: $(TEX_OBJECTS)
	-if test -x "$(LATEX2HTML_BIN)"; then \
	  echo "attempting rebuild of $@ with $(LATEX2HTML_BIN)"; \
	  $(LATEX2HTML_BIN) gaa.tex -no_navigation -no_subdir 1 -split 0 -local_icons -html_version 3.2,math -info "" -white; \
	elif test -x "$(LATEX2HTML)"; then \
	  echo "attempting rebuild of $@ with LATEX2HTML ($(LATEX2HTML))"; \
	  $(LATEX2HTML) gaa.tex -no_navigation -no_subdir 1 -split 0 -local_icons -html_version 3.2,math -info "" -white; \
	elif test -x "`which latex2html`"; then \
	  echo "attempting rebuild of $@ with whichever latex2html we can find"; \
	  latex2html gaa.tex -no_navigation -no_subdir 1 -split 0 -local_icons -html_version 3.2,math -info "" -white; \
	else \
	  touch gaa.tex.html; \
	fi

info_TEXINFOS =
dist_info_TEXINFOS =
if BUILD_DOCS
info_TEXINFOS += gaa.texi
EXTRA_DIST += $(info_TEXINFOS)
else
dist_info_TEXINFOS += gaa.texi
EXTRA_DIST += $(dist_info_TEXINFOS)
endif

EXTRA_DIST += gaa.dvi version.texi

diststuff: $(EXTRA_DIST)
	ls
.PHONY: diststuff

check-local:
	for myfile in $(EXTRA_DIST); do \
	  if test -e $${myfile}; then \
	    stat $${myfile}; \
	  elif test -e $(srcdir)/$${myfile}; then \
	    stat $(srcdir)/$${myfile}; \
	  elif test -e $(builddir)/$${myfile}; then \
	    stat $(builddir)/$${myfile}; \
	  else \
	    echo "missing file $${myfile}!" >&2; exit 1; \
	  fi; \
	done

clean-local:
	echo "CLEANFILES are: \"$(CLEANFILES)\""; \
	sleep 1; \
	if test -d ../.git && test -x "`which git`"; then \
	  for keepme in gaa.dvi gaa.html/index.html; do \
	    if test ! -e $${dontclean}; then \
	      if test -n "`git status -s $${keepme} 2>/dev/null | grep D`"; then \
	        echo "$${keepme} appears to have been deleted; attempting to restore it..."; \
	        git restore $${keepme}; \
	      else \
	        git status -s $${keepme} 2>/dev/null; \
	      fi; \
	    elif test ! -e $(srcdir)/$${dontclean}; then \
	      mv -v $${dontclean} $(srcdir); \
	    else \
	      stat $${dontclean}; \
	    fi; \
	  done; \
	else \
	  echo "FIXME: come up with another way besides git to restore things"; \
	fi

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
	fi; \
	if test ! -e gaa.html/index.html && test -d ../.git && test -x "`which git`"; then \
	  echo "gaa.html/index.html might be missing; checking with git..."; \
	  if test -n "`git status -s gaa.html/index.html 2>/dev/null | grep D`"; then \
	    echo "gaa.html/index.html appears to have been deleted; attempting to restore it..."; \
	    git restore gaa.html/index.html; \
	  elif test -d gaa.html -a -r gaa.html; then \
	    stat gaa.html && ls gaa.html/*; \
	  else \
	    ls; \
	  fi; \
	fi

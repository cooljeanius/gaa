EXTRA_DIST = sample.gaa smain.c sample3.gaa sample2.gaa smain2.c config sample4.gaa
gaasample_DATA = sample3.gaa sample.gaa smain.c sample2.gaa smain2.c config sample4.gaa

GAA_EXE = $(top_builddir)/source/gaa

check-local: $(GAA_EXE)
	for gaafile in sample.gaa sample2.gaa sample3.gaa sample4.gaa; do \
	  if test -x $(GAA_EXE) -a -r $${gaafile} -a -w .; then \
	    echo "skipping testing $(GAA_EXE) on $${gaafile} (FIXME)"; \
	  elif test -e $${gaafile}; then \
	    stat $${gaafile}; \
	  else \
	    echo "uh oh, what happened to $${gaafile}?!"; \
	  fi; \
	done

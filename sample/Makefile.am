EXTRA_DIST = sample.gaa smain.c sample3.gaa sample2.gaa smain2.c config sample4.gaa
gaasample_DATA = sample3.gaa sample.gaa smain.c sample2.gaa smain2.c config sample4.gaa

## FIXME: these should actually be programs, but that would require getting linking
## to work properly, which would require gaa to stop crashing, so...
check_LIBRARIES = libsmain.a libsmain2.a

libsmain_a_SOURCES = smain.c
libsmain2_a_SOURCES = smain2.c

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

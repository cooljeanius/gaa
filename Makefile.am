SUBDIRS = source doc sample
EXTRA_DIST = TODO

ACLOCAL_AMFLAGS = -I m4 --install

DISTCLEANFILES = *~ autoscan.log .DS_Store

distclean-local:
	-rm -rf autom4te.cache || rmdir autom4te.cache

diststuff: $(EXTRA_DIST)
	$(MAKE) -C doc diststuff
	ls
.PHONY: diststuff

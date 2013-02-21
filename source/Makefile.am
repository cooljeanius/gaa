SUBDIRS = skel 
EXTRA_DIST = gaa.gaa gaa.c gaaout.h gaa.h
bin_PROGRAMS = gaa
gaa_CFLAGS = -DSKEL_DIR=\"$(gaadatadir)\"
gaa_SOURCES = gaaout.c gaa_parser.y gaa_lex.l

AM_YFLAGS = -d

gaaout.c: gaa.gaa
	gaa gaa.gaa -o gaaout.c -i gaaout.h

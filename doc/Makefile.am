EXTRA_DIST = ref.tex gaa.html gaa.ps gaa.tex img1.png tut.tex gaa.css
gaadoc_DATA = gaa.html gaa.ps img1.png gaa.css

TEX_OBJECTS = ref.tex gaa.tex tut.tex

gaa.ps: $(TEX_OBJECTS)
	-latex gaa.tex && latex gaa.tex && dvips gaa.dvi -o gaa.ps

gaa.tex.html: $(TEX_OBJECTS)
	-latex2html gaa.tex -no_navigation -no_subdir 1 -split 0 -local_icons -html_version 3.2,math \
	-info "" -white

info_TEXINFOS = gaa.texi

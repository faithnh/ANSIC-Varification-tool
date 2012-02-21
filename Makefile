pdf:
	cd DoxygenDocument/platex-kanji; \
	sed -e '2i\\\usepackage{jtygm}' refman.tex > refman.new.tex; \
	platex -kanji=utf8 refman.new.tex doxygen.sty jtygm.sty ; \
	jmakeindex refman.new.idx; \
	platex -kanji=utf8 refman.new.tex doxygen.sty jtygm.sty ; \
	dvipdfmx -o ../man.pdf refman.new.dvi; \
	rm -f *.log *.aux *.dvi *.toc *.idx;
 
.PHONY: pdf
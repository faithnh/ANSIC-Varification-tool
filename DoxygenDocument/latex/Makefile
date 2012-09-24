all: clean refman.pdf

pdf: refman.pdf

refman.pdf: refman.tex
	platex -kanji=utf8 refman.tex
	makeindex refman.idx
	platex -kanji=utf8 refman.tex
	latex_count=5 ; \
	while egrep -s 'Rerun (LaTeX|to get cross-references right)' refman.log && [ $$latex_count -gt 0 ] ;\
	    do \
	      echo "Rerunning latex...." ;\
	      platex -kanji=utf8 refman.tex ;\
	      latex_count=`expr $$latex_count - 1` ;\
	    done
	dvipdfmx refman.dvi

clean:
	rm -f *.ps *.dvi *.aux *.toc *.idx *.ind *.ilg *.log *.out refman.pdf

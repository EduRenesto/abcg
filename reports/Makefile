TARGETS := a1.gl-ball.pdf \
	a2.sponza.pdf \
	a3.sponza-pretty.pdf

%.pdf: %.md
	pandoc $< -o $@

all: ${TARGETS}

clean:
	rm -f ${TARGETS}

.PHONY: clean

TARGETS := a1.gl-ball.pdf \
	a2.sponza.pdf

%.pdf: %.md
	pandoc $< -o $@

all: ${TARGETS}

clean:
	rm -f ${TARGETS}

.PHONY: clean

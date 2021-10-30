TARGETS := a1.gl-ball.pdf

%.pdf: %.md
	pandoc $< -o $@

all: ${TARGETS}

clean:
	rm -f ${TARGETS}

.PHONY: clean

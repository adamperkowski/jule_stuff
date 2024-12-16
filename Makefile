JULEC = julec

BINARY = stuff

# JULECFLAGS = --opt L2 --production
JULECFLAGS = -o bin/$(BINARY)

all: build

build:
	mkdir -p bin
	$(JULEC) $(JULECFLAGS) .

run: build
	./bin/$(BINARY)

test: build
	$(JULEC) test $(JULECFLAGS) .

format:
	julefmt -w .

clean:
	rm -rf bin dist

.PHONY: all build run test format clean

target=./build/Release/divsufsort.node

all: $(target)

build/:
	node-gyp configure

$(target): build/ src/*.cc
	node-gyp build

clean:
	rm -rf build

test: clean $(target)
	npm test

.PHONY: test clean

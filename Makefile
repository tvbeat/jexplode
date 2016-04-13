
PROG    =   jexplode
CORES   =   4
TARGET  ?=  debug

all:	build

debug:
	@sh -c "([ -d debug ] || mkdir debug) && \
                cd debug && \
                cmake -DCMAKE_BUILD_TYPE=debug .."

release:
	@sh -c "([ -d release ] || mkdir release) && \
                cd release && \
                cmake -DCMAKE_BUILD_TYPE=release .."

build: $(TARGET)
	@sh -c "cd $(TARGET) && make -j$(CORES)"

clean:
	@rm -rf debug
	@rm -rf release

.PHONY: build clean debug release


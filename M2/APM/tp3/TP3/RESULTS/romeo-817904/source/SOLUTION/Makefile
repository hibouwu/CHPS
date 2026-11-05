NVCC ?= nvcc
ARCH ?= sm_120
NVCCFLAGS ?= -O3 -std=c++17 -lineinfo -Xptxas=-v
TARGET := dgemm_tp3.exe

all: $(TARGET)

$(TARGET): dgemm_tp3.cu ../CODE/dgemm-shared.cu
	$(NVCC) $(NVCCFLAGS) -arch=$(ARCH) $< -o $@

run: $(TARGET)
	./$(TARGET) 256

sass: $(TARGET)
	cuobjdump --dump-sass $(TARGET) > dgemm_tp3.sass

clean:
	rm -f $(TARGET) dgemm_tp3.sass

.PHONY: all run sass clean

CC = gcc
CFLAGS = -Og -g -Wall -Wextra
LDFLAGS = -lm

SRCDIR = src
OBJDIR = obj
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/image.c $(SRCDIR)/parser.c $(SRCDIR)/transformation.c
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
TARGET = ./mytransform

all: $(TARGET)
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJDIR):
	mkdir -p $(OBJDIR)
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(OBJDIR) *.o *.so *.out $(TARGET)

.PHONY: all clean



all: ./mytransform

./mytransform: obj/main.o obj/image.o obj/parser.o obj/transformation.o
	gcc -Og -g -Wall -Wextra $^ -o $@ -lm

# 模式规则：自动生成每个 .o 文件
obj/%.o: src/%.c | obj
	gcc -Og -g -Wall -Wextra -c $< -o $@

# 保证 obj 目录存在
obj:
	mkdir -p obj

clean:
	rm -rf obj *.o *.so *.out ./mytransform

.PHONY: all clean

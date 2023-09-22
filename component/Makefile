CPPFLAGS += -I /usr/include/python3.7m
LIBS = -lpython3.7m

COMPOSANT = bip39
LIBSO = ${COMPOSANT}.so
LIBSO_OBJS = ${COMPOSANT}.o

%.o: %.cpp
    g++ -c $(CPPFLAGS) $< -o $@

all: ${LIBSO}

${LIBSO}: ${LIBSO_OBJS}
    g++ -shared $^ $(LIBS) -o $@

test: ${LIBSO}
    echo "Test execution"
    python3 test.py

clean:
    rm -f ${LIBSO} ${LIBSO_OBJS}

.PHONY: all clean test

HACL_HOME     = ../..
FSTAR_HOME   ?= $(HACL_HOME)/dependencies/FStar
KREMLIN_HOME ?= $(HACL_HOME)/dependencies/kremlin

FSTAR ?= $(FSTAR_HOME)/bin/fstar.exe

KRML_BIN=$(KREMLIN_HOME)/_build/src/Kremlin.native
INCLUDES= -I $(HACL_HOME)/code/lib/kremlin -I $(HACL_HOME)/specs \
  -I $(KREMLIN_HOME)/kremlib -I $(HACL_HOME)/code/hash
KRML=$(KRML_BIN) $(KREMLIN_ARGS) -verbose $(INCLUDES) \
  -drop Prims,FStar,Hacl.Cast,Hacl.UInt8,Hacl.UInt16,Hacl.UInt32,Hacl.UInt64,Hacl.UInt128 \
  -drop Hacl.Spec.Endianness,Hacl.Endianness,Seq.Create,Spec.* \
  -drop Hacl.Hash.SHA2_256.Lemmas,Hacl.Hash.SHA2_384.Lemmas,Hacl.Hash.SHA2_512.Lemmas \
  $(KREMLIN_HOME)/kremlib/testlib.c \
  -add-include '"testlib.h"' -ccopt -march=native

HINTS_ENABLED= --use_hints


FSTARB=$(FSTAR_HOME)/bin/fstar.exe --include $(FSTAR_HOME)/ulib/hyperstack \
        --include $(HACL_HOME)/code/lib/kremlin --include $(KREMLIN_HOME)/kremlib \
         --include $(HACL_HOME)/specs  \
        $(HINTS_ENABLED) $(OTHERFLAGS)

FSTAR_CT=$(FSTAR_HOME)/bin/fstar.exe --include $(FSTAR_HOME)/ulib/hyperstack \
        --include $(HACL_HOME)/code/lib  --include $(KREMLIN_HOME)/kremlib \
        --include $(HACL_HOME)/specs

# Files for verification
SHA2_FILES = \
	Hacl.Hash.Lib.LoadStore.fst \
	Hacl.Hash.Lib.Create.fst \
	Hacl.Hash.SHA2_512.Lemmas.fst \
	Hacl.Hash.SHA2_512.fst \
	Hacl.Hash.SHA2_384.Lemmas.fst \
	Hacl.Hash.SHA2_384.fst \
	Hacl.Hash.SHA2_256.Lemmas.fst \
	Hacl.Hash.SHA2_256.fst

# Full typechecking against the transparent integer interface
%.fst-ver: %.fst
	$(FSTARB) $^

%.fsti-ver: %.fsti
	$(FSTARB) $^

# CI
all-ci: all-ver

# Verification
all-ver: $(addsuffix -ver, $(SHA2_FILES))

# Lax typechecking against the restricted integer interface
%.fst-ct: %.fst
	$(FSTAR_CT) --lax $^

all-ct: $(addsuffix -ct, $(SHA2_FILES))

# Extraction
extract-c: sha2-256-c/SHA2_256.c sha2-384-c/SHA2_384.c sha2-512-c/SHA2_512.c

test: test-sha2_256.exe test-sha2_384.exe test-sha2_512.exe

clean:
	rm -rf *~ *.exe *.exe.dSYM
	rm -rf sha2-c sha2-*-c

sha2-c/out.krml: $(SHA2_FILES) SHA2_256.fst SHA2_384.fst SHA2_512.fst Hacl.Test.SHA2_256.fst Hacl.Test.SHA2_384.fst Hacl.Test.SHA2_512.fst
	$(KRML) -tmpdir sha2-c -skip-translation $^

sha2-256-c/SHA2_256.c sha2-256-c/Hacl_Test_SHA2_256.c: sha2-c/out.krml
	$(KRML) -tmpdir sha2-256-c $^ -skip-compilation -no-prefix Hacl.Test.SHA2_256 \
     -drop SHA2_384,SHA2_512,Hacl.Hash.SHA2_384,Hacl.Hash.SHA2_512 \
	  -bundle "SHA2_256=Hacl.Hash.Lib.Create,Hacl.Hash.Lib.LoadStore,Hacl.Hash.SHA2_256,SHA2_256"

sha2-384-c/SHA2_384.c sha2-384-c/Hacl_Test_SHA2_384.c: sha2-c/out.krml
	$(KRML) -tmpdir sha2-384-c $^ -skip-compilation -no-prefix Hacl.Test.SHA2_384 \
     -drop SHA2_256,SHA2_512,Hacl.Hash.SHA2_256,Hacl.Hash.SHA2_512 \
	  -bundle "SHA2_384=Hacl.Hash.Lib.Create,Hacl.Hash.Lib.LoadStore,Hacl.Hash.SHA2_384,SHA2_384"

sha2-512-c/SHA2_512.c sha2-512-c/Hacl_Test_SHA2_512.c: sha2-c/out.krml
	$(KRML) -tmpdir sha2-512-c $^ -skip-compilation -no-prefix Hacl.Test.SHA2_512 \
     -drop SHA2_384,SHA2_256,Hacl.Hash.SHA2_384,Hacl.Hash.SHA2_256 \
	  -bundle "SHA2_512=Hacl.Hash.Lib.Create,Hacl.Hash.Lib.LoadStore,Hacl.Hash.SHA2_512,SHA2_512"

CC := $(CC) $(INCLUDES)

%.o: %.c
	$(CC) -c $< -o $@

BASE_OBJ = $(VALE_A) $(KREMLIN_HOME)/kremlib/testlib.o $(KREMLIN_HOME)/kremlib/kremlib.o

test-sha2_256.exe: sha2-256-c/SHA2_256.o sha2-256-c/Hacl_Test_SHA2_256.o $(BASE_OBJ)
	$(CC) -o $@ $^

test-sha2_384.exe: sha2-384-c/SHA2_384.o sha2-384-c/Hacl_Test_SHA2_384.o $(BASE_OBJ)
	$(CC) -o $@ $^

test-sha2_512.exe: sha2-512-c/SHA2_512.o sha2-512-c/Hacl_Test_SHA2_512.o $(BASE_OBJ)
	$(CC) -o $@ $^

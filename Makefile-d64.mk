D64 = $(NAME).d64

C1541 ?= c1541.exe

# Unix or Windows
ifeq ($(shell echo),)
	CP = cp $1
else
	CP = copy $(subst /,\,$1)
endif

REMOVES += $(D64)

.PHONY: d64
d64: $(D64)

$(D64): $(wildcard $(NAME).plus4) $(wildcard $(NAME).c64)
	$(C1541) -format "$(NAME)","01" d64 $(NAME).d64
	$(foreach t,$^,-$(C1541) -attach $(NAME).d64 -write $t $t$(NEWLINE))

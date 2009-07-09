# this makefile was automatically generated; do not edit 

TIMEOUT ?= 10

DP ?= why-dp -timeout $(TIMEOUT)
WHYEXEC ?= why
GWHYEXEC ?= gwhy-bin
WHYLIB ?= e:\\\\Frama-C\\\\bin\\\\share\\\\frama-c\\\\why

WHY=WHYLIB=$(WHYLIB) $(WHYEXEC) --no-arrays  -split-user-conj -explain -locs 8.loc

GWHY=WHYLIB=$(WHYLIB) $(GWHYEXEC) --no-arrays  -split-user-conj -explain -locs 8.loc

JESSIELIBFILES ?= $(WHYLIB)\\why\\jessie.why

COQDEP = coqdep

.PHONY: all coq pvs simplify cvcl harvey smtlib zenon

all: simplify/8_why.sx

project: why/8.wpr

why/%.wpr: why/%.why
	@echo 'why --project [...] why/$*.why' && $(WHY) --project -dir why $(JESSIELIBFILES) why/$*.why

goals: why/8_ctx.why

why/%_ctx.why: why/%.why
	@echo 'why --multi-why [...] why/$*.why' && $(WHY) --multi-why -dir why $(JESSIELIBFILES) why/$*.why

coq: coq/8_why.vo

coq/8_why.v: why/8.why
	@echo 'why -coq-v8 [...] why/8.why' &&$(WHY) -coq-v8 -dir coq -coq-preamble "Require Export jessie_why." -coq-tactic "intuition" $(JESSIELIBFILES) why/8.why

coq-goals: goals coq/8_ctx_why.vo
	for f in why/8_po*.why; do make -f 8.makefile coq/`basename $$f .why`_why.v ; done

coq/8_ctx_why.v: why/8_ctx.why
	@echo 'why -coq-v8 [...] why/8_ctx.why' &&$(WHY) -no-prelude -coq-v8 -dir coq -coq-preamble "Require Export jessie_why." -coq-tactic "intuition" why/8_ctx.why

coq/%_why.v: why/%.why
	@echo 'why -coq-v8 [...] why/$*.why' &&$(WHY) -no-prelude -coq-v8 -dir coq -coq-preamble "Require Export 8_ctx_why." -coq-tactic "intuition" why/8_ctx.why why/$*.why

coq/%.vo: coq/%.v
	coqc -I coq $<

pvs: pvs/8_why.pvs

pvs/%_why.pvs: why/%.why
	$(WHY) -pvs -dir pvs -pvs-preamble "IMPORTING why@jessie" $(JESSIELIBFILES) why/$*.why

pvs/jessie_why.pvs:
	$(WHY) -pvs -dir pvs -pvs-preamble "IMPORTING why@why" $(JESSIELIBFILES)

isabelle: isabelle/8_why.thy

isabelle/%_why.thy: why/%.why
	$(WHY) -isabelle -dir isabelle -isabelle-base-theory jessie_why $(JESSIELIBFILES) why/$*.why
	cp -f e:\\Frama-C\\bin\\share\\frama-c\\why/isabelle/jessie_why.thy isabelle/

simplify: simplify/8_why.sx
	@echo 'Running Simplify on proof obligations' && ($(DP) $^)

simplify/%_why.sx: why/%.why
	@echo 'why -simplify [...] why/$*.why' && $(WHY) -simplify -dir simplify $(JESSIELIBFILES) why/$*.why

alt-ergo ergo: why/8_why.why
	@echo 'Running Alt-Ergo on proof obligations' && ($(DP) $^)

why/%_why.why: why/%.why
	@echo 'why -alt-ergo [...] why/$*.why' && $(WHY) -alt-ergo -dir why $(JESSIELIBFILES) why/$*.why

cvcl: cvcl/8_why.cvc

	@echo 'Running CVC Lite on proof obligations' && ($(DP) $^)

cvcl/%_why.cvc: why/%.why
	@echo 'why -cvcl [...] why/$*.why' && $(WHY) -cvcl -dir cvcl $(JESSIELIBFILES) why/$*.why

harvey: harvey/8_why.rv
	@echo 'Running haRVey on proof obligations' && ($(DP) $^)

harvey/%_why.rv: why/%.why
	@echo 'why -harvey [...] why/$*.why' && $(WHY) -harvey -dir harvey $(JESSIELIBFILES) why/$*.why

zenon: zenon/8_why.znn
	@echo 'Running Zenon on proof obligations' && ($(DP) $^)

zenon/%_why.znn: why/%.why
	@echo 'why -zenon [...] why/$*.why' && $(WHY) -zenon -dir zenon $(JESSIELIBFILES) why/$*.why

smtlib: smtlib/8_why.smt
	@echo 'Running Z3 on proof obligations' && ($(DP) $^)

smtlib/%_why.smt: why/%.why
	@echo 'why -smtlib [...] why/$*.why' && $(WHY) -smtlib --encoding sstrat --exp goal -dir smtlib $(JESSIELIBFILES) why/$*.why

z3: smtlib/8_why.smt
	@echo 'Running Z3 on proof obligations' && ($(DP) -smt-solver z3 $^)

yices: smtlib/8_why.smt
	@echo 'Running Yices on proof obligations' && ($(DP) -smt-solver yices $^)

cvc3: smtlib/8_why.smt
	@echo 'Running CVC3 on proof obligations' && ($(DP) -smt-solver cvc3 $^)

gui stat: 8.stat

%.stat: why/%.why
	@echo 'gwhy-bin [...] why/$*.why' && $(GWHY) $(JESSIELIBFILES) why/$*.why

-include 8.depend

depend: coq/8_why.v
	-$(COQDEP) -I coq coq/8*_why.v > 8.depend

clean:
	rm -f coq/*.vo


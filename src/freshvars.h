#ifndef RCHK_FRESHVARS_H
#define RCHK_FRESHVARS_H

#include "common.h"
#include "linemsg.h"
#include "state.h"

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>

using namespace llvm;

typedef VarsSetTy FreshVarsTy;
  // variables known to hold newly allocated pointers (SEXPs)
  // attempts to include only reliably unprotected pointers,
  // so as of now, any use of a variable removes it from the set

struct StateWithFreshVarsTy : virtual public StateBaseTy {
  FreshVarsTy freshVars;
  
  StateWithFreshVarsTy(BasicBlock *bb ,FreshVarsTy& freshVars): StateBaseTy(bb), freshVars(freshVars) {};
  StateWithFreshVarsTy(BasicBlock *bb): StateBaseTy(bb), freshVars() {};
  
  virtual StateWithFreshVarsTy* clone(BasicBlock *newBB) = 0;
  
  void dump(bool verbose);
};

void handleFreshVarsForNonTerminator(Instruction *in, FunctionsSetTy& possibleAllocators, FunctionsSetTy& allocatingFunctions,
  StateWithFreshVarsTy& s, LineMessenger& msg, unsigned& refinableInfos);

#endif
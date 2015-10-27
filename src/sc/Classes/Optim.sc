Optim2DMaxRe : MultiOutUGen{

	*ar{arg inputArray, order = 1, mul = 1.0, add = 0.0;
		^this.multiNewList(['audio', order] ++ inputArray.asArray).madd(mul,add);
	}
	*kr{arg inputArray, order = 1, mul = 1.0, add = 0.0;
		^this.multiNewList(['control', order] ++ inputArray.asArray).madd(mul,add);
	}

	init {arg ... theInputs;
		inputs = theInputs;
		^this.initOutputs((theInputs[0]*2)+1, rate);
	}
}

Optim3DMaxRe : MultiOutUGen{

	*ar{arg inputArray, order = 1, mul = 1.0, add = 0.0;
		^this.multiNewList(['audio', order] ++ inputArray.asArray).madd(mul,add);
	}
	*kr{arg inputArray, order = 1, mul = 1.0, add = 0.0;
		^this.multiNewList(['control', order] ++ inputArray.asArray).madd(mul,add);
	}

	init {arg ... theInputs;
		inputs = theInputs;
		^this.initOutputs((theInputs[0]+1) * (theInputs[0]+1), rate);
	}
}

Optim2DInPhase : MultiOutUGen{

	*ar{arg inputArray, order = 1, mul = 1.0, add = 0.0;
		^this.multiNewList(['audio', order] ++ inputArray.asArray).madd(mul,add);
	}
	*kr{arg inputArray, order = 1, mul = 1.0, add = 0.0;
		^this.multiNewList(['control', order] ++ inputArray.asArray).madd(mul,add);
	}

	init {arg ... theInputs;
		inputs = theInputs;
		^this.initOutputs((theInputs[0]*2)+1, rate);
	}
}



Optim3DInPhase : MultiOutUGen{

	*ar{arg inputArray, order = 1, mul = 1.0, add = 0.0;
		^this.multiNewList(['audio', order] ++ inputArray.asArray).madd(mul,add);
	}
	*kr{arg inputArray, order = 1, mul = 1.0, add = 0.0;
		^this.multiNewList(['control', order] ++ inputArray.asArray).madd(mul,add);
	}

	init {arg ... theInputs;
		inputs = theInputs;
		^this.initOutputs((theInputs[0]+1) * (theInputs[0]+1), rate);
	}
}


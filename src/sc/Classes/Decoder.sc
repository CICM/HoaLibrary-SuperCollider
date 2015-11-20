Decoder2D : MultiOutUGen{

	*ar{arg inputArray, order = 1, numberOfOutputs = 3, mul = 1.0, add = 0.0;
		if(inputArray.asArray.size  != (order * 2 +1)) {^"Wrong number of Inputs"};
		^this.multiNewList(['audio', order, numberOfOutputs] ++ inputArray.asArray).madd(mul,add);
	}


	init {arg ... theInputs;
		inputs = theInputs;
		^this.initOutputs(theInputs[1], rate);
	}
}

Decoder2DIrregular : MultiOutUGen{

	*ar{arg inputArray, order = 1, numberOfOutputs = 3, offset = 0, mul = 1.0, add = 0.0;
		if(inputArray.asArray.size  != (order * 2 +1)) {^"Wrong number of Inputs"};
		^this.multiNewList(['audio', order, numberOfOutputs, offset] ++ inputArray.asArray).madd(mul,add);
	}

	init {arg ... theInputs;
		inputs = theInputs;
		^this.initOutputs(theInputs[1], rate);
	}
}

Decoder2DBinaural : MultiOutUGen{

	*ar{arg inputArray, order = 1, cropSize = 256, mul = 1.0, add = 0.0;
		if((inputArray.asArray.size)  != (order * 2 +1), {^"Wrong number of Inputs"},
			{^this.multiNewList(['audio', order, cropSize] ++ inputArray.asArray).madd(mul,add);

	});}


	init {arg ... theInputs;
		inputs = theInputs;
		this.initOutputs(2, rate);
	}
}

Decoder3D : MultiOutUGen{

	*ar{arg inputArray, order = 1, numberOfOutputs = 4, mul = 1.0, add = 0.0;
		if(inputArray.asArray.size  != ((order + 1) * (order +1))) {^"Wrong number of Inputs"};
		^this.multiNewList(['audio', order, numberOfOutputs] ++ inputArray.asArray).madd(mul,add);
	}

	init {arg ... theInputs;
		inputs = theInputs;
		^this.initOutputs(theInputs[1], rate);
	}
}

Decoder3DBinaural : MultiOutUGen{

	*ar{arg inputArray, order = 1, cropSize = 256, mul = 1.0, add = 0.0;
		if(inputArray.asArray.size  != ((order + 1) * (order +1))) {^"Wrong number of Inputs"};
		^this.multiNewList(['audio', order, cropSize] ++ inputArray.asArray).madd(mul,add);
	}

	init {arg ... theInputs;
		inputs = theInputs;
		^this.initOutputs(2, rate);
	}
}

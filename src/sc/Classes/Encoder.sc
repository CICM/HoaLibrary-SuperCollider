Encoder2D : MultiOutUGen{

	*ar{arg input =0, order = 1, azimuth = 0.0, radius = 1.0, mul = 1.0, add = 0.0;
		^this.multiNew('audio', input, azimuth, radius, order).madd(mul,add);
	}

	init {arg ... theInputs;
		inputs = theInputs;
		^this.initOutputs((theInputs[3]*2)+1, rate);
	}
}

Encoder3D : MultiOutUGen{

	*ar{arg input =0, order = 1, azimuth = 0.0, elevation = 0.0, radius = 1.0, mul = 1.0, add = 0.0;
		^this.multiNew('audio', input, azimuth, elevation, radius, order).madd(mul,add);
	}

	init {arg ... theInputs;
		inputs = theInputs;
		^this.initOutputs((theInputs[4]+1) * (theInputs[4]+1), rate);
	}
}

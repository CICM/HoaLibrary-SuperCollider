Encoder2D : UGen{
*ar{arg input =0, azimuth = 0.0, radius = 1.0, mul = 1.0, add = 0.0;
		^this.multiNew('audio', input, order, azimuth, radius).madd(mul,add);
	}
*kr{arg input =0, azimuth = 0.0, radius = 1.0, mul = 1.0, add = 0.0;
		^this.multiNew('control', input, order, azimuth, radius).madd(mul,add);
	}

}
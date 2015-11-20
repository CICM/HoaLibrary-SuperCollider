s.boot
s.quit

(

Routine.run{

	~order = 2;

	// ~numHarmonics = ~order * 2 + 1;
	~numHarmonics = (~order + 1) * (~order + 1);
	~soundSource = NodeProxy.new(s, \audio, 1);
	~soundSource.fadeTime = 1.0;
	~soundSource.source = { |amp = 1| MoogFF.ar(Saw.ar(220,0.5),200,2.5) * EnvGen.ar(Env.perc,Impulse.ar(5)) * amp;};

	s.sync;

	~encoder = NodeProxy.new(s, \audio, ~numHarmonics);
	~encoder.fadeTime = 1.0;
	~encoder.source = { var inBus; inBus = \in.ar(1); Encoder3D.ar(inBus, ~order, MouseX.kr(pi,-pi,0,0.2),0, 1) };

	s.sync;


	~optimizer = NodeProxy.new(s, \audio, ~numHarmonics);
	~optimizer.fadeTime = 1.0;
	~optimizer.source = { var inBus; inBus = \in.ar( 0!(~numHarmonics)  ); Optim3DMaxRe.ar(inBus, ~order) };

	s.sync;


	~decoder = NodeProxy.new(s, \audio, ~numHarmonics);
	~decoder.fadeTime = 1.0;
	~decoder.source = { var inBus; inBus = \in.ar( 0!(~numHarmonics));  Decoder3DBinaural.ar(inBus, ~order) };
	~decoder.play( out:0, numChannels:2, vol:0.1);

	s.sync;

	~soundSource <>> ~encoder  <>>  ~optimizer  <>>  ~decoder ;
}
)
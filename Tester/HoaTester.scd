s.reboot
s.quit


(

Routine.run{

	~order = 3;

	~numHarmonics = ~order * 2 + 1;
	// ~numHarmonics = (~order + 1) * (~order + 1);
	~soundSource = NodeProxy.new(s, \audio, 1);
	~soundSource.fadeTime = 1.0;
	~soundSource.source = { |amp = 1| MoogFF.ar(Saw.ar(220,0.5),200,2.5) * EnvGen.ar(Env.perc,Impulse.ar(5)) * amp;};

	s.sync;

	~encoder = NodeProxy.new(s, \audio, ~numHarmonics);
	~encoder.fadeTime = 1.0;
	~encoder.source = { var inBus; inBus = \in.ar(1); Encoder2D.ar(inBus, ~order, MouseX.kr(pi/2,-pi/2,0,0.2),0, 1) };
	~encoder.source = { var inBus; inBus = \in.ar(1); Encoder2D.ar(inBus, ~order, pi/2); };

	s.sync;


	~optimizer = NodeProxy.new(s, \audio, ~numHarmonics);
	~optimizer.fadeTime = 1.0;
	~optimizer.source = { var inBus; inBus = \in.ar( 0!(~numHarmonics)  ); Optim2DMaxRe.ar(inBus, ~order) };

	s.sync;


	~decoder = NodeProxy.new(s, \audio, ~numHarmonics);
	~decoder.fadeTime = 1.0;
	~decoder.source = { var inBus; inBus = \in.ar( 0!(~numHarmonics));  Decoder2DBinaural.ar(inBus, ~order,256) };
	~decoder.play( out:6, numChannels:2, vol:0.3);

	s.sync;

	~soundSource <>> ~encoder  <>>  ~optimizer  <>>  ~decoder ;
}
)

s.plotTree

s.
~decoder.stop

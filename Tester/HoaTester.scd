s.boot

(

Routine.run{

	~order = 4;

	~numHarmonics = ~order * 2 + 1;

	~soundSource = NodeProxy.new(s, \audio, 1);
	~soundSource.fadeTime = 1.0;
	~soundSource.source = { |amp = 1| MoogFF.ar(Saw.ar(220,0.5),200,2.5) * EnvGen.ar(Env.perc,Impulse.ar(5)) * amp;};

	s.sync;

	~encoder = NodeProxy.new(s, \audio, ~numHarmonics);
	~encoder.fadeTime = 1.0;
	~encoder.source = { var inBus; inBus = \in.ar(1); Encoder2D.ar(inBus, ~order, MouseX.kr(pi,-pi,0,0.2), 1) };

	s.sync;


	~optimizer = NodeProxy.new(s, \audio, (~order * 2) + 1  );
	~optimizer.fadeTime = 1.0;
	~optimizer.source = { var inBus; inBus = \in.ar( 0!(~numHarmonics)  ); Optim2DMaxRe.ar(inBus, ~order) };

	s.sync;


	~decoder = NodeProxy.new(s, \audio, ~numHarmonics);
	~decoder.fadeTime = 1.0;
	~decoder.source = { var inBus; inBus = \in.ar( 0!(~numHarmonics));  Decoder2DBinaural.ar(inBus, ~order) };
	~decoder.play( out:0, numChannels:2, vol:0.1);

	s.sync;

	~soundSource <>> ~encoder  <>>  ~optimizer  <>>  ~decoder ;
}
)

	~order = 4;
	~numHarmonics = ~order * 2 + 1;

	~decoder = NodeProxy.new(s, \audio, ~numHarmonics);
~decoder.source = { var inBus; inBus = \in.ar(0!(~numHarmonics));  Decoder2DBinaural.ar(inBus, ~order) };

b = [3,4,5]

b[1] = [5,6,7]

b[1].size
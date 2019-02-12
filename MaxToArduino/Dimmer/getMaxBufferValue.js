outlets = 2;
var buf;
function bufname(name)
{
  buf= new Buffer(name);
  var frames = buf.framecount()
  var samples = new Array;
  samples= buf.peek(1, 0, frames);
  var max = -9999999;
  for (var i = 0; i < frames; i++)
  {
    if (Math.abs(samples[i]) > max)
    max = samples[i];
  }
  outlet(0, max);
}

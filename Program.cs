var f = File.Open("foo.log", FileMode.Append);
var logger = new Sog.Logger(f);

logger.Log("foo!", Sog.LogLevel.Debug);
logger.Flush();

logger.Dispose();
f.Close();

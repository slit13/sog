var f = File.Open("foo.log", FileMode.Append);
var logger = new Sog.Logger(f);

logger.Log("foo!", Sog.LogLevel.Debug);
logger.Error("this is just a test");
logger.Info("(prong reference)");
logger.Flush();

logger.Dispose();
f.Close();

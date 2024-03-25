var logger = new Sog.Logger();

logger.Log("foo!", Sog.LogLevel.Debug);
logger.Flush();

logger.Dispose();

namespace Sog {
    public enum LogLevel {
        Unknown,
        Print,
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
    }

    public struct LogEntry {
        public DateTime Timestamp = DateTime.UnixEpoch;
        public string Message = "placeholder";
        public LogLevel Level = LogLevel.Unknown;

        public LogEntry() {
        }

        public LogEntry(string message, LogLevel level) {
            Message = message;
            Level = level;
        }
    }
}

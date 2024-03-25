namespace Sog {
    public enum LogMode {
        Deferred,
        Immediate,
    }

    public class Logger(Stream stream) : IDisposable {
        private Queue<LogEntry> queue = new Queue<LogEntry>();
        private StreamWriter writer = new StreamWriter(stream);
        public LogMode Mode = LogMode.Deferred;

        public Logger() : this(Console.OpenStandardOutput()) {
        }

        public Logger(FileStream file) : this((Stream)file) {
        }

        ~Logger() {
            Dispose();
        }

        public void Dispose() {
            writer?.Close();
        }

        public void AddEntry(LogEntry entry) {
            queue.Enqueue(entry);
            if (Mode == LogMode.Immediate) {
                Flush();
            }
        }

        public void Log(string message, LogLevel level) {
            AddEntry(new LogEntry(message, level) {
                Timestamp = DateTime.Now
            });
        }

        public void Print(string message) {
            Log(message, LogLevel.Print);
        }

        public void Debug(string message) {
            Log(message, LogLevel.Debug);
        }

        public void Info(string message) {
            Log(message, LogLevel.Info);
        }

        public void Warning(string message) {
            Log(message, LogLevel.Warning);
        }

        public void Error(string message) {
            Log(message, LogLevel.Error);
        }

        public void Fatal(string message) {
            Log(message, LogLevel.Fatal);
        }

        public void Flush() {
            while (queue.Count > 0) {
                var entry = queue.Dequeue();
                var text = $"[{entry.Timestamp}][{entry.Level}]: {entry.Message}";
                writer.WriteLine(text);
            }
        }
    }
}

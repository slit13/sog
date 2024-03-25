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

        public void Flush() {
            while (queue.Count > 0) {
                var entry = queue.Dequeue();
                var text = $"[{entry.Timestamp}][{entry.Level}]: {entry.Message}";
                writer.WriteLine(text);
            }
        }
    }
}

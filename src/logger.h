#pragma once

#include <chrono>
#include <cstdint>
#include <queue>
#include <string>

namespace sog {

enum class LogLevel : uint8_t {
	Print,
	Debug,
	Info,
	Warning,
	Important,
	Error,
	Fatal,
};
struct LogEntry {
	LogLevel level;
	const std::string message;
	const std::chrono::time_point<std::chrono::high_resolution_clock> timestamp;
};

class Logger {
private:
	const std::string level_strings[7] = {
		[(uint8_t)LogLevel::Print]     = "",
		[(uint8_t)LogLevel::Debug]     = "Debug",
		[(uint8_t)LogLevel::Info]      = "Info",
		[(uint8_t)LogLevel::Warning]   = "Warning",
		[(uint8_t)LogLevel::Important] = "Important",
		[(uint8_t)LogLevel::Error]     = "Error",
		[(uint8_t)LogLevel::Fatal]     = "Fatal",
	};

	std::queue<LogEntry> queue = {};

	void aggregate_flush();
	void individual_flush();
public:
	std::ostream& output;
	bool immediate_write = false;
	bool aggregate_write = false;
	std::string time_format = "%Y-%m-%d %H:%M:%S";

	Logger();
	Logger(std::ostream& _output);
	~Logger();

	void add_entry(const LogEntry entry);
	void log(LogLevel level, const std::string msg);

	void print(const std::string msg);
	void debug(const std::string msg);
	void info(const std::string msg);
	void warning(const std::string msg);
	void important(const std::string msg);
	void error(const std::string msg);
	void fatal(const std::string msg);

	void flush();
};

}

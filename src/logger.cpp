#include "logger.h"
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>

using namespace sog;

Logger::Logger()
	: Logger(std::cout) {
}

Logger::Logger(std::ostream& _output)
	: output(_output) {
}

Logger::~Logger() {
}

void Logger::add_entry(const LogEntry entry) {
	this->queue.push(entry);

	if (this->immediate_write) {
		this->flush();
	}
}

void Logger::log(LogLevel level, const std::string msg) {
	const LogEntry entry = {
		.level = level,
		.message = msg,
		.timestamp = std::chrono::high_resolution_clock::now(),
	};
	this->add_entry(entry);
}

void Logger::flush() {
	const auto& buf = this->output.rdbuf();
	if (not buf) {
		return;
	}

	this->aggregate_flush();
}

void Logger::aggregate_flush() {
	std::string str = "";

	while (not this->queue.empty()) {
		const auto entry = this->queue.front();

		std::time_t time = std::chrono::high_resolution_clock::to_time_t(entry.timestamp);
		std::tm tm = *std::localtime(&time);
		std::stringstream ss;
		ss << std::put_time(&tm, this->time_format.c_str());

		str +=
			'[' +
			ss.str() +
			' ' +
			this->level_strings[(uint8_t)entry.level] +
			"]: " +
			entry.message +
			'\n';

		this->queue.pop();
	}

	this->output << str;
}

void Logger::individual_flush() {
	while (not this->queue.empty()) {
		const auto entry = this->queue.front();

		std::time_t time = std::chrono::high_resolution_clock::to_time_t(entry.timestamp);
		std::tm tm = *std::localtime(&time);

		this->output
			<< '['
			<< std::put_time(&tm, this->time_format.c_str())
			<< ' '
			<< this->level_strings[(uint8_t)entry.level]
			<< "]: "
			<< entry.message
			<< std::endl;

		this->queue.pop();
	}
}

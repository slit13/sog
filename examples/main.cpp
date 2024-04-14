// this file is meant to show how sog is used
// it's not meant to be compile-able
#include "logger.h" // wherever this shit is

int main() {
	// create logger
	std::ofstream log_file("some_file.log");
	sog::Logger logger(log_file);

	// if you wish to combine all messages in one string and write once
	logger.aggregate_write = true;

	// if you wish to write as soon as a log is queued
	logger.immediate_write = true;
	// by default both are false

	// or by default printing to std::cout
	sog::Logger logger;

	// log a message
	logger.log(sog::LogLevel::Info, "foo!");

	// with a shorthand method
	logger.important("this message is important");

	// flush the messages and actually write them
	logger.flush()

	// the logger won't take ownership of the stream so you'll have to manually handle it
	log_file.close();

	return 0;
}

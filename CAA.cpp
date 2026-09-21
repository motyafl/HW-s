#include <iostream>
#include <string>

class Logger {
private:
	Logger() {};
public:
	static int total_logs;

	static Logger& get_Instance() {
		static Logger instance; //create a single logger instace
		return instance;
	}

	Logger& log( const std::string& mess ) {
		total_logs ++;
		std::cout << "[" << total_logs << " | Log] " << mess << std::endl;
		return *this;
	}

	Logger(Logger const &) = delete;
    	void operator=(Logger const &l) = delete;
};

int Logger::total_logs {};
int main()
{
	Logger::get_Instance().log("Start").log("Process");
}

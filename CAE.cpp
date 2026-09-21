#include<iostream>
#include<string>

class Config {
private:
	const std::string app_name;
	int max_users;
public:
	Config( std::string n, int m_u ) : app_name{n}, max_users{m_u} {}
	~Config() {}

	std::string getAppName() const { return app_name; }

	void printConfig() const { std::cout << "App name: " << app_name << " | Max users: " << max_users << std::endl; }

	void setAppMUsers( int m_u ) { max_users = m_u; }
	void setAppMUsers( int m_u ) const { std::cout << "Cannot set the user count, the object is constant" << std::endl; }
/*
	friend Config* clone ( Config& other ) {
		Config* ptr = new Config(other.app_name, other.max_users);
		return ptr;
	}

	friend Config* clone ( const Config& other ) {
		Config* ptr = new Config(other.app_name, other.max_users);
		return ptr;
	}
*/
	// Easier method to clone
	Config clone() const {
		return *this;
	}
};

int main() 
{
	const Config conf( "Minecraft", 356 );
	//Config conf_clone = *clone( conf );
	Config conf_clone = conf.clone();
	conf_clone.setAppMUsers( 2500 );

	conf.printConfig();
	conf_clone.printConfig();
}

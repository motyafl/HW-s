#include<iostream>
#include<vector>

class Entity {
public:
	static int counter[3];
	Entity() { ++*(counter+2); }

	void get_stats() {
		std::cout << "Entities: " << counter[2] <<
			" | Players: " << counter[0] << 
			" | Enemies: " << counter[1] << std::endl;
	}
};

int Entity::counter[3] = { 0, 0, 0 };

class Player : public Entity {
private: 
	int id;
	std::string name;
public:
	Player( std::string n ) : Entity(), name{n} {
		*counter += 1;
		id = counter[2];
	}
};

class Enemy : public Entity {
private: 
	int id;
	std::string name;
public:
	Enemy( std::string n ) : Entity(), name{n} {
		*(counter+1) += 1;
		id = counter[2];
	}
};

int main() {
	Player Miner( "Miner" );
	Enemy Abbys ( "The Abbys" );
	Miner.get_stats();
}

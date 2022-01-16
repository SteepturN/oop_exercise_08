#include <iostream>
#include "Read_input/Read_input.hpp"
#include "Figure/Figure.hpp"
#include "Figure/Triangle/Triangle.h"
#include "Figure/Square/Square.h"
#include "Figure/Octahedron/Octahedron.h"
#include <cstdio>
#include <set>
#include <string>
#include <algorithm>
#include <list>
#include <thread>
#include <functional>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <sstream>

int main(int argc, char *argv[]) {
	std::size_t max_size;
	if(argc != 2) {
		std::cout << "not enough arguments" << std::endl;
		return -1;
	}
	else {
		max_size = std::stoi(argv[1]);
	}
	std::list<std::shared_ptr<Figure<double>>> buff;
	std::vector<std::function<void()>> managers;

	managers.push_back([&buff](){ //std::cout
		for(auto figure : buff) {
			std::cout << *figure << '\n';
		}
	});
	managers.push_back([&buff](){
		std::stringstream ss;
		for(auto figure : buff) {
			ss << *figure << '\n';
		}
		char filename[] = "./figureXXXXXX";
		int fd = mkstemp(filename);
		close(fd);
		std::fstream file(filename, std::ios_base::out | std::ios_base::trunc);
		file << ss.str();
		file.close();
	});

	std::string help_message = "You can use\n\
--add figure (square, triangle, octahendron): add *s || t || o*\n\
    *(point) 3 times for square, for octahedron and triangle center\
 position,\n radius, starting angle* *position to put in*\n \
--help for this list of commands\n\
--exit\n";
	char ch(' ');


	char command[20];
	std::set<std::string> valid_commands = {"add", "exit", "help"};
	std::cout << help_message;
	do {
		while(get_command(valid_commands, command) != VALID_INPUT) {
			do ch=getchar();
			while((ch != EOF) && (ch != '\n'));
			std::cout << "wrong input" << std::endl;
			if(ch == EOF) return 0;
		}
		std::string&& command_string = static_cast<std::string>(command);
		if(command_string == "help") {
			std::cout << help_message;
		} else if (command_string == "add") {

			if(buff.size() == max_size) {
				std::thread th([&managers, &buff](){
					for(auto func : managers) {
						func();
					}
					buff.clear();
				});
				th.join();
			}

			Figure<double>* f;
			std::set<std::string> valid_figures{"t", "o", "s"};
			char figure_type[3];
			if(get_command(valid_figures, figure_type) != VALID_INPUT) {
				std::cout << "wrong input\n";
				continue;
			}
			std::string figure_type_str =
				static_cast<std::string>(figure_type);
			if(figure_type_str == "t") {
				f = new Triangle<double>;
				if(get_value<Triangle<double>>
				   (*dynamic_cast<Triangle<double>*>(f)) != VALID_INPUT) {
					std::cout << "wrong input\n";
					delete f;
					continue;
				}
			} else if(figure_type_str == "o") {
				f = new Octahedron<double>;
				if(get_value<Octahedron<double>>
				   (*dynamic_cast<Octahedron<double>*>(f)) != VALID_INPUT) {
					std::cout << "wrong input\n";
					delete f;
					continue;
				}
			} else if(figure_type_str == "s") {
				f = new Square<double>;
				if(get_value<Square<double>>
				   (*dynamic_cast<Square<double>*>(f)) != VALID_INPUT) {
					std::cout << "wrong input\n";
					delete f;
				}
			}
			std::size_t index;
			if(get_value<std::size_t>(index) != VALID_INPUT || index > buff.size()) {
				std::cout << "wrong input\n";
				delete f;
			} else {
				auto i = buff.begin();
				for(int j = index; j > 0; --j, ++i);
				buff.insert(i, std::shared_ptr<Figure<double>>(f));
			}
		} else if(command_string == "exit") return 0;
		do ch = getchar(); while((ch != '\n') && (ch != EOF));
		if(ch == EOF) return 0;
	} while(true);
	return 0;
}

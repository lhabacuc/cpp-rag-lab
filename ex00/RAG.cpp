#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <readline/readline.h>

class Sematic
{
	private:
	std::vector<std::string>	db;
	std::vector<std::vector<std::string>>	docs;
	int							score;

	public:
	Sematic(std::string name)
	{
		add_doc(name);
	}
	Sematic(char* name)
	{
		add_doc(std::string(name));
	}
	void add_doc(std::string name)
	{
		db = (get_data_document(name));
		docs.push_back(db);
	}
	std::vector<std::string> get_data_document(std::string name)
	{
		std::vector<std::string> data;
		std::fstream f(name.c_str());
		std::string line;
		while (getline(f, line))
		{
			data.push_back(line);
			data.back() += "\n";
		}
		return data;
	}

	std::map<std::string, int> analyze(std::string query)
	{
		std::map<std::string, int> scores;

		for (size_t i = 0; i < db.size(); i++)
		{
			std::string line = db[i];

			std::stringstream ss(query);
			std::string word;

			while (ss >> word)
			{
				if (line.find(word) != std::string::npos)
					scores[line] += 1;
			}
		}

		return scores;
	}

	std::string generate_response(std::string query)
	{
		std::map<std::string, int> scores = analyze(query);
		std::string response;
		for (auto& score : scores)
		{
			if (score.second > 0)
				response += score.first + " ";
		}
		return response;
	}

	// std::string get_dados_document(std::string name)
	// {
		
	// 	return ;
	// }
};

int main(int ac, char** av)
{
	if (ac != 2)
	{
		std::cout << "Usage: " << av[0] << " <file>" << std::endl;
		return (1);
	}

	Sematic sematic(av[1]);
	std::string query;
	while (true)
	{
		query = readline(">> ");
		if (query.empty())
			continue ;
		if (query == "exit")
			break;
		if (query == "clear")
		{
			std::cout << "\033[2J\033[1;1H";
			continue ;
		}
		std::cout << sematic.generate_response(query) << std::endl;
	}
}

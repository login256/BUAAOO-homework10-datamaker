/*
 * By LYT(login)
 * For BUAAOO homework-10
 * Can generate Random data
 */

#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include <vector>
#include <string>

const int NODECOUNT = 250;
const int PATHNODE = 200;

const int ADDTIMES = 15;
const int REMOVETIMES = 5;
const int LINETIMES = 500;
const int TOTALTIMES = 7000;

std::default_random_engine random_engine(time(0));

class Node_Map
{
private:
	Node_Map()
	{
		std::uniform_int_distribution<int> dis(INT32_MIN, INT32_MAX);
		for (int i = 0; i < NODECOUNT; i++)
		{
			map[i] = dis(random_engine);
		}
	}


public:
	int map[300];

	static Node_Map &get_instance()
	{
		static Node_Map ins;
		return ins;
	}
};


class Path
{
	friend std::ostream &operator<<(std::ostream &os, const Path &path);

public:
	std::vector<int> nodes;

	Path()
	{
		std::uniform_int_distribution<int> dis(0, 7);
		for (int i = 1; i <= PATHNODE; i++)
		{
			nodes.push_back(Node_Map::get_instance().map[dis(random_engine) % NODECOUNT]);
		}
	}

};

std::ostream &operator<<(std::ostream &os, const Path &path)
{
	for (int i : path.nodes)
	{
		os << i << ' ';
	}
	return os;
}

Path path[50];
int cnt_path = 0;

void add()
{
	std::uniform_real_distribution<double> rand_dis(0, 1);
	if (rand_dis(random_engine) < 0.125 && cnt_path != 0)
	{
		std::uniform_int_distribution<int> dis(0, cnt_path - 1);
		std::cout << "PATH_ADD " << path[dis(random_engine)] << std::endl;
	}
	else
	{
		cnt_path++;
		std::cout << "PATH_ADD " << path[cnt_path - 1] << std::endl;
	}
}


void gen_path_instr(const std::string &s, double ratio)
{
	std::uniform_real_distribution<double> rand_dis(0, 1);
	if (rand_dis(random_engine) < ratio && cnt_path != 0)
	{
		std::uniform_int_distribution<int> dis(0, cnt_path - 1);
		std::cout << s << " " << path[dis(random_engine)] << std::endl;
	}
	else
	{
		std::cout << s << " " << *(new Path) << std::endl;
	}
}

void gen_id_instr(const std::string &s, double ratio)
{
	std::uniform_real_distribution<double> rand_dis(0, 1);
	if (rand_dis(random_engine) < ratio && cnt_path != 0)
	{
		std::uniform_int_distribution<int> dis(0, cnt_path - 1);
		std::cout << s << " " << dis(random_engine) << std::endl;
	}
	else
	{
		std::uniform_int_distribution<int> dis(INT32_MIN, INT32_MAX);
		std::cout << s << " " << dis(random_engine) << std::endl;
	}
}

int gen_path_id(double ratio)
{
	std::uniform_real_distribution<double> rand_dis(0, 1);
	if (rand_dis(random_engine) < ratio || cnt_path != 0)
	{
		std::uniform_int_distribution<int> dis(0, cnt_path - 1);
		return dis(random_engine);
	}
	else
	{
		std::uniform_int_distribution<int> dis(INT32_MIN, INT32_MAX);
		return dis(random_engine);
	}
}

int gen_node_id(double ratio)
{
	std::uniform_real_distribution<double> rand_dis(0, 1);
	if (rand_dis(random_engine) < ratio)
	{
		std::uniform_int_distribution<int> dis(0, NODECOUNT - 1);
		return Node_Map::get_instance().map[dis(random_engine)];
	}
	else
	{
		std::uniform_int_distribution<int> dis(INT32_MIN, INT32_MAX);
		return dis(random_engine);
	}
}

void remove()
{
	gen_path_instr("PATH_REMOVE", 0.25);
}

void remove_id()
{
	gen_id_instr("PATH_REMOVE_BY_ID", 0.25);
}

void get_id()
{
	gen_path_instr("PATH_GET_ID", 0.75);
}

void get_by_id()
{
	gen_id_instr("PATH_GET_BY_ID", 0.75);
}

void path_count()
{
	std::cout << "PATH_COUNT" << std::endl;
}

void path_size()
{
	gen_id_instr("PATH_SIZE", 0.75);
}

void path_distinct_node()
{
	gen_id_instr("PATH_DISTINCT_NODE_COUNT", 0.75);
}

void contains_path()
{
	gen_path_instr("CONTAINS_PATH", 0.5);
}

void contains_path_id()
{
	gen_id_instr("CONTAINS_PATH_ID", 0.5);
}

void distinct_node()
{
	std::cout << "DISTINCT_NODE_COUNT" << std::endl;
}

void compare()
{
	std::cout << "COMPARE_PATHS" << " " << gen_path_id(0.9) << " " << gen_path_id(0.9) << std::endl;
}

void path_contains_node()
{
	std::cout << "PATH_CONTAINS_NODE" << " " << gen_path_id(0.9) << " " << gen_node_id(0.9) << std::endl;
}

void contains_node()
{
	std::cout << "CONTAINS_NODE" << " " << gen_node_id(0.8) << std::endl;
}

void contains_edge()
{
	std::cout << "CONTAINS_EDGE" << " " << gen_node_id(0.95) << " " << gen_node_id(0.95) << std::endl;
}

void is_node_connected()
{
	std::cout << "IS_NODE_CONNECTED" << " " << gen_node_id(0.95) << " " << gen_node_id(0.95) << std::endl;
}

void shortest_node_length()
{
	std::cout << "SHORTEST_PATH_LENGTH" << " " << gen_node_id(0.95) << " " << gen_node_id(0.95) << std::endl;
}

int a[10000];

int main()
{
	int cnt = 0;
	for (int i = 1; i <= ADDTIMES; i++)
	{
		a[++cnt] = 1;
	}
	for (int i = 1; i <= REMOVETIMES; i++)
	{
		a[++cnt] = 2;
	}
	for (int i = 1; i <= LINETIMES - ADDTIMES - REMOVETIMES; i++)
	{
		a[++cnt] = 3;
	}
	while (cnt < TOTALTIMES)
	{
		a[++cnt] = 4;
	}
	std::shuffle(a + 1, a + cnt + 1, random_engine);
	for (int i = 1; i <= cnt; i++)
	{
		switch (a[i])
		{
			case 1:
			{
				add();
				break;
			}
			case 2:
			{
				std::uniform_int_distribution<int> dis(1, 2);
				switch (dis(random_engine))
				{
					case 1:
					{
						remove();
						break;
					}
					case 2:
					{
						remove_id();
						break;
					}
				}
				break;
			}
			case 3:
			{
				std::uniform_int_distribution<int> dis(1, 4);
				switch (dis(random_engine))
				{
					case 1:
					{
						get_id();
						break;
					}
					case 2:
					{
						get_by_id();
						break;
					}
					case 3:
					{
						contains_path();
						break;
					}
					case 4:
					{
						compare();
						break;
					}
				}
				break;
			}
			case 4:
			{
				std::uniform_int_distribution<int> dis(1, 4);
				switch (dis(random_engine))
				{
					case 1:
					{
						path_count();
						break;
					}
					case 2:
					{
						path_size();
						break;
					}
					case 3:
					{
						path_distinct_node();
						break;
					}
					case 4:
					{
						contains_path_id();
						break;
					}
					case 5:
					{
						distinct_node();
						break;
					}
					case 6:
					{
						compare();
						break;
					}
					case 7:
					{
						path_contains_node();
						break;
					}
					case 8:
					{
						contains_node();
						break;
					}
					case 9:
					{
						contains_edge();
						break;
					}
					case 10:
					{
						is_node_connected();
						break;
					}
					case 11:
					{
						shortest_node_length();
						break;
					}
				}
				break;
			}
		}
	}
	return 0;
}
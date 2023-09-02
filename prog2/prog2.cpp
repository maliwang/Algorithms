#include <iostream>
#include <vector>
#include <queue>

class Cell {
	public:
	int x;
	int y;
	Cell(int a, int b) {
		x = a;
		y = b;
	};
};

int  BFS(std::vector<std::vector <char>> field, int size, int x, int y, std::vector<std::vector <int>> *visited) {
	std::vector<std::vector <int>> dist;
	for (int i = 0; i < size; i++) {
		std::vector <int> row;
		for (int j = 0; j < size; j++) {
			row.push_back(0);
		}
		dist.push_back(row);
	}

	std::queue<Cell> q;
	(*visited)[x][y] = 1;
	dist[x][y] = 1;
	Cell start(x,y);
	q.push(start);

	while (!q.empty()) {
		Cell c = q.front();
		q.pop();
		if (c.x > 0) {
			if ((!(*visited)[c.x-1][c.y]) && (field[c.x-1][c.y] == 'c')) {
				dist[c.x-1][c.y] = dist[c.x][c.y]+1;
				(*visited)[c.x-1][c.y] =1;
				Cell c_above(c.x-1, c.y);
				q.push(c_above);
			}
		} 
		if (c.x < size-1) {
			if ((!(*visited)[c.x+1][c.y]) && (field[c.x+1][c.y] == 'c')) {
				dist[c.x+1][c.y] = dist[c.x][c.y]+1;
                                (*visited)[c.x+1][c.y] =1;
				Cell c_below(c.x+1, c.y);
				q.push(c_below);
			}
		} 
		if (c.y > 0) {
			if ((!(*visited)[c.x][c.y-1]) && (field[c.x][c.y-1] == 'c')) {
				dist[c.x][c.y-1] = dist[c.x][c.y]+1;
                                (*visited)[c.x][c.y-1] =1;
				Cell c_left(c.x, c.y-1);
				q.push(c_left);
			}
		}
		if (c.y < size-1) {
			 if ((!(*visited)[c.x][c.y+1]) && (field[c.x][c.y+1] == 'c')) {
                                dist[c.x][c.y+1] = dist[c.x][c.y]+1;
                                (*visited)[c.x][c.y+1] =1;
				Cell c_right(c.x, c.y+1);
				q.push(c_right);
                        }
		}
	}
	int time = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (dist[i][j] > time) time = dist[i][j];
		}
	}
	return time;
}

int remainingCorn(std::vector<std::vector <char>> field, int size, std::vector<std::vector <int>> visited) {
	int sum = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((!visited[i][j]) && (field[i][j] == 'c')) sum += 1;
		}
	}
	return sum;
}

Cell unvisitedCell(std::vector<std::vector <char>> field, std::vector<std::vector <int>> visited, int size) {
	Cell c(-1,-1);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((!visited[i][j]) && (field[i][j] == 'c')) {
				c.x = i;
				c.y = j;
			}
		}
	}
	return c;
}

int Fires(std::vector<std::vector <char>> field, int size, std::vector<std::vector <int>> visited){
	std::vector<std::vector <int>> tmp_visited = visited;
	int num_fires = 1;
	while (remainingCorn(field, size, tmp_visited) != 0) {
		 num_fires += 1;
		 Cell c = unvisitedCell(field, tmp_visited, size);
		 BFS(field, size, c.x, c.y, &tmp_visited);
	}
	 return num_fires;
}

int main() {
	int size;
	std::vector<std::vector <char>> field;
	int x;
	int y;
	char cell;
	std::vector<std::vector <int>> visited;

	std::cin >> size;
	for (int i = 0; i < size; i++) {
		std::vector<char> row1;
		std::vector<int> row2;
		for(int j = 0; j < size; j++) {
			std::cin >> cell;
			row1.push_back(cell);
			row2.push_back(0);
		}
		field.push_back(row1);
		visited.push_back(row2);
	}
	std::cin >> x;
	std::cin >> y;

	int time = BFS(field, size, x-1, y-1, &visited);
	int sum = remainingCorn(field, size, visited);
	int num_fires = Fires(field, size, visited);
	std::cout << time << std::endl;
	std::cout << sum << std::endl;
	std::cout << num_fires << std::endl;
}

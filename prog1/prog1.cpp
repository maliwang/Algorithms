#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

class Point {
	public:
	float x;
	float y;
	Point(float a, float b) {
		x = a;
		y = b;
	};
};

class Pair {
	public:
	Point p1;
	Point p2;
	Pair(Point point1, Point point2);
};

Pair::Pair(Point point1, Point point2)
	:p1(point1), p2(point2)
{
}

float dist(Point p1, Point p2) {
	return std::sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

std::vector<Point>  merge_sort_by_x(std::vector<Point> input) {
	//base case
	if (input.size() == 1) return input;

	//divide and conquer
	std::vector<Point> left;
	std::vector<Point> right;
	for (int i = 0; i < input.size(); i++) {
		if (i < input.size()/2) {
			left.push_back(input[i]);
		} else {
			right.push_back(input[i]);
		}
	}
	left = merge_sort_by_x(left);
	right = merge_sort_by_x(right);

	//combine
	std::vector<Point> output;
	int left_idx = 0;
	int right_idx = 0;
	for (; left_idx < left.size() and right_idx < right.size(); ) {
		if (left[left_idx].x < right[right_idx].x) {
			output.push_back(left[left_idx]);
			left_idx++;
		}else {
			output.push_back(right[right_idx]);
			right_idx++;
		}
	}
	if (left_idx == left.size()) {
		while (right_idx < right.size()) {
			output.push_back(right[right_idx]);
			right_idx++;
		}
	} else {
		while (left_idx < left.size()) {
                        output.push_back(left[left_idx]);
                        left_idx++;
                }
	}
	return output;
}

std::vector<Point>  merge_sort_by_y(std::vector<Point> input) {
        //base case
	if (input.size() == 1) return input;

	//devide and conquer
        std::vector<Point> left;
        std::vector<Point> right;
        for (int i = 0; i < input.size(); i++) {
                if (i < input.size()/2) {
                        left.push_back(input[i]);
                } else {
                        right.push_back(input[i]);
                }
        }
        left = merge_sort_by_y(left);
        right = merge_sort_by_y(right);

	//combine
        std::vector<Point> output;
        int left_idx = 0;
        int right_idx = 0;
        for (; left_idx < left.size() and right_idx < right.size(); ) {
                if (left[left_idx].y < right[right_idx].y) {
                        output.push_back(left[left_idx]);
                        left_idx++;
                }else {
                        output.push_back(right[right_idx]);
                        right_idx++;
                }
        }
        if (left_idx == left.size()) {
                while (right_idx < right.size()) {
                        output.push_back(right[right_idx]);
                        right_idx++;
                }
        } else {
                while (left_idx < left.size()) {
                        output.push_back(left[left_idx]);
                        left_idx++;
                }
        }
        return output;
}

Pair findMinSpanningPair(float delta, std::vector<Point> sorted_input) {
        //find set S
	std::vector<Point> S;
        for (int i = 0; i < sorted_input.size(); i++) {
                if (abs(sorted_input[sorted_input.size()/2].x - sorted_input[i].x) <= delta) {
                        S.push_back(sorted_input[i]);
                }
        }
        //S has only one element
        if (S.size() == 1) {
               Pair minPair(sorted_input[sorted_input.size()/2], sorted_input[sorted_input.size()/2+1]);
               return minPair;
        }

	//S has at least two elements
        std::vector<Point> sorted_S = merge_sort_by_y(S);
        Pair minPair(sorted_S[0], sorted_S[1]);//arbitrary minPair

        for (int i = 0; i < sorted_S.size(); i++) {
                for (int j = i+1; j < sorted_S.size(); j++) {
                        if ((sorted_S[j].y - sorted_S[i].y) > delta) break;
                        if (dist(sorted_S[i], sorted_S[j]) < dist(minPair.p1, minPair.p2)) {
                                minPair.p1 = sorted_S[i];
			       minPair.p2 = sorted_S[j];
                        }
                }
        }
        return minPair;
}

Pair recurse(std::vector<Point> sorted_input) {
	//base case
	if (sorted_input.size() < 4) {
		Pair tmp_closest(sorted_input[0], sorted_input[1]);
		for (int i = 0; i < sorted_input.size(); i++) {
			for (int j = i+1; j < sorted_input.size(); j++) {
				if (dist(sorted_input[i], sorted_input[j]) < dist(tmp_closest.p1, tmp_closest.p2)) {
					tmp_closest.p1 = sorted_input[i];
					tmp_closest.p2 = sorted_input[j];
				}
			}
		}
		return tmp_closest;
	}

	//divide and conquer
	std::vector<Point> left;
	std::vector<Point> right;
	for (int i = 0; i < sorted_input.size(); i++) {
		if (i < sorted_input.size()/2) {
			left.push_back(sorted_input[i]);
		}else {
			right.push_back(sorted_input[i]);
		}
	}
	Pair pairL = recurse(left);
	Pair pairR = recurse(right);
	float distL = dist(pairL.p1, pairL.p2);
	float distR = dist(pairR.p1, pairR.p2);

	//find delta
	float delta;
	if (distL < distR) delta = distL;
	else delta = distR;

	//find min spannig pair
	Pair pairS = findMinSpanningPair(delta, sorted_input);
	float distS = dist(pairS.p1, pairS.p2);
	
	//combine
	if ((distL < distR) & (distL < distS)) return pairL;
	else if ((distR < distL) & (distR < distS)) return pairR;
	else return pairS;
}

Pair closest(std::vector<Point> input) {
        std::vector<Point> sorted_input = merge_sort_by_x(input);
        return recurse(sorted_input);
}


int main() {
	int num_set;
	std::cin >> num_set;
	std::vector<float> output;
	int num_points;

	while(std::cin >> num_points) {
		std::vector<Point> input;
		for (int i = 0; i < num_points; i++) {
			Point p(0,0);
			std::cin >> p.x;
			std::cin >> p.y;
			input.push_back(p);
		}
		Pair closest_pair = closest(input);
		Point closest_point_1 = closest_pair.p1;
		Point closest_point_2 = closest_pair.p2;
		output.push_back(dist(closest_point_1, closest_point_2));
		for (int i = 0; i < input.size(); i++) {
			if (((input[i].x == closest_point_1.x) & (input[i].y == closest_point_1.y)) |
				((input[i].x == closest_point_2.x) & (input[i].y == closest_point_2.y))) {
				output.push_back(i);
			}
		}			
	}
	for (int j = 0; j < output.size(); j += 3) {
		std::cout << std::fixed << std::setprecision(4) << output[j] << std::endl;
		std::cout << std::fixed << std::setprecision(0) << output[j+1] << " " << output[j+2] << std::endl;
	}
}

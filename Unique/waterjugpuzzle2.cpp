/*******************************************************************************
 * Name    : waterjugpuzzle.cpp
 * Author  : Eric Rudzin + Shreyas Keerthi
 * Version : 1.0
 * Date    : September 19, 2020
 * Description : Solves the water jug puzzle using BFS.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <queue>
#include <array>
#include <typeinfo>
#include <string>
using namespace std;

char jug[] = {'A', 'B', 'C'};

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;

    State(int _a, int _b, int _c, string _directions) :
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

void backtrack(State goalstate){
	vector<string> directions;
	State s = goalstate;
	while(s.parent != nullptr){
		directions.push_back(s.directions);
		s = *s.parent;
	}
	for(unsigned int i = directions.size() - 1; i >= 0; i--){
		cout << directions[i] << endl;
	}
}

string bfs(int a, int b, int c, State goal){
	vector<vector<bool> > seenStates(a + 1, vector<bool>(b + 1, false));
    for (int i = 0; i < a + 1; i++) {
        for (int j = 0; j < b + 1; j++) {
            seenStates[i][j] = false;
        }
    }
	queue <State> q;
	State current(0, 0, c, "Initial State.");
	State *temp = nullptr;
	current.parent = temp;
	q.push(current);
	while(!q.empty()){
		current = q.front();
		q.pop();
		if(current.parent != nullptr){
			cout << current.to_string() << current.parent->to_string()<< endl;
		}
		else{
			cout << current.to_string()<< endl;
		}

		if(current.to_string() == goal.to_string()){
			backtrack(current);
			break;
		}

		bool nextIt = false;
	    for (int i = 0; i < a + 1; i++) {
	        for (int j = 0; j < b + 1; j++) {
	            if(seenStates[i][j] == true){
	            	nextIt = true;
	            }
	        }
	    }
	    if(nextIt){
	    	continue;
	    }


	    for (int i = 0; i < a + 1; i++) {
	        for (int j = 0; j < b + 1; j++) {
	            if(i == current.a && j == current.b){
                    seenStates[i][j]=true;
	            }
	        }
	    }

        temp = &current;

        string direct;
        //try pour from C to A
    	if(current.c > 0 && current.a < a){
    		if(a - current.a <= current.c){
    			direct = "Pour " + to_string(a-current.a) +  " gallons from C to A. ";
    			State CA(a, current.b, current.c - (a - current.a), direct + CA.to_string());
    			CA.parent = temp;
    			q.push(CA);
    		}
    		else{
    			direct = "Pour " + to_string(current.c) + " gallons from C to A. ";
    			State CA(current.a + current.c, current.b, 0, direct + CA.to_string());
    			CA.parent = temp;
    			q.push(CA);
    		}
    	}
    	//Pour from B to A
    	if(current.b > 0 && current.a < a){
    		if(a - current.a <= current.b){
    			direct = "Pour " + to_string(a-current.a) +  " gallons from B to A. ";
    			State BA(a, current.c - (a-current.a), current.c, direct + BA.to_string());
    			BA.parent = temp;
    			q.push(BA);
    		}
    		else{
    			direct = "Pour " + to_string(current.b) +  " gallons from B to A. ";
    			State BA(current.a + current.b, 0, current.c, direct + BA.to_string());
    			BA.parent = temp;
    			q.push(BA);
    		}
    	}
    	//Pour from C to B
    	if(current.c > 0 && current.b < b){
    		if(b - current.b <= current.c){
    			direct = "Pour" + to_string(b-current.b) +  "gallons from C to B. ";
    			State CB(current.a, b, current.c - (b-current.b), direct + CB.to_string());
    			CB.parent = temp;
    			q.push(CB);
    		}
    		else{
    			direct = "Pour" + to_string(current.c) + "gallons from C to B. ";
    			State CB(current.a, current.b + current.c, 0, direct + CB.to_string());
    			CB.parent = temp;
    			q.push(CB);
    		}
    	}
    	//Pour from A to B
    	if(current.a > 0 && current.b < b){
    		if(b - current.b <= current.a){
    			direct = "Pour" + to_string(b-current.b) +  "gallons from A to B. ";
    			State AB(current.a - (b-current.b), b, current.c, direct + AB.to_string());
    			AB.parent = temp;
    			q.push(AB);
    		}
    		else{
    			direct = "Pour" + to_string(current.a) + "gallons from A to B. ";
    			State AB(0, current.b + current.a, current.c, direct + AB.to_string());
    			AB.parent = temp;
    			q.push(AB);
    		}
    	}
    	//Pour from B to C
    	if(current.b > 0 && current.c < c){
    		if(c - current.c <= current.b){
    			direct = "Pour" + to_string(a-current.a) +  "gallons from B to C. ";
    			State BC(current.a, current.b - (c-current.c), c, direct + BC.to_string());
    			BC.parent = temp;
    			q.push(BC);
    		}
    		else{
    			direct = "Pour" + to_string(current.b) + "gallons from B to C. ";
    			State BC(current.a, 0, current.c + current.b, direct + BC.to_string());
    			BC.parent = temp;
    			q.push(BC);
    		}
    	}
    	//Pour from A to C
    	if(current.c > 0 && current.a < a){
    		if(c - current.c <= current.a){
    			direct = "Pour" + to_string(a-current.a) +  "gallons from A to C. ";
    			State AC(current.a - (c - current.c), current.b, c, direct + AC.to_string());
    			AC.parent = temp;
    			q.push(AC);
    		}
    		else{
    			direct = "Pour" + to_string(current.a) + "gallons from A to C. ";
    			State AC(0, current.b, current.c + current.a, direct + AC.to_string());
    			AC.parent = temp;
    			q.push(AC);
    		}
    	}
	}
	return "No solution.";
}
/*
int main(int argc, char *argv[]) {
	istringstream iss;
	int inputs[6];
	if (argc != 7){
		cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"<< endl;
		return 1;
	}

	int x;
	for(int i = 1; i < argc; i++){
		iss.str(argv[i]);
		if(i < 4){
			if(!(iss >> x)){
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << jug[i-1] << "." <<  endl;
				return 1;
			}
			else{
				iss >> x;
				if(x <= 0){
					cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << jug[i-1] << "." <<  endl;
					return 1;
				}
			}
		}
		else{
			if(!(iss >> x)){
				cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << jug[i-4] << "." <<endl;
				return 1;
			}
			else{
				iss >> x;
				if(x < 0){
					cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << jug[i-1] << "." <<  endl;
					return 1;
				}
			}
		}
		iss.clear();
	}

	for(int i = 1; i < argc; i++){
		iss >> x;
		inputs[i-1] = x;
	}

	for(int i = 0; i < 3; i++){
		if(inputs[i] < inputs[i+3]){
			cerr << "Error: Goal cannot exceed capacity of jug" << jug[i] << endl;
			return 1;
		}
	}

	int goaltotal = 0;
	for(int i = 3; i < 6; i ++){
		goaltotal += inputs[i];
	}
	if(goaltotal != inputs[2]){
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}

	aCap = inputs[0], bCap = inputs[1], cCap = inputs[2];

	State goal_state(inputs[3], inputs[4], inputs[5], "");

	cout <<  bfs(aCap, bCap, cCap, goal_state);

}
*/
int main(int argc, char * const argv[]) {
	    if (argc != 7){
	    		cout << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
	    		return 1;
	    	}
	    for (int i=1; i < argc; i++){
	    	int m;
	    	istringstream iss;
	    	iss.str(argv[i]);
	    	if ((!(iss >> m)) ){
	    		if (i == 1){
	    			cout << "Error: Invalid capacity '" << argv[i] << "' for jug A." << endl;
	    			return 1;
	    		}
	    		if (i == 2){
	    			cout << "Error: Invalid capacity '" << argv[i] << "' for jug B." << endl;
	    			return 1;
	    		}
	    		if (i == 3){
	    			cout << "Error: Invalid capacity '" << argv[i] << "' for jug C." << endl;
	    			return 1;
	    		}
	    		if (i == 4){
	    			cout << "Error: Invalid goal '" << argv[i] << "' for jug A." << endl;
	    			return 1;
	    		}
	    		if (i == 5){
					cout << "Error: Invalid goal '" << argv[i] << "' for jug B." << endl;
					return 1;
	    		}
	    		if (i == 6){
					cout << "Error: Invalid goal '" << argv[i] << "' for jug C." << endl;
					return 1;
				}

	    	}
	    	else{
	    		iss >> m;
	    		if (m == 0){
	    			if (i == 1){
						cout << "Error: Invalid capacity '" << argv[i] << "' for jug A." << endl;
						return 1;
					}
					if (i == 2){
						cout << "Error: Invalid capacity '" << argv[i] << "' for jug B." << endl;
						return 1;
					}
					if (i == 3){
						cout << "Error: Invalid capacity '" << argv[i] << "' for jug C." << endl;
						return 1;
					}
	    		}
	    		if (m < 0){
	    			if (i == 1){
						cout << "Error: Invalid capacity '" << argv[i] << "' for jug A." << endl;
						return 1;
					}
					if (i == 2){
						cout << "Error: Invalid capacity '" << argv[i] << "' for jug B." << endl;
						return 1;
					}
					if (i == 3){
						cout << "Error: Invalid capacity '" << argv[i] << "' for jug C." << endl;
						return 1;
					}
	    			if (i == 4){
						cout << "Error: Invalid goal '" << argv[i] << "' for jug A." << endl;
						return 1;
					}
					if (i == 5){
						cout << "Error: Invalid goal '" << argv[i] << "' for jug B." << endl;
						return 1;
					}
					if (i == 6){
						cout << "Error: Invalid goal '" << argv[i] << "' for jug C." << endl;
						return 1;
					}
	    		}
	    	}
	    }
	    vector<int> arguments;
	    	    for (int j = 1; j <= 6; j++){
	    	    	int k;
	    	    	istringstream iss3;
	    	    	iss3.str(argv[j]);
	    	    	iss3 >> k;
	    	    	arguments.push_back(k);


	    }
	    if (arguments[3] > arguments[0]){
	    	cout << "Error: Goal cannot exceed capacity of jug A." << endl;
	    	return 1;
	    }
	    if (arguments[4] > arguments[1]){
			cout << "Error: Goal cannot exceed capacity of jug B." << endl;
			return 1;
		}
	    if (arguments[5] > arguments[2]){
			cout << "Error: Goal cannot exceed capacity of jug C." << endl;
			return 1;
		}
	    if ((arguments[3] + arguments[4] + arguments[5]) != arguments[2]){
	    	cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
	    	return 1;
	    }


	State s(0, 0, arguments[2], "Initial State.");
	State g(arguments[3], arguments[4], arguments[5], "Goal State");


	cout << bfs(arguments[0], arguments[1], arguments[2], g) << endl;
    return 0;
}

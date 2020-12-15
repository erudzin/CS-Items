/*******************************************************************************
 * Name    : waterjugpuzzle.cpp
 * Author  : Eric Rudzin and Shreyas Keerthi
 * Version : 1.0
 * Date    : October, 20, 2020
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
    vector<State> parent;

    State(int _a, int _b, int _c, string _directions) :
        a{_a}, b{_b}, c{_c}, directions{_directions} { }

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

void backtrack(State goalstate){
	string directions;
	State s = goalstate;
	while(!s.parent.empty()){
		directions = s.directions + "\n" + directions;
		s = s.parent[0];
	}
	directions = s.directions + "\n" + directions;
	cout << directions << endl;
}

void bfs(int a, int b, int c, State goal){
	vector<vector<bool>> seenStates(a + 1, vector<bool>(b + 1, false));

	queue <State> q;
	State current(0, 0, c, "");
	current.directions = "Initial state. (0, 0, " + to_string(current.c) + ")";
	q.push(current);
	while(!q.empty()){
		current = q.front();
		q.pop();
		if(current.to_string().compare(goal.to_string()) == 0){
			backtrack(current);
			return;
		}

	    if(seenStates[current.a][current.b]){
	    	continue;
	    }

	    for (int i = 0; i < a + 1; i++) {
	        for (int j = 0; j < b + 1; j++) {
	            if(i == current.a && j == current.b){
                    seenStates[i][j]=true;
	            }
	        }
	    }

        string direct;
        //try pour from C to A
    	if(current.c > 0 && current.a < a){
    		if(a - current.a <= current.c){
    			if(a - current.a == 1){
    				direct = "Pour " + to_string(a-current.a) +  " gallon from C to A. ";
    			}
    			else{
    				direct = "Pour " + to_string(a-current.a) +  " gallons from C to A. ";
    			}
    			State CA(a, current.b, current.c - (a - current.a), direct);
    			CA.directions += CA.to_string();
    			CA.parent.push_back(current);
    			q.push(CA);
    		}
    		else{
    			if(current.c == 1){
    				direct = "Pour " + to_string(current.c) + " gallon from C to A. ";
    			}
    			else{
    				direct = "Pour " + to_string(current.c) + " gallons from C to A. ";
    			}
    			State CA(current.a + current.c, current.b, 0, direct);
    			CA.directions += CA.to_string();
    			CA.parent.push_back(current);
    			q.push(CA);
    		}
    	}
    	//Pour from B to A
    	if(current.b > 0 && current.a < a){
    		if(a - current.a <= current.b){
    			if(a - current.a == 1){
    				direct = "Pour " + to_string(a-current.a) +  " gallon from B to A. ";
    			}
    			else{
    				direct = "Pour " + to_string(a-current.a) +  " gallons from B to A. ";
    			}
    			State BA(a, current.b - (a-current.a), current.c, direct);
    			BA.directions += BA.to_string();
    			BA.parent.push_back(current);
    			q.push(BA);
    		}
    		else{
    			if(current.b == 1){
    				direct = "Pour " + to_string(current.b) + " gallon from B to A. ";
    			}
    			else{
    				direct = "Pour " + to_string(current.b) + " gallons from B to A. ";
    			}
    			State BA(current.a + current.b, 0, current.c, direct);
    			BA.directions += BA.to_string();
    			BA.parent.push_back(current);
    			q.push(BA);
    		}
    	}
    	//Pour from C to B
    	if(current.c > 0 && current.b < b){
    		if(b - current.b <= current.c){
    			if(b - current.b == 1){
    				direct = "Pour " + to_string(b-current.b) +  " gallon from C to B. ";
    			}
    			else{
    				direct = "Pour " + to_string(b-current.b) +  " gallons from C to B. ";
    			}
    			State CB(current.a, b, current.c - (b-current.b), direct);
    			CB.directions += CB.to_string();
    			CB.parent.push_back(current);
    			q.push(CB);
    		}
    		else{
    			if(current.c == 1){
    				direct = "Pour " + to_string(current.c) + " gallon from C to B. ";
    			}
    			else{
    				direct = "Pour " + to_string(current.c) + " gallons from C to B. ";
    			}
    			State CB(current.a, current.b + current.c, 0, direct);
    			CB.directions += CB.to_string();
    			CB.parent.push_back(current);
    			q.push(CB);
    		}
    	}
    	//Pour from A to B
    	if(current.a > 0 && current.b < b){
    		if(b - current.b <= current.a){
    			if(b - current.b == 1){
    				direct = "Pour " + to_string(b-current.b) +  " gallon from A to B. ";
    			}
    			else{
    				direct = "Pour " + to_string(b-current.b) +  " gallons from A to B. ";
    			}
    			State AB(current.a - (b-current.b), b, current.c, direct);
    			AB.directions += AB.to_string();
    			AB.parent.push_back(current);
    			q.push(AB);
    		}
    		else{
    			if(current.a == 1){
    				direct = "Pour " + to_string(current.a) + " gallon from A to B. ";
    			}
    			else{
    				direct = "Pour " + to_string(current.a) + " gallons from A to B. ";
    			}
    			State AB(0, current.b + current.a, current.c, direct);
    			AB.directions += AB.to_string();
    			AB.parent.push_back(current);
    			q.push(AB);
    		}
    	}
    	//Pour from B to C
    	if(current.b > 0 && current.c < c){
    		if(c - current.c <= current.b){
    			if(c - current.c == 1){
    				direct = "Pour " + to_string(c-current.c) +  " gallon from B to C. ";
    			}
    			else{
    				direct = "Pour " + to_string(c-current.c) +  " gallons from B to C. ";
    			}
    			State BC(current.a, current.b - (c-current.c), c, direct);
    			BC.directions += BC.to_string();
    			BC.parent.push_back(current);
    			q.push(BC);
    		}
    		else{
    			if(current.b == 1){
    				direct = "Pour " + to_string(current.b) + " gallon from B to C. ";
    			}
    			else{
    				direct = "Pour " + to_string(current.b) + " gallons from B to C. ";
    			}
    			State BC(current.a, 0, current.c + current.b, direct);
    			BC.directions += BC.to_string();
    			BC.parent.push_back(current);
    			q.push(BC);
    		}
    	}
    	//Pour from A to C
    	if(current.a > 0 && current.c < c){
    		if(c - current.c <= current.a){
    			if(c - current.c == 1){
    				direct = "Pour " + to_string(c-current.c) +  " gallon from A to C. ";
    			}
    			else{
    				direct = "Pour " + to_string(c-current.c) +  " gallons from A to C. ";
    			}
    			State AC(current.a - (c - current.c), current.b, c, direct);
    			AC.directions += AC.to_string();
    			AC.parent.push_back(current);
    			q.push(AC);
    		}
    		else{
    			if(current.a == 1){
    				direct = "Pour " + to_string(current.a) + " gallon from A to C. ";
    			}
    			else{
    				direct = "Pour " + to_string(current.a) + " gallons from A to C. ";
    			}
    			State AC(0, current.b, current.c + current.a, direct);
    			AC.directions += AC.to_string();
    			AC.parent.push_back(current);
    			q.push(AC);
    		}
    	}
	}
	cout <<  "No solution.";
}

int main(int argc, char *argv[]) {
	char jug[] = {'A', 'B', 'C'};
    istringstream iss;

    if (argc != 7){
        cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"<< endl;
        return 1;
    }

    int x;
    for(int i = 1; i < argc; i++){
        iss.str(argv[i]);
		if ((!(iss >> x)) ){
			if(i<4){
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << jug[i-1] << "." <<  endl;
                return 1;
			}else if(i<=4){
				cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << jug[i-4] << "." <<  endl;
                return 1;
			}

		}else{
            iss >> x;
            if(x==0){
                if(i>=1&&i<4){
                    cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << jug[i-1] << "." <<  endl;
                    return 1;
                }
            }if(x<0){
                if(i<4){
                    cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << jug[i-1] << "." <<  endl;
                    return 1;
                }else if (i>=4){
                    cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << jug[i-4] << "." <<  endl;
                    return 1;
                }
            }
        }
		iss.clear();
	}

    vector<int> inputs;
	for(int i = 1; i < argc; i++){
		istringstream iss2;
		iss2.str(argv[i]);
        iss2 >> x;
        inputs.push_back(x);
    }

	for(int i=3;i<6;i++){
		if(inputs[i]>inputs[i-3]){
			cerr << "Error: Goal cannot exceed capacity of jug " << jug[i-3] << "." << endl;
	    	return 1;
		}
	}

	if ((inputs[3] + inputs[4] + inputs[5]) != inputs[2]){
	     cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
	     return 1;
	 }


    State goal_state(inputs[3], inputs[4], inputs[5], "");


    bfs(inputs[0], inputs[1], inputs[2], goal_state);
    return 0;
}

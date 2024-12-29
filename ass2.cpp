#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

// First-come first-serve scheduling algorithm
void FCFS(int initial_position, const vector<int>& requests)
{
    int head = initial_position;
    int seek_time = 0;
    vector<int> order;

    // Process requests in the order they came
    for (size_t i = 0; i < requests.size(); ++i) {
    	int request = requests[i];
        seek_time += abs(request - head); // Get distance from head to the request value
        head = request; // Set request as head
        order.push_back(request);
    }

    cout << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "First-come First-serve (FCFS) Algorithm: " << endl;
    cout << "Order of processed requests             : ";
    for (size_t i = 0; i < order.size(); ++i) // Display request order
    	cout << order[i] << " ";
    cout << endl;
    cout << "\nTotal seek time                        : " << seek_time << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

void SCAN(int initial_position, const vector<int>& requests, int total_cylinders, string direction)
{
    int head = initial_position;
    int seek_time = 0, cur_track, distance;
    vector<int> order;
    vector<int> left_request, right_request;

    // Determine the direction of the scan
    if (direction == "left")
        left_request.push_back(0);
    else if (direction == "right")
        right_request.push_back(total_cylinders - 1);

    // Divide the requests into left and right of the head
    for (size_t i = 0; i < requests.size(); ++i) {
	    int request = requests[i];
	    if (request < head)
	        left_request.push_back(request);
	    else if (request > head)
	        right_request.push_back(request);
	}


    // Sort the left and right vectors
    sort(left_request.begin(), left_request.end());
    sort(right_request.begin(), right_request.end());

    // Run the loop twice: one for scanning left and one for right
    int run = 2;
    while (run--) {
        if (direction == "left") { // Moving left
            for (vector<int>::reverse_iterator it = left_request.rbegin(); it != left_request.rend(); ++it) {
                cur_track = *it;
                order.push_back(cur_track);
                distance = abs(cur_track - head);
                seek_time += distance;
                head = cur_track;
            }
            direction = "right"; // Change direction to right
        } else { // Moving right
            for (size_t i = 0; i < right_request.size(); ++i) {
			    int cur_track = right_request[i];
			    order.push_back(cur_track);
			    distance = abs(cur_track - head);
			    seek_time += distance;
			    head = cur_track;
			}

            direction = "left"; // Change direction to left
        }
    }

    cout << endl;
    cout << "SCAN Algorithm: " << endl;
    cout << "Order of processed requests             : ";
    for (size_t i = 0; i < order.size(); ++i)
	    cout << order[i] << " ";
    cout << endl;
    cout << "\nTotal seek time                        : " << seek_time << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

int main()
{
    int head, total_cylinders, num_request;
    string direction;

    cout << "Enter the initial head position                   : ";
    cin >> head;
    cout << "Enter the number of cylinders on the disk         : ";
    cin >> total_cylinders;
    cout << "Enter the number of requests in the queue         : ";
    cin >> num_request;
    cout << "Enter the direction ('left' or 'right')           : ";
    cin >> direction;

    if(direction =="right"||direction=="left")
    {
      // Request input
      vector<int> requests(num_request);
      cout << "Enter the list of I/O requests separated by space : ";
      for (int i = 0; i < num_request; i++) {
          cin >> requests[i];
      }

      FCFS(head, requests);
      SCAN(head, requests, total_cylinders, direction);
    }
    else
    {
      cout << "\nError : only enter 'right' or 'left'."<<endl;
      cout << "Restart code for new execution.";
    }

    return 0;
}
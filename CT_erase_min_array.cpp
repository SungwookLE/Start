#include <string>
#include <vector>
using namespace std;

vector<int> solution(vector<int> arr){
	vector<int> answer;
	int k =0;
	for (unsigned int i = 0 ; i < arr.size(); ++ i) {
		for (unsigned int j =0 ; j < arr.size(); ++ j) {
			if (arr.at(i) > arr.at(j))
				break;
			else{
				if (j == arr.size() -1)
					k = int(i);
			}
		}
	}

	arr.erase(arr.begin()+k);
	if ( arr.size() ! = 0 )
		answer = arr;
	else
		answer.push_back(-1);

	return answer;
}
	
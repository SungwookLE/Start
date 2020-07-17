//////////////////////////////////

#include <string>
#include <vector>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {
    vector<vector<int>> answer(arr1.size(),vector<int>(arr1.at(0).size()));
    int temp;


    for (int i =0 ; i<arr1.size(); ++i){
        for (int j=0 ; j < arr1.at(i).size(); ++j ){
            temp=arr1.at(i).at(j) + arr2.at(i).at(j);
            answer[i][j]=temp;
            }
    }

    return answer;
}

//////////////////////////////////

#include <string>
#include <vector>

using namespace std;

double solution(vector<int> arr) {
    double answer = 0;

    for (int i =0; i<arr.size() ; ++i){
        answer+=arr.at(i);
    }

    answer = answer / arr.size();

    return answer;
}

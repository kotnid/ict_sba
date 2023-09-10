#include "stat.h"
#include <iostream>
#include <algorithm> 
#include <unordered_map>
#include "numeric"
#include "cmath"

using namespace std;

bool scoreCmp(Data a, Data b,const vector<float>& maxScore, const vector<float>& weighting, bool ASC){
    float scoreA = 0;
    float scoreB = 0;

    // base on weighting
    for(int i=0 ; i<a.scores.size();i++){
        scoreA += a.scores[i]/maxScore[i]*weighting[i]; 
        scoreB += b.scores[i]/maxScore[i]*weighting[i];
    }

    // ASC / DESC
    if(ASC){
        return scoreA < scoreB;
    }else{
        return scoreA > scoreB;
    }
}

bool classNumCmp(Data a, Data b,bool ASC){
    if(ASC){
        if(a.form != b.form)return a.form < b.form;
        if(a.Class != b.Class)return a.Class < b.Class;
        return a.classNum < b.classNum;
    }else{
        if(a.form != b.form)return a.form > b.form;
        if(a.Class != b.Class)return a.Class > b.Class;
        return a.classNum > b.classNum;
    }
}

vector<Data> dbSort(int type, vector<Data> scores){
    /*
    parameter:
    0 - score ascending
    1 - score descending
    2 - form+class+Num ascending
    3 - form+class+Num descending
    */

    vector<float>maxScore = {100,100};
    vector<float>weighting = {100,100};

    if(type == 0){
        sort(scores.begin(),scores.end(),[maxScore, weighting](Data a, Data b){
            return scoreCmp(a,b, maxScore, weighting,1);
        });
    }else if(type == 1){
        sort(scores.begin(),scores.end(),[maxScore, weighting](Data a, Data b){
            return scoreCmp(a,b, maxScore, weighting,0);
        });
    }else if(type == 2){
        sort(scores.begin(),scores.end(),[](Data a, Data b){
            return classNumCmp(a,b, 1);
        });
    }else{
        sort(scores.begin(),scores.end(),[](Data a, Data b){
            return classNumCmp(a,b, 0);
        });
    }

    return scores;
}

unordered_map<string,float> getStats(vector<Data>input){
    unordered_map<string,float> stat;

    vector<float>maxScore = {100,100};
    vector<float>weighting = {100,100};

    vector<float> calculatedScores;
    for (const Data& data : input) {
        float sum = data.scores[0];
        // for (size_t i = 0; i < data.scores.size(); ++i) {
        //     sum += data.scores[i] / maxScore[i] * weighting[i];
        // }
        calculatedScores.push_back(sum);
    }
    sort(calculatedScores.begin(), calculatedScores.end());

    // find median
    if (calculatedScores.size() % 2 == 0) {
        stat["median"] = (calculatedScores[calculatedScores.size() / 2 - 1] + calculatedScores[calculatedScores.size() / 2]) / 2.0;
    } else {
        stat["median"] = calculatedScores[calculatedScores.size() / 2];
    }

    // find mean
    float sum2 = std::accumulate(calculatedScores.begin(), calculatedScores.end(), 0.0);
    stat["mean"] = sum2 / calculatedScores.size();

    // find the maximum and minimum
    stat["max"] = *std::max_element(calculatedScores.begin(), calculatedScores.end());
    stat["min"] = *std::min_element(calculatedScores.begin(), calculatedScores.end());

    // find normal distribution
    float sum = 0.0;
    for (float value : calculatedScores) {
        sum += pow(value - stat["mean"], 2);
    }
    stat["normal distribution"] = sqrt(sum / calculatedScores.size());

    // find Q3/Q1 
    if (calculatedScores.size()%4 != 0) {
        stat["Q1"] = (calculatedScores[calculatedScores.size()/4] + calculatedScores[calculatedScores.size()/4-1]) / 2.0;
        stat["Q3"] = (calculatedScores[3*calculatedScores.size()/4] + calculatedScores[3*calculatedScores.size()/4+1]) / 2.0;
    }else{
        stat["Q1"] = calculatedScores[calculatedScores.size()/4];
        stat["Q3"] = calculatedScores[calculatedScores.size()/4];
    }
    


    return stat;
} 
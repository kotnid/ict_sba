#include "stat.h"
#include <iostream>
#include <algorithm> 

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
        return a.classNum < b.classNum;
    }else{
        return a.classNum > b.classNum;
    }
}

dbData dbSort(int type, dbData data){
    /*
    parameter:
    0 - score ascending
    1 - score descending
    2 - classNum ascending
    3 - classNum descending
    */

    vector<Data>scores = data.result;
    vector<float>maxScore = data.maxScore;
    vector<float>weighting = data.weighting;

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

    return dbData{data.headers,maxScore,weighting,scores};
}

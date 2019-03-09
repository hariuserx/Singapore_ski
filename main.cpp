/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kishore
 *
 * Created on 24 November, 2018, 11:22 PM
 */

#include <cstdlib>
#include <fstream>
#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < n; i++)

using namespace std;

typedef pair<int, int> pii;

pii longest_and_deepest_path(int i, int j, int **mat, int level, int n, pii **pathAndLastElement, pii **nextElement){
    
    if(pathAndLastElement[i][j].first != -1)
        return pathAndLastElement[i][j];
        
    pii depth(0,mat[i][j]);
    pathAndLastElement[i][j].first = 0;
    pathAndLastElement[i][j].second = mat[i][j];
    
    if(i > 0 && mat[i-1][j] < mat[i][j]){
        depth = longest_and_deepest_path(i-1, j, mat, level+1, n, pathAndLastElement, nextElement);
        if(depth.first >= pathAndLastElement[i][j].first){
            pathAndLastElement[i][j].first = depth.first;
            pathAndLastElement[i][j].second = min(pathAndLastElement[i][j].second, depth.second);
            if(!(nextElement[i][j].first != -1 && nextElement[i][j].second != -1
                    && mat[i-1][j] > mat[nextElement[i][j].first][nextElement[i][j].second]
                    && pathAndLastElement[nextElement[i][j].first][nextElement[i][j].second].second < pathAndLastElement[i-1][j].second)){
                nextElement[i][j].first = i-1;
                nextElement[i][j].second = j;
            }
        }
    }
    if(i < n-1 && mat[i+1][j] < mat[i][j]){
        depth = longest_and_deepest_path(i+1, j, mat, level+1, n, pathAndLastElement, nextElement);
        if(depth.first >= pathAndLastElement[i][j].first){
            pathAndLastElement[i][j].first = depth.first;
            pathAndLastElement[i][j].second = min(pathAndLastElement[i][j].second, depth.second);
            if(!(nextElement[i][j].first != -1 && nextElement[i][j].second != -1
                    && mat[i+1][j] > mat[nextElement[i][j].first][nextElement[i][j].second]
                    && pathAndLastElement[nextElement[i][j].first][nextElement[i][j].second].second < pathAndLastElement[i+1][j].second)){
                nextElement[i][j].first = i+1;
                nextElement[i][j].second = j;
            }
        }
    }
    if(j > 0 && mat[i][j-1] < mat[i][j]){
        depth = longest_and_deepest_path(i, j-1, mat, level+1, n, pathAndLastElement, nextElement);
        if(depth.first >= pathAndLastElement[i][j].first){
            pathAndLastElement[i][j].first = depth.first;
            pathAndLastElement[i][j].second = min(pathAndLastElement[i][j].second, depth.second);
            if(!(nextElement[i][j].first != -1 && nextElement[i][j].second != -1
                    && mat[i][j-1] > mat[nextElement[i][j].first][nextElement[i][j].second]
                    && pathAndLastElement[nextElement[i][j].first][nextElement[i][j].second].second < pathAndLastElement[i][j-1].second)){
                nextElement[i][j].first = i;
                nextElement[i][j].second = j-1;
            }
        }
    }
    if(j < n-1 && mat[i][j+1] < mat[i][j]){
        depth = longest_and_deepest_path(i, j+1, mat, level+1, n, pathAndLastElement, nextElement);
        if(depth.first >= pathAndLastElement[i][j].first){
            pathAndLastElement[i][j].first = depth.first;
            pathAndLastElement[i][j].second = min(pathAndLastElement[i][j].second, depth.second);
            if(!(nextElement[i][j].first != -1 && nextElement[i][j].second != -1
                    && mat[i][j+1] > mat[nextElement[i][j].first][nextElement[i][j].second]
                    && pathAndLastElement[nextElement[i][j].first][nextElement[i][j].second].second < pathAndLastElement[i][j+1].second)){
                nextElement[i][j].first = i;
                nextElement[i][j].second = j+1;
            }
        }
    }
    
    pathAndLastElement[i][j].first++;
         
    return pathAndLastElement[i][j];
}


int main(int argc, char** argv) {
    
    ifstream in("data.txt");
    string line = "";
    getline(in, line);
    
    stringstream ss(line);
    int mapSize;
    ss >> mapSize;
    
    int **mat;
    pii **pathAndLastElement;
    pii **nextElement;
    mat = new int *[mapSize];
    pathAndLastElement = new pii *[mapSize];
    nextElement = new pii *[mapSize];
    REP(i, mapSize){
        mat[i] = new int [mapSize];
        pathAndLastElement[i] = new pii [mapSize];
        nextElement[i] = new pii [mapSize];
    }
    
    REP(i, mapSize){
        
        getline(in, line); stringstream ss(line);
        
        REP(j, mapSize){
            ss >> mat[i][j];
        }
    }
    
    REP(i, mapSize)
    REP(j, mapSize)
    {
        pathAndLastElement[i][j].first = -1;
        pathAndLastElement[i][j].second = -1;
        nextElement[i][j].first = -1;
        nextElement[i][j].second = -1;
    }
    
    int maxPath = -1;
    int maxDrop = -1;
    int maxX = -1;
    int maxY = -1;
    
    REP(i,mapSize){
        REP(j,mapSize){
            pathAndLastElement[i][j] = longest_and_deepest_path(i, j, mat, 1, mapSize, pathAndLastElement, nextElement);
            if(pathAndLastElement[i][j].first > maxPath){
                maxPath = pathAndLastElement[i][j].first;
                maxDrop = mat[i][j] - pathAndLastElement[i][j].second;
                maxX = i;
                maxY = j;
            }
            else if(pathAndLastElement[i][j].first == maxPath && mat[i][j] - pathAndLastElement[i][j].second > maxDrop){
                maxDrop = mat[i][j] - pathAndLastElement[i][j].second;
                maxX = i;
                maxY = j;
            }
        }
    }
    
    int i=maxX,j=maxY;
    int tmpI,tmpJ,counter=0;
    printf("Path is ------- ");
    while(i != -1 && j != -1){
        printf("%d<<", mat[i][j]);
        tmpI = nextElement[i][j].first;
        tmpJ = nextElement[i][j].second;
        i = tmpI;
        j = tmpJ;
        counter++;
    }
    
    printf("\n");
    
    printf("Maximum length is %d\n", maxPath);
    printf("Maximum drop is is %d\n", maxDrop);
    
    printf("\n");
    
    return 0;
}


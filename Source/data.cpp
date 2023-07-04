#include "data.hpp"
#include <iostream>
using namespace std;

bool comp(data const &a, data const &b){// COMPARE POINTS BY DISTANCES 
    return a.current_distance < b.current_distance;
}

double distance(vector<double> x, vector<double> y, int d){//CALCULATE DISTANCE
    
    double dist = 0.0;
    double z;
    double n = 2.0;                  //for Eucledian distance

    for(int i = 0; i < d; i++){
        z = abs(x[i] - y[i]);
        dist = dist + (pow(z, n));
    }
    dist = pow(dist, (1.0/n));

    return dist;
}

double Discrete_Frechet_Distance(vector<double> x, vector<double> y){

    int m1 = x.size();
    int m2 = y.size();

    double Dynamic_Array[m1][m2];
    double distance = 0.0;
    
    Dynamic_Array[0][0] = abs(x[0] - y[0]);
    distance = Dynamic_Array[0][0];

    for(int i = 1; i < m1; i++){
        double cij = abs(x[i] - y[0]);
        if(Dynamic_Array[i - 1][0] > cij){
            Dynamic_Array[i][0] = Dynamic_Array[i -1][0];
            continue;
        }
        Dynamic_Array[i][0] = cij;

    }

    for(int j = 1; j < m2; j++){
        double cij = abs(x[0] - y[j]);
        if(Dynamic_Array[0][j - 1] > cij){
            Dynamic_Array[0][j] = Dynamic_Array[0][j - 1];
            continue;
        }
        Dynamic_Array[0][j] = cij;

    }

    for(int i = 1; i < m1; i++){
        for(int j = 1; j < m2; j++){
            double c1 = Dynamic_Array[i - 1][j];
            double c2 = Dynamic_Array[i - 1][j - 1];
            double c3 = Dynamic_Array[i][j - 1];
            double cij = abs(x[i] - y[j]);
            double c;
            if(c1 < c2){
                if(c1 < c3)
                    c = c1;
                else
                    c = c3;
            }else{
                if(c2 < c3)
                    c = c2;
                else
                    c = c3;
            }
            
            if(c > cij)
                Dynamic_Array[i][j] = c;
            else    
                Dynamic_Array[i][j] = cij;

            if(i == j)
                distance += Dynamic_Array[i][j];

        }
    }
    
    //cout<<Dynamic_Array[d-1][d-1]<<endl;
    return Dynamic_Array[m1-1][m2-1];
}

bool compare_distance(data const& a, data const& b){//COMPARE POINTS BY DISTANCES
    return a.current_distance < b.current_distance;
}

bool compare_dist(data* const& a, data* const& b){//COMPARE POINTS BY DISTANCES
    return a->true_distance < b->true_distance;
}

bool compare_ID_pointer(data* const& a, data* const& b){// COMPAIR POINT BY ID
    return a->ID < b->ID;
}


//CONTINUOUS

void filtering(vector<double> current_data, data* current_data_node){

    double e = 1.0;
    current_data_node->p_data.push_back(current_data[0]);

    int current_size = current_data.size();
   
    for(int i = 1; i < current_size - 1; i++){
        double a = current_data[i - 1];
        double b = current_data[i];
        double c = current_data[i + 1];

        if(abs(a-b) <= e && abs(b-c) <= e){
            
            if(i != current_size - 2){
                current_data_node->p_data.push_back(current_data[i + 1]);
            }
            i++; 
        }else{
        
            current_data_node->p_data.push_back(current_data[i]);
        }
    }
    
    current_data_node->p_data.push_back(current_data[current_size - 1]);

}

double ContinuousFrechet_distance(vector<double> current_curve, vector<double> query_curve){

    int dimension = 2;
    Curve CurrentCurve(dimension, "current_curve");
    Curve QueryCurve(dimension, "query_curve");

    for(int i = 0; i < current_curve.size(); i++){
       
        Point current_point(1);
        current_point.set(0, current_curve[i]);

        CurrentCurve.push_back(current_point);
    }

    for(int i = 0; i < query_curve.size(); i++){
       
        Point query_point(1);
        query_point.set(0, query_curve[i]);

        QueryCurve.push_back(query_point);
    }

    return Frechet::Continuous::distance(CurrentCurve, QueryCurve).value;

}
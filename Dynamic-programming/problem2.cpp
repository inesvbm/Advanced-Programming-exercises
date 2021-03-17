#include <iostream>
#include <string>
#include <vector>
#include <math.h> 
#include <algorithm> 
#include <iomanip> 
using namespace std;

class Point {
public:
    double x, y;
    double area;
};

size_t numberPoints, subsetSize;
vector<Point> totalPoints;
vector<Point> selectedPoints;

bool operator<(Point a, Point b){
    return a.x < b.x;
}

void readLines() {
    cin >> numberPoints >> subsetSize;
    for (size_t i = 0; i < numberPoints; i++) {
        vector<Point> v;
        double a, b;
        cin >> a >> b;
        Point p;
        p.x = a;
        p.y = b;
        p.area = a * b;
        totalPoints.push_back(p);
    }
    sort(totalPoints.begin(), totalPoints.end());
}

void bottomTop() {
    double area = 0;
    // 1o caso base - area que inclui todos os pontos
    if (subsetSize == numberPoints) {
        for (size_t i = 0; i < numberPoints; i++) {
            area += totalPoints[i].x * totalPoints[i].y;
        }
    }
    else {  
        // 2o caso base - subset=1
        if (subsetSize == 1) {
            for (size_t i = 0; i < numberPoints; i++) {
                if (totalPoints[i].area > area) {
                    area = totalPoints[i].area;
                }
            }
        }
        // restantes casos
        else {
            // selectedPoints=vector de pontos com a área atualizada; totalPoints=vector de pontos a serem testados 
            selectedPoints = totalPoints;
            for (size_t i = 1; i < subsetSize; i++) {
                for (size_t j = 0; j < totalPoints.size() - i; j++) {
                    double bigger = 0;
                    for (size_t k = j + 1; k <= selectedPoints.size() - i; k++) {
                        // acrescenta a área do ponto j à área de k=j+1
                        double compare = totalPoints[j].x * (totalPoints[j].y - selectedPoints[k].y) + selectedPoints[k].area;
                        // obtém a área máxima
                        if (compare > bigger) {
                            bigger = compare;
                        }
                    }
                    // atualiza área no respectivo index
                    selectedPoints[j].area = bigger;
                }
            }
            // encontra a maior área
            for (size_t i = 0; i < selectedPoints.size(); i++) {
                if (selectedPoints[i].area > area) {
                    area = selectedPoints[i].area;
                }
            }
        }                
    }
    cout << fixed << setprecision(12) << area << "\n";
}

int main() {
    readLines();
    bottomTop();
    return 0;
}
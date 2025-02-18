#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

struct Point 
{
    double x, y; //Define Points
};

double distance(const Point& p1, const Point& p2)
{
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2)); //Distance Function
}

Point calculateMean(const std::vector<Point>& points) //Calculating the Mean Value
{
    Point mean = { 0.0, 0.0 };
    if (!points.empty()) {
        for (const auto& p : points) {
            mean.x += p.x;
            mean.y += p.y;
        }
        mean.x /= points.size();
        mean.y /= points.size();
    }
    return mean;
}

int findNearestCentroid(const Point& point, const std::vector<Point>& centroids) //Finding the nearest centroid
{
    int nearestCentroidIndex = 0;
    double minDistance = distance(point, centroids[0]);
    for (size_t i = 1; i < centroids.size(); ++i) {
        double dist = distance(point, centroids[i]);
        if (dist < minDistance) {
            minDistance = dist;
            nearestCentroidIndex = i;
        }
    }
    return nearestCentroidIndex;
}

void kMeans(std::vector<Point>& points, int k, int maxIterations) //Iterating the kMeans algorithm
{
    if (points.empty() || k <= 0 || k > points.size()) {
        return;
    }

    std::srand(std::time(0));
    std::vector<Point> centroids(k);
    for (int i = 0; i < k; ++i) {
        centroids[i] = points[std::rand() % points.size()];
    }

    std::vector<int> assignments(points.size());
    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        for (size_t i = 0; i < points.size(); ++i) {
            assignments[i] = findNearestCentroid(points[i], centroids);
        }

        std::vector<std::vector<Point>> clusters(k);
        for (size_t i = 0; i < points.size(); ++i) {
            clusters[assignments[i]].push_back(points[i]);
        }

        for (int i = 0; i < k; ++i) {
            if (!clusters[i].empty()) {
                centroids[i] = calculateMean(clusters[i]);
            }
        }
    }

    std::cout << "Centroids:" << std::endl;
    for (int i = 0; i < k; ++i) {
        std::cout << "Cluster " << i + 1 << ": (" << centroids[i].x << ", " << centroids[i].y << ")" << std::endl;
    }
}

int main() 
{
    std::vector<Point> points = //Setting the vectors of the values
    {
        {1.0, 1.0}, {1.5, 2.0}, {3.0, 4.0}, {5.0, 7.0}, {3.5, 5.0},
        {4.5, 5.0}, {2.5, 3.0}, {6.0, 8.0}, {5.5, 9.0}, {4.0, 6.0}
    };
    int k = 2;
    int maxIterations = 100;

    kMeans(points, k, maxIterations); //Execute kMeans algorithm

    return 0;
}
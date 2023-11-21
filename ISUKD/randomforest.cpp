#include "randomforest.h"

#include <math.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <ctime>
#include <cstdlib>


using namespace std;

int maxTime;

randomForest::randomForest(int numTrees, int maxDepth) : numTrees(numTrees), maxDepth(maxDepth)
{
    srand(time(nullptr));
}

void randomForest::train(const vector<InputData>& data)
{
    //record max time
    maxTime = 0;
    for (const InputData& sample : data)
    {
        for (quint64 time : sample.input)
        {
            if (maxTime < time)
                maxTime = time;
        }
    }

    for (int i = 0; i < numTrees; ++i)
    {
        vector<InputData> subset = getRandomSubset(data, data.size());

        trees.push_back(buildDecisionTree(subset, maxDepth));
    }
}

bool randomForest::predict(const vector<quint64>& pressingTime)
{
    int positiveVotes = 0;
    for (const TreeNode* tree : trees)
    {
        const TreeNode* currentNode = tree;
        while (!currentNode->isLeaf)
        {
            if (pressingTime[currentNode->featureIndex] < currentNode->threshold)
            {
                currentNode = currentNode->left;
            }
            else
            {
                currentNode = currentNode->right;
            }
        }
        positiveVotes += currentNode->leafClass ? 1 : 0;
    }
    return positiveVotes > numTrees / 2;
}

//random subset
vector<InputData> randomForest::getRandomSubset(const vector<InputData>& data, int subsetSize)
{
    vector<InputData> subset;
    for (int i = 0; i < subsetSize; ++i)
    {
        int index = rand() % data.size();
        subset.push_back(data[index]);
    }
    return subset;
}

//class ratio
double randomForest::calculateClassRatio(const vector<InputData>& data)
{
    int positiveCount = 0;
    for (const InputData& sample : data)
    {
        if (sample.isMatch)
        {
            positiveCount++;
        }
    }

    return static_cast<double>(positiveCount) / data.size();
}

// gini index
double randomForest::calculateGiniIndex(const vector<InputData>& data)
{
    double classRatio = calculateClassRatio(data);
    return classRatio * (1 - classRatio);
}

//choose threshold
void randomForest::findBestSplit(const vector<InputData>& data, int& bestFeatureIndex, double& bestThreshold)
{
    //random choose feature and threshold
    bestFeatureIndex = rand() % data[0].input.size();
    bestThreshold = (rand() % 100) / 100.0 * maxTime;
}

//build tree
TreeNode* randomForest::buildDecisionTree(const vector<InputData>& data, int depth)
{
    if (depth == 0 || calculateGiniIndex(data) == 0 || data.empty())
    {
        TreeNode* leaf = new TreeNode;
        leaf->isLeaf = true;
        leaf->leafClass = calculateClassRatio(data) > 0.5;
        return leaf;
    }

    int bestFeatureIndex;
    double bestThreshold;
    findBestSplit(data, bestFeatureIndex, bestThreshold);

    vector<InputData> leftSubset, rightSubset;
    for (const InputData& sample : data)
    {
        if (sample.input[bestFeatureIndex] < bestThreshold)
        {
            leftSubset.push_back(sample);
        }
        else
        {
            rightSubset.push_back(sample);
        }
    }

    TreeNode* node = new TreeNode;
    node->isLeaf = false;
    node->featureIndex = bestFeatureIndex;
    node->threshold = bestThreshold;
    node->left = buildDecisionTree(leftSubset, depth - 1);
    node->right = buildDecisionTree(rightSubset, depth - 1);

    return node;
}

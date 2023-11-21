#ifndef RANDOMFOREST_H
#define RANDOMFOREST_H

#include <QKeyEvent>
#include <vector>

using namespace std;

//struct input
struct InputData
{
    vector<quint64> input;
    bool isMatch;
};

//struct tree nodes
struct TreeNode
{
    int featureIndex;
    double threshold;
    bool isLeaf;
    bool leafClass;
    TreeNode* left;
    TreeNode* right;
};

class randomForest {

public:

    randomForest(int numTrees, int maxDepth);

    void train(const vector<InputData>& data);

    bool predict(const vector<quint64>& pressingTime);

private:
    int numTrees;

    int maxDepth;

    vector<TreeNode*> trees;

    vector<InputData> getRandomSubset(const std::vector<InputData>& data, int subsetSize);

    double calculateClassRatio(const std::vector<InputData>& data);

    double calculateGiniIndex(const std::vector<InputData>& data);

    void findBestSplit(const std::vector<InputData>& data, int& bestFeatureIndex, double& bestThreshold);

    TreeNode* buildDecisionTree(const std::vector<InputData>& data, int depth);
};

#endif // RANDOMFOREST_H

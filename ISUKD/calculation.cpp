#include "calculation.h"
#include "randomforest.h"

#include <math.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

double normalPDF(double x, double mean, double stddev)
{
    double coefficient = 1.0 / (stddev * sqrt(2.0 * M_PI));
    double exponent = -0.5 * pow((x - mean) / stddev, 2.0);
    return coefficient * exp(exponent);
}

double calculationNS(quint64 data [20] [15], quint64 input [15])
{
    double prob = 0.0;
    double pdf [15];

    double sum [15];
    double mean [15];
    double variance [15];
    double stddev [15];
    double max [15];
    long double percent [15];

    //Calculated using nanosecond precision
    double dataProcess [20] [15];
    double inputProcess [15];
    double ns = 0;

    if (input [1] >= 1000000)
        ns = 1000000.0;
    else if (input [1] >= 1000)
        ns = 1000.0;
    else
        ns = 1.0;

    for (int i=0; i<20; i++)
    {
        for (int j=0; j<15; j++)
        {
            dataProcess [i] [j] = data [i] [j] / ns;
            inputProcess [j] = input [j] / ns;
        }
    }

    //Determin the number of digits entered
    int bits = 0;
    for (int j=0; j<15; j++)
    {
        if (data [1] [j] != 0)
            bits ++;
    }

    // Initialization
    for (int k=0; k<15; k++)
    {
        sum [k] = 0.0;
        mean [k] = 0.0;
        variance [k] = 0.0;
        pdf [k] = 0.0;
        max [k] = 0.0;
        percent [k] = 0.0;
    }

    // sum
    for (int j=0; j<bits; j++)
    {
        for (int i=0; i<20; i++)
            sum [j] = sum [j] + dataProcess [i] [j];
    }

    // mean
    for (int j=0; j<bits; j++)
        mean [j] = sum [j] / 20.0;

    // variance & stddev
    for (int j=0; j<bits; j++)
    {
        for (int i=0; i<20; i++)
            variance [j] = pow ((dataProcess [i] [j] - mean [j]), 2) + variance [j];

        variance [j] = variance [j] / 20;
        stddev [j] = sqrt(variance [j]);
    }

    //pdf & max & precent
    double a = 0;
    cout << "precent_ns: \n";
    for (int j=0; j<bits; j++)
    {
        pdf [j] = normalPDF(inputProcess [j], mean [j], stddev [j]);
        max [j] = normalPDF(mean [j], mean [j], stddev [j]);
        percent [j] = pdf [j] / max [j];

        //Debug
        cout << setw (15) << percent [j];
    }
    cout << "\n";

    int t=0;
    double b=0;
    for (int j=0; j<bits; j++)
    {
        if (percent [j] < 0.1)
            t++;
        else
            b = b + percent [j];
    }

    if (t >= bits / 4)
        prob = 0;
    else
        prob = b / (15 - t);

    //Debug
    cout << "Final probability_ns: " << prob << "\n";

    return prob;
}

double calculationMS (quint64 data [20] [15], quint64 input [15])
{
    double prob = 0.0;
    double pdf [15];

    double sum [15];
    double mean [15];
    double variance [15];
    double stddev [15];
    double max [15];
    long double percent [15];

    //Calculate using millisecond precision
    quint64 dataProcess [20] [15];
    quint64 inputProcess [15];
    int ms = 1000000;

    for (int i=0; i<20; i++)
    {
        for (int j=0; j<15; j++)
        {
            dataProcess [i] [j] = data [i] [j] / ms;
            inputProcess [j] = input [j] / ms;
        }
    }

    //Determin the number of digits entered
    int bits = 0;
    for (int j=0; j<15; j++)
    {
        if (data [1] [j] != 0)
            bits ++;
    }

    // Initialization
    for (int k=0; k<15; k++)
    {
        sum [k] = 0.0;
        mean [k] = 0.0;
        variance [k] = 0.0;
        pdf [k] = 0.0;
        max [k] = 0.0;
        percent [k] = 0.0;
    }

    // sum
    for (int j=0; j<bits; j++)
    {
        for (int i=0; i<20; i++)
            sum [j] = sum [j] + dataProcess [i] [j];
    }

    // mean
    for (int j=0; j<bits; j++)
        mean [j] = sum [j] / 20.0;

    // variance & stddev
    for (int j=0; j<bits; j++)
    {
        for (int i=0; i<20; i++)
            variance [j] = pow ((dataProcess [i] [j] - mean [j]), 2) + variance [j];

        variance [j] = variance [j] / 20;
        stddev [j] = sqrt(variance [j]);
    }

    //pdf & max & precent
    double a = 0;
    cout << "precent_ms: \n";
    for (int j=0; j<bits; j++)
    {
        pdf [j] = normalPDF(inputProcess [j], mean [j], stddev [j]);
        max [j] = normalPDF(mean [j], mean [j], stddev [j]);
        percent [j] = pdf [j] / max [j];

        //Debug
        cout << setw (15) << percent [j];
    }
    cout << "\n";

    int t=0;
    double b=0;
    for (int j=0; j<bits; j++)
    {
        if (percent [j] < 0.1)
            t++;
        else
            b = b + percent [j];
    }

    if (t > bits / 4)
        prob = 0;
    else
        prob = b / (15 - t);

    //Debug
    cout << "Final probability_ms: " << prob << "\n";

    return prob;
}

bool mathematical (quint64 dataPre [20] [15], quint64 dataBtw [20] [15], quint64 inputPre [15], quint64 inputBtw [15])
{
    //Result of using millisecond. (just show)
    double PpreMS = calculationMS(dataPre, inputPre);
    double PbtwMS = calculationMS(dataBtw, inputBtw);

    cout << "The result of using millisecond is: ";
    if (PpreMS > 0 && PbtwMS > 0)
    {
        cout << "log-in succcessful. \n";
    }
    else
    {
        cout << "log-in failed. \n";
    }

    //Result of using nanosecond. (output)
    double PpreNS = calculationNS(dataPre, inputPre);
    double PbtwNS = calculationNS(dataBtw, inputBtw);

    if (PpreNS > 0 && PbtwNS > 0)
    {
        return true;
    }
    else
        return false;
}



//machine learning part
bool machineLearning (quint64 dataPre [20] [15], quint64 dataBtw [20] [15], quint64 inputPre [15], quint64 inputBtw [15],
                      quint64 dataPreFalse [20] [15], quint64 dataBtwFalse[20] [15])
{
//    int numTreesPre = 0;
//    for (int j=0; j<15; j++)
//    {
//        if (dataPre [1] [j] != 0)
//            numTreesPre ++;
//    }
//    numTreesPre = (numTreesPre + 1) / 2 ;

//    int numTreesBtw = 0;
//    for (int j=0; j<15; j++)
//    {
//        if (dataPre [1] [j] != 0)
//            numTreesBtw ++;
//    }
//    numTreesBtw = (numTreesBtw + 1) / 2;

    int numTrees = 5;
    int maxDepth = 3;

    //Initialize PressingTime data
    vector<InputData> trainingDataPre;
    for (int i=0; i<20; i++)
    {
        InputData inputDataT;
        for (int j=0; j<15; j++)
        {
            inputDataT.input.push_back(dataPre [i] [j]);
        }
        inputDataT.isMatch = true;
        trainingDataPre.push_back(inputDataT);

        InputData inputDataF;
        for (int j=0; j<15; j++)
        {
            inputDataF.input.push_back(dataPreFalse [i] [j]);
        }
        inputDataF.isMatch = false;
        trainingDataPre.push_back(inputDataF);
    }

    //create randomForest
    randomForest randomForestPre(numTrees, maxDepth);

    //train model
    randomForestPre.train(trainingDataPre);

    //read input
    vector<quint64> inputPreTime;
    for (int j=0; j<15; j++)
    {
        inputPreTime.push_back(inputPre [j]);
    }

    //predict
    bool isMatchPre = randomForestPre.predict(inputPreTime);

    //debug
    cout << "Prediction (Pre): " << (isMatchPre ? "Match" : "Not Match") << endl;

    //Initialize PressBtwTime data
    vector<InputData> trainingDataBtw;
    for (int i=0; i<20; i++)
    {
        InputData inputDataT;
        for (int j=0; j<15; j++)
        {
            inputDataT.input.push_back(dataBtw[i][j]);
        }
        inputDataT.isMatch = true;
        trainingDataBtw.push_back(inputDataT);

        InputData inputDataF;
        for (int j=0; j<15; j++)
        {
            inputDataF.input.push_back(dataBtwFalse [i] [j]);
        }
        inputDataF.isMatch = false;
        trainingDataBtw.push_back(inputDataF);
    }

    //create random forest
    randomForest randomForestBtw(numTrees, maxDepth);

    //train model
    randomForestBtw.train(trainingDataPre);

    //read input
    vector<quint64> inputBtwTime;
    for (int j=0; j<15; j++)
    {
        inputPreTime.push_back(inputBtw [j]);
    }

    //predict
    bool isMatchBtw = randomForestBtw.predict(inputPreTime);

    //debug
    cout << "Prediction (Btw): " << (isMatchBtw ? "Match" : "Not Match") << endl;


    if (isMatchPre && isMatchBtw)
    {
        return true;
    }
    else
    {
        return false;
    }
}

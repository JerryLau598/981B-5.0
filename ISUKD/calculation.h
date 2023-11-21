#ifndef CALCULATION_H
#define CALCULATION_H

#include <QKeyEvent>

extern double calculationNS (quint64 data [20] [15], quint64 input [15]);

extern double calculationMS (quint64 data [20] [15], quint64 input [15]);

extern bool mathematical (quint64 dataPre [20] [15], quint64 dataBtw [20] [15], quint64 inputPre [15], quint64 inputBtw [15]);

extern bool machineLearning (quint64 dataPre [20] [15], quint64 dataBtw [20] [15], quint64 inputPre [15], quint64 inputBtw [15],
                                quint64 dataPreFalse [20] [15], quint64 dataBtwFalse[20] [15]);

#endif // CALCULATION_H

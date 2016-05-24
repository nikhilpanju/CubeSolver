#ifndef SOLVERSQ_H
#define SOLVERSQ_H


int possibleNRotate(QStringList list, int n);
int possibleNRotatei(QStringList list, int n);
void createCheckpointSQ();
void resetLocationSQ();
void U(int n);
void Uinv(int n);
void D(int n);
void Di(int n);
void S();
void convertString(QString &scram, int gui = 0);
void cubeShape();
void CO();
void EO();
int checkPLL(int layer);
void CP();
QString checkEP(int layer);
void EP();
void finalAdjusts();
QStringList shortSolutionSQ(QStringList &list);
void solveCubeSQ();
int findMoveCountSQ(QString &s);


#endif // SOLVERSQ_H

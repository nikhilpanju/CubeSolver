#ifndef SOLVER2X2
#define SOLVER2X2

void createCheckpoint2();
void resetLocation2();
void Cw_2(QString  &face, QString &face_temp);
void Ccw_2(QString &face, QString &face_temp);
void Cw2_2(QString &face, QString &face_temp);
void L_2();
void Li_2();
void R_2();
void Ri_2();
void U_2();
void Uinv_2();
void D_2();
void Di_2();
void F_2();
void Fi_2();
void B_2();
void Bi_2();
void L2_2();
void R2_2();
void U2_2();
void D2_2();
void F2_2();
void B2_2();
int identifyDPerm();
void convertScramble2(QString &scram);
int firstLayer();
char identifyUColour();
void secondLayer(int n);
void auf2();
QStringList shortSolution(QStringList &list);
int findMoveCount(QString &s);
void solveCube2x2();


#endif // SOLVER2X2


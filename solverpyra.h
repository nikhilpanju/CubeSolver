#ifndef SOLVERPYRA_H
#define SOLVERPYRA_H

void createCheckpointP();
void resetLocationP();
void L_P();
void Li_P();
void R_P();
void Ri_P();
void U_P();
void Ui_P();
void B_P();
void Bi_P();
void lT();
void liT();
void rT();
void riT();
void uT();
void uiT();
void bT();
void biT();
void l_P();
void li_P();
void r_P();
void ri_P();
void u_P();
void ui_P();
void b_P();
void bi_P();
void convertScrambleP(QString &scram);
void tips();
int blockPresent();
void firstBlock();
void centreLocation(int n[2]);
int mapNewCentreLocation(int n);
int newBlockLocation(int n);
void lastCentre();
int edgeLocation(QString &edgeColour);
int mapNewEdgeLocation(int n);
void backEdge();
QStringList identifyLastThreeEdges();
void lastThreeEdges();
QStringList shortSolutionP(QStringList &list);
int findMoveCount(QString &s);
void solveCubePyra();

#endif // SOLVERPYRA_H

#include <iostream>
#include "Map.h"


using namespace std;

int mapMain() {
	Map newGameMap("America");

	/*
	North America=7
	Central America=4
	South America=3
	*/
	newGameMap.insertContinent("North America", 7);
	newGameMap.insertContinent("Central America", 4);
	newGameMap.insertContinent("South America", 3);

	/*
	AA,40,120,North America,AB
	AB,105,155,North America,AA,AC,AF,AJ
	AC,130,130,North America,AB,AF,AG,AD
	AD,210,60,North America,AC,AG,AE,AI
	AE,305,80,North America,AD,AI
	AF,140,165,North America,AB,AC,AG,AJ,AK
	AG,170,165,North America,AF,AC,AD,AH,AK,AL
	AH,200,175,North America,AG,AI,AL,AM
	AI,235,170,North America,AH,AD,AE,AM
	AJ,120,210,North America,AB,AF,AK,AO,AN
	AK,145,205,North America,AJ,AF,AG,AL,AO
	AL,175,215,North America,AK,AG,AH,AM,AO
	AM,205,215,North America,AL,AH,AI,AP
	AN,40,250,North America,AJ,AT

	AO,160,250,Central America,AJ,AK,AL,AQ
	AP,215,260,Central America,AM,AQ,AS
	AQ,185,270,Central America,AO,AP,AR
	AR,230,300,Central America,AQ,AS,AT
	AS,255,300,Central America,AR,AP,AU,AV

	AT,230,335,South America,AN,AR,AU,AW,AX
	AU,260,340,South America,AT,AS,AV,AX
	AV,300,335,South America,AU,AS,AX
	AW,240,390,South America,AT,AX
	AX,260,395,South America,AW,AT,AU,AV
	*/
	//north america
	float aa_pos[] = { 40,120 };
	vector<string> aa_adj;
	aa_adj.push_back("AB");
	newGameMap.insertTerritory("AA", aa_pos, "North America",aa_adj);

	float ab_pos[] = { 105,155 };
	vector<string> ab_adj;
	ab_adj.push_back("AA");
	ab_adj.push_back("AC");
	ab_adj.push_back("AF");
	ab_adj.push_back("AJ");
	newGameMap.insertTerritory("AB", ab_pos, "North America", ab_adj);

	float ac_pos[] = { 130,130 };
	vector<string> ac_adj;
	ac_adj.push_back("AB");
	ac_adj.push_back("AF");
	ac_adj.push_back("AG");
	ac_adj.push_back("AD");
	newGameMap.insertTerritory("AC", ac_pos, "North America", ac_adj);

	float ad_pos[] = { 210,60 };
	vector<string> ad_adj;
	ad_adj.push_back("AC");
	ad_adj.push_back("AG");
	ad_adj.push_back("AE");
	ad_adj.push_back("AI");
	newGameMap.insertTerritory("AD", ad_pos, "North America", ad_adj);

	float ae_pos[] = { 305,80 };
	vector<string> ae_adj;
	ae_adj.push_back("AD");
	ae_adj.push_back("AI");
	newGameMap.insertTerritory("AE", ae_pos, "North America", ae_adj);

	float af_pos[] = { 140,165 };
	vector<string> af_adj;
	af_adj.push_back("AB");
	af_adj.push_back("AC");
	af_adj.push_back("AG");
	af_adj.push_back("AJ");
	af_adj.push_back("AK");
	newGameMap.insertTerritory("AF", af_pos, "North America", af_adj);

	float ag_pos[] = { 170,165 };
	vector<string> ag_adj;
	ag_adj.push_back("AF");
	ag_adj.push_back("AC");
	ag_adj.push_back("AD");
	ag_adj.push_back("AH");
	ag_adj.push_back("AK");
	ag_adj.push_back("AL");
	newGameMap.insertTerritory("AG", ag_pos, "North America", ag_adj);

	float ah_pos[] = { 200,175 };
	vector<string> ah_adj;
	ah_adj.push_back("AG");
	ah_adj.push_back("AI");
	ah_adj.push_back("AL");
	ah_adj.push_back("AM");
	newGameMap.insertTerritory("AH", ah_pos, "North America", ah_adj);

	float ai_pos[] = { 235,170 };
	vector<string> ai_adj;
	ai_adj.push_back("AH");
	ai_adj.push_back("AD");
	ai_adj.push_back("AE");
	ai_adj.push_back("AM");
	newGameMap.insertTerritory("AI", ai_pos, "North America", ai_adj);

	float aj_pos[] = { 120,210 };
	vector<string> aj_adj;
	aj_adj.push_back("AB");
	aj_adj.push_back("AF");
	aj_adj.push_back("AK");
	aj_adj.push_back("AO");
	aj_adj.push_back("AN");
	newGameMap.insertTerritory("AJ", aj_pos, "North America", aj_adj);

	float ak_pos[] = { 145,205 };
	vector<string> ak_adj;
	ak_adj.push_back("AJ");
	ak_adj.push_back("AF");
	ak_adj.push_back("AG");
	ak_adj.push_back("AL");
	ak_adj.push_back("AO");
	newGameMap.insertTerritory("AK", ak_pos, "North America", ak_adj);

	float al_pos[] = { 175,215 };
	vector<string> al_adj;
	al_adj.push_back("AK");
	al_adj.push_back("AG");
	al_adj.push_back("AH");
	al_adj.push_back("AM");
	al_adj.push_back("AO");
	newGameMap.insertTerritory("AL", al_pos, "North America", al_adj);

	float am_pos[] = { 205,215 };
	vector<string> am_adj;
	am_adj.push_back("AL");
	am_adj.push_back("AH");
	am_adj.push_back("AI");
	am_adj.push_back("AP");
	newGameMap.insertTerritory("AM", am_pos, "North America", am_adj);

	float an_pos[] = { 40,250 };
	vector<string> an_adj;
	an_adj.push_back("AJ");
	an_adj.push_back("AT");
	newGameMap.insertTerritory("AN", an_pos, "North America", an_adj);
	
	//central america
	float ao_pos[] = { 160,250 };
	vector<string> ao_adj;
	ao_adj.push_back("AJ");
	ao_adj.push_back("AK");
	ao_adj.push_back("AL");
	ao_adj.push_back("AQ");
	newGameMap.insertTerritory("AO", ao_pos, "Central America", ao_adj);

	float ap_pos[] = { 215,260 };
	vector<string> ap_adj;
	ap_adj.push_back("AM");
	ap_adj.push_back("AQ");
	ap_adj.push_back("AS");
	newGameMap.insertTerritory("AP", ap_pos, "Central America", ap_adj);

	float aq_pos[] = { 185,270 };
	vector<string> aq_adj;
	aq_adj.push_back("AO");
	aq_adj.push_back("AP");
	aq_adj.push_back("AR");
	newGameMap.insertTerritory("AQ", aq_pos, "Central America", aq_adj);

	float ar_pos[] = { 230,300 };
	vector<string> ar_adj;
	ar_adj.push_back("AQ");
	ar_adj.push_back("AS");
	ar_adj.push_back("AT");
	newGameMap.insertTerritory("AR", ar_pos, "Central America", ar_adj);

	float as_pos[] = { 255,300 };
	vector<string> as_adj;
	as_adj.push_back("AR");
	as_adj.push_back("AP");
	as_adj.push_back("AU");
	as_adj.push_back("AV");
	newGameMap.insertTerritory("AS", as_pos, "Central America", as_adj);
	
	//south america
	float at_pos[] = { 230,335 };
	vector<string> at_adj;
	at_adj.push_back("AN");
	at_adj.push_back("AR");
	at_adj.push_back("AU");
	at_adj.push_back("AW");
	at_adj.push_back("AX");
	newGameMap.insertTerritory("AT", at_pos, "South America", at_adj);

	float au_pos[] = { 260,340 };
	vector<string> au_adj;
	au_adj.push_back("AT");
	au_adj.push_back("AS");
	au_adj.push_back("AV");
	au_adj.push_back("AX");
	newGameMap.insertTerritory("AU", au_pos, "South America", au_adj);

	float av_pos[] = { 300,335 };
	vector<string> av_adj;
	av_adj.push_back("AU");
	av_adj.push_back("AS");
	av_adj.push_back("AX");
	newGameMap.insertTerritory("AV", av_pos, "South America", av_adj);

	float aw_pos[] = { 240,390 };
	vector<string> aw_adj;
	aw_adj.push_back("AT");
	aw_adj.push_back("AX");
	newGameMap.insertTerritory("AW", aw_pos, "South America", aw_adj);

	float ax_pos[] = { 260,395 };
	vector<string> ax_adj;
	ax_adj.push_back("AW");
	ax_adj.push_back("AT");
	ax_adj.push_back("AU");
	ax_adj.push_back("AV");
	newGameMap.insertTerritory("AX", ax_pos, "South America", ax_adj);

	newGameMap.LinkAllTerri();
	newGameMap.linkAdj();

	newGameMap.displayConti();
	newGameMap.displayTerri();

	system("PAUSE");

	return 0;
}
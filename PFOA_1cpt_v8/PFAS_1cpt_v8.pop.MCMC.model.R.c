/* PFAS_1cpt_v8.pop.MCMC.model.R.c
   ___________________________________________________

   Model File:  PFAS_1cpt_v8.pop.MCMC.model.R

   Date:  Sun Jan 23 12:21:10 2022

   Created by:  "./MCSim/mod.exe v6.1.0"
    -- a model preprocessor by Don Maszle
   ___________________________________________________

   Copyright (c) 1993-2019 Free Software Foundation, Inc.

   Model calculations for compartmental model:

   1 State:
     Cserum_t -> 0.0;

   9 Outputs:
     Cbgd_Css -> 0.0;
     Cserum -> 0.0;
     M_Cbgd_Css -> 0.0;
     M_Cserum -> 0.0;
     Cbgd = -1;
     C_0 = -1;
     k = -1;
     Vd = -1;
     DWI_BW_d = -1;

   6 Inputs:
     DWC (is a function)
     DWC_t (is a function)
     Cbgd_in_gm (is a function)
     Cbgd_in_gsd (is a function)
     C_0_in_gm (is a function)
     C_0_in_gsd (is a function)

   20 Parameters:
     M_ln_Cbgd_sc = 0;
     M_ln_C_0_sc = 0;
     M_ln_k = -2.5367;
     M_ln_Vd = -1.3863;
     M_ln_DWI_BW_d = -4.395473;
     SD_ln_Cbgd_sc = 1;
     SD_ln_C_0_sc = 1;
     V_ln_k = 0;
     SD_ln_Vd = 0;
     SD_ln_DWI_BW_d = 0.8880025;
     ln_Cbgd = 0;
     ln_C_0 = 0;
     ln_k = 0;
     ln_Vd = 0;
     ln_DWI_BW_d = 0;
     GSD_M_Cserum = 1.2;
     GSD_Cserum = 1.2;
     GSD_M_Cbgd_Css = 1.2;
     GSD_Cbgd_Css = 1.2;
     DWC_belowMRL = 1e-30;
*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include "modelu.h"
#include "random.h"
#include "yourcode.h"


/*----- Indices to Global Variables */

/* Model variables: States and other outputs */
#define ID_Cserum_t 0x00000
#define ID_Cbgd_Css 0x00001
#define ID_Cserum 0x00002
#define ID_M_Cbgd_Css 0x00003
#define ID_M_Cserum 0x00004
#define ID_Cbgd 0x00005
#define ID_C_0 0x00006
#define ID_k 0x00007
#define ID_Vd 0x00008
#define ID_DWI_BW_d 0x00009

/* Inputs */
#define ID_DWC 0x00000
#define ID_DWC_t 0x00001
#define ID_Cbgd_in_gm 0x00002
#define ID_Cbgd_in_gsd 0x00003
#define ID_C_0_in_gm 0x00004
#define ID_C_0_in_gsd 0x00005

/* Parameters */
#define ID_M_ln_Cbgd_sc 0x00010
#define ID_M_ln_C_0_sc 0x00011
#define ID_M_ln_k 0x00012
#define ID_M_ln_Vd 0x00013
#define ID_M_ln_DWI_BW_d 0x00014
#define ID_SD_ln_Cbgd_sc 0x00015
#define ID_SD_ln_C_0_sc 0x00016
#define ID_V_ln_k 0x00017
#define ID_SD_ln_Vd 0x00018
#define ID_SD_ln_DWI_BW_d 0x00019
#define ID_ln_Cbgd 0x0001a
#define ID_ln_C_0 0x0001b
#define ID_ln_k 0x0001c
#define ID_ln_Vd 0x0001d
#define ID_ln_DWI_BW_d 0x0001e
#define ID_GSD_M_Cserum 0x0001f
#define ID_GSD_Cserum 0x00020
#define ID_GSD_M_Cbgd_Css 0x00021
#define ID_GSD_Cbgd_Css 0x00022
#define ID_DWC_belowMRL 0x00023


/*----- Global Variables */

/* For export. Keep track of who we are. */
char szModelDescFilename[] = "PFAS_1cpt_v8.pop.MCMC.model.R";
char szModelSourceFilename[] = __FILE__;
char szModelGenAndVersion[] = "./MCSim/mod.exe v6.1.0";

/* Externs */
extern BOOL vbModelReinitd;

/* Model Dimensions */
int vnStates = 1;
int vnOutputs = 9;
int vnModelVars = 10;
int vnInputs = 6;
int vnParms = 20;

/* States and Outputs*/
double vrgModelVars[10];

/* Inputs */
IFN vrgInputs[6];

/* Parameters */
double M_ln_Cbgd_sc;
double M_ln_C_0_sc;
double M_ln_k;
double M_ln_Vd;
double M_ln_DWI_BW_d;
double SD_ln_Cbgd_sc;
double SD_ln_C_0_sc;
double V_ln_k;
double SD_ln_Vd;
double SD_ln_DWI_BW_d;
double ln_Cbgd;
double ln_C_0;
double ln_k;
double ln_Vd;
double ln_DWI_BW_d;
double GSD_M_Cserum;
double GSD_Cserum;
double GSD_M_Cbgd_Css;
double GSD_Cbgd_Css;
double DWC_belowMRL;

BOOL bDelays = 0;


/*----- Global Variable Map */

VMMAPSTRCT vrgvmGlo[] = {
  {"Cserum_t", (PVOID) &vrgModelVars[ID_Cserum_t], ID_STATE | ID_Cserum_t},
  {"Cbgd_Css", (PVOID) &vrgModelVars[ID_Cbgd_Css], ID_OUTPUT | ID_Cbgd_Css},
  {"Cserum", (PVOID) &vrgModelVars[ID_Cserum], ID_OUTPUT | ID_Cserum},
  {"M_Cbgd_Css", (PVOID) &vrgModelVars[ID_M_Cbgd_Css], ID_OUTPUT | ID_M_Cbgd_Css},
  {"M_Cserum", (PVOID) &vrgModelVars[ID_M_Cserum], ID_OUTPUT | ID_M_Cserum},
  {"Cbgd", (PVOID) &vrgModelVars[ID_Cbgd], ID_OUTPUT | ID_Cbgd},
  {"C_0", (PVOID) &vrgModelVars[ID_C_0], ID_OUTPUT | ID_C_0},
  {"k", (PVOID) &vrgModelVars[ID_k], ID_OUTPUT | ID_k},
  {"Vd", (PVOID) &vrgModelVars[ID_Vd], ID_OUTPUT | ID_Vd},
  {"DWI_BW_d", (PVOID) &vrgModelVars[ID_DWI_BW_d], ID_OUTPUT | ID_DWI_BW_d},
  {"DWC", (PVOID) &vrgInputs[ID_DWC], ID_INPUT | ID_DWC},
  {"DWC_t", (PVOID) &vrgInputs[ID_DWC_t], ID_INPUT | ID_DWC_t},
  {"Cbgd_in_gm", (PVOID) &vrgInputs[ID_Cbgd_in_gm], ID_INPUT | ID_Cbgd_in_gm},
  {"Cbgd_in_gsd", (PVOID) &vrgInputs[ID_Cbgd_in_gsd], ID_INPUT | ID_Cbgd_in_gsd},
  {"C_0_in_gm", (PVOID) &vrgInputs[ID_C_0_in_gm], ID_INPUT | ID_C_0_in_gm},
  {"C_0_in_gsd", (PVOID) &vrgInputs[ID_C_0_in_gsd], ID_INPUT | ID_C_0_in_gsd},
  {"M_ln_Cbgd_sc", (PVOID) &M_ln_Cbgd_sc, ID_PARM | ID_M_ln_Cbgd_sc},
  {"M_ln_C_0_sc", (PVOID) &M_ln_C_0_sc, ID_PARM | ID_M_ln_C_0_sc},
  {"M_ln_k", (PVOID) &M_ln_k, ID_PARM | ID_M_ln_k},
  {"M_ln_Vd", (PVOID) &M_ln_Vd, ID_PARM | ID_M_ln_Vd},
  {"M_ln_DWI_BW_d", (PVOID) &M_ln_DWI_BW_d, ID_PARM | ID_M_ln_DWI_BW_d},
  {"SD_ln_Cbgd_sc", (PVOID) &SD_ln_Cbgd_sc, ID_PARM | ID_SD_ln_Cbgd_sc},
  {"SD_ln_C_0_sc", (PVOID) &SD_ln_C_0_sc, ID_PARM | ID_SD_ln_C_0_sc},
  {"V_ln_k", (PVOID) &V_ln_k, ID_PARM | ID_V_ln_k},
  {"SD_ln_Vd", (PVOID) &SD_ln_Vd, ID_PARM | ID_SD_ln_Vd},
  {"SD_ln_DWI_BW_d", (PVOID) &SD_ln_DWI_BW_d, ID_PARM | ID_SD_ln_DWI_BW_d},
  {"ln_Cbgd", (PVOID) &ln_Cbgd, ID_PARM | ID_ln_Cbgd},
  {"ln_C_0", (PVOID) &ln_C_0, ID_PARM | ID_ln_C_0},
  {"ln_k", (PVOID) &ln_k, ID_PARM | ID_ln_k},
  {"ln_Vd", (PVOID) &ln_Vd, ID_PARM | ID_ln_Vd},
  {"ln_DWI_BW_d", (PVOID) &ln_DWI_BW_d, ID_PARM | ID_ln_DWI_BW_d},
  {"GSD_M_Cserum", (PVOID) &GSD_M_Cserum, ID_PARM | ID_GSD_M_Cserum},
  {"GSD_Cserum", (PVOID) &GSD_Cserum, ID_PARM | ID_GSD_Cserum},
  {"GSD_M_Cbgd_Css", (PVOID) &GSD_M_Cbgd_Css, ID_PARM | ID_GSD_M_Cbgd_Css},
  {"GSD_Cbgd_Css", (PVOID) &GSD_Cbgd_Css, ID_PARM | ID_GSD_Cbgd_Css},
  {"DWC_belowMRL", (PVOID) &DWC_belowMRL, ID_PARM | ID_DWC_belowMRL},
  {"", NULL, 0} /* End flag */
};  /* vrgpvmGlo[] */


/*----- InitModel
   Should be called to initialize model variables at
   the beginning of experiment before reading
   variants from the simulation spec file.
*/

void InitModel(void)
{
  /* Initialize things in the order that they appear in
     model definition file so that dependencies are
     handled correctly. */

  vrgModelVars[ID_Cserum_t] = 0.0;
  vrgInputs[ID_DWC].iType = IFN_CONSTANT;
  vrgInputs[ID_DWC].dTStartPeriod = 0;
  vrgInputs[ID_DWC].bOn = FALSE;
  vrgInputs[ID_DWC].dMag = 0.000000;
  vrgInputs[ID_DWC].dT0 = 0.000000;
  vrgInputs[ID_DWC].dTexp = 0.000000;
  vrgInputs[ID_DWC].dDecay = 0.000000;
  vrgInputs[ID_DWC].dTper = 0.000000;
  vrgInputs[ID_DWC].hMag = 0;
  vrgInputs[ID_DWC].hT0 = 0;
  vrgInputs[ID_DWC].hTexp = 0;
  vrgInputs[ID_DWC].hDecay = 0;
  vrgInputs[ID_DWC].hTper = 0;
  vrgInputs[ID_DWC].dVal = 0.0;
  vrgInputs[ID_DWC].nDoses = 0;
  vrgInputs[ID_DWC_t].iType = IFN_CONSTANT;
  vrgInputs[ID_DWC_t].dTStartPeriod = 0;
  vrgInputs[ID_DWC_t].bOn = FALSE;
  vrgInputs[ID_DWC_t].dMag = 0.000000;
  vrgInputs[ID_DWC_t].dT0 = 0.000000;
  vrgInputs[ID_DWC_t].dTexp = 0.000000;
  vrgInputs[ID_DWC_t].dDecay = 0.000000;
  vrgInputs[ID_DWC_t].dTper = 0.000000;
  vrgInputs[ID_DWC_t].hMag = 0;
  vrgInputs[ID_DWC_t].hT0 = 0;
  vrgInputs[ID_DWC_t].hTexp = 0;
  vrgInputs[ID_DWC_t].hDecay = 0;
  vrgInputs[ID_DWC_t].hTper = 0;
  vrgInputs[ID_DWC_t].dVal = 0.0;
  vrgInputs[ID_DWC_t].nDoses = 0;
  vrgInputs[ID_Cbgd_in_gm].iType = IFN_CONSTANT;
  vrgInputs[ID_Cbgd_in_gm].dTStartPeriod = 0;
  vrgInputs[ID_Cbgd_in_gm].bOn = FALSE;
  vrgInputs[ID_Cbgd_in_gm].dMag = 0.000000;
  vrgInputs[ID_Cbgd_in_gm].dT0 = 0.000000;
  vrgInputs[ID_Cbgd_in_gm].dTexp = 0.000000;
  vrgInputs[ID_Cbgd_in_gm].dDecay = 0.000000;
  vrgInputs[ID_Cbgd_in_gm].dTper = 0.000000;
  vrgInputs[ID_Cbgd_in_gm].hMag = 0;
  vrgInputs[ID_Cbgd_in_gm].hT0 = 0;
  vrgInputs[ID_Cbgd_in_gm].hTexp = 0;
  vrgInputs[ID_Cbgd_in_gm].hDecay = 0;
  vrgInputs[ID_Cbgd_in_gm].hTper = 0;
  vrgInputs[ID_Cbgd_in_gm].dVal = 0.0;
  vrgInputs[ID_Cbgd_in_gm].nDoses = 0;
  vrgInputs[ID_Cbgd_in_gsd].iType = IFN_CONSTANT;
  vrgInputs[ID_Cbgd_in_gsd].dTStartPeriod = 0;
  vrgInputs[ID_Cbgd_in_gsd].bOn = FALSE;
  vrgInputs[ID_Cbgd_in_gsd].dMag = 0.000000;
  vrgInputs[ID_Cbgd_in_gsd].dT0 = 0.000000;
  vrgInputs[ID_Cbgd_in_gsd].dTexp = 0.000000;
  vrgInputs[ID_Cbgd_in_gsd].dDecay = 0.000000;
  vrgInputs[ID_Cbgd_in_gsd].dTper = 0.000000;
  vrgInputs[ID_Cbgd_in_gsd].hMag = 0;
  vrgInputs[ID_Cbgd_in_gsd].hT0 = 0;
  vrgInputs[ID_Cbgd_in_gsd].hTexp = 0;
  vrgInputs[ID_Cbgd_in_gsd].hDecay = 0;
  vrgInputs[ID_Cbgd_in_gsd].hTper = 0;
  vrgInputs[ID_Cbgd_in_gsd].dVal = 0.0;
  vrgInputs[ID_Cbgd_in_gsd].nDoses = 0;
  vrgInputs[ID_C_0_in_gm].iType = IFN_CONSTANT;
  vrgInputs[ID_C_0_in_gm].dTStartPeriod = 0;
  vrgInputs[ID_C_0_in_gm].bOn = FALSE;
  vrgInputs[ID_C_0_in_gm].dMag = 0.000000;
  vrgInputs[ID_C_0_in_gm].dT0 = 0.000000;
  vrgInputs[ID_C_0_in_gm].dTexp = 0.000000;
  vrgInputs[ID_C_0_in_gm].dDecay = 0.000000;
  vrgInputs[ID_C_0_in_gm].dTper = 0.000000;
  vrgInputs[ID_C_0_in_gm].hMag = 0;
  vrgInputs[ID_C_0_in_gm].hT0 = 0;
  vrgInputs[ID_C_0_in_gm].hTexp = 0;
  vrgInputs[ID_C_0_in_gm].hDecay = 0;
  vrgInputs[ID_C_0_in_gm].hTper = 0;
  vrgInputs[ID_C_0_in_gm].dVal = 0.0;
  vrgInputs[ID_C_0_in_gm].nDoses = 0;
  vrgInputs[ID_C_0_in_gsd].iType = IFN_CONSTANT;
  vrgInputs[ID_C_0_in_gsd].dTStartPeriod = 0;
  vrgInputs[ID_C_0_in_gsd].bOn = FALSE;
  vrgInputs[ID_C_0_in_gsd].dMag = 0.000000;
  vrgInputs[ID_C_0_in_gsd].dT0 = 0.000000;
  vrgInputs[ID_C_0_in_gsd].dTexp = 0.000000;
  vrgInputs[ID_C_0_in_gsd].dDecay = 0.000000;
  vrgInputs[ID_C_0_in_gsd].dTper = 0.000000;
  vrgInputs[ID_C_0_in_gsd].hMag = 0;
  vrgInputs[ID_C_0_in_gsd].hT0 = 0;
  vrgInputs[ID_C_0_in_gsd].hTexp = 0;
  vrgInputs[ID_C_0_in_gsd].hDecay = 0;
  vrgInputs[ID_C_0_in_gsd].hTper = 0;
  vrgInputs[ID_C_0_in_gsd].dVal = 0.0;
  vrgInputs[ID_C_0_in_gsd].nDoses = 0;
  vrgModelVars[ID_Cbgd_Css] = 0.0;
  vrgModelVars[ID_Cserum] = 0.0;
  vrgModelVars[ID_M_Cbgd_Css] = 0.0;
  vrgModelVars[ID_M_Cserum] = 0.0;
  M_ln_Cbgd_sc = 0;
  M_ln_C_0_sc = 0;
  M_ln_k = -2.5367;
  M_ln_Vd = -1.3863;
  M_ln_DWI_BW_d = -4.395473;
  SD_ln_Cbgd_sc = 1;
  SD_ln_C_0_sc = 1;
  V_ln_k = 0;
  SD_ln_Vd = 0;
  SD_ln_DWI_BW_d = 0.8880025;
  ln_Cbgd = 0;
  ln_C_0 = 0;
  ln_k = 0;
  ln_Vd = 0;
  ln_DWI_BW_d = 0;
  vrgModelVars[ID_Cbgd] = -1;
  vrgModelVars[ID_C_0] = -1;
  vrgModelVars[ID_k] = -1;
  vrgModelVars[ID_Vd] = -1;
  vrgModelVars[ID_DWI_BW_d] = -1;
  GSD_M_Cserum = 1.2;
  GSD_Cserum = 1.2;
  GSD_M_Cbgd_Css = 1.2;
  GSD_Cbgd_Css = 1.2;
  DWC_belowMRL = 1e-30;

  vbModelReinitd = TRUE;

} /* InitModel */


/*----- Dynamics section */

void CalcDeriv (double  rgModelVars[], double  rgDerivs[], PDOUBLE pdTime)
{

  CalcInputs (pdTime); /* Get new input vals */


  rgDerivs[ID_Cserum_t] = rgModelVars[ID_DWI_BW_d] * 365.25 * vrgInputs[ID_DWC_t].dVal / rgModelVars[ID_Vd] + rgModelVars[ID_k] * ( rgModelVars[ID_Cbgd] - rgModelVars[ID_Cserum_t] ) ;

} /* CalcDeriv */


/*----- Model scaling */

void ScaleModel (PDOUBLE pdTime)
{

  vrgModelVars[ID_Cbgd] = ( vrgModelVars[ID_Cbgd] < 0 ) ? ( vrgInputs[ID_Cbgd_in_gm].dVal * exp ( M_ln_Cbgd_sc + SD_ln_Cbgd_sc * log ( vrgInputs[ID_Cbgd_in_gsd].dVal ) * ln_Cbgd ) ) : vrgModelVars[ID_Cbgd] ;

  vrgModelVars[ID_C_0] = ( vrgModelVars[ID_C_0] < 0 ) ? ( vrgInputs[ID_C_0_in_gm].dVal * exp ( M_ln_C_0_sc + SD_ln_C_0_sc * log ( vrgInputs[ID_C_0_in_gsd].dVal ) * ln_C_0 ) ) : vrgModelVars[ID_C_0] ;
  vrgModelVars[ID_k] = ( vrgModelVars[ID_k] < 0 ) ? exp ( M_ln_k + pow ( V_ln_k , 0.5 ) * ln_k ) : vrgModelVars[ID_k] ;
  vrgModelVars[ID_Vd] = ( vrgModelVars[ID_Vd] < 0 ) ? exp ( M_ln_Vd + SD_ln_Vd * ln_Vd ) : vrgModelVars[ID_Vd] ;

  vrgModelVars[ID_DWI_BW_d] = ( vrgModelVars[ID_DWI_BW_d] < 0 ) ? exp ( M_ln_DWI_BW_d + SD_ln_DWI_BW_d * ln_DWI_BW_d ) : vrgModelVars[ID_DWI_BW_d] ;
  vrgModelVars[ID_Cserum_t] = vrgModelVars[ID_C_0] ;

} /* ScaleModel */


/*----- Jacobian calculations */

void CalcJacob (PDOUBLE pdTime, double rgModelVars[],
                long column, double rgdJac[])
{

} /* CalcJacob */


/*----- Outputs calculations */

void CalcOutputs (double  rgModelVars[], double  rgDerivs[], PDOUBLE pdTime)
{
  /* local */ double M_Cbgd;
  /* local */ double mu_Css;
  /* local */ double V_Css;
  /* local */ double M_Css;
  /* local */ double M_kt;
  /* local */ double V_kt;
  /* local */ double mu_Cbgd_expkt;
  /* local */ double V_Cbgd_expkt;
  /* local */ double M_Cbgd_expkt;
  /* local */ double mu_C_0_expkt;
  /* local */ double V_C_0_expkt;
  /* local */ double M_C_0_expkt;
  /* local */ double mu_Css_expkt;
  /* local */ double V_Css_expkt;
  /* local */ double M_Css_expkt;
  /* local */ double Css;

  M_Cbgd = vrgInputs[ID_Cbgd_in_gm].dVal * exp ( M_ln_Cbgd_sc + pow ( SD_ln_Cbgd_sc * log ( vrgInputs[ID_Cbgd_in_gsd].dVal ) , 2 ) / 2 ) ;

  mu_Css = M_ln_DWI_BW_d + log ( 365.25 ) + log ( vrgInputs[ID_DWC].dVal ) - M_ln_k - M_ln_Vd ;
  V_Css = pow ( SD_ln_DWI_BW_d , 2 ) + V_ln_k + pow ( SD_ln_Vd , 2 ) ;
  M_Css = exp ( mu_Css + V_Css / 2 ) ;

  M_kt = - (*pdTime) * exp ( M_ln_k + V_ln_k / 2 ) ;
  V_kt = ( exp ( V_ln_k ) -1 ) * pow ( M_kt , 2 ) ;

  mu_Cbgd_expkt = log ( vrgInputs[ID_Cbgd_in_gm].dVal ) + M_ln_Cbgd_sc + M_kt ;
  V_Cbgd_expkt = pow ( SD_ln_Cbgd_sc * log ( vrgInputs[ID_Cbgd_in_gsd].dVal ) , 2 ) + V_kt ;
  M_Cbgd_expkt = exp ( mu_Cbgd_expkt + V_Cbgd_expkt / 2 ) ;

  mu_C_0_expkt = log ( vrgInputs[ID_C_0_in_gm].dVal ) + M_ln_C_0_sc + M_kt ;
  V_C_0_expkt = pow ( SD_ln_C_0_sc * log ( vrgInputs[ID_C_0_in_gsd].dVal ) , 2 ) + V_kt ;
  M_C_0_expkt = exp ( mu_C_0_expkt + V_C_0_expkt / 2 ) ;

  mu_Css_expkt = M_ln_DWI_BW_d + log ( 365.25 * vrgInputs[ID_DWC].dVal ) - M_ln_k - M_ln_Vd + M_kt ;
  V_Css_expkt = pow ( SD_ln_DWI_BW_d , 2 ) + V_ln_k + pow ( SD_ln_Vd , 2 ) + V_kt ;
  M_Css_expkt = exp ( mu_Css_expkt + V_Css_expkt / 2 ) ;

  rgModelVars[ID_M_Cbgd_Css] = M_Cbgd + M_Css_expkt ;

  rgModelVars[ID_M_Cserum] = M_Cbgd + M_C_0_expkt - M_Cbgd_expkt + M_Css - M_Css_expkt ;

  Css = rgModelVars[ID_DWI_BW_d] * 365.25 * vrgInputs[ID_DWC].dVal / ( rgModelVars[ID_k] * rgModelVars[ID_Vd] ) ;

  rgModelVars[ID_Cbgd_Css] = rgModelVars[ID_Cbgd] + Css * exp ( - rgModelVars[ID_k] * (*pdTime) ) ;

  rgModelVars[ID_Cserum] = rgModelVars[ID_Cbgd] + ( rgModelVars[ID_C_0] - rgModelVars[ID_Cbgd] ) * exp ( - rgModelVars[ID_k] * (*pdTime) ) + Css * ( 1 - exp ( - rgModelVars[ID_k] * (*pdTime) ) ) ;

  rgModelVars[ID_Cbgd] = rgModelVars[ID_Cbgd] ;
  rgModelVars[ID_C_0] = rgModelVars[ID_C_0] ;
  rgModelVars[ID_k] = rgModelVars[ID_k] ;
  rgModelVars[ID_Vd] = rgModelVars[ID_Vd] ;
  rgModelVars[ID_DWI_BW_d] = rgModelVars[ID_DWI_BW_d] ;

}  /* CalcOutputs */



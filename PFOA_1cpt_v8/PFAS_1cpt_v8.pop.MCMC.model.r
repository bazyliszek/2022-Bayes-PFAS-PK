# Description ####
# Generic single PFAS one-compartment model 
#
# Units: 
# - time in years (yr) or days (d) [365.25 days/year]
# - volumes in liters (L)
# - PFAS in micrograms (ug)
#
# Population model including error variance
############
# Version 4 - includes ODE in addition to analytic solution
#   For single time point only, must assume constant drinking water concentration
#     and study state.  Thus, use DWC and compare to
#     Cbgd_Css - individual
#     M_Cbgd_Css - population mean
#   For multiple time points, but constant drinking water concentration,
#     use DWC and compare to
#     Cserum - individual
#     M_Cserum - population mean
#   For multiple time points, but time-varying drinking water concentration,
#     use DWC_t and compare to
#     Cserum_t - individual (cannot do population mean)
############
# Version 6 
#   Added provision for DWC below reporting level
#     For each study, sample DWC_belowMRL from a distribution 
#     (e.g., Uniform from 0 to MRL)
#     In each simulation, set DWC = DWC_belowMRL;
#     Then compare to Cserum or M_Cserum
#   Made into a single generic PFAS model
#   Removed unused parameters (MW, BW)
#   Clarified comments
############
# Version 7
#   Separate GSD_error for Cbgd_Css
############
# Version 8
#   Cbgd_Css includes possible intervention at time interval t before measurement
#   both for individual and population mean

States = {
  Cserum_t # ODE solution for time-varying DWC
};

Inputs = { DWC, # Drinking water concentration (ug/L) (constant)
  DWC_t, # Drinking water concentration (ug/L) (time-varying)
  Cbgd_in_gm, # Background concentration GM (central estimate)
  Cbgd_in_gsd, # Background concentration GSD (central estimate)
  C_0_in_gm, # Initial concentration GM (central estimate)
  C_0_in_gsd}; # Initial concentration GSD (central estimate)

Outputs = { 
  # Individual predictions
  Cbgd_Css, Cserum,   # Serum concentration (ug/L) including background
  # Population predictions
  M_Cbgd_Css, M_Cserum, 
  # Individual parameters
  Cbgd, C_0, k, Vd, DWI_BW_d
  };

# Population Mean Parameters
M_ln_Cbgd_sc = 0; # Background serum concentration scaling (e.g., 2.7 ug/L)
M_ln_C_0_sc = 0; # Initial serum concentration scaling (e.g., 1 ug/L)
M_ln_k = -2.5367; # Elimination rate (e.g., 0.07912639 1/yr)
M_ln_Vd =  -1.3863; # Distribution volume (e.g., 0.25 L/kg; from MN 2019 DOH information)
M_ln_DWI_BW_d = -4.395473; # Drinking water intake per kg body weight (e.g., 0.00933 L/(kg d)) See fit_distributions.docx for calculation

# Population SD or Variance Parameters
SD_ln_Cbgd_sc = 1; # Background serum concentration scaling (ug/L)
SD_ln_C_0_sc = 1; # Initial serum concentration scaling (ug/L)
V_ln_k = 0; # Elimination rate (1/yr)
SD_ln_Vd = 0; # Distribution volume (L/kg)
SD_ln_DWI_BW_d = 0.8880025; # Drinking water intake. See fit_distributions.docx for calculation

# Individual parameters, log tranformed, z-score
ln_Cbgd = 0; # Background serum concentration (ug/L)
ln_C_0 = 0; # Initial serum concentration (ug/L) 
ln_k = 0; # Elimination rate (1/yr)
ln_Vd = 0; # Distribution volume (L/kg)
ln_DWI_BW_d = 0; # Drinking water intake per kg body weight (L/(kg d))

# Individual Parameters - only can be fixed at individual level (would override sampled values)
Cbgd = -1; # Background serum concentration (ug/L)
C_0 = -1; # Initial serum concentration (ug/L)
k = -1; # Elimination rate (1/yr)
Vd = -1; # Distribution volume (L/kg)
DWI_BW_d = -1; # Drinking water intake per kg body weight (L/(kg d))

# Error GSD
GSD_M_Cserum = 1.2;
GSD_Cserum = 1.2;
GSD_M_Cbgd_Css = 1.2;
GSD_Cbgd_Css = 1.2;

# DWC below reporting limit
DWC_belowMRL = 1e-30;

Initialize {
  # If specified in simulation file (so >= 0), then use that value
  # Otherwise use sampled value
  Cbgd = (Cbgd < 0) ? 
    (Cbgd_in_gm * exp(M_ln_Cbgd_sc + SD_ln_Cbgd_sc * log(Cbgd_in_gsd) * ln_Cbgd )) : Cbgd;
  C_0 = (C_0 < 0) ? 
    (C_0_in_gm * exp(M_ln_C_0_sc + SD_ln_C_0_sc * log(C_0_in_gsd) * ln_C_0 )) : C_0;
  k = (k < 0) ? exp(M_ln_k + pow(V_ln_k,0.5) * ln_k) : k;
  Vd = (Vd < 0) ? exp(M_ln_Vd + SD_ln_Vd * ln_Vd) : Vd;
  DWI_BW_d = (DWI_BW_d < 0) ? 
    exp(M_ln_DWI_BW_d + SD_ln_DWI_BW_d * ln_DWI_BW_d) : DWI_BW_d;
  Cserum_t = C_0;
}

Dynamics { # only for DWC_t time-varying
  dt(Cserum_t) = DWI_BW_d * 365.25 * DWC_t / Vd + k*(Cbgd - Cserum_t);
}

CalcOutputs { 
  
  # Population - exact or approximate arith. mean 
  # Arith mean of Background
  M_Cbgd = Cbgd_in_gm * exp(M_ln_Cbgd_sc + pow(SD_ln_Cbgd_sc * log(Cbgd_in_gsd),2)/2);
  # Arith mean of Css from drinking water
  mu_Css = M_ln_DWI_BW_d + log(365.25) + log(DWC) - M_ln_k - M_ln_Vd;
  V_Css = pow(SD_ln_DWI_BW_d,2) + V_ln_k + pow(SD_ln_Vd,2);
  M_Css = exp(mu_Css + V_Css/2);
  # Approximating -kt by normal with matching mean and variance  
  M_kt = -t*exp(M_ln_k + V_ln_k/2);
  V_kt = (exp(V_ln_k)-1)*pow(M_kt,2);
  # Arith mean of Background * exp(-kt)
  mu_Cbgd_expkt = log(Cbgd_in_gm) + M_ln_Cbgd_sc + M_kt;
  V_Cbgd_expkt = pow(SD_ln_Cbgd_sc * log(Cbgd_in_gsd),2) + V_kt;
  M_Cbgd_expkt = exp(mu_Cbgd_expkt + V_Cbgd_expkt/2);
  # Arith mean of C_0 * exp(-kt)
  mu_C_0_expkt = log(C_0_in_gm) + M_ln_C_0_sc + M_kt;
  V_C_0_expkt = pow(SD_ln_C_0_sc * log(C_0_in_gsd),2) + V_kt;
  M_C_0_expkt = exp(mu_C_0_expkt + V_C_0_expkt/2);
  # Arith mean of Css from drinking water * exp(-kt)
  mu_Css_expkt = M_ln_DWI_BW_d + log(365.25 * DWC) - M_ln_k - M_ln_Vd + M_kt;
  V_Css_expkt = pow(SD_ln_DWI_BW_d,2) + V_ln_k + pow(SD_ln_Vd,2) + V_kt;
  M_Css_expkt = exp(mu_Css_expkt + V_Css_expkt/2);
  # Arith mean of Cbgd + Css*exp(-kt) from drinking water
  M_Cbgd_Css = M_Cbgd + M_Css_expkt;
  # Serum concentration as a function of time
  M_Cserum = M_Cbgd + M_C_0_expkt - M_Cbgd_expkt + M_Css - M_Css_expkt;

  # Individual
  Css = DWI_BW_d * 365.25 * DWC / (k * Vd);
  # Cbgd + Css*exp(-kt) from drinking water
  Cbgd_Css = Cbgd + Css * exp(-k*t);
  # time-dependent Cserum with constant DWC
  Cserum = Cbgd + (C_0 - Cbgd) * exp(-k*t) + Css * (1 - exp(-k*t));

  # Individual Parameters
  Cbgd = Cbgd;
  C_0 = C_0;
  k = k;
  Vd = Vd;
  DWI_BW_d = DWI_BW_d;
}

End.

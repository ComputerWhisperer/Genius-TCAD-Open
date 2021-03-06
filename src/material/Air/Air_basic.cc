/*****************************************************************************/
/*                                                                           */
/*              8888888         88888888         88888888                    */
/*            8                8                8                            */
/*           8                 8                8                            */
/*           8                  88888888         88888888                    */
/*           8      8888                8                8                   */
/*            8       8                 8                8                   */
/*              888888         888888888        888888888                    */
/*                                                                           */
/*       A Two-Dimensional General Purpose Semiconductor Simulator.          */
/*                                                                           */
/*  GSS material database Version 0.4                                        */
/*  Last update: Feb 17, 2006                                                */
/*                                                                           */
/*  Gong Ding                                                                */
/*  gdiso@ustc.edu                                                           */
/*  NINT, No.69 P.O.Box, Xi'an City, China                                   */
/*                                                                           */
/*****************************************************************************/
//
// Material Type: Air


#include "PMI.h"

class GSS_Air_BasicParameter : public PMII_BasicParameter
{
private:
  PetscScalar PERMITTI;  // The relative dielectric permittivity of Air.
  PetscScalar PERMEABI;  // The relative megnetic permeability of Air.
  PetscScalar AFFINITY;  // The electron affinity for the material.
  PetscScalar DENSITY;   // Specific mass density for the material.

  void   Basic_Init()
  {
    PERMITTI = 1.0;
    PERMEABI = 1.0;
    AFFINITY = 0.0*eV;
    DENSITY  = 1.290000e-06*kg*std::pow(cm,-3);

#ifdef __CALIBRATE__
    parameter_map.insert(para_item("PERMITTI",    PARA("PERMITTI",    "The relative dielectric permittivity", "-", 1.0, &PERMITTI)) );
    parameter_map.insert(para_item("PERMEABI",  PARA("PERMEABI",  "The relative megnetic permeability ", "-", 1.0, &PERMEABI)) );
    parameter_map.insert(para_item("AFFINITY", PARA("AFFINITY", "The electron affinity for the material", "eV", eV, &AFFINITY)) );
    parameter_map.insert(para_item("DENSITY", PARA("DENSITY", "Specific mass density for the material", "kg*cm^-3", kg*std::pow(cm,-3), &DENSITY)) );
#endif
  }
public:
  PetscScalar Density       (const PetscScalar &Tl) const { return DENSITY;  }
  PetscScalar Permittivity  ()                      const { return PERMITTI; }
  PetscScalar Permeability  ()                      const { return PERMEABI; }
  PetscScalar Affinity      (const PetscScalar &Tl) const { return AFFINITY; }

  PetscScalar Conductance   (const PetscScalar &Tl, const PetscScalar &E) const
  { return 1.0/(1e+30*V/A*m); }
  AutoDScalar Conductance   (const AutoDScalar &Tl, const AutoDScalar &E) const
  { return 1.0/(1e+30*V/A*m); }

  PetscScalar RadConductance(const PetscScalar &DRate)const
  { return 0.0; }

  PetscScalar RadGenRate   (const PetscScalar &E) const
  { return 0.0; }

  PetscScalar ElecMobility      (const PetscScalar &Tl) const
  { return 1e-15*cm*cm/V/s; }

  PetscScalar HoleMobility      (const PetscScalar &Tl) const
  { return 5e-11*cm*cm/V/s; }

  void G4Material(std::vector<Atom> &atoms, std::vector<double> & fraction) const
  {
    atoms.push_back(Atom("Oxygen",   "O", 8, 16.0)); //Oxygen
    atoms.push_back(Atom("Nitrogen", "N", 7, 14.01)); //Nitrogen

    fraction.push_back(0.3);
    fraction.push_back(0.7);
  }


  GSS_Air_BasicParameter(const PMII_Environment &env):PMII_BasicParameter(env)
  {
    Basic_Init();
  }
  ~GSS_Air_BasicParameter()
  {
  }
}
;

extern "C"
{
  DLL_EXPORT_DECLARE  PMII_BasicParameter* PMII_Air_BasicParameter_Default (const PMII_Environment& env)
  {
    return new GSS_Air_BasicParameter(env);
  }
}

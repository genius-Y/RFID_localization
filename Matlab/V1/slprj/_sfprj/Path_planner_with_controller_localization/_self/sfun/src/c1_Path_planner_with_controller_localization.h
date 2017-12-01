#ifndef __c1_Path_planner_with_controller_localization_h__
#define __c1_Path_planner_with_controller_localization_h__

/* Type Definitions */
#ifndef typedef_SFc1_Path_planner_with_controller_localizationInstanceStruct
#define typedef_SFc1_Path_planner_with_controller_localizationInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_Path_planner_with_controller_localization;
  void *c1_fEmlrtCtx;
  real_T *c1_k1;
  real_T *c1_v;
  real_T *c1_k2;
  real_T *c1_b_v;
  real_T *c1_l;
  real_T *c1_etheta;
  real_T *c1_kappa;
  real_T *c1_omega;
} SFc1_Path_planner_with_controller_localizationInstanceStruct;

#endif                                 /*typedef_SFc1_Path_planner_with_controller_localizationInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c1_Path_planner_with_controller_localization_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c1_Path_planner_with_controller_localization_get_check_sum
  (mxArray *plhs[]);
extern void c1_Path_planner_with_controller_localization_method_dispatcher
  (SimStruct *S, int_T method, void *data);

#endif

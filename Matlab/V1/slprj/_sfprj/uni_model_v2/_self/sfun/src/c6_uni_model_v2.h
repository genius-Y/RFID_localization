#ifndef __c6_uni_model_v2_h__
#define __c6_uni_model_v2_h__

/* Type Definitions */
#ifndef typedef_SFc6_uni_model_v2InstanceStruct
#define typedef_SFc6_uni_model_v2InstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c6_sfEvent;
  boolean_T c6_doneDoubleBufferReInit;
  uint8_T c6_is_active_c6_uni_model_v2;
  void *c6_fEmlrtCtx;
  real_T (*c6_m)[6];
  real_T (*c6_xi)[8];
  real_T (*c6_i)[2];
  real_T (*c6_P_post_prev)[64];
  real_T (*c6_xi_post)[8];
  real_T (*c6_P_post)[64];
  real_T *c6_xk;
  real_T *c6_yk;
} SFc6_uni_model_v2InstanceStruct;

#endif                                 /*typedef_SFc6_uni_model_v2InstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c6_uni_model_v2_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c6_uni_model_v2_get_check_sum(mxArray *plhs[]);
extern void c6_uni_model_v2_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif

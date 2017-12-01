#ifndef __c2_untitled_h__
#define __c2_untitled_h__

/* Type Definitions */
#ifndef typedef_SFc2_untitledInstanceStruct
#define typedef_SFc2_untitledInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_untitled;
  void *c2_fEmlrtCtx;
  real_T (*c2_x_in)[8];
  real_T (*c2_x_out)[8];
  real_T *c2_vl;
  real_T *c2_vr;
  real_T *c2_x_post;
  real_T *c2_y_post;
  real_T *c2_dx_post;
  real_T *c2_dy_post;
  real_T *c2_ddx_post;
  real_T *c2_ddy_post;
  real_T *c2_th_post;
  real_T *c2_dth_post;
  real_T *c2_dt;
} SFc2_untitledInstanceStruct;

#endif                                 /*typedef_SFc2_untitledInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_untitled_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_untitled_get_check_sum(mxArray *plhs[]);
extern void c2_untitled_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif

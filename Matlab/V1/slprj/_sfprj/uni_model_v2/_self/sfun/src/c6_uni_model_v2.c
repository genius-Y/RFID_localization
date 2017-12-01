/* Include files */

#include "uni_model_v2_sfun.h"
#include "c6_uni_model_v2.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "uni_model_v2_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c6_debug_family_names[31] = { "d", "dt", "x", "y", "dx",
  "dy", "ddx", "ddy", "th", "dphi", "phi", "vl", "vr", "xi_prio", "A", "Q",
  "P_prio", "zhat", "C", "R", "K", "nargin", "nargout", "m", "xi", "i",
  "P_post_prev", "xi_post", "P_post", "xk", "yk" };

/* Function Declarations */
static void initialize_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance);
static void initialize_params_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance);
static void enable_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance);
static void disable_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance);
static void c6_update_debugger_state_c6_uni_model_v2
  (SFc6_uni_model_v2InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c6_uni_model_v2
  (SFc6_uni_model_v2InstanceStruct *chartInstance);
static void set_sim_state_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance, const mxArray *c6_st);
static void finalize_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance);
static void sf_gateway_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance);
static void mdl_start_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance);
static void c6_chartstep_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance);
static void initSimStructsc6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber, uint32_T c6_instanceNumber);
static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData);
static real_T c6_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_b_yk, const char_T *c6_identifier);
static real_T c6_b_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_c_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_b_P_post, const char_T *c6_identifier, real_T c6_y[64]);
static void c6_d_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[64]);
static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_e_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_b_xi_post, const char_T *c6_identifier, real_T c6_y[8]);
static void c6_f_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[8]);
static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static const mxArray *c6_e_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static const mxArray *c6_f_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_g_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[48]);
static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_g_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_h_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[36]);
static void c6_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_h_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_i_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[48]);
static void c6_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static void c6_j_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[6]);
static void c6_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static real_T c6_cosd(SFc6_uni_model_v2InstanceStruct *chartInstance, real_T
                      c6_x);
static real_T c6_sind(SFc6_uni_model_v2InstanceStruct *chartInstance, real_T
                      c6_x);
static void c6_mrdivide(SFc6_uni_model_v2InstanceStruct *chartInstance, real_T
  c6_A[48], real_T c6_B[36], real_T c6_y[48]);
static void c6_check_forloop_overflow_error(SFc6_uni_model_v2InstanceStruct
  *chartInstance, boolean_T c6_overflow);
static void c6_warning(SFc6_uni_model_v2InstanceStruct *chartInstance);
static const mxArray *c6_i_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static int32_T c6_k_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static uint8_T c6_l_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct
  *chartInstance, const mxArray *c6_b_is_active_c6_uni_model_v2, const char_T
  *c6_identifier);
static uint8_T c6_m_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_b_cosd(SFc6_uni_model_v2InstanceStruct *chartInstance, real_T
                      *c6_x);
static void c6_b_sind(SFc6_uni_model_v2InstanceStruct *chartInstance, real_T
                      *c6_x);
static void c6_b_mrdivide(SFc6_uni_model_v2InstanceStruct *chartInstance, real_T
  c6_A[48], real_T c6_B[36]);
static void init_dsm_address_info(SFc6_uni_model_v2InstanceStruct *chartInstance);
static void init_simulink_io_address(SFc6_uni_model_v2InstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc6_uni_model_v2(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c6_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c6_is_active_c6_uni_model_v2 = 0U;
}

static void initialize_params_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c6_update_debugger_state_c6_uni_model_v2
  (SFc6_uni_model_v2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c6_uni_model_v2
  (SFc6_uni_model_v2InstanceStruct *chartInstance)
{
  const mxArray *c6_st;
  const mxArray *c6_y = NULL;
  const mxArray *c6_b_y = NULL;
  const mxArray *c6_c_y = NULL;
  real_T c6_hoistedGlobal;
  const mxArray *c6_d_y = NULL;
  real_T c6_b_hoistedGlobal;
  const mxArray *c6_e_y = NULL;
  uint8_T c6_c_hoistedGlobal;
  const mxArray *c6_f_y = NULL;
  c6_st = NULL;
  c6_st = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createcellmatrix(5, 1), false);
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", *chartInstance->c6_P_post, 0, 0U, 1U,
    0U, 2, 8, 8), false);
  sf_mex_setcell(c6_y, 0, c6_b_y);
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", *chartInstance->c6_xi_post, 0, 0U,
    1U, 0U, 1, 8), false);
  sf_mex_setcell(c6_y, 1, c6_c_y);
  c6_hoistedGlobal = *chartInstance->c6_xk;
  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", &c6_hoistedGlobal, 0, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c6_y, 2, c6_d_y);
  c6_b_hoistedGlobal = *chartInstance->c6_yk;
  c6_e_y = NULL;
  sf_mex_assign(&c6_e_y, sf_mex_create("y", &c6_b_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c6_y, 3, c6_e_y);
  c6_c_hoistedGlobal = chartInstance->c6_is_active_c6_uni_model_v2;
  c6_f_y = NULL;
  sf_mex_assign(&c6_f_y, sf_mex_create("y", &c6_c_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c6_y, 4, c6_f_y);
  sf_mex_assign(&c6_st, c6_y, false);
  return c6_st;
}

static void set_sim_state_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance, const mxArray *c6_st)
{
  const mxArray *c6_u;
  real_T c6_dv0[64];
  int32_T c6_i0;
  real_T c6_dv1[8];
  int32_T c6_i1;
  chartInstance->c6_doneDoubleBufferReInit = true;
  c6_u = sf_mex_dup(c6_st);
  c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 0)),
                        "P_post", c6_dv0);
  for (c6_i0 = 0; c6_i0 < 64; c6_i0++) {
    (*chartInstance->c6_P_post)[c6_i0] = c6_dv0[c6_i0];
  }

  c6_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 1)),
                        "xi_post", c6_dv1);
  for (c6_i1 = 0; c6_i1 < 8; c6_i1++) {
    (*chartInstance->c6_xi_post)[c6_i1] = c6_dv1[c6_i1];
  }

  *chartInstance->c6_xk = c6_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 2)), "xk");
  *chartInstance->c6_yk = c6_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 3)), "yk");
  chartInstance->c6_is_active_c6_uni_model_v2 = c6_l_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 4)),
     "is_active_c6_uni_model_v2");
  sf_mex_destroy(&c6_u);
  c6_update_debugger_state_c6_uni_model_v2(chartInstance);
  sf_mex_destroy(&c6_st);
}

static void finalize_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance)
{
  int32_T c6_i2;
  int32_T c6_i3;
  int32_T c6_i4;
  int32_T c6_i5;
  int32_T c6_i6;
  int32_T c6_i7;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c6_sfEvent);
  for (c6_i2 = 0; c6_i2 < 64; c6_i2++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c6_P_post_prev)[c6_i2], 3U);
  }

  for (c6_i3 = 0; c6_i3 < 2; c6_i3++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c6_i)[c6_i3], 2U);
  }

  for (c6_i4 = 0; c6_i4 < 8; c6_i4++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c6_xi)[c6_i4], 1U);
  }

  for (c6_i5 = 0; c6_i5 < 6; c6_i5++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c6_m)[c6_i5], 0U);
  }

  chartInstance->c6_sfEvent = CALL_EVENT;
  c6_chartstep_c6_uni_model_v2(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_uni_model_v2MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c6_i6 = 0; c6_i6 < 8; c6_i6++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c6_xi_post)[c6_i6], 4U);
  }

  for (c6_i7 = 0; c6_i7 < 64; c6_i7++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c6_P_post)[c6_i7], 5U);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c6_xk, 6U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c6_yk, 7U);
}

static void mdl_start_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void c6_chartstep_c6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance)
{
  int32_T c6_i8;
  int32_T c6_i9;
  real_T c6_b_m[6];
  int32_T c6_i10;
  real_T c6_b_xi[8];
  int32_T c6_i11;
  real_T c6_b_i[2];
  uint32_T c6_debug_family_var_map[31];
  real_T c6_b_P_post_prev[64];
  real_T c6_d;
  real_T c6_dt;
  real_T c6_x;
  real_T c6_y;
  real_T c6_dx;
  real_T c6_dy;
  real_T c6_ddx;
  real_T c6_ddy;
  real_T c6_th;
  real_T c6_dphi;
  real_T c6_phi;
  real_T c6_vl;
  real_T c6_vr;
  real_T c6_xi_prio[8];
  real_T c6_A[64];
  real_T c6_Q[64];
  real_T c6_P_prio[64];
  real_T c6_zhat[6];
  real_T c6_C[48];
  real_T c6_R[36];
  real_T c6_K[48];
  real_T c6_nargin = 4.0;
  real_T c6_nargout = 4.0;
  real_T c6_b_xi_post[8];
  real_T c6_b_P_post[64];
  real_T c6_b_xk;
  real_T c6_b_yk;
  real_T c6_b_A;
  real_T c6_d0;
  real_T c6_c_A;
  real_T c6_d1;
  real_T c6_d_A;
  real_T c6_e_A;
  real_T c6_d2;
  real_T c6_f_A;
  real_T c6_d3;
  real_T c6_g_A;
  real_T c6_d4;
  real_T c6_h_A;
  real_T c6_d5;
  real_T c6_i_A;
  real_T c6_d6;
  real_T c6_j_A;
  real_T c6_d7;
  real_T c6_k_A;
  real_T c6_l_A;
  real_T c6_m_A;
  real_T c6_d8;
  real_T c6_n_A;
  real_T c6_d9;
  real_T c6_o_A;
  real_T c6_d10;
  real_T c6_p_A;
  real_T c6_d11;
  real_T c6_q_A;
  int32_T c6_i12;
  int32_T c6_i13;
  int32_T c6_i14;
  static real_T c6_dv2[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 };

  int32_T c6_i15;
  int32_T c6_i16;
  static real_T c6_dv3[8] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 };

  int32_T c6_i17;
  int32_T c6_i18;
  static real_T c6_dv4[8] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.1 };

  int32_T c6_i19;
  static real_T c6_dv5[8] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  int32_T c6_i20;
  int32_T c6_j;
  int32_T c6_b_j;
  static real_T c6_dv6[8] = { 0.01, 0.01, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1 };

  int32_T c6_i21;
  int32_T c6_i22;
  real_T c6_a[64];
  real_T c6_alpha1;
  real_T c6_b[64];
  real_T c6_beta1;
  char_T c6_TRANSB;
  char_T c6_TRANSA;
  int32_T c6_i23;
  ptrdiff_t c6_m_t;
  real_T c6_b_y[64];
  ptrdiff_t c6_n_t;
  ptrdiff_t c6_k_t;
  ptrdiff_t c6_lda_t;
  ptrdiff_t c6_ldb_t;
  ptrdiff_t c6_ldc_t;
  int32_T c6_i24;
  int32_T c6_i25;
  real_T c6_b_alpha1;
  int32_T c6_i26;
  real_T c6_b_beta1;
  int32_T c6_i27;
  char_T c6_b_TRANSB;
  char_T c6_b_TRANSA;
  int32_T c6_i28;
  ptrdiff_t c6_b_m_t;
  real_T c6_c_y[64];
  ptrdiff_t c6_b_n_t;
  ptrdiff_t c6_b_k_t;
  ptrdiff_t c6_b_lda_t;
  ptrdiff_t c6_b_ldb_t;
  ptrdiff_t c6_b_ldc_t;
  int32_T c6_i29;
  real_T c6_d12;
  real_T c6_d13;
  real_T c6_d14;
  real_T c6_d15;
  int32_T c6_i30;
  int32_T c6_i31;
  int32_T c6_i32;
  real_T c6_b_a[48];
  static real_T c6_dv7[8] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c6_i33;
  static real_T c6_dv8[8] = { 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c6_i34;
  int32_T c6_i35;
  int32_T c6_i36;
  static real_T c6_dv9[8] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };

  int32_T c6_i37;
  int32_T c6_i38;
  int32_T c6_i39;
  real_T c6_b_b[8];
  int32_T c6_i40;
  real_T c6_d16;
  int32_T c6_i41;
  int32_T c6_i42;
  real_T c6_d17;
  real_T c6_d18;
  real_T c6_d19;
  real_T c6_d20;
  real_T c6_d21;
  real_T c6_d22;
  real_T c6_d23;
  int32_T c6_i43;
  int32_T c6_i44;
  int32_T c6_i45;
  int32_T c6_i46;
  int32_T c6_i47;
  int32_T c6_i48;
  int32_T c6_i49;
  int32_T c6_i50;
  int32_T c6_i51;
  int32_T c6_c_j;
  int32_T c6_d_j;
  static real_T c6_dv10[6] = { 1.0, 1.0, 0.099999999999999992,
    0.099999999999999992, 0.01, 0.01 };

  int32_T c6_i52;
  int32_T c6_i53;
  int32_T c6_i54;
  int32_T c6_i55;
  int32_T c6_i56;
  int32_T c6_i57;
  int32_T c6_i58;
  real_T c6_c_b[48];
  int32_T c6_i59;
  int32_T c6_i60;
  int32_T c6_i61;
  int32_T c6_i62;
  int32_T c6_i63;
  int32_T c6_i64;
  int32_T c6_i65;
  int32_T c6_i66;
  real_T c6_d_b[48];
  int32_T c6_i67;
  int32_T c6_i68;
  int32_T c6_i69;
  real_T c6_dv11[48];
  int32_T c6_i70;
  int32_T c6_i71;
  real_T c6_c_a[36];
  int32_T c6_i72;
  int32_T c6_i73;
  int32_T c6_i74;
  int32_T c6_i75;
  int32_T c6_i76;
  real_T c6_d_a[48];
  int32_T c6_i77;
  int32_T c6_i78;
  int32_T c6_i79;
  real_T c6_d24;
  int32_T c6_i80;
  int32_T c6_i81;
  int32_T c6_i82;
  int32_T c6_i83;
  real_T c6_e_b[6];
  real_T c6_d25;
  int32_T c6_i84;
  int32_T c6_i85;
  int32_T c6_i86;
  int32_T c6_k;
  int32_T c6_b_k;
  int32_T c6_i87;
  int32_T c6_i88;
  int32_T c6_i89;
  int32_T c6_i90;
  int32_T c6_i91;
  int32_T c6_i92;
  int32_T c6_i93;
  int32_T c6_i94;
  real_T c6_d26;
  real_T c6_c_alpha1;
  int32_T c6_i95;
  real_T c6_c_beta1;
  int32_T c6_i96;
  int32_T c6_i97;
  char_T c6_c_TRANSB;
  char_T c6_c_TRANSA;
  int32_T c6_i98;
  ptrdiff_t c6_c_m_t;
  ptrdiff_t c6_c_n_t;
  ptrdiff_t c6_c_k_t;
  ptrdiff_t c6_c_lda_t;
  ptrdiff_t c6_c_ldb_t;
  ptrdiff_t c6_c_ldc_t;
  int32_T c6_i99;
  int32_T c6_i100;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c6_sfEvent);
  for (c6_i8 = 0; c6_i8 < 6; c6_i8++) {
    c6_b_m[c6_i8] = (*chartInstance->c6_m)[c6_i8];
  }

  for (c6_i9 = 0; c6_i9 < 8; c6_i9++) {
    c6_b_xi[c6_i9] = (*chartInstance->c6_xi)[c6_i9];
  }

  for (c6_i10 = 0; c6_i10 < 2; c6_i10++) {
    c6_b_i[c6_i10] = (*chartInstance->c6_i)[c6_i10];
  }

  for (c6_i11 = 0; c6_i11 < 64; c6_i11++) {
    c6_b_P_post_prev[c6_i11] = (*chartInstance->c6_P_post_prev)[c6_i11];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 31U, 31U, c6_debug_family_names,
    c6_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_d, 0U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_dt, 1U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_x, 2U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_y, 3U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_dx, 4U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_dy, 5U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_ddx, 6U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_ddy, 7U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_th, 8U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_dphi, 9U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_phi, 10U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_vl, 11U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_vr, 12U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_xi_prio, 13U, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_A, 14U, c6_b_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_Q, 15U, c6_b_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_P_prio, 16U, c6_b_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_zhat, 17U, c6_e_sf_marshallOut,
    c6_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_C, 18U, c6_h_sf_marshallOut,
    c6_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_R, 19U, c6_g_sf_marshallOut,
    c6_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_K, 20U, c6_f_sf_marshallOut,
    c6_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargin, 21U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargout, 22U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_b_m, 23U, c6_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_b_xi, 24U, c6_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_b_i, 25U, c6_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_b_P_post_prev, 26U, c6_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_b_xi_post, 27U, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_b_P_post, 28U, c6_b_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_b_xk, 29U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_b_yk, 30U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 4);
  c6_d = 0.15;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 4);
  c6_dt = 0.1;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 5);
  c6_x = c6_b_xi[0];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 5);
  c6_y = c6_b_xi[1];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 5);
  c6_dx = c6_b_xi[2];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 5);
  c6_dy = c6_b_xi[3];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 5);
  c6_ddx = c6_b_xi[4];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 5);
  c6_ddy = c6_b_xi[5];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 5);
  c6_th = c6_b_xi[6];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 5);
  c6_dphi = c6_b_xi[7];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 6);
  c6_phi = c6_th + 0.5 * c6_dphi * c6_dt;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 7);
  c6_vl = c6_b_i[0];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 7);
  c6_vr = c6_b_i[1];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 8);
  c6_b_A = c6_ddx * 0.010000000000000002;
  c6_d0 = c6_phi;
  c6_b_cosd(chartInstance, &c6_d0);
  c6_c_A = c6_dt * c6_vl * c6_d0;
  c6_d1 = c6_phi;
  c6_b_cosd(chartInstance, &c6_d1);
  c6_d_A = c6_dt * c6_vr * c6_d1;
  c6_e_A = c6_ddy * 0.010000000000000002;
  c6_d2 = c6_phi;
  c6_b_sind(chartInstance, &c6_d2);
  c6_f_A = c6_dt * c6_vl * c6_d2;
  c6_d3 = c6_phi;
  c6_b_sind(chartInstance, &c6_d3);
  c6_g_A = c6_dt * c6_vr * c6_d3;
  c6_d4 = c6_phi;
  c6_b_cosd(chartInstance, &c6_d4);
  c6_h_A = c6_vl * c6_d4;
  c6_d5 = c6_phi;
  c6_b_cosd(chartInstance, &c6_d5);
  c6_i_A = c6_vr * c6_d5;
  c6_d6 = c6_phi;
  c6_b_sind(chartInstance, &c6_d6);
  c6_j_A = c6_vl * c6_d6;
  c6_d7 = c6_phi;
  c6_b_sind(chartInstance, &c6_d7);
  c6_k_A = c6_vr * c6_d7;
  c6_l_A = ((c6_d * c6_phi - c6_dt * c6_vl) + c6_dt * c6_vr) + c6_d * c6_dphi *
    c6_dt;
  c6_m_A = (c6_vr - c6_vl) + c6_d * c6_dphi;
  c6_xi_prio[0] = (((c6_x + c6_dt * c6_dx) + c6_b_A / 2.0) + c6_c_A / 2.0) +
    c6_d_A / 2.0;
  c6_xi_prio[1] = (((c6_y + c6_dt * c6_dy) + c6_e_A / 2.0) + c6_f_A / 2.0) +
    c6_g_A / 2.0;
  c6_xi_prio[2] = ((c6_dx + c6_ddx * c6_dt) + c6_h_A / 2.0) + c6_i_A / 2.0;
  c6_xi_prio[3] = ((c6_dy + c6_ddy * c6_dt) + c6_j_A / 2.0) + c6_k_A / 2.0;
  c6_xi_prio[4] = c6_ddx;
  c6_xi_prio[5] = c6_ddy;
  c6_xi_prio[6] = c6_l_A / 0.15;
  c6_xi_prio[7] = c6_m_A / 0.15;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 18);
  c6_d8 = c6_phi;
  c6_b_sind(chartInstance, &c6_d8);
  c6_n_A = -(c6_dt * c6_d8 * (c6_vl + c6_vr));
  c6_d9 = c6_phi;
  c6_b_cosd(chartInstance, &c6_d9);
  c6_o_A = c6_dt * c6_d9 * (c6_vl + c6_vr);
  c6_d10 = c6_phi;
  c6_b_sind(chartInstance, &c6_d10);
  c6_p_A = -(c6_d10 * (c6_vl + c6_vr));
  c6_d11 = c6_phi;
  c6_b_cosd(chartInstance, &c6_d11);
  c6_q_A = c6_d11 * (c6_vl + c6_vr);
  c6_A[0] = 1.0;
  c6_A[8] = 0.0;
  c6_A[16] = 0.1;
  c6_A[24] = 0.0;
  c6_A[32] = 0.005000000000000001;
  c6_A[40] = 0.0;
  c6_A[48] = c6_n_A / 2.0;
  c6_A[56] = 0.0;
  c6_A[1] = 0.0;
  c6_A[9] = 1.0;
  c6_A[17] = 0.0;
  c6_A[25] = 0.1;
  c6_A[33] = 0.0;
  c6_A[41] = 0.005000000000000001;
  c6_A[49] = c6_o_A / 2.0;
  c6_A[57] = 0.0;
  c6_A[2] = 0.0;
  c6_A[10] = 0.0;
  c6_A[18] = 1.0;
  c6_A[26] = 0.0;
  c6_A[34] = 0.1;
  c6_A[42] = 0.0;
  c6_A[50] = c6_p_A / 2.0;
  c6_A[58] = 0.0;
  c6_A[3] = 0.0;
  c6_A[11] = 0.0;
  c6_A[19] = 0.0;
  c6_A[27] = 1.0;
  c6_A[35] = 0.0;
  c6_A[43] = 0.1;
  c6_A[51] = c6_q_A / 2.0;
  c6_A[59] = 0.0;
  c6_i12 = 0;
  for (c6_i13 = 0; c6_i13 < 8; c6_i13++) {
    c6_A[c6_i12 + 4] = c6_dv2[c6_i13];
    c6_i12 += 8;
  }

  c6_i14 = 0;
  for (c6_i15 = 0; c6_i15 < 8; c6_i15++) {
    c6_A[c6_i14 + 5] = c6_dv3[c6_i15];
    c6_i14 += 8;
  }

  c6_i16 = 0;
  for (c6_i17 = 0; c6_i17 < 8; c6_i17++) {
    c6_A[c6_i16 + 6] = c6_dv4[c6_i17];
    c6_i16 += 8;
  }

  c6_i18 = 0;
  for (c6_i19 = 0; c6_i19 < 8; c6_i19++) {
    c6_A[c6_i18 + 7] = c6_dv5[c6_i19];
    c6_i18 += 8;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 27);
  for (c6_i20 = 0; c6_i20 < 64; c6_i20++) {
    c6_Q[c6_i20] = 0.0;
  }

  c6_j = 0;
  for (c6_b_j = 0; c6_b_j < 8; c6_b_j++) {
    c6_Q[c6_j] = c6_dv6[c6_b_j];
    c6_j += 9;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 28);
  for (c6_i21 = 0; c6_i21 < 64; c6_i21++) {
    c6_a[c6_i21] = c6_A[c6_i21];
  }

  for (c6_i22 = 0; c6_i22 < 64; c6_i22++) {
    c6_b[c6_i22] = c6_b_P_post_prev[c6_i22];
  }

  c6_alpha1 = 1.0;
  c6_beta1 = 0.0;
  c6_TRANSB = 'N';
  c6_TRANSA = 'N';
  for (c6_i23 = 0; c6_i23 < 64; c6_i23++) {
    c6_b_y[c6_i23] = 0.0;
  }

  c6_m_t = (ptrdiff_t)8;
  c6_n_t = (ptrdiff_t)8;
  c6_k_t = (ptrdiff_t)8;
  c6_lda_t = (ptrdiff_t)8;
  c6_ldb_t = (ptrdiff_t)8;
  c6_ldc_t = (ptrdiff_t)8;
  dgemm(&c6_TRANSA, &c6_TRANSB, &c6_m_t, &c6_n_t, &c6_k_t, &c6_alpha1, &c6_a[0],
        &c6_lda_t, &c6_b[0], &c6_ldb_t, &c6_beta1, &c6_b_y[0], &c6_ldc_t);
  c6_i24 = 0;
  for (c6_i25 = 0; c6_i25 < 8; c6_i25++) {
    c6_i26 = 0;
    for (c6_i27 = 0; c6_i27 < 8; c6_i27++) {
      c6_b[c6_i27 + c6_i24] = c6_A[c6_i26 + c6_i25];
      c6_i26 += 8;
    }

    c6_i24 += 8;
  }

  c6_b_alpha1 = 1.0;
  c6_b_beta1 = 0.0;
  c6_b_TRANSB = 'N';
  c6_b_TRANSA = 'N';
  for (c6_i28 = 0; c6_i28 < 64; c6_i28++) {
    c6_c_y[c6_i28] = 0.0;
  }

  c6_b_m_t = (ptrdiff_t)8;
  c6_b_n_t = (ptrdiff_t)8;
  c6_b_k_t = (ptrdiff_t)8;
  c6_b_lda_t = (ptrdiff_t)8;
  c6_b_ldb_t = (ptrdiff_t)8;
  c6_b_ldc_t = (ptrdiff_t)8;
  dgemm(&c6_b_TRANSA, &c6_b_TRANSB, &c6_b_m_t, &c6_b_n_t, &c6_b_k_t,
        &c6_b_alpha1, &c6_b_y[0], &c6_b_lda_t, &c6_b[0], &c6_b_ldb_t,
        &c6_b_beta1, &c6_c_y[0], &c6_b_ldc_t);
  for (c6_i29 = 0; c6_i29 < 64; c6_i29++) {
    c6_P_prio[c6_i29] = c6_c_y[c6_i29] + c6_Q[c6_i29];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 31);
  c6_d12 = c6_phi;
  c6_b_cosd(chartInstance, &c6_d12);
  c6_d13 = c6_phi;
  c6_b_sind(chartInstance, &c6_d13);
  c6_d14 = c6_phi;
  c6_b_sind(chartInstance, &c6_d14);
  c6_d15 = c6_phi;
  c6_b_cosd(chartInstance, &c6_d15);
  c6_i30 = 0;
  for (c6_i31 = 0; c6_i31 < 8; c6_i31++) {
    c6_b_a[c6_i30] = c6_dv7[c6_i31];
    c6_i30 += 6;
  }

  c6_i32 = 0;
  for (c6_i33 = 0; c6_i33 < 8; c6_i33++) {
    c6_b_a[c6_i32 + 1] = c6_dv8[c6_i33];
    c6_i32 += 6;
  }

  c6_b_a[2] = 0.0;
  c6_b_a[8] = 0.0;
  c6_b_a[14] = 0.0;
  c6_b_a[20] = 0.0;
  c6_b_a[26] = c6_d12;
  c6_b_a[32] = c6_d13;
  c6_b_a[38] = 0.0;
  c6_b_a[44] = 0.0;
  c6_b_a[3] = 0.0;
  c6_b_a[9] = 0.0;
  c6_b_a[15] = 0.0;
  c6_b_a[21] = 0.0;
  c6_b_a[27] = -c6_d14;
  c6_b_a[33] = c6_d15;
  c6_b_a[39] = 0.0;
  c6_b_a[45] = 0.0;
  c6_i34 = 0;
  for (c6_i35 = 0; c6_i35 < 8; c6_i35++) {
    c6_b_a[c6_i34 + 4] = c6_dv9[c6_i35];
    c6_i34 += 6;
  }

  c6_i36 = 0;
  for (c6_i37 = 0; c6_i37 < 8; c6_i37++) {
    c6_b_a[c6_i36 + 5] = c6_dv5[c6_i37];
    c6_i36 += 6;
  }

  for (c6_i38 = 0; c6_i38 < 8; c6_i38++) {
    c6_b_b[c6_i38] = c6_xi_prio[c6_i38];
  }

  for (c6_i39 = 0; c6_i39 < 6; c6_i39++) {
    c6_zhat[c6_i39] = 0.0;
  }

  for (c6_i40 = 0; c6_i40 < 6; c6_i40++) {
    c6_zhat[c6_i40] = 0.0;
    c6_i41 = 0;
    for (c6_i42 = 0; c6_i42 < 8; c6_i42++) {
      c6_zhat[c6_i40] += c6_b_a[c6_i41 + c6_i40] * c6_b_b[c6_i42];
      c6_i41 += 6;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 37);
  c6_d16 = c6_phi;
  c6_b_cosd(chartInstance, &c6_d16);
  c6_d17 = c6_phi;
  c6_b_sind(chartInstance, &c6_d17);
  c6_d18 = c6_phi;
  c6_b_cosd(chartInstance, &c6_d18);
  c6_d19 = c6_phi;
  c6_b_sind(chartInstance, &c6_d19);
  c6_d20 = c6_phi;
  c6_b_sind(chartInstance, &c6_d20);
  c6_d21 = c6_phi;
  c6_b_cosd(chartInstance, &c6_d21);
  c6_d22 = c6_phi;
  c6_b_cosd(chartInstance, &c6_d22);
  c6_d23 = c6_phi;
  c6_b_sind(chartInstance, &c6_d23);
  c6_i43 = 0;
  for (c6_i44 = 0; c6_i44 < 8; c6_i44++) {
    c6_C[c6_i43] = c6_dv7[c6_i44];
    c6_i43 += 6;
  }

  c6_i45 = 0;
  for (c6_i46 = 0; c6_i46 < 8; c6_i46++) {
    c6_C[c6_i45 + 1] = c6_dv8[c6_i46];
    c6_i45 += 6;
  }

  c6_C[2] = 0.0;
  c6_C[8] = 0.0;
  c6_C[14] = 0.0;
  c6_C[20] = 0.0;
  c6_C[26] = c6_d16;
  c6_C[32] = c6_d17;
  c6_C[38] = c6_ddy * c6_d18 - c6_ddx * c6_d19;
  c6_C[44] = 0.0;
  c6_C[3] = 0.0;
  c6_C[9] = 0.0;
  c6_C[15] = 0.0;
  c6_C[21] = 0.0;
  c6_C[27] = -c6_d20;
  c6_C[33] = c6_d21;
  c6_C[39] = -c6_ddx * c6_d22 - c6_ddy * c6_d23;
  c6_C[45] = 0.0;
  c6_i47 = 0;
  for (c6_i48 = 0; c6_i48 < 8; c6_i48++) {
    c6_C[c6_i47 + 4] = c6_dv9[c6_i48];
    c6_i47 += 6;
  }

  c6_i49 = 0;
  for (c6_i50 = 0; c6_i50 < 8; c6_i50++) {
    c6_C[c6_i49 + 5] = c6_dv5[c6_i50];
    c6_i49 += 6;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 43);
  for (c6_i51 = 0; c6_i51 < 36; c6_i51++) {
    c6_R[c6_i51] = 0.0;
  }

  c6_c_j = 0;
  for (c6_d_j = 0; c6_d_j < 6; c6_d_j++) {
    c6_R[c6_c_j] = c6_dv10[c6_d_j];
    c6_c_j += 7;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 44);
  for (c6_i52 = 0; c6_i52 < 64; c6_i52++) {
    c6_a[c6_i52] = c6_P_prio[c6_i52];
  }

  c6_i53 = 0;
  for (c6_i54 = 0; c6_i54 < 6; c6_i54++) {
    c6_i56 = 0;
    for (c6_i57 = 0; c6_i57 < 8; c6_i57++) {
      c6_c_b[c6_i57 + c6_i53] = c6_C[c6_i56 + c6_i54];
      c6_i56 += 6;
    }

    c6_i53 += 8;
  }

  for (c6_i55 = 0; c6_i55 < 48; c6_i55++) {
    c6_b_a[c6_i55] = c6_C[c6_i55];
  }

  for (c6_i58 = 0; c6_i58 < 64; c6_i58++) {
    c6_b[c6_i58] = c6_P_prio[c6_i58];
  }

  c6_i59 = 0;
  for (c6_i60 = 0; c6_i60 < 6; c6_i60++) {
    c6_i62 = 0;
    for (c6_i63 = 0; c6_i63 < 8; c6_i63++) {
      c6_d_b[c6_i63 + c6_i59] = c6_C[c6_i62 + c6_i60];
      c6_i62 += 6;
    }

    c6_i59 += 8;
  }

  for (c6_i61 = 0; c6_i61 < 8; c6_i61++) {
    c6_i65 = 0;
    for (c6_i66 = 0; c6_i66 < 6; c6_i66++) {
      c6_dv11[c6_i65 + c6_i61] = 0.0;
      c6_i71 = 0;
      for (c6_i73 = 0; c6_i73 < 8; c6_i73++) {
        c6_dv11[c6_i65 + c6_i61] += c6_a[c6_i71 + c6_i61] * c6_c_b[c6_i73 +
          c6_i65];
        c6_i71 += 8;
      }

      c6_i65 += 8;
    }
  }

  for (c6_i64 = 0; c6_i64 < 6; c6_i64++) {
    c6_i68 = 0;
    c6_i69 = 0;
    for (c6_i70 = 0; c6_i70 < 8; c6_i70++) {
      c6_d_a[c6_i68 + c6_i64] = 0.0;
      c6_i77 = 0;
      for (c6_i78 = 0; c6_i78 < 8; c6_i78++) {
        c6_d_a[c6_i68 + c6_i64] += c6_b_a[c6_i77 + c6_i64] * c6_b[c6_i78 +
          c6_i69];
        c6_i77 += 6;
      }

      c6_i68 += 6;
      c6_i69 += 8;
    }
  }

  for (c6_i67 = 0; c6_i67 < 6; c6_i67++) {
    c6_i72 = 0;
    c6_i75 = 0;
    for (c6_i76 = 0; c6_i76 < 6; c6_i76++) {
      c6_d24 = 0.0;
      c6_i80 = 0;
      for (c6_i81 = 0; c6_i81 < 8; c6_i81++) {
        c6_d24 += c6_d_a[c6_i80 + c6_i67] * c6_d_b[c6_i81 + c6_i75];
        c6_i80 += 6;
      }

      c6_c_a[c6_i72 + c6_i67] = c6_d24 + c6_R[c6_i72 + c6_i67];
      c6_i72 += 6;
      c6_i75 += 8;
    }
  }

  c6_b_mrdivide(chartInstance, c6_dv11, c6_c_a);
  for (c6_i74 = 0; c6_i74 < 48; c6_i74++) {
    c6_K[c6_i74] = c6_dv11[c6_i74];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 48);
  for (c6_i79 = 0; c6_i79 < 48; c6_i79++) {
    c6_b_a[c6_i79] = c6_K[c6_i79];
  }

  for (c6_i82 = 0; c6_i82 < 6; c6_i82++) {
    c6_e_b[c6_i82] = c6_b_m[c6_i82] - c6_zhat[c6_i82];
  }

  for (c6_i83 = 0; c6_i83 < 8; c6_i83++) {
    c6_d25 = 0.0;
    c6_i85 = 0;
    for (c6_i86 = 0; c6_i86 < 6; c6_i86++) {
      c6_d25 += c6_b_a[c6_i85 + c6_i83] * c6_e_b[c6_i86];
      c6_i85 += 8;
    }

    c6_b_xi_post[c6_i83] = c6_xi_prio[c6_i83] + c6_d25;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 49);
  for (c6_i84 = 0; c6_i84 < 64; c6_i84++) {
    c6_c_y[c6_i84] = 0.0;
  }

  c6_k = 0;
  for (c6_b_k = 0; c6_b_k < 8; c6_b_k++) {
    c6_c_y[c6_k] = 1.0;
    c6_k += 9;
  }

  for (c6_i87 = 0; c6_i87 < 48; c6_i87++) {
    c6_b_a[c6_i87] = c6_K[c6_i87];
  }

  for (c6_i88 = 0; c6_i88 < 48; c6_i88++) {
    c6_c_b[c6_i88] = c6_C[c6_i88];
  }

  for (c6_i89 = 0; c6_i89 < 8; c6_i89++) {
    c6_i91 = 0;
    c6_i92 = 0;
    for (c6_i93 = 0; c6_i93 < 8; c6_i93++) {
      c6_d26 = 0.0;
      c6_i95 = 0;
      for (c6_i96 = 0; c6_i96 < 6; c6_i96++) {
        c6_d26 += c6_b_a[c6_i95 + c6_i89] * c6_c_b[c6_i96 + c6_i92];
        c6_i95 += 8;
      }

      c6_a[c6_i91 + c6_i89] = c6_c_y[c6_i91 + c6_i89] - c6_d26;
      c6_i91 += 8;
      c6_i92 += 6;
    }
  }

  for (c6_i90 = 0; c6_i90 < 64; c6_i90++) {
    c6_b[c6_i90] = c6_P_prio[c6_i90];
  }

  for (c6_i94 = 0; c6_i94 < 64; c6_i94++) {
    c6_b_P_post[c6_i94] = 0.0;
  }

  c6_c_alpha1 = 1.0;
  c6_c_beta1 = 0.0;
  for (c6_i97 = 0; c6_i97 < 64; c6_i97++) {
    c6_c_y[c6_i97] = c6_b_P_post[c6_i97];
  }

  c6_c_TRANSB = 'N';
  c6_c_TRANSA = 'N';
  for (c6_i98 = 0; c6_i98 < 64; c6_i98++) {
    c6_b_P_post[c6_i98] = c6_c_y[c6_i98];
  }

  c6_c_m_t = (ptrdiff_t)8;
  c6_c_n_t = (ptrdiff_t)8;
  c6_c_k_t = (ptrdiff_t)8;
  c6_c_lda_t = (ptrdiff_t)8;
  c6_c_ldb_t = (ptrdiff_t)8;
  c6_c_ldc_t = (ptrdiff_t)8;
  dgemm(&c6_c_TRANSA, &c6_c_TRANSB, &c6_c_m_t, &c6_c_n_t, &c6_c_k_t,
        &c6_c_alpha1, &c6_a[0], &c6_c_lda_t, &c6_b[0], &c6_c_ldb_t, &c6_c_beta1,
        &c6_b_P_post[0], &c6_c_ldc_t);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 50);
  c6_b_xk = c6_b_xi_post[0];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 50);
  c6_b_yk = c6_b_xi_post[1];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, -50);
  _SFD_SYMBOL_SCOPE_POP();
  for (c6_i99 = 0; c6_i99 < 8; c6_i99++) {
    (*chartInstance->c6_xi_post)[c6_i99] = c6_b_xi_post[c6_i99];
  }

  for (c6_i100 = 0; c6_i100 < 64; c6_i100++) {
    (*chartInstance->c6_P_post)[c6_i100] = c6_b_P_post[c6_i100];
  }

  *chartInstance->c6_xk = c6_b_xk;
  *chartInstance->c6_yk = c6_b_yk;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c6_sfEvent);
}

static void initSimStructsc6_uni_model_v2(SFc6_uni_model_v2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber, uint32_T c6_instanceNumber)
{
  (void)(c6_machineNumber);
  (void)(c6_chartNumber);
  (void)(c6_instanceNumber);
}

static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  real_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  c6_u = *(real_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static real_T c6_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_b_yk, const char_T *c6_identifier)
{
  real_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = (const char *)c6_identifier;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_y = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_yk), &c6_thisId);
  sf_mex_destroy(&c6_b_yk);
  return c6_y;
}

static real_T c6_b_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  real_T c6_y;
  real_T c6_d27;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_d27, 1, 0, 0U, 0, 0U, 0);
  c6_y = c6_d27;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_yk;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y;
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_b_yk = sf_mex_dup(c6_mxArrayInData);
  c6_thisId.fIdentifier = (const char *)c6_varName;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_y = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_yk), &c6_thisId);
  sf_mex_destroy(&c6_b_yk);
  *(real_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  int32_T c6_i101;
  int32_T c6_i102;
  const mxArray *c6_y = NULL;
  int32_T c6_i103;
  real_T c6_u[64];
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  c6_i101 = 0;
  for (c6_i102 = 0; c6_i102 < 8; c6_i102++) {
    for (c6_i103 = 0; c6_i103 < 8; c6_i103++) {
      c6_u[c6_i103 + c6_i101] = (*(real_T (*)[64])c6_inData)[c6_i103 + c6_i101];
    }

    c6_i101 += 8;
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 8, 8), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static void c6_c_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_b_P_post, const char_T *c6_identifier, real_T c6_y[64])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = (const char *)c6_identifier;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_P_post), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_b_P_post);
}

static void c6_d_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[64])
{
  real_T c6_dv12[64];
  int32_T c6_i104;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv12, 1, 0, 0U, 1, 0U, 2, 8, 8);
  for (c6_i104 = 0; c6_i104 < 64; c6_i104++) {
    c6_y[c6_i104] = c6_dv12[c6_i104];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_P_post;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[64];
  int32_T c6_i105;
  int32_T c6_i106;
  int32_T c6_i107;
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_b_P_post = sf_mex_dup(c6_mxArrayInData);
  c6_thisId.fIdentifier = (const char *)c6_varName;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_P_post), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_b_P_post);
  c6_i105 = 0;
  for (c6_i106 = 0; c6_i106 < 8; c6_i106++) {
    for (c6_i107 = 0; c6_i107 < 8; c6_i107++) {
      (*(real_T (*)[64])c6_outData)[c6_i107 + c6_i105] = c6_y[c6_i107 + c6_i105];
    }

    c6_i105 += 8;
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  int32_T c6_i108;
  const mxArray *c6_y = NULL;
  real_T c6_u[8];
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  for (c6_i108 = 0; c6_i108 < 8; c6_i108++) {
    c6_u[c6_i108] = (*(real_T (*)[8])c6_inData)[c6_i108];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 8), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static void c6_e_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_b_xi_post, const char_T *c6_identifier, real_T c6_y[8])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = (const char *)c6_identifier;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_xi_post), &c6_thisId,
                        c6_y);
  sf_mex_destroy(&c6_b_xi_post);
}

static void c6_f_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[8])
{
  real_T c6_dv13[8];
  int32_T c6_i109;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv13, 1, 0, 0U, 1, 0U, 1, 8);
  for (c6_i109 = 0; c6_i109 < 8; c6_i109++) {
    c6_y[c6_i109] = c6_dv13[c6_i109];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_xi_post;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[8];
  int32_T c6_i110;
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_b_xi_post = sf_mex_dup(c6_mxArrayInData);
  c6_thisId.fIdentifier = (const char *)c6_varName;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_xi_post), &c6_thisId,
                        c6_y);
  sf_mex_destroy(&c6_b_xi_post);
  for (c6_i110 = 0; c6_i110 < 8; c6_i110++) {
    (*(real_T (*)[8])c6_outData)[c6_i110] = c6_y[c6_i110];
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  int32_T c6_i111;
  const mxArray *c6_y = NULL;
  real_T c6_u[2];
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  for (c6_i111 = 0; c6_i111 < 2; c6_i111++) {
    c6_u[c6_i111] = (*(real_T (*)[2])c6_inData)[c6_i111];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static const mxArray *c6_e_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  int32_T c6_i112;
  const mxArray *c6_y = NULL;
  real_T c6_u[6];
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  for (c6_i112 = 0; c6_i112 < 6; c6_i112++) {
    c6_u[c6_i112] = (*(real_T (*)[6])c6_inData)[c6_i112];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static const mxArray *c6_f_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  int32_T c6_i113;
  int32_T c6_i114;
  const mxArray *c6_y = NULL;
  int32_T c6_i115;
  real_T c6_u[48];
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  c6_i113 = 0;
  for (c6_i114 = 0; c6_i114 < 6; c6_i114++) {
    for (c6_i115 = 0; c6_i115 < 8; c6_i115++) {
      c6_u[c6_i115 + c6_i113] = (*(real_T (*)[48])c6_inData)[c6_i115 + c6_i113];
    }

    c6_i113 += 8;
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 8, 6), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static void c6_g_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[48])
{
  real_T c6_dv14[48];
  int32_T c6_i116;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv14, 1, 0, 0U, 1, 0U, 2, 8, 6);
  for (c6_i116 = 0; c6_i116 < 48; c6_i116++) {
    c6_y[c6_i116] = c6_dv14[c6_i116];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_K;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[48];
  int32_T c6_i117;
  int32_T c6_i118;
  int32_T c6_i119;
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_K = sf_mex_dup(c6_mxArrayInData);
  c6_thisId.fIdentifier = (const char *)c6_varName;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_K), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_K);
  c6_i117 = 0;
  for (c6_i118 = 0; c6_i118 < 6; c6_i118++) {
    for (c6_i119 = 0; c6_i119 < 8; c6_i119++) {
      (*(real_T (*)[48])c6_outData)[c6_i119 + c6_i117] = c6_y[c6_i119 + c6_i117];
    }

    c6_i117 += 8;
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_g_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  int32_T c6_i120;
  int32_T c6_i121;
  const mxArray *c6_y = NULL;
  int32_T c6_i122;
  real_T c6_u[36];
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  c6_i120 = 0;
  for (c6_i121 = 0; c6_i121 < 6; c6_i121++) {
    for (c6_i122 = 0; c6_i122 < 6; c6_i122++) {
      c6_u[c6_i122 + c6_i120] = (*(real_T (*)[36])c6_inData)[c6_i122 + c6_i120];
    }

    c6_i120 += 6;
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 6, 6), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static void c6_h_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[36])
{
  real_T c6_dv15[36];
  int32_T c6_i123;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv15, 1, 0, 0U, 1, 0U, 2, 6, 6);
  for (c6_i123 = 0; c6_i123 < 36; c6_i123++) {
    c6_y[c6_i123] = c6_dv15[c6_i123];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_R;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[36];
  int32_T c6_i124;
  int32_T c6_i125;
  int32_T c6_i126;
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_R = sf_mex_dup(c6_mxArrayInData);
  c6_thisId.fIdentifier = (const char *)c6_varName;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_R), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_R);
  c6_i124 = 0;
  for (c6_i125 = 0; c6_i125 < 6; c6_i125++) {
    for (c6_i126 = 0; c6_i126 < 6; c6_i126++) {
      (*(real_T (*)[36])c6_outData)[c6_i126 + c6_i124] = c6_y[c6_i126 + c6_i124];
    }

    c6_i124 += 6;
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_h_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  int32_T c6_i127;
  int32_T c6_i128;
  const mxArray *c6_y = NULL;
  int32_T c6_i129;
  real_T c6_u[48];
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  c6_i127 = 0;
  for (c6_i128 = 0; c6_i128 < 8; c6_i128++) {
    for (c6_i129 = 0; c6_i129 < 6; c6_i129++) {
      c6_u[c6_i129 + c6_i127] = (*(real_T (*)[48])c6_inData)[c6_i129 + c6_i127];
    }

    c6_i127 += 6;
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 6, 8), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static void c6_i_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[48])
{
  real_T c6_dv16[48];
  int32_T c6_i130;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv16, 1, 0, 0U, 1, 0U, 2, 6, 8);
  for (c6_i130 = 0; c6_i130 < 48; c6_i130++) {
    c6_y[c6_i130] = c6_dv16[c6_i130];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_C;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[48];
  int32_T c6_i131;
  int32_T c6_i132;
  int32_T c6_i133;
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_C = sf_mex_dup(c6_mxArrayInData);
  c6_thisId.fIdentifier = (const char *)c6_varName;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_C), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_C);
  c6_i131 = 0;
  for (c6_i132 = 0; c6_i132 < 8; c6_i132++) {
    for (c6_i133 = 0; c6_i133 < 6; c6_i133++) {
      (*(real_T (*)[48])c6_outData)[c6_i133 + c6_i131] = c6_y[c6_i133 + c6_i131];
    }

    c6_i131 += 6;
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static void c6_j_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[6])
{
  real_T c6_dv17[6];
  int32_T c6_i134;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv17, 1, 0, 0U, 1, 0U, 1, 6);
  for (c6_i134 = 0; c6_i134 < 6; c6_i134++) {
    c6_y[c6_i134] = c6_dv17[c6_i134];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_zhat;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[6];
  int32_T c6_i135;
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_zhat = sf_mex_dup(c6_mxArrayInData);
  c6_thisId.fIdentifier = (const char *)c6_varName;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_zhat), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_zhat);
  for (c6_i135 = 0; c6_i135 < 6; c6_i135++) {
    (*(real_T (*)[6])c6_outData)[c6_i135] = c6_y[c6_i135];
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

const mxArray *sf_c6_uni_model_v2_get_eml_resolved_functions_info(void)
{
  const mxArray *c6_nameCaptureInfo = NULL;
  c6_nameCaptureInfo = NULL;
  sf_mex_assign(&c6_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c6_nameCaptureInfo;
}

static real_T c6_cosd(SFc6_uni_model_v2InstanceStruct *chartInstance, real_T
                      c6_x)
{
  real_T c6_b_x;
  c6_b_x = c6_x;
  c6_b_cosd(chartInstance, &c6_b_x);
  return c6_b_x;
}

static real_T c6_sind(SFc6_uni_model_v2InstanceStruct *chartInstance, real_T
                      c6_x)
{
  real_T c6_b_x;
  c6_b_x = c6_x;
  c6_b_sind(chartInstance, &c6_b_x);
  return c6_b_x;
}

static void c6_mrdivide(SFc6_uni_model_v2InstanceStruct *chartInstance, real_T
  c6_A[48], real_T c6_B[36], real_T c6_y[48])
{
  int32_T c6_i136;
  int32_T c6_i137;
  real_T c6_b_B[36];
  for (c6_i136 = 0; c6_i136 < 48; c6_i136++) {
    c6_y[c6_i136] = c6_A[c6_i136];
  }

  for (c6_i137 = 0; c6_i137 < 36; c6_i137++) {
    c6_b_B[c6_i137] = c6_B[c6_i137];
  }

  c6_b_mrdivide(chartInstance, c6_y, c6_b_B);
}

static void c6_check_forloop_overflow_error(SFc6_uni_model_v2InstanceStruct
  *chartInstance, boolean_T c6_overflow)
{
  const mxArray *c6_y = NULL;
  static char_T c6_cv0[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  const mxArray *c6_b_y = NULL;
  static char_T c6_cv1[5] = { 'i', 'n', 't', '3', '2' };

  (void)chartInstance;
  if (!c6_overflow) {
  } else {
    c6_y = NULL;
    sf_mex_assign(&c6_y, sf_mex_create("y", c6_cv0, 10, 0U, 1U, 0U, 2, 1, 34),
                  false);
    c6_b_y = NULL;
    sf_mex_assign(&c6_b_y, sf_mex_create("y", c6_cv1, 10, 0U, 1U, 0U, 2, 1, 5),
                  false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message",
      1U, 2U, 14, c6_y, 14, c6_b_y));
  }
}

static void c6_warning(SFc6_uni_model_v2InstanceStruct *chartInstance)
{
  const mxArray *c6_y = NULL;
  static char_T c6_cv2[7] = { 'w', 'a', 'r', 'n', 'i', 'n', 'g' };

  const mxArray *c6_b_y = NULL;
  static char_T c6_cv3[7] = { 'm', 'e', 's', 's', 'a', 'g', 'e' };

  const mxArray *c6_c_y = NULL;
  static char_T c6_msgID[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a', 't',
    'r', 'i', 'x' };

  (void)chartInstance;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_cv2, 10, 0U, 1U, 0U, 2, 1, 7),
                false);
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", c6_cv3, 10, 0U, 1U, 0U, 2, 1, 7),
                false);
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", c6_msgID, 10, 0U, 1U, 0U, 2, 1, 27),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "feval", 0U, 2U, 14, c6_y, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "feval", 1U,
    2U, 14, c6_b_y, 14, c6_c_y));
}

static const mxArray *c6_i_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  int32_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  c6_u = *(int32_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static int32_T c6_k_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  int32_T c6_y;
  int32_T c6_i138;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_i138, 1, 6, 0U, 0, 0U, 0);
  c6_y = c6_i138;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_sfEvent;
  emlrtMsgIdentifier c6_thisId;
  int32_T c6_y;
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)chartInstanceVoid;
  c6_b_sfEvent = sf_mex_dup(c6_mxArrayInData);
  c6_thisId.fIdentifier = (const char *)c6_varName;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_y = c6_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_sfEvent),
    &c6_thisId);
  sf_mex_destroy(&c6_b_sfEvent);
  *(int32_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static uint8_T c6_l_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct
  *chartInstance, const mxArray *c6_b_is_active_c6_uni_model_v2, const char_T
  *c6_identifier)
{
  uint8_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = (const char *)c6_identifier;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_y = c6_m_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_b_is_active_c6_uni_model_v2), &c6_thisId);
  sf_mex_destroy(&c6_b_is_active_c6_uni_model_v2);
  return c6_y;
}

static uint8_T c6_m_emlrt_marshallIn(SFc6_uni_model_v2InstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint8_T c6_y;
  uint8_T c6_u0;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_u0, 1, 3, 0U, 0, 0U, 0);
  c6_y = c6_u0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_b_cosd(SFc6_uni_model_v2InstanceStruct *chartInstance, real_T
                      *c6_x)
{
  real_T c6_b_x;
  real_T c6_absx;
  int8_T c6_n;
  (void)chartInstance;
  if (!((!muDoubleScalarIsInf(*c6_x)) && (!muDoubleScalarIsNaN(*c6_x)))) {
    *c6_x = rtNaN;
  } else {
    c6_b_x = muDoubleScalarRem(*c6_x, 360.0);
    c6_absx = muDoubleScalarAbs(c6_b_x);
    if (c6_absx > 180.0) {
      if (c6_b_x > 0.0) {
        c6_b_x -= 360.0;
      } else {
        c6_b_x += 360.0;
      }

      c6_absx = muDoubleScalarAbs(c6_b_x);
    }

    if (c6_absx <= 45.0) {
      c6_b_x *= 0.017453292519943295;
      c6_n = 0;
    } else if (c6_absx <= 135.0) {
      if (c6_b_x > 0.0) {
        c6_b_x = 0.017453292519943295 * (c6_b_x - 90.0);
        c6_n = 1;
      } else {
        c6_b_x = 0.017453292519943295 * (c6_b_x + 90.0);
        c6_n = -1;
      }
    } else if (c6_b_x > 0.0) {
      c6_b_x = 0.017453292519943295 * (c6_b_x - 180.0);
      c6_n = 2;
    } else {
      c6_b_x = 0.017453292519943295 * (c6_b_x + 180.0);
      c6_n = -2;
    }

    if ((real_T)c6_n == 0.0) {
      *c6_x = muDoubleScalarCos(c6_b_x);
    } else if ((real_T)c6_n == 1.0) {
      *c6_x = -muDoubleScalarSin(c6_b_x);
    } else if ((real_T)c6_n == -1.0) {
      *c6_x = muDoubleScalarSin(c6_b_x);
    } else {
      *c6_x = -muDoubleScalarCos(c6_b_x);
    }
  }
}

static void c6_b_sind(SFc6_uni_model_v2InstanceStruct *chartInstance, real_T
                      *c6_x)
{
  real_T c6_b_x;
  real_T c6_c_x;
  real_T c6_absx;
  int8_T c6_n;
  (void)chartInstance;
  if (!((!muDoubleScalarIsInf(*c6_x)) && (!muDoubleScalarIsNaN(*c6_x)))) {
    c6_c_x = rtNaN;
  } else {
    c6_b_x = muDoubleScalarRem(*c6_x, 360.0);
    c6_absx = muDoubleScalarAbs(c6_b_x);
    if (c6_absx > 180.0) {
      if (c6_b_x > 0.0) {
        c6_b_x -= 360.0;
      } else {
        c6_b_x += 360.0;
      }

      c6_absx = muDoubleScalarAbs(c6_b_x);
    }

    if (c6_absx <= 45.0) {
      c6_b_x *= 0.017453292519943295;
      c6_n = 0;
    } else if (c6_absx <= 135.0) {
      if (c6_b_x > 0.0) {
        c6_b_x = 0.017453292519943295 * (c6_b_x - 90.0);
        c6_n = 1;
      } else {
        c6_b_x = 0.017453292519943295 * (c6_b_x + 90.0);
        c6_n = -1;
      }
    } else if (c6_b_x > 0.0) {
      c6_b_x = 0.017453292519943295 * (c6_b_x - 180.0);
      c6_n = 2;
    } else {
      c6_b_x = 0.017453292519943295 * (c6_b_x + 180.0);
      c6_n = -2;
    }

    if ((real_T)c6_n == 0.0) {
      c6_c_x = muDoubleScalarSin(c6_b_x);
    } else if ((real_T)c6_n == 1.0) {
      c6_c_x = muDoubleScalarCos(c6_b_x);
    } else if ((real_T)c6_n == -1.0) {
      c6_c_x = -muDoubleScalarCos(c6_b_x);
    } else {
      c6_c_x = -muDoubleScalarSin(c6_b_x);
    }
  }

  *c6_x = c6_c_x;
}

static void c6_b_mrdivide(SFc6_uni_model_v2InstanceStruct *chartInstance, real_T
  c6_A[48], real_T c6_B[36])
{
  int32_T c6_i139;
  int32_T c6_i140;
  real_T c6_b_A[36];
  int32_T c6_info;
  int32_T c6_ipiv[6];
  int32_T c6_j;
  int32_T c6_c;
  int32_T c6_idxmax;
  int32_T c6_ix;
  int32_T c6_b_j;
  real_T c6_smax;
  boolean_T c6_overflow;
  int32_T c6_jA;
  int32_T c6_b;
  int32_T c6_b_ix;
  int32_T c6_c_j;
  int32_T c6_jBcol;
  int32_T c6_jy;
  boolean_T c6_b_overflow;
  int32_T c6_iy;
  int32_T c6_jAcol;
  int32_T c6_k;
  boolean_T c6_c_overflow;
  int32_T c6_b_k;
  boolean_T c6_d_overflow;
  int32_T c6_xj;
  int32_T c6_b_jBcol;
  int32_T c6_b_i;
  int32_T c6_b_jAcol;
  int32_T c6_d_j;
  real_T c6_temp;
  int32_T c6_c_k;
  int32_T c6_d_k;
  real_T c6_s;
  int32_T c6_jp;
  real_T c6_yjy;
  int32_T c6_b_xi;
  int32_T c6_kBcol;
  real_T c6_b_temp;
  int32_T c6_b_kBcol;
  int32_T c6_c_i;
  int32_T c6_c_ix;
  int32_T c6_d_i;
  int32_T c6_e_i;
  int32_T c6_b_b;
  real_T c6_c_temp;
  boolean_T c6_e_overflow;
  int32_T c6_ijA;
  for (c6_i139 = 0; c6_i139 < 36; c6_i139++) {
    c6_b_A[c6_i139] = c6_B[c6_i139];
  }

  for (c6_i140 = 0; c6_i140 < 6; c6_i140++) {
    c6_ipiv[c6_i140] = 1 + c6_i140;
  }

  c6_info = 0;
  for (c6_j = 0; c6_j < 5; c6_j++) {
    c6_c = c6_j * 7;
    if (6 - c6_j < 1) {
      c6_idxmax = 0;
    } else {
      c6_idxmax = 1;
      if (6 - c6_j > 1) {
        c6_ix = c6_c;
        c6_smax = muDoubleScalarAbs(c6_b_A[c6_c]) + muDoubleScalarAbs(0.0);
        c6_overflow = ((!(2 > 6 - c6_j)) && (6 - c6_j > 2147483646));
        if (c6_overflow) {
          c6_check_forloop_overflow_error(chartInstance, c6_overflow);
        }

        for (c6_k = 2; c6_k <= 6 - c6_j; c6_k++) {
          c6_ix++;
          c6_s = muDoubleScalarAbs(c6_b_A[c6_ix]) + muDoubleScalarAbs(0.0);
          if (c6_s > c6_smax) {
            c6_idxmax = c6_k;
            c6_smax = c6_s;
          }
        }
      }
    }

    if (c6_b_A[(c6_c + c6_idxmax) - 1] != 0.0) {
      if (c6_idxmax - 1 != 0) {
        c6_ipiv[c6_j] = c6_j + c6_idxmax;
        c6_b_ix = c6_j;
        c6_iy = (c6_j + c6_idxmax) - 1;
        for (c6_b_k = 0; c6_b_k < 6; c6_b_k++) {
          c6_temp = c6_b_A[c6_b_ix];
          c6_b_A[c6_b_ix] = c6_b_A[c6_iy];
          c6_b_A[c6_iy] = c6_temp;
          c6_b_ix += 6;
          c6_iy += 6;
        }
      }

      c6_b = (c6_c - c6_j) + 6;
      c6_b_overflow = ((!(c6_c + 2 > c6_b)) && (c6_b > 2147483646));
      if (c6_b_overflow) {
        c6_check_forloop_overflow_error(chartInstance, c6_b_overflow);
      }

      for (c6_b_i = c6_c + 1; c6_b_i + 1 <= c6_b; c6_b_i++) {
        c6_b_A[c6_b_i] /= c6_b_A[c6_c];
      }
    } else {
      c6_info = c6_j + 1;
    }

    c6_jA = c6_c + 8;
    c6_jy = c6_c + 6;
    c6_c_overflow = ((!(1 > 5 - c6_j)) && (5 - c6_j > 2147483646));
    if (c6_c_overflow) {
      c6_check_forloop_overflow_error(chartInstance, c6_c_overflow);
    }

    for (c6_d_j = 1; c6_d_j <= 5 - c6_j; c6_d_j++) {
      c6_yjy = c6_b_A[c6_jy];
      if (c6_b_A[c6_jy] != 0.0) {
        c6_c_ix = c6_c;
        c6_b_b = (c6_jA - c6_j) + 4;
        c6_e_overflow = ((!(c6_jA > c6_b_b)) && (c6_b_b > 2147483646));
        if (c6_e_overflow) {
          c6_check_forloop_overflow_error(chartInstance, c6_e_overflow);
        }

        for (c6_ijA = c6_jA - 1; c6_ijA + 1 <= c6_b_b; c6_ijA++) {
          c6_b_A[c6_ijA] += c6_b_A[c6_c_ix + 1] * -c6_yjy;
          c6_c_ix++;
        }
      }

      c6_jy += 6;
      c6_jA += 6;
    }
  }

  if (((real_T)c6_info == 0.0) && (!(c6_b_A[35] != 0.0))) {
    c6_info = 6;
  }

  if ((real_T)c6_info > 0.0) {
    c6_warning(chartInstance);
  }

  for (c6_b_j = 0; c6_b_j < 6; c6_b_j++) {
    c6_jBcol = c6_b_j << 3;
    c6_jAcol = 6 * c6_b_j - 1;
    c6_d_overflow = ((!(1 > c6_b_j)) && (c6_b_j > 2147483646));
    if (c6_d_overflow) {
      c6_check_forloop_overflow_error(chartInstance, c6_d_overflow);
    }

    for (c6_d_k = 1; c6_d_k <= c6_b_j; c6_d_k++) {
      c6_b_kBcol = (c6_d_k - 1) << 3;
      if (c6_b_A[c6_d_k + c6_jAcol] != 0.0) {
        for (c6_e_i = 0; c6_e_i < 8; c6_e_i++) {
          c6_A[c6_e_i + c6_jBcol] -= c6_b_A[c6_d_k + c6_jAcol] * c6_A[c6_e_i +
            c6_b_kBcol];
        }
      }
    }

    c6_b_temp = 1.0 / c6_b_A[(c6_b_j + c6_jAcol) + 1];
    for (c6_c_i = 0; c6_c_i < 8; c6_c_i++) {
      c6_A[c6_c_i + c6_jBcol] *= c6_b_temp;
    }
  }

  for (c6_c_j = 5; c6_c_j > -1; c6_c_j--) {
    c6_b_jBcol = c6_c_j << 3;
    c6_b_jAcol = 6 * c6_c_j - 1;
    for (c6_c_k = c6_c_j + 2; c6_c_k < 7; c6_c_k++) {
      c6_kBcol = (c6_c_k - 1) << 3;
      if (c6_b_A[c6_c_k + c6_b_jAcol] != 0.0) {
        for (c6_d_i = 0; c6_d_i < 8; c6_d_i++) {
          c6_A[c6_d_i + c6_b_jBcol] -= c6_b_A[c6_c_k + c6_b_jAcol] * c6_A[c6_d_i
            + c6_kBcol];
        }
      }
    }
  }

  for (c6_xj = 4; c6_xj > -1; c6_xj--) {
    if (c6_ipiv[c6_xj] != c6_xj + 1) {
      c6_jp = c6_ipiv[c6_xj] - 1;
      for (c6_b_xi = 0; c6_b_xi < 8; c6_b_xi++) {
        c6_c_temp = c6_A[c6_b_xi + (c6_xj << 3)];
        c6_A[c6_b_xi + (c6_xj << 3)] = c6_A[c6_b_xi + (c6_jp << 3)];
        c6_A[c6_b_xi + (c6_jp << 3)] = c6_c_temp;
      }
    }
  }
}

static void init_dsm_address_info(SFc6_uni_model_v2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc6_uni_model_v2InstanceStruct
  *chartInstance)
{
  chartInstance->c6_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c6_m = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c6_xi = (real_T (*)[8])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c6_i = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c6_P_post_prev = (real_T (*)[64])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c6_xi_post = (real_T (*)[8])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c6_P_post = (real_T (*)[64])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c6_xk = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c6_yk = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c6_uni_model_v2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2644228314U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1799799178U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3055709825U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2773197847U);
}

mxArray* sf_c6_uni_model_v2_get_post_codegen_info(void);
mxArray *sf_c6_uni_model_v2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("vZTutC1HFv7HyUcvFzXKM");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(8);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(8);
      pr[1] = (double)(8);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(8);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(8);
      pr[1] = (double)(8);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c6_uni_model_v2_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c6_uni_model_v2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,1);
  mxSetCell(mxcell3p, 0, mxCreateString("coder.internal.blas.BLASApi"));
  return(mxcell3p);
}

mxArray *sf_c6_uni_model_v2_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("pre");
  mxArray *fallbackReason = mxCreateString("hasBreakpoints");
  mxArray *hiddenFallbackType = mxCreateString("none");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c6_uni_model_v2_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c6_uni_model_v2_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c6_uni_model_v2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[16],T\"P_post\",},{M[1],M[5],T\"xi_post\",},{M[1],M[30],T\"xk\",},{M[1],M[31],T\"yk\",},{M[8],M[0],T\"is_active_c6_uni_model_v2\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c6_uni_model_v2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc6_uni_model_v2InstanceStruct *chartInstance =
      (SFc6_uni_model_v2InstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _uni_model_v2MachineNumber_,
           6,
           1,
           1,
           0,
           8,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_uni_model_v2MachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_uni_model_v2MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _uni_model_v2MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"m");
          _SFD_SET_DATA_PROPS(1,1,1,0,"xi");
          _SFD_SET_DATA_PROPS(2,1,1,0,"i");
          _SFD_SET_DATA_PROPS(3,1,1,0,"P_post_prev");
          _SFD_SET_DATA_PROPS(4,2,0,1,"xi_post");
          _SFD_SET_DATA_PROPS(5,2,0,1,"P_post");
          _SFD_SET_DATA_PROPS(6,2,0,1,"xk");
          _SFD_SET_DATA_PROPS(7,2,0,1,"yk");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2515);

        {
          unsigned int dimVector[1];
          dimVector[0]= 6U;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 8U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 8U;
          dimVector[1]= 8U;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 8U;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)
            c6_c_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 8U;
          dimVector[1]= 8U;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)
            c6_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)c6_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)c6_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _uni_model_v2MachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc6_uni_model_v2InstanceStruct *chartInstance =
      (SFc6_uni_model_v2InstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c6_m);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c6_xi);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c6_i);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c6_P_post_prev);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c6_xi_post);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c6_P_post);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c6_xk);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)chartInstance->c6_yk);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sMBnfbb9oJslIfErhO6DbiC";
}

static void sf_opaque_initialize_c6_uni_model_v2(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc6_uni_model_v2InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c6_uni_model_v2((SFc6_uni_model_v2InstanceStruct*)
    chartInstanceVar);
  initialize_c6_uni_model_v2((SFc6_uni_model_v2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c6_uni_model_v2(void *chartInstanceVar)
{
  enable_c6_uni_model_v2((SFc6_uni_model_v2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c6_uni_model_v2(void *chartInstanceVar)
{
  disable_c6_uni_model_v2((SFc6_uni_model_v2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c6_uni_model_v2(void *chartInstanceVar)
{
  sf_gateway_c6_uni_model_v2((SFc6_uni_model_v2InstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c6_uni_model_v2(SimStruct* S)
{
  return get_sim_state_c6_uni_model_v2((SFc6_uni_model_v2InstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c6_uni_model_v2(SimStruct* S, const mxArray *
  st)
{
  set_sim_state_c6_uni_model_v2((SFc6_uni_model_v2InstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c6_uni_model_v2(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc6_uni_model_v2InstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_uni_model_v2_optimization_info();
    }

    finalize_c6_uni_model_v2((SFc6_uni_model_v2InstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc6_uni_model_v2((SFc6_uni_model_v2InstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c6_uni_model_v2(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c6_uni_model_v2((SFc6_uni_model_v2InstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c6_uni_model_v2(SimStruct *S)
{
  /* Set overwritable ports for inplace optimization */
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetInputPortDirectFeedThrough(S, 2, 1);
  ssSetInputPortDirectFeedThrough(S, 3, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 1);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 1);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_uni_model_v2_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,6);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,6,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 6);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,6);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,6,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,6,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,6);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3053760152U));
  ssSetChecksum1(S,(218777862U));
  ssSetChecksum2(S,(1782200138U));
  ssSetChecksum3(S,(1399614971U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c6_uni_model_v2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c6_uni_model_v2(SimStruct *S)
{
  SFc6_uni_model_v2InstanceStruct *chartInstance;
  chartInstance = (SFc6_uni_model_v2InstanceStruct *)utMalloc(sizeof
    (SFc6_uni_model_v2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc6_uni_model_v2InstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c6_uni_model_v2;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c6_uni_model_v2;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c6_uni_model_v2;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c6_uni_model_v2;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c6_uni_model_v2;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c6_uni_model_v2;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c6_uni_model_v2;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c6_uni_model_v2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c6_uni_model_v2;
  chartInstance->chartInfo.mdlStart = mdlStart_c6_uni_model_v2;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c6_uni_model_v2;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c6_uni_model_v2(chartInstance);
}

void c6_uni_model_v2_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c6_uni_model_v2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c6_uni_model_v2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c6_uni_model_v2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c6_uni_model_v2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}

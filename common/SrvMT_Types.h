
#ifndef RBA_SRVMT_TYPES_H
#define RBA_SRVMT_TYPES_H

/*#define DEBUG*/
/*To enable DEBUG please uncomment */

#include "Platform_Types.h"

/*
 **********************************************************************************************************************
 * Specific data types
 **********************************************************************************************************************
 */

 /*! \var typedef rba_SrvMT_Size_u32 */
 /*! Data type for matrix and vector dimensions and indices. Simulink does not support the use of `rba_SrvMT_Size_u32` in function
     interfaces. */
 typedef uint32 rba_SrvMT_Size_u32;

 /*! \var typedef rba_SrvMT_Int_s32 */
 /*! Data type for signed integers. */
 typedef sint32 rba_SrvMT_Int_s32;

 /*! \var typedef rba_SrvMT_f32 */
 /*! Data type for float values. */
 typedef float32 rba_SrvMT_f32;


/*
 **********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************
 */

//! \def RBA_SRVMT_NULL (void *)0
/*! Macro for the null pointer. */
#define RBA_SRVMT_NULL (void *)0


 /*! \def  RBA_SRVMT_MAX(X, Y)*/
 /*! Macro for maximum computation of \a X \a Y. */
 /*MR12 DIR 4.9 VIOLATION: The warning is uncritical and non-removable since function-like macro is required to improve
  * runtime performance for frequently invoked functions. Approved by MISRA2012_SUPPORT_TEAM. */
#define RBA_SRVMT_MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define RBA_SRVMT_SQRT_EPSILON 3.4526698e-04F /**< sqrt of MT_EPSILON */

#define RBA_SRVMT_PI        3.14159265358979323846F
#define RBA_SRVMT_PI2       1.570796326794896558F
#define RBA_SRVMT_2PI       6.283185307179586232F
#define RBA_SRVMT_2DIVPI    0.63661977236758138243F
#define RBA_SRVMT_2INVLN2   2.88539008F /**< Constant for saving the value of 2/ln(2) in 32 bit floating point format. */

 /**
 Number of Kalman diagnosis information in order track the information in a detailed diagnosis of the Kalman filter run in offline investigation.
 \def MT_KALMAN_DIAGNOSIS_TOTAL
 */
 #define RBA_SRVMT_KALMAN_DIAGNOSIS_TOTAL 9U

 //Dummy function to determine cause of divergence --> should be overwritten
 //Default behaviour (i.e when all warnings are 0) is to blame the numerics
 #define RBA_SRVMT_KALMAN_DVG_DIAGNOSIS(warnings) ((((((((warnings[RBA_SRVMT_NON_PD_PHAT]+warnings[RBA_SRVMT_NON_PD_PTILDE])+warnings[RBA_SRVMT_NEGATIVE_GAIN])+warnings[RBA_SRVMT_SUPERIOR_TO_ONE_GAIN])+warnings[RBA_SRVMT_CLOSE_TO_SINGULAR_R])+warnings[RBA_SRVMT_CLOSE_TO_SINGULAR_Q])+warnings[RBA_SRVMT_CLOSE_TO_SINGULAR_P0]) >= warnings[RBA_SRVMT_X_NORM_INCREASE] ) ? RBA_SRVMT_NUMERICAL_DIVERGENCE : RBA_SRVMT_MODEL_DIVERGENCE)

 #define RBA_SRVMT_GET_AT(m, r,c, i, j) ((m.super).vtable->rba_SrvMT_getAt((const rba_SrvMT_Matrix_type_tst *) &m,r,c,i,j))

 #define RBA_SRVMT_SET_AT(m, r,c, v, i, j) ((m.super).vtable->rba_SrvMT_setAt((rba_SrvMT_Matrix_type_tst *) (&m),r,c, v, i,j))

 #define RBA_SRVMT_GET_AT_SAFE(m, i, j) ((m.super).vtable->rba_SrvMT_getAtSafe((rba_SrvMT_Matrix_type_tst *) (&m),i,j))

 #define RBA_SRVMT_SET_AT_SAFE(m, v, i, j) ((m.super).vtable->rba_SrvMT_setAtSafe((rba_SrvMT_Matrix_type_tst *) (&m), v, i,j))

/**
* Since variable length array types are forbidden to be used in BSW(according to MISRA 2012 Rule 18.8 Variable-length
* array types shall not be used) there is a statically defined maximal matrix size to be used for auxiliary matrices
* in the respective algorithms.
* \def RBA_SRVMT_MAX_MATRIX_SIZE 10U
*/
 #define RBA_SRVMT_MAX_MATRIX_SIZE 10U


 /*! \def RBA_SRVMT_DLLEXPORT extern */
 /*! DLL export flag. */
 #define RBA_SRVMT_DLLEXPORT extern

 /*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
 */
    /*! \enum rba_SrvMT_Status_ten */
    /*! Status indicators for error handling. */
    typedef enum
    {
        RBA_SRVMT_SUCCESS = 0,                   /**< Flagging successful operation */
        RBA_SRVMT_NO_MEMORY,                     /**< Flagging non-availability of enough memory */
        RBA_SRVMT_OVERFLOW,                      /**< Flagging overflow in an operation */
        RBA_SRVMT_UNDERFLOW,                     /**< Flagging underflow in an operation */
        RBA_SRVMT_EXCEEDS_MAX_MATRIX_SIZE,       /**< Flagging that the maximum matrix size is exceeded */
        RBA_SRVMT_SINGULAR_MATRIX,               /**< Flagging that the matrix is singular */
        RBA_SRVMT_NON_POSITIVE_DEFINITE_MATRIX,  /**< Flagging that the matrix is not positive definite */
        RBA_SRVMT_ILL_CONDITIONED,               /**< Flagging that the problem is ill-conditioned */
        RBA_SRVMT_NOZERO_IN_INTERVAL,            /**< Used for root finding function that no root found in given
                                                     interval*/
        RBA_SRVMT_VALUE_RANGE_EXCEEDED,          /**< Flagging that input range is exceeded and thus no result can be
                                                     calculated*/
        RBA_SRVMT_MATRIX_DIMENSION_INCOMPATIBLE, /**< Flagging that the operation failed because the input matrices'
                                                      dimensions were incompatible*/
        RBA_SRVMT_CLOSE_TO_SINGULAR_MATRIX       /**< Flagging that the matrix is close to being singular */
    } rba_SrvMT_Status_ten;

    //! \enum rba_SrvMT_optim_status_ten
    /*! Status indicators for error handling, specific to optimization. */
    typedef enum
    {
        RBA_SRVMT_OPTIM_SUCCESS = 0,           /**< Flagging successful operation */
        RBA_SRVMT_GRADIENT_IS_ZERO,            /**< Flagging that the gradient is nearly zero */   //exit status matches fmincon status from Matlab
        RBA_SRVMT_PROJECTED_GRADIENT_IS_ZERO,  /**< Flagging that the projected gradient is nearly zero */
        RBA_SRVMT_INITIAL_POINT_VIOLATES_CONSTRAINTS, /**< Flagging that the starting point violates already the constraints */
        RBA_SRVMT_DIRECTION_VERY_SMALL,        /**< Flagging that the computed direction is very small */ //exit status matches fmincon status from Matlab (active set)
        RBA_SRVMT_OPTIM_DELTAF_ZERO,           /**< Flagging Delta f is zero */ //exit status matches fmincon status from Matlab (active set)
        RBA_SRVMT_OPTIM_DELTAX_ZERO,           /**< Flagging Delta X is zero (exceeds eps_precision) in Armijo */
        RBA_SRVMT_LINE_SEARCH_ERROR,           /**< Flagging that the line search strategy could not find a good step length */
        RBA_SRVMT_OPTIM_MAX_ITER,              /**< Flagging maximal number of iterations exceeded */
        RBA_SRVMT_OPTIM_MAX_FCALLS,            /**< Flagging maximal number of function calls exceeded */
        RBA_SRVMT_INF_NAN_ERROR,               /**< Flagging error due to norm2 that can only result from NaN or Overflow */
        RBA_SRVMT_OPTI_ERROR,                  /**< Flagging ERROR in the Optimization algorithm -> VERY BAD */
        RBA_SRVMT_INITIAL_LD_NONPD              /**< Flagging that the initially provided LD-matrix is non-PD */
    }rba_SrvMT_Optim_Status_ten;

    /*! \union rba_SrvMT_f32u */
    /*! This is a union used for extracting the single bits (sign, exponent, mantissa) of a floating point number. */
    /* IGNORE RULE 3629: The warning is uncritical and non-removable since floating type is required in the union
       to manipulate floating number and it has no side effect. Approved by MISRA2012_SUPPORT_TEAM. */
    typedef union
    {
        rba_SrvMT_Size_u32 u32;          /**< unsigned 32 bit integer */
        rba_SrvMT_Int_s32 s32;           /**< signed 32 bit integer */
        rba_SrvMT_f32 f32;         /**< floating point value */
    } rba_SrvMT_f32u;

//! \struct rba_SrvMT_xinfo_type
/*! Structure used for searching data point and evaluating the characteristic curve for interpolation. */
typedef struct
{
    rba_SrvMT_Size_u32 index_u32; /**<  Data point index */
    rba_SrvMT_f32 h_f32;  /**<  Distance between XInput and respective data point */
    rba_SrvMT_f32 h_af32[3]; /**<  Distances among the three neighbouring data points and the XInput*/
} rba_SrvMT_xinfo_type_tst;

//! \var typedef rba_SrvMT_f32*
/*! Function pointer of type float \f$ \mapsto \f$ float. Required e.g. for root finding algorithm of Brent. */
typedef rba_SrvMT_f32 (*rba_SrvMT_Brent_fct)(rba_SrvMT_f32 x_f32, void* const context_pcv);

//! \var typedef rba_SrvMT_f32*
/*! Function pointer of type float \f$  \times \f$  uint \f$ \times \f$  float \f$ \times \f$ uint \f$ \mapsto \f$
 mt_status_t. Required e.g. for the interpolation functions where different search strategies might be chosen. The
 resulting status denotes whether the element being searched is outside the array, then the left- resp. rightmost
 neigbour is returned or the element is inside the array. */
typedef rba_SrvMT_Status_ten (*rba_SrvMT_Search_fct)(const rba_SrvMT_f32 *X_array, rba_SrvMT_Size_u32 N, rba_SrvMT_f32 Xin, rba_SrvMT_Size_u32 *index);

/* definition of the boolean data type for the transpose; */
typedef boolean rba_SrvMT_boolean;

//! \var typedef rba_SrvMT_f32*
/* Function pointer of type \f$ x*:float* \mapsto void \f$. Required e.g. model evaluation in the Kalman filter.
Function takes a vector as input and overwrites it internally. */
typedef void (*FUNC_PTR_FPVEC2FPVEC)(rba_SrvMT_f32* x_f32, rba_SrvMT_f32* u_f32, void *const context);

/* ! \enum rba_SrvMT_matrix_property_ten */
/*!  information for a property like pd, invertible. */
typedef enum
{
    RBA_SRVMT_YES = 0,                   /**< Flagging that the property does hold */
    RBA_SRVMT_NO,                        /**< Flagging that the property does NOT hold */
    RBA_SRVMT_DO_NOT_KNOW                /**< Flagging that nothing is known about the property */
} rba_SrvMT_matrix_property_ten;


typedef enum
{
    RBA_SRVMT_RECTANGULAR = 0,      /**< Rectangular matrix */
    RBA_SRVMT_VECTOR,
    RBA_SRVMT_SQUARE,               /**< Square matrix */
    RBA_SRVMT_UPPER_TRIANGULAR,     /**< Upper Triangular matrix*/
    RBA_SRVMT_LOWER_TRIANGULAR,     /**< Lower Triangular matrix*/
    RBA_SRVMT_SYMMETRIC,            /**< Symmetric matrix*/
    RBA_SRVMT_BAND_MATRIX,          /**< Band matrix */
    RBA_SRVMT_SPARSE_BAND_MATRIX,   /**< Sparse Band matrix */
    RBA_SRVMT_DIAGONAL,             /**< Diagonal matrix */
    RBA_SRVMT_UNIT                  /**< Unit matrix */
} rba_SrvMT_matrix_kind_ten;


//! \enum rba_SrvMT_kalman_status_ten
/*! Status indicators for error handling, specific to the Kalman filter. */
typedef enum
{
    RBA_SRVMT_KALMAN_SUCCESS = 0,          /**< Flagging successful operation */
    RBA_SRVMT_NON_POSITIVE_DEFINITE_R,      /**< Flagging a non positive definite R matrix (measurement noise covariance, given by the user) */
    RBA_SRVMT_NON_POSITIVE_DEFINITE_Q,      /**< Flagging a non positive definite Q matrix (model noise covariance, given by the user) */
    RBA_SRVMT_NON_POSITIVE_DEFINITE_P0, /**< Flagging a non positive definite P0 matrix (initial error covariance, given by the user) */
    RBA_SRVMT_NUMERICAL_DIVERGENCE,     /**< Flagging that the estimations have diverged because of numerical errors (in particular, non positive-definite error covariance) */
    RBA_SRVMT_MODEL_DIVERGENCE,         /**< Flagging that the estimations have diverged because of the model (instability, non-detectability) */
    RBA_SRVMT_MISMODELLING,             /**< Flagging that the model is incorrect, i.e either the system equation or the measurement equation is incorrect*/
    RBA_SRVMT_A_DECOMPOSITION_ERROR        /**< Flagging that the matrix A failed to be Schur-decomposed, the algorithm should not be run in debug mode*/
} rba_SrvMT_kalman_status_ten;


//! \enum rba_SrvMT_kalman_diagnosis_ten
/*! Diagnosis indicators, specific to the Kalman filter. */
/*! This enum should be kept consistent with the RBA_SRVMT_KALMAN_DIAGNOSIS_TOTAL constant (i.e the number of diagnosis types defined in the enum)*/
typedef enum
{
    RBA_SRVMT_NON_PD_PHAT,                  /**< Warning when one of P_hat's diagonal UD coefficients has turned negative (i.e Phat is non-PD) */
    RBA_SRVMT_NON_PD_PTILDE,                /**< Warning when one of P_tilde's diagonal UD coefficients has turned negative (i.e Ptilde is non-PD) */
    RBA_SRVMT_NEGATIVE_GAIN,                /**< Warning when one of KH's eigenvalues is negative*/
    RBA_SRVMT_SUPERIOR_TO_ONE_GAIN,     /**< Warning when one of KH's eigenvalues is superior to 1*/
    RBA_SRVMT_CLOSE_TO_SINGULAR_R,          /**< Warning that R is close to singular */
    RBA_SRVMT_CLOSE_TO_SINGULAR_Q,          /**< Warning that Q is close to singular */
    RBA_SRVMT_CLOSE_TO_SINGULAR_P0,     /**< Warning that P0 is close to singular*/
    RBA_SRVMT_X_NORM_INCREASE,              /**< Warning when ||Ax||/||x|| > 1, could mean that A is unstable */
    RBA_SRVMT_OUTLIER_DETECTED              /**< Warning when an outlier has been detected */
} rba_SrvMT_kalman_diagnosis_ten;

/* the attributes of a matrix */
typedef struct rba_SrvMT_MatrixData_tst{
    rba_SrvMT_Size_u32  rows_u32;   /*number of rows_u32 */
    rba_SrvMT_Size_u32  cols_u32;   /*number of column */
    rba_SrvMT_matrix_kind_ten type; /* type of the matrix -> shifted 1 level above to have the basic summarized and used as interface; */
    rba_SrvMT_f32*  data_f32;   /* flexible array member not to reside at end of struct */
} rba_SrvMT_MatrixData_type_tst;

/* forward declaration of the vtable; */
struct rba_SrvMT_MatrixVTable_tst;

/* tracking the matrix-data and a vtable reference to rba_SrvMT_access the matrix-type-specific functions */
typedef struct rba_SrvMT_Matrix{
    struct rba_SrvMT_MatrixVTable_tst const *vtable; /* virtual pointer of matrix*/

    /* this we keep separate from the vtable as it is not overriden by the  */
    rba_SrvMT_Size_u32 (*rba_SrvMT_access)(rba_SrvMT_Size_u32 rows_u32, rba_SrvMT_Size_u32 cols_u32, rba_SrvMT_Size_u32 i_u32, rba_SrvMT_Size_u32 j_u32);

    /* we use the matrix_data type structure here to capture the matrix properties
    decision taken not to include all the members here but encapsulate them;
    */
    union
    {
        rba_SrvMT_MatrixData_type_tst matrix;
    }base;

    rba_SrvMT_boolean rba_SrvMT_transpose;

    rba_SrvMT_matrix_property_ten pd;   /* flagging positive definiteness */
    rba_SrvMT_matrix_property_ten inv; /* flagging singularity */
}rba_SrvMT_Matrix_type_tst;

typedef void (*rba_SrvMT_setAt_t)(rba_SrvMT_Matrix_type_tst const * const  m, rba_SrvMT_Size_u32 rows_u32, rba_SrvMT_Size_u32 cols_u32, rba_SrvMT_f32 value_f32, rba_SrvMT_Size_u32 i_u32, rba_SrvMT_Size_u32 j_u32);
typedef rba_SrvMT_f32 (*rba_SrvMT_getAt_t)(rba_SrvMT_Matrix_type_tst const * const  m, rba_SrvMT_Size_u32 rows_u32, rba_SrvMT_Size_u32 cols_u32, rba_SrvMT_Size_u32 i_u32, rba_SrvMT_Size_u32 j_u32);
typedef rba_SrvMT_Int_s32 (*rba_SrvMT_setAtSafe_t)(rba_SrvMT_Matrix_type_tst const * const  m, rba_SrvMT_f32 value_f32, rba_SrvMT_Size_u32 i_u32, rba_SrvMT_Size_u32 j_u32);
typedef rba_SrvMT_Int_s32 (*rba_SrvMT_getAtSafe_t)(rba_SrvMT_Matrix_type_tst const * const  m, rba_SrvMT_Size_u32 i_u32, rba_SrvMT_Size_u32 j_u32, const rba_SrvMT_f32* v_pf32);

typedef struct rba_SrvMT_MatrixVTable_tst
{
    rba_SrvMT_setAt_t rba_SrvMT_setAt;
    rba_SrvMT_getAt_t rba_SrvMT_getAt;
    rba_SrvMT_setAtSafe_t rba_SrvMT_setAtSafe;
    rba_SrvMT_getAtSafe_t rba_SrvMT_getAtSafe;
} rba_SrvMT_MatrixVTable_tst;

/* Square matrix */
typedef struct rba_SrvMT_Square_tst
{
    rba_SrvMT_Matrix_type_tst super;        /*inheriting all from matrix super class */
} rba_SrvMT_Square_type_tst;

/* Triangular matrix (for both upper and lower triangular matrices) */
typedef struct rba_SrvMT_Triangular_tst
{
  rba_SrvMT_Matrix_type_tst super;          /*inheriting all from matrix super class */
} rba_SrvMT_Triangular_type_tst;

/* Diagonal matrix */
typedef struct rba_SrvMT_Diagonal_tst
{
    rba_SrvMT_Matrix_type_tst super;        /*inheriting all from matrix super class */
} rba_SrvMT_Diagonal_type_tst;

/* Unit matrix */
typedef struct rba_SrvMT_Unit_tst
{
    rba_SrvMT_Matrix_type_tst super;        /*inheriting all from matrix super class */
} rba_SrvMT_Unit_type_tst;

/* Vector */
typedef struct rba_SrvMT_Vector_tst
{
    rba_SrvMT_Matrix_type_tst super;        /*inheriting all from matrix super class */
} rba_SrvMT_Vector_type_tst;

/* Rectangular matrix */
typedef struct rba_SrvMT_Rectangular_tst
{
    rba_SrvMT_Matrix_type_tst super;        /*inheriting all from matrix super class */
} rba_SrvMT_Rectangular_type_tst;

/* Symmetric matrix */
typedef struct rba_SrvMT_Symmetric_tst
{
    rba_SrvMT_Matrix_type_tst super;        /*inheriting all from matrix super class */
} rba_SrvMT_Symmetric_type_tst;

//! \struct rba_SrvMT_kalman_return_info_tst
/*! Structure used to return to both the status (i.e success, overflow,...) and the various diagnosis information which have occurred, after the run of the Kalman filter. Diagnosis is an array of counters, of size MT_KALMAN_DIAGNOSIS_TOTAL,
such that diagnosis["warning type"] indicates the number of times the warning "warning type"
(enum value from mt_kalman_diagnosis_t) has occurred throughout the preprocessing and iterations of the filter. */
typedef struct
{
    rba_SrvMT_kalman_status_ten status;
    rba_SrvMT_Size_u32 diagnosis[RBA_SRVMT_KALMAN_DIAGNOSIS_TOTAL];
} rba_SrvMT_kalman_return_info_tst;

#endif/* RBA_SRVMT_TYPES_H */


/*!
\ingroup PkgQPSolverConcepts
\cgalconcept

A model of `NonnegativeLinearProgram` describes a linear program of the form 

\f{eqnarray*}{
\mbox{(QP)}& \mbox{minimize} 
&\qpc^{T}\qpx+c_0 \\ 
&\mbox{subject to} & A\qpx\qprel \qpb, \\ 
& & \qpx \geq 0 
\f}

in \f$ n\f$ real variables \f$ \qpx=(x_0,\ldots,x_{n-1})\f$. 
Here, 

<UL> 
<LI>\f$ A\f$ is an \f$ m\times n\f$ matrix (the constraint matrix), 
<LI>\f$ \qpb\f$ is an \f$ m\f$-dimensional vector (the right-hand side), 
<LI>\f$ \qprel\f$ is an \f$ m\f$-dimensional vector of relations 
from \f$ \{\leq, =, \geq\}\f$, 
<LI>\f$ \qpc\f$ is an \f$ n\f$-dimensional vector (the linear objective 
function), and 
<LI>\f$ c_0\f$ is a constant. 
</UL> 

The description is given by appropriate <I>random-access</I> 
iterators over the program data, see below. The program therefore 
comes in <I>dense</I> representation which includes zero entries. 

\hasModel Quadratic_program<NT> 
\hasModel Quadratic_program_from_mps<NT> 
\hasModel Nonnegative_linear_program_from_iterators<A_it, B_it, R_it, FL_it, L_it, FU_it, U_it, D_it, C_it> 

Requirements 
-------------- 

The value types of all iterator types (nested iterator types, 
respectively, for `A_iterator`) must be convertible to some common 
`IntegralDomain` `ET`. 

The models 
\hasModel `CGAL::Quadratic_program<NT>` 
\hasModel `CGAL::Quadratic_program_from_mps<NT>` 
\hasModel `CGAL::Nonnegative_linear_program_from_iterators<A_it, B_it, R_it, C_it>` 

\sa `QuadraticProgram` 
\sa `LinearProgram` 
\sa `NonnegativeQuadraticProgram` 

*/

class NonnegativeLinearProgram {
public:

/// \name Types 
/// @{

/*! 
A random access iterator type to go 
columnwise over the constraint matrix \f$ A\f$. The value type 
is a random access iterator type for an individual column that 
goes over the entries in that column. 
*/ 
typedef Hidden_type A_iterator; 

/*! 
A random access iterator type to go over 
the entries of the right-hand side \f$ \qpb\f$. 
*/ 
typedef Hidden_type B_iterator; 

/*! 
A random access iterator type to go over the 
relations \f$ \qprel\f$. The value type of `R_iterator` is 
`CGAL::Comparison_result`. 
*/ 
typedef Hidden_type R_iterator; 

/*! 
A random access iterator type to go over the 
entries of the linear objective function vector \f$ c\f$. 
*/ 
typedef Hidden_type C_iterator; 

/// @} 

/// \name Operations 
/// @{

/*! 
returns the number \f$ n\f$ of variables (number 
of columns of \f$ A\f$) in `lp`. 
*/ 
int get_n() const; 

/*! 
returns the number \f$ m\f$ of constraints 
(number of rows of \f$ A\f$) in `lp`. 
*/ 
int get_m() const; 

/*! 
returns an iterator over the columns 
of \f$ A\f$. The corresponding past-the-end iterator is `get_a()+get_n()`. 
For \f$ j=0,\ldots,n-1\f$, \f$ \ccc{*(get_a()+j)}\f$ is a random access 
iterator for column \f$ j\f$. 
*/ 
A_iterator get_a() const; 

/*! 
returns an iterator over the entries 
of \f$ \qpb\f$. The corresponding past-the-end iterator is 
`get_b()+get_m()`. 
*/ 
B_iterator get_b() const; 

/*! 
returns an iterator over the entries 
of \f$ \qprel\f$. The corresponding past-the-end iterator is 
`get_r()+get_m()`. 
The value `CGAL::SMALLER` stands 
for \f$ \leq\f$, `CGAL::EQUAL` stands for \f$ =\f$, and `CGAL::LARGER` 
stands for \f$ \geq\f$. 
*/ 
R_iterator get_r() const; 

/*! 
returns an iterator over the entries 
of \f$ \qpc\f$. The corresponding past-the-end iterator is 
`get_c()+get_n()`. 
*/ 
C_iterator get_c() const; 

/*! 
returns the constant term \f$ c_0\f$ of the objective function. 
*/ 
std::iterator_traits<C_iterator>::value_type get_c0() const; 

/// @}

}; /* end NonnegativeLinearProgram */


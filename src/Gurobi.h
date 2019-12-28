// This file is part of EigenQP.
//
// EigenQP is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// EigenQP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with EigenQP.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

// includes
// Eigen
#include <Eigen/Core>
#include <Eigen/Sparse>

//Gurobi
#include <gurobi_c++.h>

// eigen-gurobi
#include "eigen_gurobi_api.h"

namespace Eigen
{

class GurobiCommon
{
public:
	enum class WarmStatus : int
	{
		DEFAULT = -1,
		PRIMAL = 0,
		DUAL = 1,
		NONE = 2
	};

public:
	EIGEN_GUROBI_API GurobiCommon();

	EIGEN_GUROBI_API int iter() const;
	EIGEN_GUROBI_API int fail() const;

	EIGEN_GUROBI_API const VectorXd& result() const;
	EIGEN_GUROBI_API const VectorXd& dual_eq() const;
	EIGEN_GUROBI_API const VectorXd& dual_ineq() const;

	EIGEN_GUROBI_API GurobiCommon::WarmStatus warmStart() const;
	EIGEN_GUROBI_API void warmStart(GurobiCommon::WarmStatus warmStatus);

	EIGEN_GUROBI_API void inform() const;
	EIGEN_GUROBI_API void displayOutput(bool doDisplay);

	EIGEN_GUROBI_API double feasibilityTolerance() const;
	EIGEN_GUROBI_API void feasibilityTolerance(double tol);

	EIGEN_GUROBI_API double optimalityTolerance() const;
	EIGEN_GUROBI_API void optimalityTolerance(double tol);

	EIGEN_GUROBI_API void problem(int nrvar, int nreq, int nrineq);

	EIGEN_GUROBI_API void setVariableType(int varIndex, char GRBType);

protected:
	MatrixXd Q_;
	VectorXd C_, Beq_, Bineq_, X_, Yeq_, Yineq_;
	int fail_, nrvar_, nreq_, nrineq_, iter_;

	GRBEnv env_;
	GRBModel model_;

	GRBVar* vars_;
	std::vector<GRBVar> lvars_, rvars_, eqvars_, ineqvars_;
	GRBConstr* eqconstr_;
	GRBConstr* ineqconstr_;
};


class GurobiDense : public GurobiCommon
{
public:
	EIGEN_GUROBI_API GurobiDense();
	EIGEN_GUROBI_API GurobiDense(int nrvar, int nreq, int nrineq);


	/**
	 Performs the following operations:
     - Removes existing variables and constraints from the model.
     - Clears variables.
     - Alocates matrices.
     - Creates variables (all continuous for the moment).
     - Creates constraints.

	 @param nrvar Number of variables.
	 @param nreq Number of equalities.
	 @param nrineq Number of inequalities.
	 */
	EIGEN_GUROBI_API void problem(int nrvar, int nreq, int nrineq);


	/**
     Solves a model with quadratic objective:
     \f[
     \underset{x}{\text{min}}\; x^TQx^T + c^Tx
     \f]
     Subject to equality constraints:
     \f[
     A_{\text{eq}} x = b_{\text{eq}}
     \f]
     And inequality constraints:
     \f[
     A_{\text{ineq}} x = b_{\text{ineeq}}
     \f]
     Variables \f$x\f$ can also be bounded such that:
     \f[
     x_{\text{l}} \leq x \leq x_{\text{u}}
     \f]

	 Performs the following operations:
     - Creates and sets a quadratic objective.
     - Sets lower and upper boundaries.
     - Updates constraints (equalities and inequalities).
     - Optimizes.

	 @param Q Dense matrix \f$Q\f$ with the quadratic coefficients.
	 @param C Linear part of the objective function, i.e. \f$c^T\f$
	 @param Aeq Equality matrix \f$A_{eq}\f$
	 @param Beq Right hand side of the equality equation \f$b_{eq}\f$
	 @param Aineq Inequality matrix \f$A_{ineq}\f$
	 @param Bineq Inequality vector \f$b_{ineq}\f$
	 @param XL Vector of lower boundaries of the variables \f$x_l\f$
	 @param XU Vector of upper boundaries of the variables \f$x_u\f$
	 @return True if solved successfully, False otherwise.
	 */
	EIGEN_GUROBI_API bool solve(const MatrixXd& Q, const VectorXd& C,
		const MatrixXd& Aeq, const VectorXd& Beq,
		const MatrixXd& Aineq, const VectorXd& Bineq,
		const VectorXd& XL, const VectorXd& XU);

private:
	void updateConstr(GRBConstr* constrs, const std::vector<GRBVar>& vars,
		const Eigen::MatrixXd& A, const Eigen::VectorXd& b, int len);

};


class GurobiSparse : public GurobiCommon
{
public:
	EIGEN_GUROBI_API GurobiSparse();
	EIGEN_GUROBI_API GurobiSparse(int nrvar, int nreq, int nrineq);

	EIGEN_GUROBI_API void problem(int nrvar, int nreq, int nrineq);

	EIGEN_GUROBI_API bool solve(const SparseMatrix<double>& Q, const SparseVector<double>& C,
		const SparseMatrix<double>& Aeq, const SparseVector<double>& Beq,
		const SparseMatrix<double>& Aineq, const SparseVector<double>& Bineq,
		const VectorXd& XL, const VectorXd& XU);

private:
	void updateConstr(GRBConstr* constrs, const std::vector<GRBVar>& vars,
		const Eigen::SparseMatrix<double>& A, const Eigen::SparseVector<double>& b, int len);
};

} // namespace Eigen

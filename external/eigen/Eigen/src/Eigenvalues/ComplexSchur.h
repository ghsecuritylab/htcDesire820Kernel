// Copyright (C) 2009 Claire Maurice
// Copyright (C) 2009 Gael Guennebaud <gael.guennebaud@inria.fr>
// Copyright (C) 2010 Jitse Niesen <jitse@maths.leeds.ac.uk>
// Public License v. 2.0. If a copy of the MPL was not distributed

#ifndef EIGEN_COMPLEX_SCHUR_H
#define EIGEN_COMPLEX_SCHUR_H

#include "./HessenbergDecomposition.h"

namespace Eigen { 

namespace internal {
template<typename MatrixType, bool IsComplex> struct complex_schur_reduce_to_hessenberg;
}

template<typename _MatrixType> class ComplexSchur
{
  public:
    typedef _MatrixType MatrixType;
    enum {
      RowsAtCompileTime = MatrixType::RowsAtCompileTime,
      ColsAtCompileTime = MatrixType::ColsAtCompileTime,
      Options = MatrixType::Options,
      MaxRowsAtCompileTime = MatrixType::MaxRowsAtCompileTime,
      MaxColsAtCompileTime = MatrixType::MaxColsAtCompileTime
    };

    
    typedef typename MatrixType::Scalar Scalar;
    typedef typename NumTraits<Scalar>::Real RealScalar;
    typedef typename MatrixType::Index Index;

    typedef std::complex<RealScalar> ComplexScalar;

    typedef Matrix<ComplexScalar, RowsAtCompileTime, ColsAtCompileTime, Options, MaxRowsAtCompileTime, MaxColsAtCompileTime> ComplexMatrixType;

    ComplexSchur(Index size = RowsAtCompileTime==Dynamic ? 1 : RowsAtCompileTime)
      : m_matT(size,size),
        m_matU(size,size),
        m_hess(size),
        m_isInitialized(false),
        m_matUisUptodate(false)
    {}

    ComplexSchur(const MatrixType& matrix, bool computeU = true)
            : m_matT(matrix.rows(),matrix.cols()),
              m_matU(matrix.rows(),matrix.cols()),
              m_hess(matrix.rows()),
              m_isInitialized(false),
              m_matUisUptodate(false)
    {
      compute(matrix, computeU);
    }

    const ComplexMatrixType& matrixU() const
    {
      eigen_assert(m_isInitialized && "ComplexSchur is not initialized.");
      eigen_assert(m_matUisUptodate && "The matrix U has not been computed during the ComplexSchur decomposition.");
      return m_matU;
    }

    const ComplexMatrixType& matrixT() const
    {
      eigen_assert(m_isInitialized && "ComplexSchur is not initialized.");
      return m_matT;
    }

    ComplexSchur& compute(const MatrixType& matrix, bool computeU = true);

    ComputationInfo info() const
    {
      eigen_assert(m_isInitialized && "RealSchur is not initialized.");
      return m_info;
    }

    static const int m_maxIterations = 30;

  protected:
    ComplexMatrixType m_matT, m_matU;
    HessenbergDecomposition<MatrixType> m_hess;
    ComputationInfo m_info;
    bool m_isInitialized;
    bool m_matUisUptodate;

  private:  
    bool subdiagonalEntryIsNeglegible(Index i);
    ComplexScalar computeShift(Index iu, Index iter);
    void reduceToTriangularForm(bool computeU);
    friend struct internal::complex_schur_reduce_to_hessenberg<MatrixType, NumTraits<Scalar>::IsComplex>;
};

template<typename MatrixType>
inline bool ComplexSchur<MatrixType>::subdiagonalEntryIsNeglegible(Index i)
{
  RealScalar d = internal::norm1(m_matT.coeff(i,i)) + internal::norm1(m_matT.coeff(i+1,i+1));
  RealScalar sd = internal::norm1(m_matT.coeff(i+1,i));
  if (internal::isMuchSmallerThan(sd, d, NumTraits<RealScalar>::epsilon()))
  {
    m_matT.coeffRef(i+1,i) = ComplexScalar(0);
    return true;
  }
  return false;
}


template<typename MatrixType>
typename ComplexSchur<MatrixType>::ComplexScalar ComplexSchur<MatrixType>::computeShift(Index iu, Index iter)
{
  if (iter == 10 || iter == 20) 
  {
    
    return internal::abs(internal::real(m_matT.coeff(iu,iu-1))) + internal::abs(internal::real(m_matT.coeff(iu-1,iu-2)));
  }

  
  
  Matrix<ComplexScalar,2,2> t = m_matT.template block<2,2>(iu-1,iu-1);
  RealScalar normt = t.cwiseAbs().sum();
  t /= normt;     

  ComplexScalar b = t.coeff(0,1) * t.coeff(1,0);
  ComplexScalar c = t.coeff(0,0) - t.coeff(1,1);
  ComplexScalar disc = sqrt(c*c + RealScalar(4)*b);
  ComplexScalar det = t.coeff(0,0) * t.coeff(1,1) - b;
  ComplexScalar trace = t.coeff(0,0) + t.coeff(1,1);
  ComplexScalar eival1 = (trace + disc) / RealScalar(2);
  ComplexScalar eival2 = (trace - disc) / RealScalar(2);

  if(internal::norm1(eival1) > internal::norm1(eival2))
    eival2 = det / eival1;
  else
    eival1 = det / eival2;

  
  if(internal::norm1(eival1-t.coeff(1,1)) < internal::norm1(eival2-t.coeff(1,1)))
    return normt * eival1;
  else
    return normt * eival2;
}


template<typename MatrixType>
ComplexSchur<MatrixType>& ComplexSchur<MatrixType>::compute(const MatrixType& matrix, bool computeU)
{
  m_matUisUptodate = false;
  eigen_assert(matrix.cols() == matrix.rows());

  if(matrix.cols() == 1)
  {
    m_matT = matrix.template cast<ComplexScalar>();
    if(computeU)  m_matU = ComplexMatrixType::Identity(1,1);
    m_info = Success;
    m_isInitialized = true;
    m_matUisUptodate = computeU;
    return *this;
  }

  internal::complex_schur_reduce_to_hessenberg<MatrixType, NumTraits<Scalar>::IsComplex>::run(*this, matrix, computeU);
  reduceToTriangularForm(computeU);
  return *this;
}

namespace internal {

template<typename MatrixType, bool IsComplex>
struct complex_schur_reduce_to_hessenberg
{
  
  static void run(ComplexSchur<MatrixType>& _this, const MatrixType& matrix, bool computeU)
  {
    _this.m_hess.compute(matrix);
    _this.m_matT = _this.m_hess.matrixH();
    if(computeU)  _this.m_matU = _this.m_hess.matrixQ();
  }
};

template<typename MatrixType>
struct complex_schur_reduce_to_hessenberg<MatrixType, false>
{
  static void run(ComplexSchur<MatrixType>& _this, const MatrixType& matrix, bool computeU)
  {
    typedef typename ComplexSchur<MatrixType>::ComplexScalar ComplexScalar;
    typedef typename ComplexSchur<MatrixType>::ComplexMatrixType ComplexMatrixType;

    
    _this.m_hess.compute(matrix);
    _this.m_matT = _this.m_hess.matrixH().template cast<ComplexScalar>();
    if(computeU)  
    {
      
      MatrixType Q = _this.m_hess.matrixQ(); 
      _this.m_matU = Q.template cast<ComplexScalar>();
    }
  }
};

} 

template<typename MatrixType>
void ComplexSchur<MatrixType>::reduceToTriangularForm(bool computeU)
{  
  
  
  
  
  Index iu = m_matT.cols() - 1;
  Index il;
  Index iter = 0; 

  while(true)
  {
    
    while(iu > 0)
    {
      if(!subdiagonalEntryIsNeglegible(iu-1)) break;
      iter = 0;
      --iu;
    }

    
    if(iu==0) break;

    
    iter++;
    if(iter > m_maxIterations * m_matT.cols()) break;

    
    il = iu-1;
    while(il > 0 && !subdiagonalEntryIsNeglegible(il-1))
    {
      --il;
    }


    ComplexScalar shift = computeShift(iu, iter);
    JacobiRotation<ComplexScalar> rot;
    rot.makeGivens(m_matT.coeff(il,il) - shift, m_matT.coeff(il+1,il));
    m_matT.rightCols(m_matT.cols()-il).applyOnTheLeft(il, il+1, rot.adjoint());
    m_matT.topRows((std::min)(il+2,iu)+1).applyOnTheRight(il, il+1, rot);
    if(computeU) m_matU.applyOnTheRight(il, il+1, rot);

    for(Index i=il+1 ; i<iu ; i++)
    {
      rot.makeGivens(m_matT.coeffRef(i,i-1), m_matT.coeffRef(i+1,i-1), &m_matT.coeffRef(i,i-1));
      m_matT.coeffRef(i+1,i-1) = ComplexScalar(0);
      m_matT.rightCols(m_matT.cols()-i).applyOnTheLeft(i, i+1, rot.adjoint());
      m_matT.topRows((std::min)(i+2,iu)+1).applyOnTheRight(i, i+1, rot);
      if(computeU) m_matU.applyOnTheRight(i, i+1, rot);
    }
  }

  if(iter <= m_maxIterations * m_matT.cols()) 
    m_info = Success;
  else
    m_info = NoConvergence;

  m_isInitialized = true;
  m_matUisUptodate = computeU;
}

} 

#endif 

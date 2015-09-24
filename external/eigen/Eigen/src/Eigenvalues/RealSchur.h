// Copyright (C) 2008 Gael Guennebaud <gael.guennebaud@inria.fr>
// Copyright (C) 2010 Jitse Niesen <jitse@maths.leeds.ac.uk>
// Public License v. 2.0. If a copy of the MPL was not distributed

#ifndef EIGEN_REAL_SCHUR_H
#define EIGEN_REAL_SCHUR_H

#include "./HessenbergDecomposition.h"

namespace Eigen { 

template<typename _MatrixType> class RealSchur
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
    typedef std::complex<typename NumTraits<Scalar>::Real> ComplexScalar;
    typedef typename MatrixType::Index Index;

    typedef Matrix<ComplexScalar, ColsAtCompileTime, 1, Options & ~RowMajor, MaxColsAtCompileTime, 1> EigenvalueType;
    typedef Matrix<Scalar, ColsAtCompileTime, 1, Options & ~RowMajor, MaxColsAtCompileTime, 1> ColumnVectorType;

    RealSchur(Index size = RowsAtCompileTime==Dynamic ? 1 : RowsAtCompileTime)
            : m_matT(size, size),
              m_matU(size, size),
              m_workspaceVector(size),
              m_hess(size),
              m_isInitialized(false),
              m_matUisUptodate(false)
    { }

    RealSchur(const MatrixType& matrix, bool computeU = true)
            : m_matT(matrix.rows(),matrix.cols()),
              m_matU(matrix.rows(),matrix.cols()),
              m_workspaceVector(matrix.rows()),
              m_hess(matrix.rows()),
              m_isInitialized(false),
              m_matUisUptodate(false)
    {
      compute(matrix, computeU);
    }

    const MatrixType& matrixU() const
    {
      eigen_assert(m_isInitialized && "RealSchur is not initialized.");
      eigen_assert(m_matUisUptodate && "The matrix U has not been computed during the RealSchur decomposition.");
      return m_matU;
    }

    const MatrixType& matrixT() const
    {
      eigen_assert(m_isInitialized && "RealSchur is not initialized.");
      return m_matT;
    }
  
    RealSchur& compute(const MatrixType& matrix, bool computeU = true);

    ComputationInfo info() const
    {
      eigen_assert(m_isInitialized && "RealSchur is not initialized.");
      return m_info;
    }

    static const int m_maxIterations = 40;

  private:
    
    MatrixType m_matT;
    MatrixType m_matU;
    ColumnVectorType m_workspaceVector;
    HessenbergDecomposition<MatrixType> m_hess;
    ComputationInfo m_info;
    bool m_isInitialized;
    bool m_matUisUptodate;

    typedef Matrix<Scalar,3,1> Vector3s;

    Scalar computeNormOfT();
    Index findSmallSubdiagEntry(Index iu, Scalar norm);
    void splitOffTwoRows(Index iu, bool computeU, Scalar exshift);
    void computeShift(Index iu, Index iter, Scalar& exshift, Vector3s& shiftInfo);
    void initFrancisQRStep(Index il, Index iu, const Vector3s& shiftInfo, Index& im, Vector3s& firstHouseholderVector);
    void performFrancisQRStep(Index il, Index im, Index iu, bool computeU, const Vector3s& firstHouseholderVector, Scalar* workspace);
};


template<typename MatrixType>
RealSchur<MatrixType>& RealSchur<MatrixType>::compute(const MatrixType& matrix, bool computeU)
{
  assert(matrix.cols() == matrix.rows());

  
  m_hess.compute(matrix);
  m_matT = m_hess.matrixH();
  if (computeU)
    m_matU = m_hess.matrixQ();

  
  m_workspaceVector.resize(m_matT.cols());
  Scalar* workspace = &m_workspaceVector.coeffRef(0);

  
  
  
  
  Index iu = m_matT.cols() - 1;
  Index iter = 0; 
  Scalar exshift(0); 
  Scalar norm = computeNormOfT();

  if(norm!=0)
  {
    while (iu >= 0)
    {
      Index il = findSmallSubdiagEntry(iu, norm);

      
      if (il == iu) 
      {
        m_matT.coeffRef(iu,iu) = m_matT.coeff(iu,iu) + exshift;
        if (iu > 0)
          m_matT.coeffRef(iu, iu-1) = Scalar(0);
        iu--;
        iter = 0;
      }
      else if (il == iu-1) 
      {
        splitOffTwoRows(iu, computeU, exshift);
        iu -= 2;
        iter = 0;
      }
      else 
      {
        
        Vector3s firstHouseholderVector(0,0,0), shiftInfo;
        computeShift(iu, iter, exshift, shiftInfo);
        iter = iter + 1;
        if (iter > m_maxIterations * m_matT.cols()) break;
        Index im;
        initFrancisQRStep(il, iu, shiftInfo, im, firstHouseholderVector);
        performFrancisQRStep(il, im, iu, computeU, firstHouseholderVector, workspace);
      }
    }
  }
  if(iter <= m_maxIterations * m_matT.cols()) 
    m_info = Success;
  else
    m_info = NoConvergence;

  m_isInitialized = true;
  m_matUisUptodate = computeU;
  return *this;
}

template<typename MatrixType>
inline typename MatrixType::Scalar RealSchur<MatrixType>::computeNormOfT()
{
  const Index size = m_matT.cols();
  
  
  
  Scalar norm(0);
  for (Index j = 0; j < size; ++j)
    norm += m_matT.row(j).segment((std::max)(j-1,Index(0)), size-(std::max)(j-1,Index(0))).cwiseAbs().sum();
  return norm;
}

template<typename MatrixType>
inline typename MatrixType::Index RealSchur<MatrixType>::findSmallSubdiagEntry(Index iu, Scalar norm)
{
  Index res = iu;
  while (res > 0)
  {
    Scalar s = internal::abs(m_matT.coeff(res-1,res-1)) + internal::abs(m_matT.coeff(res,res));
    if (s == 0.0)
      s = norm;
    if (internal::abs(m_matT.coeff(res,res-1)) < NumTraits<Scalar>::epsilon() * s)
      break;
    res--;
  }
  return res;
}

template<typename MatrixType>
inline void RealSchur<MatrixType>::splitOffTwoRows(Index iu, bool computeU, Scalar exshift)
{
  const Index size = m_matT.cols();

  
  
  Scalar p = Scalar(0.5) * (m_matT.coeff(iu-1,iu-1) - m_matT.coeff(iu,iu));
  Scalar q = p * p + m_matT.coeff(iu,iu-1) * m_matT.coeff(iu-1,iu);   
  m_matT.coeffRef(iu,iu) += exshift;
  m_matT.coeffRef(iu-1,iu-1) += exshift;

  if (q >= Scalar(0)) 
  {
    Scalar z = internal::sqrt(internal::abs(q));
    JacobiRotation<Scalar> rot;
    if (p >= Scalar(0))
      rot.makeGivens(p + z, m_matT.coeff(iu, iu-1));
    else
      rot.makeGivens(p - z, m_matT.coeff(iu, iu-1));

    m_matT.rightCols(size-iu+1).applyOnTheLeft(iu-1, iu, rot.adjoint());
    m_matT.topRows(iu+1).applyOnTheRight(iu-1, iu, rot);
    m_matT.coeffRef(iu, iu-1) = Scalar(0); 
    if (computeU)
      m_matU.applyOnTheRight(iu-1, iu, rot);
  }

  if (iu > 1) 
    m_matT.coeffRef(iu-1, iu-2) = Scalar(0);
}

template<typename MatrixType>
inline void RealSchur<MatrixType>::computeShift(Index iu, Index iter, Scalar& exshift, Vector3s& shiftInfo)
{
  shiftInfo.coeffRef(0) = m_matT.coeff(iu,iu);
  shiftInfo.coeffRef(1) = m_matT.coeff(iu-1,iu-1);
  shiftInfo.coeffRef(2) = m_matT.coeff(iu,iu-1) * m_matT.coeff(iu-1,iu);

  
  if (iter == 10)
  {
    exshift += shiftInfo.coeff(0);
    for (Index i = 0; i <= iu; ++i)
      m_matT.coeffRef(i,i) -= shiftInfo.coeff(0);
    Scalar s = internal::abs(m_matT.coeff(iu,iu-1)) + internal::abs(m_matT.coeff(iu-1,iu-2));
    shiftInfo.coeffRef(0) = Scalar(0.75) * s;
    shiftInfo.coeffRef(1) = Scalar(0.75) * s;
    shiftInfo.coeffRef(2) = Scalar(-0.4375) * s * s;
  }

  
  if (iter == 30)
  {
    Scalar s = (shiftInfo.coeff(1) - shiftInfo.coeff(0)) / Scalar(2.0);
    s = s * s + shiftInfo.coeff(2);
    if (s > Scalar(0))
    {
      s = internal::sqrt(s);
      if (shiftInfo.coeff(1) < shiftInfo.coeff(0))
        s = -s;
      s = s + (shiftInfo.coeff(1) - shiftInfo.coeff(0)) / Scalar(2.0);
      s = shiftInfo.coeff(0) - shiftInfo.coeff(2) / s;
      exshift += s;
      for (Index i = 0; i <= iu; ++i)
        m_matT.coeffRef(i,i) -= s;
      shiftInfo.setConstant(Scalar(0.964));
    }
  }
}

template<typename MatrixType>
inline void RealSchur<MatrixType>::initFrancisQRStep(Index il, Index iu, const Vector3s& shiftInfo, Index& im, Vector3s& firstHouseholderVector)
{
  Vector3s& v = firstHouseholderVector; 

  for (im = iu-2; im >= il; --im)
  {
    const Scalar Tmm = m_matT.coeff(im,im);
    const Scalar r = shiftInfo.coeff(0) - Tmm;
    const Scalar s = shiftInfo.coeff(1) - Tmm;
    v.coeffRef(0) = (r * s - shiftInfo.coeff(2)) / m_matT.coeff(im+1,im) + m_matT.coeff(im,im+1);
    v.coeffRef(1) = m_matT.coeff(im+1,im+1) - Tmm - r - s;
    v.coeffRef(2) = m_matT.coeff(im+2,im+1);
    if (im == il) {
      break;
    }
    const Scalar lhs = m_matT.coeff(im,im-1) * (internal::abs(v.coeff(1)) + internal::abs(v.coeff(2)));
    const Scalar rhs = v.coeff(0) * (internal::abs(m_matT.coeff(im-1,im-1)) + internal::abs(Tmm) + internal::abs(m_matT.coeff(im+1,im+1)));
    if (internal::abs(lhs) < NumTraits<Scalar>::epsilon() * rhs)
    {
      break;
    }
  }
}

template<typename MatrixType>
inline void RealSchur<MatrixType>::performFrancisQRStep(Index il, Index im, Index iu, bool computeU, const Vector3s& firstHouseholderVector, Scalar* workspace)
{
  assert(im >= il);
  assert(im <= iu-2);

  const Index size = m_matT.cols();

  for (Index k = im; k <= iu-2; ++k)
  {
    bool firstIteration = (k == im);

    Vector3s v;
    if (firstIteration)
      v = firstHouseholderVector;
    else
      v = m_matT.template block<3,1>(k,k-1);

    Scalar tau, beta;
    Matrix<Scalar, 2, 1> ess;
    v.makeHouseholder(ess, tau, beta);
    
    if (beta != Scalar(0)) 
    {
      if (firstIteration && k > il)
        m_matT.coeffRef(k,k-1) = -m_matT.coeff(k,k-1);
      else if (!firstIteration)
        m_matT.coeffRef(k,k-1) = beta;

      
      m_matT.block(k, k, 3, size-k).applyHouseholderOnTheLeft(ess, tau, workspace);
      m_matT.block(0, k, (std::min)(iu,k+3) + 1, 3).applyHouseholderOnTheRight(ess, tau, workspace);
      if (computeU)
        m_matU.block(0, k, size, 3).applyHouseholderOnTheRight(ess, tau, workspace);
    }
  }

  Matrix<Scalar, 2, 1> v = m_matT.template block<2,1>(iu-1, iu-2);
  Scalar tau, beta;
  Matrix<Scalar, 1, 1> ess;
  v.makeHouseholder(ess, tau, beta);

  if (beta != Scalar(0)) 
  {
    m_matT.coeffRef(iu-1, iu-2) = beta;
    m_matT.block(iu-1, iu-1, 2, size-iu+1).applyHouseholderOnTheLeft(ess, tau, workspace);
    m_matT.block(0, iu-1, iu+1, 2).applyHouseholderOnTheRight(ess, tau, workspace);
    if (computeU)
      m_matU.block(0, iu-1, size, 2).applyHouseholderOnTheRight(ess, tau, workspace);
  }

  
  for (Index i = im+2; i <= iu; ++i)
  {
    m_matT.coeffRef(i,i-2) = Scalar(0);
    if (i > im+2)
      m_matT.coeffRef(i,i-3) = Scalar(0);
  }
}

} 

#endif 

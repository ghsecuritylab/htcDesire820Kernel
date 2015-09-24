// Copyright (C) 2009 Benoit Jacob <jacob.benoit.1@gmail.com>
// Public License v. 2.0. If a copy of the MPL was not distributed

#ifndef EIGEN_MISC_KERNEL_H
#define EIGEN_MISC_KERNEL_H

namespace Eigen { 

namespace internal {

template<typename DecompositionType>
struct traits<kernel_retval_base<DecompositionType> >
{
  typedef typename DecompositionType::MatrixType MatrixType;
  typedef Matrix<
    typename MatrixType::Scalar,
    MatrixType::ColsAtCompileTime, 
                                   
                                   
    Dynamic,                       
    MatrixType::Options,
    MatrixType::MaxColsAtCompileTime, 
    MatrixType::MaxColsAtCompileTime 
                                     
  > ReturnType;
};

template<typename _DecompositionType> struct kernel_retval_base
 : public ReturnByValue<kernel_retval_base<_DecompositionType> >
{
  typedef _DecompositionType DecompositionType;
  typedef ReturnByValue<kernel_retval_base> Base;
  typedef typename Base::Index Index;

  kernel_retval_base(const DecompositionType& dec)
    : m_dec(dec),
      m_rank(dec.rank()),
      m_cols(m_rank==dec.cols() ? 1 : dec.cols() - m_rank)
  {}

  inline Index rows() const { return m_dec.cols(); }
  inline Index cols() const { return m_cols; }
  inline Index rank() const { return m_rank; }
  inline const DecompositionType& dec() const { return m_dec; }

  template<typename Dest> inline void evalTo(Dest& dst) const
  {
    static_cast<const kernel_retval<DecompositionType>*>(this)->evalTo(dst);
  }

  protected:
    const DecompositionType& m_dec;
    Index m_rank, m_cols;
};

} 

#define EIGEN_MAKE_KERNEL_HELPERS(DecompositionType) \
  typedef typename DecompositionType::MatrixType MatrixType; \
  typedef typename MatrixType::Scalar Scalar; \
  typedef typename MatrixType::RealScalar RealScalar; \
  typedef typename MatrixType::Index Index; \
  typedef Eigen::internal::kernel_retval_base<DecompositionType> Base; \
  using Base::dec; \
  using Base::rank; \
  using Base::rows; \
  using Base::cols; \
  kernel_retval(const DecompositionType& dec) : Base(dec) {}

} 

#endif 

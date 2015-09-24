// Copyright (C) 2009-2010 Gael Guennebaud <gael.guennebaud@inria.fr>
// Public License v. 2.0. If a copy of the MPL was not distributed

#ifndef EIGEN_SELFCWISEBINARYOP_H
#define EIGEN_SELFCWISEBINARYOP_H

namespace Eigen { 


namespace internal {
template<typename BinaryOp, typename Lhs, typename Rhs>
struct traits<SelfCwiseBinaryOp<BinaryOp,Lhs,Rhs> >
  : traits<CwiseBinaryOp<BinaryOp,Lhs,Rhs> >
{
  enum {
    
    
    Flags = traits<CwiseBinaryOp<BinaryOp,Lhs,Rhs> >::Flags | (Lhs::Flags&DirectAccessBit) | (Lhs::Flags&LvalueBit),
    OuterStrideAtCompileTime = Lhs::OuterStrideAtCompileTime,
    InnerStrideAtCompileTime = Lhs::InnerStrideAtCompileTime
  };
};
}

template<typename BinaryOp, typename Lhs, typename Rhs> class SelfCwiseBinaryOp
  : public internal::dense_xpr_base< SelfCwiseBinaryOp<BinaryOp, Lhs, Rhs> >::type
{
  public:

    typedef typename internal::dense_xpr_base<SelfCwiseBinaryOp>::type Base;
    EIGEN_DENSE_PUBLIC_INTERFACE(SelfCwiseBinaryOp)

    typedef typename internal::packet_traits<Scalar>::type Packet;

    inline SelfCwiseBinaryOp(Lhs& xpr, const BinaryOp& func = BinaryOp()) : m_matrix(xpr), m_functor(func) {}

    inline Index rows() const { return m_matrix.rows(); }
    inline Index cols() const { return m_matrix.cols(); }
    inline Index outerStride() const { return m_matrix.outerStride(); }
    inline Index innerStride() const { return m_matrix.innerStride(); }
    inline const Scalar* data() const { return m_matrix.data(); }

    
    
    inline Scalar& coeffRef(Index row, Index col)
    {
      EIGEN_STATIC_ASSERT_LVALUE(Lhs)
      return m_matrix.const_cast_derived().coeffRef(row, col);
    }
    inline const Scalar& coeffRef(Index row, Index col) const
    {
      return m_matrix.coeffRef(row, col);
    }

    
    
    inline Scalar& coeffRef(Index index)
    {
      EIGEN_STATIC_ASSERT_LVALUE(Lhs)
      return m_matrix.const_cast_derived().coeffRef(index);
    }
    inline const Scalar& coeffRef(Index index) const
    {
      return m_matrix.const_cast_derived().coeffRef(index);
    }

    template<typename OtherDerived>
    void copyCoeff(Index row, Index col, const DenseBase<OtherDerived>& other)
    {
      OtherDerived& _other = other.const_cast_derived();
      eigen_internal_assert(row >= 0 && row < rows()
                         && col >= 0 && col < cols());
      Scalar& tmp = m_matrix.coeffRef(row,col);
      tmp = m_functor(tmp, _other.coeff(row,col));
    }

    template<typename OtherDerived>
    void copyCoeff(Index index, const DenseBase<OtherDerived>& other)
    {
      OtherDerived& _other = other.const_cast_derived();
      eigen_internal_assert(index >= 0 && index < m_matrix.size());
      Scalar& tmp = m_matrix.coeffRef(index);
      tmp = m_functor(tmp, _other.coeff(index));
    }

    template<typename OtherDerived, int StoreMode, int LoadMode>
    void copyPacket(Index row, Index col, const DenseBase<OtherDerived>& other)
    {
      OtherDerived& _other = other.const_cast_derived();
      eigen_internal_assert(row >= 0 && row < rows()
                        && col >= 0 && col < cols());
      m_matrix.template writePacket<StoreMode>(row, col,
        m_functor.packetOp(m_matrix.template packet<StoreMode>(row, col),_other.template packet<LoadMode>(row, col)) );
    }

    template<typename OtherDerived, int StoreMode, int LoadMode>
    void copyPacket(Index index, const DenseBase<OtherDerived>& other)
    {
      OtherDerived& _other = other.const_cast_derived();
      eigen_internal_assert(index >= 0 && index < m_matrix.size());
      m_matrix.template writePacket<StoreMode>(index,
        m_functor.packetOp(m_matrix.template packet<StoreMode>(index),_other.template packet<LoadMode>(index)) );
    }

    
    
    template<typename RhsDerived>
    EIGEN_STRONG_INLINE SelfCwiseBinaryOp& lazyAssign(const DenseBase<RhsDerived>& rhs)
    {
      EIGEN_STATIC_ASSERT_SAME_MATRIX_SIZE(Lhs,RhsDerived)
      EIGEN_CHECK_BINARY_COMPATIBILIY(BinaryOp,typename Lhs::Scalar,typename RhsDerived::Scalar);
      
    #ifdef EIGEN_DEBUG_ASSIGN
      internal::assign_traits<SelfCwiseBinaryOp, RhsDerived>::debug();
    #endif
      eigen_assert(rows() == rhs.rows() && cols() == rhs.cols());
      internal::assign_impl<SelfCwiseBinaryOp, RhsDerived>::run(*this,rhs.derived());
    #ifndef EIGEN_NO_DEBUG
      this->checkTransposeAliasing(rhs.derived());
    #endif
      return *this;
    }
    
    
    
    
    SelfCwiseBinaryOp& operator=(const Rhs& _rhs)
    {
      typename internal::nested<Rhs>::type rhs(_rhs);
      return Base::operator=(rhs);
    }

    Lhs& expression() const 
    { 
      return m_matrix;
    }

    const BinaryOp& functor() const 
    { 
      return m_functor;
    }

  protected:
    Lhs& m_matrix;
    const BinaryOp& m_functor;

  private:
    SelfCwiseBinaryOp& operator=(const SelfCwiseBinaryOp&);
};

template<typename Derived>
inline Derived& DenseBase<Derived>::operator*=(const Scalar& other)
{
  typedef typename Derived::PlainObject PlainObject;
  SelfCwiseBinaryOp<internal::scalar_product_op<Scalar>, Derived, typename PlainObject::ConstantReturnType> tmp(derived());
  tmp = PlainObject::Constant(rows(),cols(),other);
  return derived();
}

template<typename Derived>
inline Derived& DenseBase<Derived>::operator/=(const Scalar& other)
{
  typedef typename internal::conditional<NumTraits<Scalar>::IsInteger,
                                        internal::scalar_quotient_op<Scalar>,
                                        internal::scalar_product_op<Scalar> >::type BinOp;
  typedef typename Derived::PlainObject PlainObject;
  SelfCwiseBinaryOp<BinOp, Derived, typename PlainObject::ConstantReturnType> tmp(derived());
  tmp = PlainObject::Constant(rows(),cols(), NumTraits<Scalar>::IsInteger ? other : Scalar(1)/other);
  return derived();
}

} 

#endif 

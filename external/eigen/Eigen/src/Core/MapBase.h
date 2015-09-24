// Copyright (C) 2007-2010 Benoit Jacob <jacob.benoit.1@gmail.com>
// Copyright (C) 2008 Gael Guennebaud <gael.guennebaud@inria.fr>
// Public License v. 2.0. If a copy of the MPL was not distributed

#ifndef EIGEN_MAPBASE_H
#define EIGEN_MAPBASE_H

#define EIGEN_STATIC_ASSERT_INDEX_BASED_ACCESS(Derived) \
      EIGEN_STATIC_ASSERT((int(internal::traits<Derived>::Flags) & LinearAccessBit) || Derived::IsVectorAtCompileTime, \
                          YOU_ARE_TRYING_TO_USE_AN_INDEX_BASED_ACCESSOR_ON_AN_EXPRESSION_THAT_DOES_NOT_SUPPORT_THAT)

namespace Eigen { 

template<typename Derived> class MapBase<Derived, ReadOnlyAccessors>
  : public internal::dense_xpr_base<Derived>::type
{
  public:

    typedef typename internal::dense_xpr_base<Derived>::type Base;
    enum {
      RowsAtCompileTime = internal::traits<Derived>::RowsAtCompileTime,
      ColsAtCompileTime = internal::traits<Derived>::ColsAtCompileTime,
      SizeAtCompileTime = Base::SizeAtCompileTime
    };

    typedef typename internal::traits<Derived>::StorageKind StorageKind;
    typedef typename internal::traits<Derived>::Index Index;
    typedef typename internal::traits<Derived>::Scalar Scalar;
    typedef typename internal::packet_traits<Scalar>::type PacketScalar;
    typedef typename NumTraits<Scalar>::Real RealScalar;
    typedef typename internal::conditional<
                         bool(internal::is_lvalue<Derived>::value),
                         Scalar *,
                         const Scalar *>::type
                     PointerType;

    using Base::derived;
    using Base::MaxRowsAtCompileTime;
    using Base::MaxColsAtCompileTime;
    using Base::MaxSizeAtCompileTime;
    using Base::IsVectorAtCompileTime;
    using Base::Flags;
    using Base::IsRowMajor;

    using Base::rows;
    using Base::cols;
    using Base::size;
    using Base::coeff;
    using Base::coeffRef;
    using Base::lazyAssign;
    using Base::eval;

    using Base::innerStride;
    using Base::outerStride;
    using Base::rowStride;
    using Base::colStride;

    
    using Base::operator=;

    typedef typename Base::CoeffReturnType CoeffReturnType;

    inline Index rows() const { return m_rows.value(); }
    inline Index cols() const { return m_cols.value(); }

    inline const Scalar* data() const { return m_data; }

    inline const Scalar& coeff(Index row, Index col) const
    {
      return m_data[col * colStride() + row * rowStride()];
    }

    inline const Scalar& coeff(Index index) const
    {
      EIGEN_STATIC_ASSERT_INDEX_BASED_ACCESS(Derived)
      return m_data[index * innerStride()];
    }

    inline const Scalar& coeffRef(Index row, Index col) const
    {
      return this->m_data[col * colStride() + row * rowStride()];
    }

    inline const Scalar& coeffRef(Index index) const
    {
      EIGEN_STATIC_ASSERT_INDEX_BASED_ACCESS(Derived)
      return this->m_data[index * innerStride()];
    }

    template<int LoadMode>
    inline PacketScalar packet(Index row, Index col) const
    {
      return internal::ploadt<PacketScalar, LoadMode>
               (m_data + (col * colStride() + row * rowStride()));
    }

    template<int LoadMode>
    inline PacketScalar packet(Index index) const
    {
      EIGEN_STATIC_ASSERT_INDEX_BASED_ACCESS(Derived)
      return internal::ploadt<PacketScalar, LoadMode>(m_data + index * innerStride());
    }

    inline MapBase(PointerType data) : m_data(data), m_rows(RowsAtCompileTime), m_cols(ColsAtCompileTime)
    {
      EIGEN_STATIC_ASSERT_FIXED_SIZE(Derived)
      checkSanity();
    }

    inline MapBase(PointerType data, Index size)
            : m_data(data),
              m_rows(RowsAtCompileTime == Dynamic ? size : Index(RowsAtCompileTime)),
              m_cols(ColsAtCompileTime == Dynamic ? size : Index(ColsAtCompileTime))
    {
      EIGEN_STATIC_ASSERT_VECTOR_ONLY(Derived)
      eigen_assert(size >= 0);
      eigen_assert(data == 0 || SizeAtCompileTime == Dynamic || SizeAtCompileTime == size);
      checkSanity();
    }

    inline MapBase(PointerType data, Index rows, Index cols)
            : m_data(data), m_rows(rows), m_cols(cols)
    {
      eigen_assert( (data == 0)
              || (   rows >= 0 && (RowsAtCompileTime == Dynamic || RowsAtCompileTime == rows)
                  && cols >= 0 && (ColsAtCompileTime == Dynamic || ColsAtCompileTime == cols)));
      checkSanity();
    }

  protected:

    void checkSanity() const
    {
      EIGEN_STATIC_ASSERT(EIGEN_IMPLIES(internal::traits<Derived>::Flags&PacketAccessBit,
                                        internal::inner_stride_at_compile_time<Derived>::ret==1),
                          PACKET_ACCESS_REQUIRES_TO_HAVE_INNER_STRIDE_FIXED_TO_1);
      eigen_assert(EIGEN_IMPLIES(internal::traits<Derived>::Flags&AlignedBit, (size_t(m_data) % 16) == 0)
                   && "data is not aligned");
    }

    PointerType m_data;
    const internal::variable_if_dynamic<Index, RowsAtCompileTime> m_rows;
    const internal::variable_if_dynamic<Index, ColsAtCompileTime> m_cols;
};

template<typename Derived> class MapBase<Derived, WriteAccessors>
  : public MapBase<Derived, ReadOnlyAccessors>
{
  public:

    typedef MapBase<Derived, ReadOnlyAccessors> Base;

    typedef typename Base::Scalar Scalar;
    typedef typename Base::PacketScalar PacketScalar;
    typedef typename Base::Index Index;
    typedef typename Base::PointerType PointerType;

    using Base::derived;
    using Base::rows;
    using Base::cols;
    using Base::size;
    using Base::coeff;
    using Base::coeffRef;

    using Base::innerStride;
    using Base::outerStride;
    using Base::rowStride;
    using Base::colStride;

    typedef typename internal::conditional<
                    internal::is_lvalue<Derived>::value,
                    Scalar,
                    const Scalar
                  >::type ScalarWithConstIfNotLvalue;

    inline const Scalar* data() const { return this->m_data; }
    inline ScalarWithConstIfNotLvalue* data() { return this->m_data; } 

    inline ScalarWithConstIfNotLvalue& coeffRef(Index row, Index col)
    {
      return this->m_data[col * colStride() + row * rowStride()];
    }

    inline ScalarWithConstIfNotLvalue& coeffRef(Index index)
    {
      EIGEN_STATIC_ASSERT_INDEX_BASED_ACCESS(Derived)
      return this->m_data[index * innerStride()];
    }

    template<int StoreMode>
    inline void writePacket(Index row, Index col, const PacketScalar& x)
    {
      internal::pstoret<Scalar, PacketScalar, StoreMode>
               (this->m_data + (col * colStride() + row * rowStride()), x);
    }

    template<int StoreMode>
    inline void writePacket(Index index, const PacketScalar& x)
    {
      EIGEN_STATIC_ASSERT_INDEX_BASED_ACCESS(Derived)
      internal::pstoret<Scalar, PacketScalar, StoreMode>
                (this->m_data + index * innerStride(), x);
    }

    explicit inline MapBase(PointerType data) : Base(data) {}
    inline MapBase(PointerType data, Index size) : Base(data, size) {}
    inline MapBase(PointerType data, Index rows, Index cols) : Base(data, rows, cols) {}

    Derived& operator=(const MapBase& other)
    {
      Base::Base::operator=(other);
      return derived();
    }

    using Base::Base::operator=;
};

} 

#endif 

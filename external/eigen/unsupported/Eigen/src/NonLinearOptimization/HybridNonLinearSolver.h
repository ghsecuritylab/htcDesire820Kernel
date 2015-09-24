
// Copyright (C) 2009 Thomas Capricelli <orzel@freehackers.org>
// Public License v. 2.0. If a copy of the MPL was not distributed

#ifndef EIGEN_HYBRIDNONLINEARSOLVER_H
#define EIGEN_HYBRIDNONLINEARSOLVER_H

namespace Eigen { 

namespace HybridNonLinearSolverSpace { 
    enum Status {
        Running = -1,
        ImproperInputParameters = 0,
        RelativeErrorTooSmall = 1,
        TooManyFunctionEvaluation = 2,
        TolTooSmall = 3,
        NotMakingProgressJacobian = 4,
        NotMakingProgressIterations = 5,
        UserAsked = 6
    };
}

template<typename FunctorType, typename Scalar=double>
class HybridNonLinearSolver
{
public:
    typedef DenseIndex Index;

    HybridNonLinearSolver(FunctorType &_functor)
        : functor(_functor) { nfev=njev=iter = 0;  fnorm= 0.; useExternalScaling=false;}

    struct Parameters {
        Parameters()
            : factor(Scalar(100.))
            , maxfev(1000)
            , xtol(internal::sqrt(NumTraits<Scalar>::epsilon()))
            , nb_of_subdiagonals(-1)
            , nb_of_superdiagonals(-1)
            , epsfcn(Scalar(0.)) {}
        Scalar factor;
        Index maxfev;   
        Scalar xtol;
        Index nb_of_subdiagonals;
        Index nb_of_superdiagonals;
        Scalar epsfcn;
    };
    typedef Matrix< Scalar, Dynamic, 1 > FVectorType;
    typedef Matrix< Scalar, Dynamic, Dynamic > JacobianType;
    
    typedef Matrix< Scalar, Dynamic, Dynamic > UpperTriangularType;

    HybridNonLinearSolverSpace::Status hybrj1(
            FVectorType  &x,
            const Scalar tol = internal::sqrt(NumTraits<Scalar>::epsilon())
            );

    HybridNonLinearSolverSpace::Status solveInit(FVectorType  &x);
    HybridNonLinearSolverSpace::Status solveOneStep(FVectorType  &x);
    HybridNonLinearSolverSpace::Status solve(FVectorType  &x);

    HybridNonLinearSolverSpace::Status hybrd1(
            FVectorType  &x,
            const Scalar tol = internal::sqrt(NumTraits<Scalar>::epsilon())
            );

    HybridNonLinearSolverSpace::Status solveNumericalDiffInit(FVectorType  &x);
    HybridNonLinearSolverSpace::Status solveNumericalDiffOneStep(FVectorType  &x);
    HybridNonLinearSolverSpace::Status solveNumericalDiff(FVectorType  &x);

    void resetParameters(void) { parameters = Parameters(); }
    Parameters parameters;
    FVectorType  fvec, qtf, diag;
    JacobianType fjac;
    UpperTriangularType R;
    Index nfev;
    Index njev;
    Index iter;
    Scalar fnorm;
    bool useExternalScaling; 
private:
    FunctorType &functor;
    Index n;
    Scalar sum;
    bool sing;
    Scalar temp;
    Scalar delta;
    bool jeval;
    Index ncsuc;
    Scalar ratio;
    Scalar pnorm, xnorm, fnorm1;
    Index nslow1, nslow2;
    Index ncfail;
    Scalar actred, prered;
    FVectorType wa1, wa2, wa3, wa4;

    HybridNonLinearSolver& operator=(const HybridNonLinearSolver&);
};



template<typename FunctorType, typename Scalar>
HybridNonLinearSolverSpace::Status
HybridNonLinearSolver<FunctorType,Scalar>::hybrj1(
        FVectorType  &x,
        const Scalar tol
        )
{
    n = x.size();

    
    if (n <= 0 || tol < 0.)
        return HybridNonLinearSolverSpace::ImproperInputParameters;

    resetParameters();
    parameters.maxfev = 100*(n+1);
    parameters.xtol = tol;
    diag.setConstant(n, 1.);
    useExternalScaling = true;
    return solve(x);
}

template<typename FunctorType, typename Scalar>
HybridNonLinearSolverSpace::Status
HybridNonLinearSolver<FunctorType,Scalar>::solveInit(FVectorType  &x)
{
    n = x.size();

    wa1.resize(n); wa2.resize(n); wa3.resize(n); wa4.resize(n);
    fvec.resize(n);
    qtf.resize(n);
    fjac.resize(n, n);
    if (!useExternalScaling)
        diag.resize(n);
    assert( (!useExternalScaling || diag.size()==n) || "When useExternalScaling is set, the caller must provide a valid 'diag'");

    
    nfev = 0;
    njev = 0;

    
    if (n <= 0 || parameters.xtol < 0. || parameters.maxfev <= 0 || parameters.factor <= 0. )
        return HybridNonLinearSolverSpace::ImproperInputParameters;
    if (useExternalScaling)
        for (Index j = 0; j < n; ++j)
            if (diag[j] <= 0.)
                return HybridNonLinearSolverSpace::ImproperInputParameters;

    
    
    nfev = 1;
    if ( functor(x, fvec) < 0)
        return HybridNonLinearSolverSpace::UserAsked;
    fnorm = fvec.stableNorm();

    
    iter = 1;
    ncsuc = 0;
    ncfail = 0;
    nslow1 = 0;
    nslow2 = 0;

    return HybridNonLinearSolverSpace::Running;
}

template<typename FunctorType, typename Scalar>
HybridNonLinearSolverSpace::Status
HybridNonLinearSolver<FunctorType,Scalar>::solveOneStep(FVectorType  &x)
{
    assert(x.size()==n); 

    Index j;
    std::vector<JacobiRotation<Scalar> > v_givens(n), w_givens(n);

    jeval = true;

    
    if ( functor.df(x, fjac) < 0)
        return HybridNonLinearSolverSpace::UserAsked;
    ++njev;

    wa2 = fjac.colwise().blueNorm();

    
    
    if (iter == 1) {
        if (!useExternalScaling)
            for (j = 0; j < n; ++j)
                diag[j] = (wa2[j]==0.) ? 1. : wa2[j];

        
        
        xnorm = diag.cwiseProduct(x).stableNorm();
        delta = parameters.factor * xnorm;
        if (delta == 0.)
            delta = parameters.factor;
    }

    
    HouseholderQR<JacobianType> qrfac(fjac); 

    
    R = qrfac.matrixQR();

    
    fjac = qrfac.householderQ();

    
    qtf = fjac.transpose() * fvec;

    
    if (!useExternalScaling)
        diag = diag.cwiseMax(wa2);

    while (true) {
        
        internal::dogleg<Scalar>(R, diag, qtf, delta, wa1);

        
        wa1 = -wa1;
        wa2 = x + wa1;
        pnorm = diag.cwiseProduct(wa1).stableNorm();

        
        if (iter == 1)
            delta = (std::min)(delta,pnorm);

        
        if ( functor(wa2, wa4) < 0)
            return HybridNonLinearSolverSpace::UserAsked;
        ++nfev;
        fnorm1 = wa4.stableNorm();

        
        actred = -1.;
        if (fnorm1 < fnorm) 
            actred = 1. - internal::abs2(fnorm1 / fnorm);

        
        wa3 = R.template triangularView<Upper>()*wa1 + qtf;
        temp = wa3.stableNorm();
        prered = 0.;
        if (temp < fnorm) 
            prered = 1. - internal::abs2(temp / fnorm);

        
        ratio = 0.;
        if (prered > 0.)
            ratio = actred / prered;

        
        if (ratio < Scalar(.1)) {
            ncsuc = 0;
            ++ncfail;
            delta = Scalar(.5) * delta;
        } else {
            ncfail = 0;
            ++ncsuc;
            if (ratio >= Scalar(.5) || ncsuc > 1)
                delta = (std::max)(delta, pnorm / Scalar(.5));
            if (internal::abs(ratio - 1.) <= Scalar(.1)) {
                delta = pnorm / Scalar(.5);
            }
        }

        
        if (ratio >= Scalar(1e-4)) {
            
            x = wa2;
            wa2 = diag.cwiseProduct(x);
            fvec = wa4;
            xnorm = wa2.stableNorm();
            fnorm = fnorm1;
            ++iter;
        }

        
        ++nslow1;
        if (actred >= Scalar(.001))
            nslow1 = 0;
        if (jeval)
            ++nslow2;
        if (actred >= Scalar(.1))
            nslow2 = 0;

        
        if (delta <= parameters.xtol * xnorm || fnorm == 0.)
            return HybridNonLinearSolverSpace::RelativeErrorTooSmall;

        
        if (nfev >= parameters.maxfev)
            return HybridNonLinearSolverSpace::TooManyFunctionEvaluation;
        if (Scalar(.1) * (std::max)(Scalar(.1) * delta, pnorm) <= NumTraits<Scalar>::epsilon() * xnorm)
            return HybridNonLinearSolverSpace::TolTooSmall;
        if (nslow2 == 5)
            return HybridNonLinearSolverSpace::NotMakingProgressJacobian;
        if (nslow1 == 10)
            return HybridNonLinearSolverSpace::NotMakingProgressIterations;

        
        if (ncfail == 2)
            break; 

        
        
        wa1 = diag.cwiseProduct( diag.cwiseProduct(wa1)/pnorm );
        wa2 = fjac.transpose() * wa4;
        if (ratio >= Scalar(1e-4))
            qtf = wa2;
        wa2 = (wa2-wa3)/pnorm;

        
        internal::r1updt<Scalar>(R, wa1, v_givens, w_givens, wa2, wa3, &sing);
        internal::r1mpyq<Scalar>(n, n, fjac.data(), v_givens, w_givens);
        internal::r1mpyq<Scalar>(1, n, qtf.data(), v_givens, w_givens);

        jeval = false;
    }
    return HybridNonLinearSolverSpace::Running;
}

template<typename FunctorType, typename Scalar>
HybridNonLinearSolverSpace::Status
HybridNonLinearSolver<FunctorType,Scalar>::solve(FVectorType  &x)
{
    HybridNonLinearSolverSpace::Status status = solveInit(x);
    if (status==HybridNonLinearSolverSpace::ImproperInputParameters)
        return status;
    while (status==HybridNonLinearSolverSpace::Running)
        status = solveOneStep(x);
    return status;
}



template<typename FunctorType, typename Scalar>
HybridNonLinearSolverSpace::Status
HybridNonLinearSolver<FunctorType,Scalar>::hybrd1(
        FVectorType  &x,
        const Scalar tol
        )
{
    n = x.size();

    
    if (n <= 0 || tol < 0.)
        return HybridNonLinearSolverSpace::ImproperInputParameters;

    resetParameters();
    parameters.maxfev = 200*(n+1);
    parameters.xtol = tol;

    diag.setConstant(n, 1.);
    useExternalScaling = true;
    return solveNumericalDiff(x);
}

template<typename FunctorType, typename Scalar>
HybridNonLinearSolverSpace::Status
HybridNonLinearSolver<FunctorType,Scalar>::solveNumericalDiffInit(FVectorType  &x)
{
    n = x.size();

    if (parameters.nb_of_subdiagonals<0) parameters.nb_of_subdiagonals= n-1;
    if (parameters.nb_of_superdiagonals<0) parameters.nb_of_superdiagonals= n-1;

    wa1.resize(n); wa2.resize(n); wa3.resize(n); wa4.resize(n);
    qtf.resize(n);
    fjac.resize(n, n);
    fvec.resize(n);
    if (!useExternalScaling)
        diag.resize(n);
    assert( (!useExternalScaling || diag.size()==n) || "When useExternalScaling is set, the caller must provide a valid 'diag'");

    
    nfev = 0;
    njev = 0;

    
    if (n <= 0 || parameters.xtol < 0. || parameters.maxfev <= 0 || parameters.nb_of_subdiagonals< 0 || parameters.nb_of_superdiagonals< 0 || parameters.factor <= 0. )
        return HybridNonLinearSolverSpace::ImproperInputParameters;
    if (useExternalScaling)
        for (Index j = 0; j < n; ++j)
            if (diag[j] <= 0.)
                return HybridNonLinearSolverSpace::ImproperInputParameters;

    
    
    nfev = 1;
    if ( functor(x, fvec) < 0)
        return HybridNonLinearSolverSpace::UserAsked;
    fnorm = fvec.stableNorm();

    
    iter = 1;
    ncsuc = 0;
    ncfail = 0;
    nslow1 = 0;
    nslow2 = 0;

    return HybridNonLinearSolverSpace::Running;
}

template<typename FunctorType, typename Scalar>
HybridNonLinearSolverSpace::Status
HybridNonLinearSolver<FunctorType,Scalar>::solveNumericalDiffOneStep(FVectorType  &x)
{
    assert(x.size()==n); 

    Index j;
    std::vector<JacobiRotation<Scalar> > v_givens(n), w_givens(n);

    jeval = true;
    if (parameters.nb_of_subdiagonals<0) parameters.nb_of_subdiagonals= n-1;
    if (parameters.nb_of_superdiagonals<0) parameters.nb_of_superdiagonals= n-1;

    
    if (internal::fdjac1(functor, x, fvec, fjac, parameters.nb_of_subdiagonals, parameters.nb_of_superdiagonals, parameters.epsfcn) <0)
        return HybridNonLinearSolverSpace::UserAsked;
    nfev += (std::min)(parameters.nb_of_subdiagonals+parameters.nb_of_superdiagonals+ 1, n);

    wa2 = fjac.colwise().blueNorm();

    
    
    if (iter == 1) {
        if (!useExternalScaling)
            for (j = 0; j < n; ++j)
                diag[j] = (wa2[j]==0.) ? 1. : wa2[j];

        
        
        xnorm = diag.cwiseProduct(x).stableNorm();
        delta = parameters.factor * xnorm;
        if (delta == 0.)
            delta = parameters.factor;
    }

    
    HouseholderQR<JacobianType> qrfac(fjac); 

    
    R = qrfac.matrixQR();

    
    fjac = qrfac.householderQ();

    
    qtf = fjac.transpose() * fvec;

    
    if (!useExternalScaling)
        diag = diag.cwiseMax(wa2);

    while (true) {
        
        internal::dogleg<Scalar>(R, diag, qtf, delta, wa1);

        
        wa1 = -wa1;
        wa2 = x + wa1;
        pnorm = diag.cwiseProduct(wa1).stableNorm();

        
        if (iter == 1)
            delta = (std::min)(delta,pnorm);

        
        if ( functor(wa2, wa4) < 0)
            return HybridNonLinearSolverSpace::UserAsked;
        ++nfev;
        fnorm1 = wa4.stableNorm();

        
        actred = -1.;
        if (fnorm1 < fnorm) 
            actred = 1. - internal::abs2(fnorm1 / fnorm);

        
        wa3 = R.template triangularView<Upper>()*wa1 + qtf;
        temp = wa3.stableNorm();
        prered = 0.;
        if (temp < fnorm) 
            prered = 1. - internal::abs2(temp / fnorm);

        
        ratio = 0.;
        if (prered > 0.)
            ratio = actred / prered;

        
        if (ratio < Scalar(.1)) {
            ncsuc = 0;
            ++ncfail;
            delta = Scalar(.5) * delta;
        } else {
            ncfail = 0;
            ++ncsuc;
            if (ratio >= Scalar(.5) || ncsuc > 1)
                delta = (std::max)(delta, pnorm / Scalar(.5));
            if (internal::abs(ratio - 1.) <= Scalar(.1)) {
                delta = pnorm / Scalar(.5);
            }
        }

        
        if (ratio >= Scalar(1e-4)) {
            
            x = wa2;
            wa2 = diag.cwiseProduct(x);
            fvec = wa4;
            xnorm = wa2.stableNorm();
            fnorm = fnorm1;
            ++iter;
        }

        
        ++nslow1;
        if (actred >= Scalar(.001))
            nslow1 = 0;
        if (jeval)
            ++nslow2;
        if (actred >= Scalar(.1))
            nslow2 = 0;

        
        if (delta <= parameters.xtol * xnorm || fnorm == 0.)
            return HybridNonLinearSolverSpace::RelativeErrorTooSmall;

        
        if (nfev >= parameters.maxfev)
            return HybridNonLinearSolverSpace::TooManyFunctionEvaluation;
        if (Scalar(.1) * (std::max)(Scalar(.1) * delta, pnorm) <= NumTraits<Scalar>::epsilon() * xnorm)
            return HybridNonLinearSolverSpace::TolTooSmall;
        if (nslow2 == 5)
            return HybridNonLinearSolverSpace::NotMakingProgressJacobian;
        if (nslow1 == 10)
            return HybridNonLinearSolverSpace::NotMakingProgressIterations;

        
        if (ncfail == 2)
            break; 

        
        
        wa1 = diag.cwiseProduct( diag.cwiseProduct(wa1)/pnorm );
        wa2 = fjac.transpose() * wa4;
        if (ratio >= Scalar(1e-4))
            qtf = wa2;
        wa2 = (wa2-wa3)/pnorm;

        
        internal::r1updt<Scalar>(R, wa1, v_givens, w_givens, wa2, wa3, &sing);
        internal::r1mpyq<Scalar>(n, n, fjac.data(), v_givens, w_givens);
        internal::r1mpyq<Scalar>(1, n, qtf.data(), v_givens, w_givens);

        jeval = false;
    }
    return HybridNonLinearSolverSpace::Running;
}

template<typename FunctorType, typename Scalar>
HybridNonLinearSolverSpace::Status
HybridNonLinearSolver<FunctorType,Scalar>::solveNumericalDiff(FVectorType  &x)
{
    HybridNonLinearSolverSpace::Status status = solveNumericalDiffInit(x);
    if (status==HybridNonLinearSolverSpace::ImproperInputParameters)
        return status;
    while (status==HybridNonLinearSolverSpace::Running)
        status = solveNumericalDiffOneStep(x);
    return status;
}

} 

#endif 


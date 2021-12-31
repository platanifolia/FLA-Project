#Q = {q0,I0,I1,J0,J1,J2,J3,J4,J5,J6,J7,J8,K0,K1,K2,K3,K4,halt_accept}
#S = {0,1}
#G = {0,1,X,Y,S,_}
#q0 = q0
#B = _
#N = 2
#F = {halt_accept}

;q0:start state
q0 1_ 1S *r I0
q0 0_ 0S *r I0

;step1
I0 1_ _1 rr I0
I0 0_ _0 rr I1
I1 1_ 11 rr I1
I1 __ __ ** J0

;step2 a mod b
J0 __ __ *l J1
J1 _1 _Y *l J2
J2 _1 _1 *l J2
J2 _0 _0 *l J3
J3 _0 _0 *l J3
J3 _X _X *l J3
J3 _1 _X *r J4
J4 _0 _0 *r J4
J4 _1 _1 *r J4
J4 _X _X *r J4
J4 _Y _Y *l J5
J5 _1 _1 ** J1
J5 _0 _0 *l J6
J6 _0 _0 *l J6
J6 _1 _1 *l J6
J6 _X _0 *l J6
J6 _Y _1 *l J6
J6 _S _S *r J7
J7 _0 _0 *r J7
J7 _1 _1 *r J7
J7 _X _0 *r J7
J7 _Y _1 *r J7
J7 __ __ ** J0
J3 _S _S *r J8
J3 __ __ *r J8
J8 _X _1 *r J8
J8 _0 __ *r J8
J8 _1 __ *r J8
J8 _Y __ *r J8
J8 __ __ ** K0

;step3 
K0 __ __ *l K0
K0 _S _S ** halt_accept
K0 _1 _1 *l K1
K1 _1 _1 *l K1
K1 _S _S ** K2
K2 _S 0_ rr K3
K3 _1 1_ rr K3
K3 __ __ l* K4
K4 1_ 1_ l* K4
K4 0_ 0_ l* K4
K4 __ __ r* q0
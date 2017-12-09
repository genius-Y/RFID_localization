function [xi_post,P_post,xk,yk, thk] = EKF(dt,m,xi,i,P_post_prev,sig)
%% Prediction

d=0.24; %dt=0.1;
x=xi(1); y=xi(2); dx=xi(3); dy=xi(4); ddx=xi(5); ddy=xi(6); phi=xi(7); dphi=xi(8);
th=phi+0.5*dphi*dt;
vl=i(2); vr=i(1);
xi_prio = ...
            [ x + dx*dt + ddx*dt^2/2
              y + dy*dt + ddy*dt^2/2
             (vl+vr)/2*cos(th)+ddx*dt
             (vl+vr)/2*sin(th)+ddy*dt
             ddx
             ddy
             phi + dphi*dt
             (vr-vl)/d               ];

A = ...
        [ 1, 0, dt,  0, dt^2/2,      0,                      0,                             0
          0, 1,  0, dt,      0, dt^2/2,                      0,                             0
          0, 0,  0,  0,     dt,      0, -sin(th)*(vl/2 + vr/2), -(dt*sin(th)*(vl/2 + vr/2))/2
          0, 0,  0,  0,      0,     dt,  cos(th)*(vl/2 + vr/2),  (dt*cos(th)*(vl/2 + vr/2))/2
          0, 0,  0,  0,      1,      0,                      0,                             0
          0, 0,  0,  0,      0,      1,                      0,                             0
          0, 0,  0,  0,      0,      0,                      1,                             dt
          0, 0,  0,  0,      0,      0,                      0,                             0];

V= ...
    [         0,         0
              0,         0
      cos(th)/2, cos(th)/2
      sin(th)/2, sin(th)/2
              0,         0
              0,         0
              0,         0
           -1/d,       1/d];
sigx=sig(1);sigy=sig(2);sigdx=sig(3);sigdy=sig(4);sigddx=sig(5);sigddy=sig(6);sigphi=sig(7);
sigdphi=sig(8);sigvl=sig(9);sigvr=sig(9);

Q = diag([sigx,sigy,sigdx,sigdy,sigddx,sigddy,sigphi,sigdphi]);
M=diag([sigvl,sigvr]);
P_prio = A*P_post_prev*A'+Q + V*M*V';

%% Update
zhat = [1    0   0   0   0           0           0   0
        0    1   0   0   0           0           0   0
        0    0   0   0   cos(th)    sin(th)    0   0
        0    0   0   0   -sin(th)   cos(th)    0   0
        0    0   0   0   0           0           1   0
        0    0   0   0   0           0           0   1]*xi_prio;
C =  [1, 0, 0, 0,         0,        0,                             0, 0;
      0, 1, 0, 0,         0,        0,                             0, 0;
      0, 0, 0, 0,  cos(th), sin(th),   ddy*cos(th) - ddx*sin(th), 0;
      0, 0, 0, 0, -sin(th), cos(th), - ddx*cos(th) - ddy*sin(th), 0;
      0, 0, 0, 0,         0,        0,                             1, 0;
      0, 0, 0, 0,         0,        0,                             0, 1];
R = diag([0.79,0.30, 1.152e-05, 9.858e-05, 0.00000163, 3.6654e-06]);
K = P_prio*C'/(C*P_prio*C'+R);

m(1,3)=9.81*m(1,3); m(1,4)=9.81*m(1,4);
% Update states and covariance matrix
xi_post = xi_prio + K*(m-zhat);
P_post = (eye(size(P_prio,1))-K*C)*P_prio; %*(eye(size(P_prio,1))-K*C)'+K*R*K';
xk=xi_post(1); yk=xi_post(2); thk=xi_post(7);
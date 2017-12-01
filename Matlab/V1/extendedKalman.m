function [xhatout,Phatout] = extendedKalman(z,uhat,dt,initial)
%   Implements an extended Kalman filter used for object tracking.

%   The states of the process are given by
%   x = [x_pos y_pos x_vel y_vel x_acc y_acc phi omega]^T
%   x = [x y dx dx ddx ddy theta dtheta]^T
%   Measurements given by 
%   z = [x_uwb y_uwb a_long a_lat theta_mag dtheta_gyro]^T
persistent P
if isempty(P)
    %     Initiation
    %xhat = [0;0;0;0;0;0;0;0];
    %uhat = [0;0];
    
%     P = zeros(5,5);
%     R = diag(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
%     M = diag(10, 10);
%end
P=initial.P; M=initial.M; R= initial.R; xhat=initial.x0;
end
d=0.15;
x=xhat(1,1); y=xhat(2,1); dx=xhat(3,1); dy=xhat(4,1); ddx=xhat(5,1); ddy=xhat(6,1); phik=xhat(7,1); dphi=xhat(8,1);
vl=uhat(1,1); vr=uhat(2,1);
% Calculate the Jacobians for the state and measurement equations
phi=phik + 1/2*dphi*dt;

        
xhat= [x + dt*dx + (ddx*dt^2)/2 + (dt*vl*cos(phi))/2 + (dt*vr*cos(phi))/2
 y + dt*dy + (ddy*dt^2)/2 + (dt*vl*sin(phi))/2 + (dt*vr*sin(phi))/2
                    dx + ddx*dt + (vl*cos(phi))/2 + (vr*cos(phi))/2
                    dy + ddy*dt + (vl*sin(phi))/2 + (vr*sin(phi))/2
                                                                ddx
                                                                ddy
                              (d*phi - dt*vl + dt*vr + d*dphi*dt)/d
                                               (vr - vl + d*dphi)/d];

% Jacobians
F =     [ 1, 0, dt,  0, dt^2/2,      0, -(dt*sin(phi)*(vl + vr))/2,  0
          0, 1,  0, dt,      0, dt^2/2,  (dt*cos(phi)*(vl + vr))/2,  0
          0, 0,  1,  0,     dt,      0,    -(sin(phi)*(vl + vr))/2,  0
          0, 0,  0,  1,      0,     dt,     (cos(phi)*(vl + vr))/2,  0
          0, 0,  0,  0,      1,      0,                          0,  0
          0, 0,  0,  0,      0,      1,                          0,  0
          0, 0,  0,  0,      0,      0,                          1, dt
          0, 0,  0,  0,      0,      0,                          0,  1];
V =     [ (dt*cos(phi))/2, (dt*cos(phi))/2
          (dt*sin(phi))/2, (dt*sin(phi))/2
               cos(phi)/2,      cos(phi)/2
               sin(phi)/2,      sin(phi)/2
                        0,               0
                        0,               0
                    -dt/d,            dt/d
                     -1/d,             1/d];
                                           
% Covariance update
P = F*P*F.' + V*M*V.';


% Measurement model

%   z = [x_uwb, y_uwb, a_long, a_lat, theta_mag, dtheta_gyro]^T
zhat = [1    0   0   0   0           0           0   0
     0    1   0   0   0           0           0   0
     0    0   0   0   cos(phi)    sin(phi)    0   0
     0    0   0   0   -sin(phi)   cos(phi)    0   0
     0    0   0   0   0           0           1   0
     0    0   0   0   0           0           0   1]*xhat;
 
% More Linearization
H = [ 1, 0, 0, 0,         0,        0,                             0, 0
      0, 1, 0, 0,         0,        0,                             0, 0
      0, 0, 0, 0,  cos(phi), sin(phi),   ddy*cos(phi) - ddx*sin(phi), 0
      0, 0, 0, 0, -sin(phi), cos(phi), - ddx*cos(phi) - ddy*sin(phi), 0
      0, 0, 0, 0,         0,        0,                             1, 0
      0, 0, 0, 0,         0,        0,                             0, 1];
  
% Calculate gain
K=P*H.'/(H*P*H.'+R);

%update
xhatout=xhat+K*(z-zhat);
Phatout=(1-K*H)*P;
end


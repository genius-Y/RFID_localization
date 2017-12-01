%% v1
clear, close, clc
syms dt phik x y v b w a
phi = phik + 1/2*w*dt;
F = [1 0 0 dt*sind(phi) -(dt^2/2)*cosd(phi)
     0 1 0 dt*cosd(phi) -(dt^2/2)*sind(phi)
     0 0 1       0           0    
     0 0 0       1      -dt*cosd(phi)
     0 0 0       0           1             ];
pos= [x y phik v b].';
B = [(dt^2/2)*cosd(phi) 0
     (dt^2/2)*sind(phi) 0
            0           dt
            dt          0
            0           0];
in=[a w].';
f=F*pos+B*in;
jfx=jacobian(f,pos);
jfu=jacobian(f,in);

%% v2
close, clear, clc

syms x y dx dy ddx ddy phi dphi dt vl vr d
pos=[x, y, dx, dy, ddx, ddy, phi, dphi].';
u=[vl vr].';
F=[1    0   dt  0   0.5*dt^2    0           0   0
   0    1   0   dt  0           0.5*dt^2    0   0
   0    0   1   0   dt          0           0   0
   0    0   0   1   0           dt          0   0
   0    0   0   0   1           0           0   0
   0    0   0   0   0           1           0   0
   0    0   0   0   0           0           1   dt
   0    0   0   0   0           0           0   1];
B= [0.5*cos(phi)*dt     0.5*cos(phi)*dt
    0.5*sin(phi)*dt     0.5*sin(phi)*dt
    0.5*cos(phi)        0.5*cos(phi)
    0.5*sin(phi)        0.5*sin(phi)
    0                   0
    0                   0
    -dt/d               dt/d
    -1/d                1/d];
f=F*pos+B*u;
jfx=jacobian(f,pos);
jfu=jacobian(f,u);
H=[1    0   0   0   0           0           0   0
   0    1   0   0   0           0           0   0
   0    0   0   0   cos(phi)    sin(phi)    0   0
   0    0   0   0   -sin(phi)   cos(phi)    0   0
   0    0   0   0   0           0           1   0
   0    0   0   0   0           0           0   1];
h=H*pos;
jhx=jacobian(h,pos);

%% v2
close, clear, clc

syms x y dx dy ddx ddy phi dphi dt vl vr d
pos=[x, y, dx, dy, ddx, ddy, phi, dphi].';
u=[vl vr].';
f=[x + dx*dt + ddx*dt^2/2
 y + dy*dt + ddy*dt^2/2
 (vl+vr)/2*cos(phi+0.5*dphi*dt)+ddx*dt
 (vl+vr)/2*sin(phi+0.5*dphi*dt)+ddy*dt
 ddx
 ddy
 phi + dphi*dt
 (vr-vl)/d];
jfx=simplify(jacobian(f,pos))
jfu=simplify(jacobian(f,u))
H=[1    0   0   0   0           0           0   0
   0    1   0   0   0           0           0   0
   0    0   0   0   cos(phi)    sin(phi)    0   0
   0    0   0   0   -sin(phi)   cos(phi)    0   0
   0    0   0   0   0           0           1   0
   0    0   0   0   0           0           0   1];
h=H*pos;
jhx=jacobian(h,pos);
%% Parameter script
clear;
close all;

Ts = 1/400;             % Sample time filter[s]
T_xy = 1/10;
T_z = 1/25;
T_att = 1/200;
T_yaw = 1/100;
T_sens = [T_xy;T_xy;T_z;T_att*ones(2,1);T_yaw;T_att*ones(3,1)];

%% Equations
% Using symbolic toolbox to calculate linearized system
syms x y z u v w phi theta psi p q r T tauphi tautheta taupsi M Ixx Iyy Izz g

Rvb = [cos(psi)*cos(theta),                             cos(theta)*sin(psi),                            -sin(theta);
       cos(psi)*sin(phi)*sin(theta)-cos(phi)*sin(psi),  sin(phi)*sin(psi)*sin(theta)+cos(phi)*cos(psi), cos(theta)*sin(phi);
       cos(phi)*cos(psi)*sin(theta)+sin(phi)*sin(psi),  cos(phi)*sin(psi)*sin(theta)-cos(psi)*sin(phi), cos(phi)*cos(theta)];
Rbv = Rvb';
Rwphi = [1, sin(phi)*tan(theta), cos(phi)*tan(theta);
         0, cos(phi),            -sin(phi);
         0, sin(phi)/cos(theta), cos(phi)/cos(theta)];

vbdot = [0,-w,v;w,0,-u;-v,u,0]*[p;q;r]+Rvb*[0;0;g]+1/M*[0;0;-T];
phidot = Rwphi*[p;q;r];
omegabdot = diag([1/Ixx,1/Iyy,1/Izz])*([tauphi;tautheta;taupsi]+[0,r,-q;-r,0,p;q -p,0]*(diag([Ixx,Iyy,Izz])*[p;q;r]));
rhodot = Rbv*[u;v;w];

xidot = [rhodot;vbdot;phidot;omegabdot];
xi = [x;y;z;u;v;w;phi;theta;psi;p;q;r];
i = [tauphi,tautheta,taupsi,T];

Ac = jacobian(xidot,xi);
Bc = jacobian(xidot,i);

% Forward Euler method discretization
xiplus = xi+Ts*xidot;

Ad = jacobian(xiplus,xi);
Bd = jacobian(xiplus,i);

%% Constants
g  = 9.81;              % Gravitational acceleration    [ms^-2]

M  = 0.487;             % Mass of the drone             [kg]

Ixx = 2e-3;                 % Inertia around x-axis         [kg m^2]
Iyy = 1.6e-3;               % Inertia around y-axis         [kg m^2]
Izz = 5.9e-3;               % Inertia around z-axis         [kg m^2]
I = diag([Ixx;Iyy;Izz]);    % Inertia matrix                [kg m^2]

%% Create discrete system for EKF
Ad = subs(Ad);
Bd = subs(Bd);
C = [eye(3),zeros(3,9);zeros(3,6),eye(3),zeros(3,3);zeros(3,9),eye(3)];

xiplus = subs(xiplus);
f_xiplus = matlabFunction(xiplus);

%% Linearization point
x = 0;      y = 0;      z = 0;
u = 0;      v = 0;      w = 0;
phi = 0;    theta = 0;  psi = 0;
p = 0;      q = 0;      r = 0;

xi0 = [x;y;z;u;v;w;phi;theta;psi;p;q;r];

tauphi = 0; tautheta = 0;
taupsi = 0; T = M*g;

i0 = [tauphi;tautheta;taupsi;T];

%% Kalman filter system
Ac = double(subs(Ac));
Bc = double(subs(Bc));
fc = double(xi0-Ac*xi0-Bc*i0);

[A,B] = c2d(Ac,[Bc fc],Ts);
%% Noise parameters
nc = size(C,1);

mean_pos = zeros(3,1);
var_pos = ones(3,1)*0.00219628793119666;

mean_att = zeros(3,1);
var_att = [9.44454290406988e-06 1.41319492944844e-05 0.000590278082576831]';

mean_av = zeros(3,1);
var_av = [8.38442613623844e-07 9.65548247114005e-07 1.06378940883219e-06]';

var = [var_pos;var_att;var_av];

%% EKF parameters
% Q = diag([ones(1,6)*1e-6,ones(1,6)*1e-7]);
Q = diag([1e-5,1e-5,1e-5,1e-7,1e-7,1e-4,ones(1,2)*2e-7,6e-7,ones(1,3)*1e-7]);
R = diag(var);

%% Steady state KF
plant = ss(A,[B eye(12)],C,0,Ts);
[kest,L,P] = kalman(plant,Q,R);
kest = kest(10:21,:);
Ak = kest.A;
Bk = kest.B;
Ck = kest.C;
Dk = kest.D;

%%
% LQi = blkdiag(diag([.5 .5 2 .1 .1 .1 1 1 1 .5 .5 .5]),diag([.5 .5 1 .1 .1 .1 1 1 1 .5 .5 .5])*.5)*1;
% LQi = blkdiag(diag([.5 .5 2 .1 .1 .001 1 1 1 .5 .5 .5]),diag([.5 .5 1 .1 .1 .001 1 1 1 .5 .5 .5])*.53)*1; % No punishment on Zdot
% LRi = eye(4)*1;
% LNi = zeros(24,4);
% LQi = blkdiag(diag([.5 .5 1 .1 .1 .1 1 1 1 .5 .5 .5]),diag([.5 .5 1 .1 .1 .1 1 1 1 .5 .5 .5])*.4)*.4;
% LRi = eye(4)*1.2;
% 
dronePowerScaling = 1.2;
propDistance = 0.125;
yawTorqueC = 5;
K = [1 1/propDistance 1/propDistance -yawTorqueC; 1 -1/propDistance 1/propDistance yawTorqueC; 1 -1/propDistance -1/propDistance -yawTorqueC; 1 1/propDistance -1/propDistance yawTorqueC];
K_inv = inv(K);

%% Controller design

%% Roll
sys = ss(Ac,Bc,C,0);
transfers = tf(sys);
H_roll = tf(transfers.Numerator(4,1),transfers.Denominator(4,1));

target_bw = 6.5;%3.88;
tau = 1/(2*pi*target_bw);
w = logspace(-1,5,1000);

[mag, phase] = bode(H_roll,w);
mag = squeeze(mag);
[~, ind] = min(abs(target_bw*2*pi-w));

k = 1/mag(ind);

% [Q,w] = freqresp(H);
% s = tf('s');
% C = k + k*tau*s


P_roll = 1.5117%k*0.45 %-0.2
D_roll = 0.1522%k/(2*pi*target_bw)*1.8
I_roll = 0.15*0;

% P_roll = 1 %.2
% D_roll = .5*P_roll %1.2 %.5*P_roll

% s = tf('s');
% C_roll = P_roll + D_roll*s;
% 
% figure
% bode(C_roll*H_roll, {1e-1, 1e3})


%% Pitch
H_pitch = tf(transfers.Numerator(5,2),transfers.Denominator(5,2));

target_bw = 7.5;
tau = 1/(2*pi*target_bw);
w = logspace(-1,5,1000);

[mag, phase] = bode(H_pitch,w);
mag = squeeze(mag);
[~, ind] = min(abs(target_bw*2*pi-w));

k = 1/mag(ind);

% [Q,w] = freqresp(H);
% s = tf('s');
% C = k + k*tau*s

P_pitch = 1.9491%k*0.4%-0.3
D_pitch = .2256%k/(2*pi*target_bw)*3
% I_pitch = 0.15*0;

% P_pitch = 1
% D_pitch = .5*P_pitch %1.2 %.5*P_pitch
 
% s = tf('s');
% C_pitch = P_pitch + D_pitch*s;
% 
% figure
% bode(C_pitch*H_pitch, {1e-1, 1e3})

%% Yaw
H_yaw = tf(transfers.Numerator(6,3),transfers.Denominator(6,3));

target_bw = 1;
tau = 1/(2*pi*target_bw);
w = logspace(-1,5,1000);

[mag, phase] = bode(H_yaw,w);
mag = squeeze(mag);
[~, ind] = min(abs(target_bw*2*pi-w));

k = 1/mag(ind);

% [Q,w] = freqresp(H);
% s = tf('s');
% C = k + k*tau*s

P_yaw = .1152 %k*.5
D_yaw = .0367 %k/(2*pi*target_bw)
%% Z
H_height = tf(transfers.Numerator(3,4),transfers.Denominator(3,4));

target_bw = 0.2; %0.1;
tau = 1/(2*pi*target_bw);
w = logspace(-1,5,1000);

[mag, phase] = bode(H_height,w);
mag = squeeze(mag);
[~, ind] = min(abs(target_bw*2*pi-w));

k = 1/mag(ind);

% [Q,w] = freqresp(H);
% s = tf('s');
% C = k + k*tau*s

P_height = .3843%k*0.5
D_height = .6117%k/(2*pi*target_bw)
I_height = 0.15
% s = tf('s');
% C_height = P_height + D_height*s;
% 
% figure
% bode(C_height*H_height, {1e-1, 1e3})

%% x

P_x = .01*P_pitch
D_x = .8*P_x%.1*D_pitch
I_x = 0


%% y

P_y = .01*P_roll
D_y = .8*P_y %.1*D_roll
I_y = 0


%%
propDistance = 0.125;
yawTorqueC = 5;
K = [1 1/propDistance 1/propDistance -yawTorqueC; 1 -1/propDistance 1/propDistance yawTorqueC; 1 -1/propDistance -1/propDistance -yawTorqueC; 1 1/propDistance -1/propDistance yawTorqueC];
K_inv = inv(K);
dronePowerScaling = 1.189;

% clearvars -except xiplus Ad Ts T_sens M g I Ixx Iyy Izz xi0 i0 C Q R mean var seed A B ... 
%            K_inv P_phi D_phi P_height D_height P_roll D_roll P_pitch D_pitch P_yaw D_yaw

% save parameters
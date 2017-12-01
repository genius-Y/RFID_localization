% This script loads the parameters required by the QuarterCar.mdl
%
% Author: Phil Goddard (phil@goddardconsulting.ca)
% Date: Q2, 2011

% Do some housekeeping
clear all
close all
clc
disp('Loading parameters for QuarterCar.mdl');

% Physical parameters
g = 9.81; % gravity

% Controller parameters
Ts = 0.005;  % Sample rate of discrete controller
Kp = 1200;
Ki = 100000;
Kd = 0;
dPole = 1000;  % Pole of non-idealized derivative

% Vehicle parameters
Wr = 0.32;  % wheel radius 
J = 1;  % wheel moment 
v0 = 30; % initial velocity
m = 450; % 1/4 car mass
m0 = m; % Initial mass (used in the EKF mass estimation)

% Road surface parameters
% Pacejka model for dry asphelt
roadCoeffs = [1.28 23.99 0.52];

% Actuator parameters
actuatorPole = 70;
actuatorSat = 4000;
actuatorDelay = 0.005;

% Reference signal
lambda_ref = 0.1;


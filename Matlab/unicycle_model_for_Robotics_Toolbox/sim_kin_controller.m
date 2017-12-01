% This script simulates an unicycle-like mobile robot considering its 
% complete dynamic model.  
% Results are plotted after the simulation.
% ======================================================================
%
% Author: Felipe Nascimento Martins
% NOV/2015
% http://www.mathworks.com/matlabcentral/fileexchange/44850-velocity-based-dynamic-model-and-adaptive-controller-for-differential-steered-mobile-robot

% **********************************************************************
% **********************************************************************
% Modify Simulink blocks to connect [ud, wd] directly to [uref, wref].
% That is, bypass the dynamic compensation controller.
% **********************************************************************
% **********************************************************************

close all;
clear all;

Tsample=0.1;                    % Pioneer 3 sampling time = 100ms
tfinal=200;                     % total simulation time
inicia_adapt=100;                % start of parameter updating
%Controller_type = 0;            % 0 = Kinematic; 1 = Dynamic

kinematic_controller_system;
sim('kinematic_controller_system');
plot_results_kin;


% This script simulates an unicycle-like mobile robot considering its 
% kinematic model using Peter Corke's Robotics Toolbox.  
% Results are plotted after the simulation.
% To download and install the Robotics Toolbox, please visit:
% http://petercorke.com/Robotics_Toolbox.html
% ======================================================================
%
% Author: Felipe Nascimento Martins
% Federal Institute of Education, Science and Technology of Espirito Santo - IFES
% NERA - Núcleo de Estudos em Robótica e Automação
% http://nera.sr.ifes.edu.br
% MAY/2013
%
% Blog sobre robótica: www.nossosrobos.blogspot.com

sl_lanechange_unicycle;
sim('sl_lanechange_unicycle');
subplot(3,1,1);
plot(tout(:,1),yout(:,2));
grid;
ylabel('y');
subplot(3,1,2);
plot(tout(:,1),yout(:,3));
grid;
ylabel('\theta');
subplot(3,1,3);
plot(tout(:,1),yout(:,4));
grid;
ylabel('\gamma');
xlabel('Time (s)');

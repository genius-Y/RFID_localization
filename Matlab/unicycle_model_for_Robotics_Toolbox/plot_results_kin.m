% Plots the simulation results: distance error and trajectory.

% Calculation of distance error for plotting
erro_x = xd - x;
erro_y = yd - y;
erro_dist=sqrt(erro_x.*erro_x+erro_y.*erro_y);

% Cosidering simulation time = tfinal and updating starts at inicia_adapt:
t0=1/Tsample;
t01=43/Tsample;    % apenas para plotar referencia
t1=inicia_adapt/Tsample;    % instante inicial de adaptação
t2=(tfinal-inicia_adapt)/Tsample;    
t22=(tfinal-inicia_adapt+30)/Tsample;
t3=tfinal/Tsample;

figure(1)
plot(tout,erro_dist);
axis([0 tout(end) 0 0.8]);
grid
%legend('Error [m]');
title('Distance Error');
xlabel('time [s]');
ylabel('error [m]');
%createtextarrow(figure(1));

figure(2)
plot(xd(t0:t01),yd(t0:t01),'r--',x,y,'b-');
axis([-2 2 -2.5 0.5]);
legend('Reference','Actual');
title('Robot Path');
xlabel('x [m]');
ylabel('y [m]');
grid on

figure(3)
subplot(2,1,1)
plot(tout,u,'b-');
axis([0 tout(end) 0 0.6]);
grid
title('Linear Velocity');
xlabel('time [s]');
ylabel('u [m/s]');
grid on
subplot(2,1,2)
plot(tout,w,'b-');
axis([0 tout(end) -1.5 1.5]);
grid
title('Angular Velocity');
xlabel('time [s]');
ylabel('\omega [rad/s]');
grid on
%createtextarrow1(figure(3));

figure(4)
subplot(2,1,1)
plot(tout,xd,'r--',tout,x,'b-');
axis([0 tout(end) -1.5 1.5]);
title('Desired and actual positions on X and Y axes');
legend('x_d','x');
grid
xlabel('time [s]');
ylabel('x [m]');
grid on
subplot(2,1,2)
plot(tout,yd,'r--',tout,y,'b-');
axis([0 tout(end) -2.5 0.5]);
%title('Robot Position - Y-axis');
legend('y_d','y');
grid
xlabel('time [s]');
ylabel('y [m]');
grid on
%createtextarrow1(figure(4));

% iae_before = iae(t1)
% iae_after = iae(end) - iae_before
% iae_total = iae(end)
% iae_0_100 = iae(int16(end/2))

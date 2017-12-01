% run 
model_script_LQR_LQI
sim model_LQI_2016a
close all;
%% Figures
pt = 10;
sizeX = 12;
sizeY = 10;

% Plotting
figure(1);
subplot(3,1,1);
hold on;
plot(t,x(:,1));
plot(t,x(:,3));
plot(t,x(:,2));
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('x-position $x$ (m)','FontUnits','points','interpreter','latex','FontSize',pt);
axis([0 20 -.1 1.5]);
leg = legend('Sensor','Estimate','Real');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
hfig = gcf();
set(hfig,'Units','centimeters','NumberTitle','off');grid on;
pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
subplot(3,1,2);
hold on;
plot(t,y(:,1));
plot(t,y(:,3));
plot(t,y(:,2));
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('y-position $y$ (m)','FontUnits','points','interpreter','latex','FontSize',pt);grid;
axis([0 20 -.1 1.5]);
subplot(3,1,3);
hold on;
plot(t,z(:,1));
plot(t,z(:,3));
plot(t,z(:,2));
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('z-position $z$ (m)','FontUnits','points','interpreter','latex','FontSize',pt);grid;
axis([0 20 -1 0]);
hold off
box off
% print(hfig,'Figures/lqr_pos','-depsc')

figure(2);
subplot(3,1,1);
hold on;
plot(t,u(:,3));
plot(t,u(:,2));
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Body vel. $u$ (m/s)','FontUnits','points','interpreter','latex','FontSize',pt);
axis([0 20 -.1 .7]);
leg = legend('Estimate','Real');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
hfig = gcf();
set(hfig,'Units','centimeters','NumberTitle','off');grid on;
pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
subplot(3,1,2);
hold on;
plot(t,v(:,3));
plot(t,v(:,2));
axis([0 20 -.5 .6]);
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Body vel. $v$ (m/s)','FontUnits','points','interpreter','latex','FontSize',pt);grid;
subplot(3,1,3);
hold on;
plot(t,w(:,3));
plot(t,w(:,2));
axis([0 20 -.8 .2]);
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Body vel. $w$ (m/s)','FontUnits','points','interpreter','latex','FontSize',pt);grid;
hold off
box off
% print(hfig,'Figures/lqr_vel','-depsc')

figure(3);
subplot(3,1,1);
hold on;
plot(t,phi(:,1));
plot(t,phi(:,3));
plot(t,phi(:,2));
axis([0 20 -.05 .05]);
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Roll ang. $\phi$ (rad)','FontUnits','points','interpreter','latex','FontSize',pt);
% axis([0 10 -0.03 .03]);
leg = legend('Sensor','Estimate','Real');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
hfig = gcf();
set(hfig,'Units','centimeters','NumberTitle','off');grid on;
pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
subplot(3,1,2);
hold on;
plot(t,theta(:,1));
plot(t,theta(:,3));
plot(t,theta(:,2));
axis([0 20 -.05 .05]);
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Pitch ang. $\theta$ (rad)','FontUnits','points','interpreter','latex','FontSize',pt);grid;
subplot(3,1,3);
hold on;
plot(t,psi(:,1));
plot(t,psi(:,3));
plot(t,psi(:,2));
axis([0 20 -.1 .1]);
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Yaw ang. $\psi$ (rad)','FontUnits','points','interpreter','latex','FontSize',pt);grid;
hold off
box off
% print(hfig,'Figures/lqr_ang','-depsc')

figure(4);
subplot(3,1,1);
hold on;
plot(t,p(:,1));
plot(t,p(:,3));
plot(t,p(:,2));
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Ang. vel. $p$ (rad/s)','FontUnits','points','interpreter','latex','FontSize',pt);
axis([0 20 -.3 .23]);
leg = legend('Sensor','Estimate','Real');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
hfig = gcf();
set(hfig,'Units','centimeters','NumberTitle','off');grid on;
pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
subplot(3,1,2);
hold on;
plot(t,q(:,1));
plot(t,q(:,3));
plot(t,q(:,2));
axis([0 20 -.3 .3]);
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Ang. vel. $q$ (rad/s)','FontUnits','points','interpreter','latex','FontSize',pt);grid;
subplot(3,1,3);
hold on;
plot(t,r(:,1));
plot(t,r(:,3));
plot(t,r(:,2));
axis([0 20 -.03 .03]);
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Ang. vel. $r$ (rad/s)','FontUnits','points','interpreter','latex','FontSize',pt);grid;
hold off
box off
% print(hfig,'Figures/lqr_angv','-depsc')

sizeX = 20;
sizeY = 6;
figure(5);
subplot(1,3,1);
hold on;
plot(t,i(:,1));
plot(t,i(:,2));
plot(t,i(:,3));
axis([0 20 -.1 .1]);
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Torque $\tau$ (Nm)','FontUnits','points','interpreter','latex','FontSize',pt);
% axis([0 20 -.2 1]);
leg = legend('$\tau_{\phi}$','$\tau_{\theta}$','$\tau_{\psi}$');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
hfig = gcf();
set(hfig,'Units','centimeters','NumberTitle','off');grid on;
pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
subplot(1,3,2)
plot(t,i(:,4));grid;
axis([0 20 4 6]);
box off
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Trust $T$ (N)','FontUnits','points','interpreter','latex','FontSize',pt);
subplot(1,3,3);
hold on;
plot(t,pwm(:,1));
plot(t,pwm(:,2));
plot(t,pwm(:,3));
plot(t,pwm(:,4));
% axis([0 20 -1 .2]);
axis([0 20 0 100]);
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('PWM signal (0-100)','FontUnits','points','interpreter','latex','FontSize',pt);grid;
leg = legend('Motor 1','Motor 2','Motor 3','Motor 4');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
hold off
box off
% print(hfig,'Figures/lqr_angv','-depsc')
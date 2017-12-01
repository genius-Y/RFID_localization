run model_script
sim model_kf
close all;
%% Figures
pt = 10;
sizeX = 12/1.5;
sizeY = 10/1.5;

% Plotting
figure(1);
hold on;
plot(t,z(:,1));
plot(t,z(:,3));
plot(t,z(:,2));
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('z-position $z$ (m)','FontUnits','points','interpreter','latex','FontSize',pt);
axis([0 10 -1.1 0]);
leg = legend('Sensor','Estimate','Real');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
hfig = gcf();
set(hfig,'Units','centimeters','NumberTitle','off');grid on;
pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
hold off
box off
print(hfig,'Figures/kf_z','-depsc')

figure(2);
hold on;
plot(t,w(:,3));
plot(t,w(:,2));
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Body velocity z-direction $w$ (m/s)','FontUnits','points','interpreter','latex','FontSize',pt);
axis([0 10 -1.1 .2]);
leg = legend('Estimate','Real');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
hfig = gcf();
set(hfig,'Units','centimeters','NumberTitle','off');grid on;
pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
hold off
box off
print(hfig,'Figures/kf_w','-depsc')

figure(3);
hold on;
plot(t,phi(:,1));
plot(t,phi(:,3));
plot(t,phi(:,2));
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Roll angle $\phi$ (rad)','FontUnits','points','interpreter','latex','FontSize',pt);
axis([0 10 -0.03 .03]);
leg = legend('Sensor','Estimate','Real');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
hfig = gcf();
set(hfig,'Units','centimeters','NumberTitle','off');grid on;
pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
hold off
box off
print(hfig,'Figures/kf_phi','-depsc')

figure(4);
hold on;
plot(t,p(:,1));
plot(t,p(:,3));
plot(t,p(:,2));
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Ang. vel. roll axis $p$ (rad/s)','FontUnits','points','interpreter','latex','FontSize',pt);
axis([0 10 -0.05 0.05]);
leg = legend('Sensor','Estimate','Real');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
hfig = gcf();
set(hfig,'Units','centimeters','NumberTitle','off');grid on;
pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
hold off
box off
print(hfig,'Figures/kf_p','-depsc')
clear; close all;
%% Plot script
load logData_no_net

for i=1:numel(logData(26,:))
    if logData(26,i) ~= 0
        begin = i;
        break
    else
        continue
    end
end

for i=begin+101:numel(logData(26,:))
    if logData(26,i) == 0
        ending = i;
        break
    else
        continue
    end
end

[~, ending] = find(logData(34,:) > 5);
if isempty(ending)
    ending = numel(logData(26,:));
end
%% Figures
pt = 10;
sizeX = 12/1.5;
sizeY = 10/1.5;
figure(1);
subplot(2,1,1)
hold on;
% title('Height Z')
plot(logData(1,begin:ending),logData(2,begin:ending));
plot(logData(1,begin:ending),logData(9,begin:ending));
plot(logData(1,begin:ending),logData(22,begin:ending));
ylabel('z-position (cm)','FontUnits','points','interpreter','latex','FontSize',pt);
leg = legend('Raw z','Filter z','Ref z');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
hfig = gcf();
set(hfig,'Units','centimeters','NumberTitle','off');grid on;
pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
xlim([36.70 46.5])
box off
hold off
subplot(2,1,2)
plot(logData(1,begin:ending),logData(10,begin:ending));
grid
hold on
ylim([-20 50])
xlim([36.70 46.5])
ylabel('Body vel. $w$ (cm/s)','FontUnits','points','interpreter','latex','FontSize',pt);
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
box off
% plot(logData(1,begin:20:ending),gradient(logData(9,begin:20:ending)))
% leg = legend('$\dot{z}$');
% set(leg,'Location','best','Interpreter','latex','FontSize',pt);
% print(hfig,'Figures/Experiment_z','-depsc')

figure(2);
subplot(2,1,1)
hold on;
% title('Roll angle \phi')
plot(logData(1,begin:ending),logData(3,begin:ending));
plot(logData(1,begin:ending),logData(11,begin:ending));
ylabel('Roll ang. $\phi$ (deg)','FontUnits','points','interpreter','latex','FontSize',pt);
leg = legend('Raw $\phi$','Filter $\phi$','Init $\phi$');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
hfig = gcf();
set(hfig,'Units','centimeters','NumberTitle','off');grid on;
pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
xlim([36.70 46.5])
box off
hold off
subplot(2,1,2)
plot(logData(1,begin:ending),logData(4,begin:ending));
hold on
plot(logData(1,begin:ending),logData(12,begin:ending));
grid
ylabel('Ang. vel. $p$ (deg/s)','FontUnits','points','interpreter','latex','FontSize',pt);
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
box off
xlim([36.70 46.5])
% leg = legend('Raw $\dot{\phi}$','Filter $\dot{\phi}$');
% set(leg,'Location','best','Interpreter','latex','FontSize',pt);
% print(hfig,'Figures/Experiment_roll','-depsc')

figure(3);
subplot(2,1,1)
hold on;
% title('Pitch angle \theta')
plot(logData(1,begin:ending),logData(5,begin:ending));
plot(logData(1,begin:ending),logData(13,begin:ending));
ylabel('Pitch ang. $\theta$ (deg)','FontUnits','points','interpreter','latex','FontSize',pt);
leg = legend('Raw $\theta$','Filter $\theta$','Init $\theta$');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
hfig = gcf();
set(hfig,'Units','centimeters','NumberTitle','off');grid on;
pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
xlim([36.70 46.5])
box off
hold off
subplot(2,1,2)
plot(logData(1,begin:ending),logData(6,begin:ending));
hold on
plot(logData(1,begin:ending),logData(14,begin:ending));
grid
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Ang. vel. $q$ (deg/s)','FontUnits','points','interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
box off
xlim([36.70 46.5])
% leg = legend('Raw $\dot{\theta}$','Filter $\dot{\theta}$');
% set(leg,'Location','best','Interpreter','latex','FontSize',pt);
% print(hfig,'Figures/Experiment_pitch','-depsc')

figure(4);
subplot(2,1,1)
hold on;
% title('Yaw angle \psi')
plot(logData(1,begin:ending),logData(7,begin:ending));
plot(logData(1,begin:ending),logData(15,begin:ending));
ylabel('Yaw ang. $\psi$ (deg)','FontUnits','points','interpreter','latex','FontSize',pt);
leg = legend('Raw $\psi$','Filter $\psi$','Init $\psi$');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
hfig = gcf();
set(hfig,'Units','centimeters','NumberTitle','off');grid on;
pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
xlim([36.70 46.5])
ylim([0 500])
box off
hold off
subplot(2,1,2)
plot(logData(1,begin:ending),logData(8,begin:ending));
hold on
plot(logData(1,begin:ending),logData(16,begin:ending));
grid
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Ang. vel $r$ (deg/s)','FontUnits','points','interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
box off
xlim([36.70 46.5])
% leg = legend('Raw $\dot{\psi}$','Filter $\dot{\psi}$');
% set(leg,'Location','best','Interpreter','latex','FontSize',pt);
% print(hfig,'Figures/Experiment_yaw','-depsc')
% print(hfig,'Figures/5_1_RefXy','-depsc')

%%
figure(5);
hold on;
% title('Input')
plot(logData(1,begin:ending),logData(26,begin:ending));
% plot(logData(1,begin:ending),logData(27,begin:ending));
plot(logData(1,begin:ending),logData(27,begin:ending));
plot(logData(1,begin:ending),logData(28,begin:ending));
plot(logData(1,begin:ending),logData(29,begin:ending));
% plot(logData(1,begin:ending),logData(20,begin:ending));
% plot(logData(1,begin:ending),logData(19,begin:ending));
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Inputs','FontUnits','points','interpreter','latex','FontSize',pt);
leg = legend('Thrust $T$ (N)','Roll torque (Nm)', 'Pitch torque (Nm)', 'Yaw torque (Nm)','Real Thrust [N]', 'Real Roll torque [Nm]', 'Real Pitch torque [Nm]');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
hfig = gcf();
set(hfig,'Units','centimeters','NumberTitle','off');grid on;
pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
xlim([36.70 46.5])
box off
hold off
% print(hfig,'Figures/5_1_RefXy','-depsc')

figure(6);
hold on;
% title('Motor inputs')
plot(logData(1,begin:ending),logData(30,begin:ending));
plot(logData(1,begin:ending),logData(31,begin:ending));
plot(logData(1,begin:ending),logData(32,begin:ending));
plot(logData(1,begin:ending),logData(33,begin:ending));
xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
ylabel('Motor input [0-100]','FontUnits','points','interpreter','latex','FontSize',pt);
leg = legend('Motor 1','Motor 2','Motor 3','Motor 4');
set(leg,'Location','best','Interpreter','latex','FontSize',pt);
set(gca,'TickLabelInterpreter','latex')
hfig = gcf();
set(hfig,'Units','centimeters','NumberTitle','off');grid on;
pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
xlim([36.70 46.5])
box off
hold off
% print(hfig,'Figures/5_1_RefXy','-depsc')

% figure(7);
% hold on;
% title('Motor inputs')
% plot(logData(1,begin:ending),logData(17,begin:ending));
% plot(logData(1,begin:ending),logData(27,begin:ending)*100)
% xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
% ylabel('Motor input [0-100]','FontUnits','points','interpreter','latex','FontSize',pt);
% leg = legend('Motor 1','Motor 2','Motor 3','Motor 4');
% set(leg,'Location','best','Interpreter','latex','FontSize',pt);
% set(gca,'TickLabelInterpreter','latex')
% hfig = gcf();
% set(hfig,'Units','centimeters','NumberTitle','off');grid on;
% pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
% box off
% hold off
% % print(hfig,'Figures/5_1_RefXy','-depsc')


% figure(8);
% hold on;
% title('Motor inputs')
% plot(logData(1,begin:ending),logData(34,begin:ending));
% xlabel('Time $t$ (s)','FontUnits','points','interpreter','latex','FontSize',pt);
% ylabel('State','FontUnits','points','interpreter','latex','FontSize',pt);
% set(gca,'TickLabelInterpreter','latex')
% hfig = gcf();
% set(hfig,'Units','centimeters','NumberTitle','off');grid on;
% pos = get(hfig,'position');set(hfig,'position',[pos(1:2),sizeX,sizeY]);
% box off
% hold off
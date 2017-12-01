function [] = analyseEKFresults(x,y,theta,xout,Pout,timeout,x_uwb,y_uwb,theta_mag)
for i=1:length(timeout)
    sigx(i) = Pout(1,1,i);
    sigy(i) = Pout(2,2,i);
    sigdx(i) = Pout(3,3,i);
    sigdy(i) = Pout(4,4,i);
    sigddx(i) = Pout(5,5,i);
    sigddy(i) = Pout(6,6,i);
    sigth(i) = Pout(7,7,i);
    sigdth(i) = Pout(8,8,i);
end

%% Belief x
maxsigx=string(max(sigx(1,50:end)));
minsigx=string(min(sigx(1,50:end)));

subplot(2,3,1)
plot(timeout,sigx), hold on
plot([0,timeout(end)],[max(sigx(1,50:end)),max(sigx(1,50:end))])
plot([0,timeout(end)],[min(sigx(1,50:end)),min(sigx(1,50:end))])
axis fill
grid on
title('Belief in x')
legend('\sigma_x',strcat("Max = ",maxsigx),strcat("Min = ",minsigx),'Location','best')
xlabel('Time [s]')
ylabel('\sigma_x')
%% Belief y
maxsigy=string(max(sigy(1,50:end)));
minsigy=string(min(sigy(1,50:end)));

subplot(2,3,2)
plot(timeout,sigy), hold on
plot([0,timeout(end)],[max(sigy(1,50:end)),max(sigy(1,50:end))])
plot([0,timeout(end)],[min(sigy(1,50:end)),min(sigy(1,50:end))])
axis fill
grid on
title('Belief in y')
legend('\sigma_y',strcat("Max = ",maxsigy),strcat("Min = ",minsigy),'Location','best')
xlabel('Time [s]')
ylabel('\sigma_y')
%% Belief THETA
maxsigth=string(max(sigth(1,50:end)));
minsigth=string(min(sigth(1,50:end)));

subplot(2,3,3)
plot(timeout,sigth), hold on
plot([0,timeout(end)],[max(sigth(1,50:end)),max(sigth(1,50:end))])
plot([0,timeout(end)],[min(sigth(1,50:end)),min(sigth(1,50:end))])
axis fill
grid on
title('Belief in \theta')
legend('\sigma_\theta',strcat("Max = ",maxsigth),strcat("Min = ",minsigth),'Location','best')
xlabel('Time [s]')
ylabel('\sigma_\theta')

%%
subplot(2,3,4)
plot(timeout,x_uwb,'.',timeout,x,timeout,xout(:,1))
legend('x from UWB','Actual x','Observed x')
grid minor
subplot(2,3,5)
plot(timeout,y_uwb,'.',timeout,y,timeout,xout(:,2))
legend('y from UWB','Actual y','Observed y')
grid minor
subplot(2,3,6)
plot(timeout,theta_mag,'.',timeout,theta,timeout,xout(:,7))
legend('\theta from magnetometer','Actual \theta','Observed \theta')
grid minor
